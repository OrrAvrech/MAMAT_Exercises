
#include "Defs.h"
#include "MessageBox.h"


#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

//helper function
int stringToInt(const string s) {
	istringstream istr(s);
	int i = 0;
	istr >> i;
	return i;
}



// exception handling


MessageBox::MessageBox(string username, list<Conversation> ConversationList) :
	username_( username) , ConversationList_(ConversationList) {}


 

//Interface




void MessageBox::VrtDo(string cmdLine, string activeUsrName)
{
	size_t idx;
	
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	vector<string>::iterator itr, itr2;
	if (cmdLineTokens[0] == "New" && cmdLineTokens.size() > 1) // New
	{
		vector<string> chatusers , userslist;
		for (itr = cmdLineTokens.begin() + 1; itr < cmdLineTokens.end(); itr++)
		{
			chatusers.end() + 1 = itr;
		}
		// checking duplication
		for (itr = chatusers.begin() + 1; itr < chatusers.end(); itr++)
		{
			for (itr2 = chatusers.begin() + 1; itr2 < itr; itr2++)
			{
				if (itr == itr2)
				{
					cout << CONVERSATION_FAIL_USER_REPETITION;
					return;
				}
			}
		}
		userslist = getUserList(); // TODO :  should be in CHATNET, removed for now because of errors
		//checking if all users exsist in the ChatNet
		bool find_flag = 0;
		for (itr = chatusers.begin() + 1; itr < chatusers.end(); itr++)
		{
			for (itr2 = userslist.begin() + 1; itr2 < userslist.end(); itr2++)
			{
				if (itr == itr2)
					find_flag = 1;
			}
			if (find_flag)
			{
				cout << CONVERSATION_FAIL_NO_USER;
				return;
			}
		}
		Conversation new_conversation();
		new_conversation->participants_ = chatusers;
		new_conversation->lastTime_ = chrono::system_clock::now();
		new_conversation->messageList_ = NULL;
		for (itr = chatusers.begin() + 1; itr < chatusers.end(); itr++)
		{
			new_conversation->readStateList_[itr] = READ;
		}
		MySharedPtr<Conversation> ptr1(*new_conversation);
		newConv newConv1(ptr1, chatusers);
		throw newConv1;
	}
	else if (cmdLineTokens[0] == "Open" && cmdLineTokens.size() == 2) // Open
	{
		if (cmdLineTokens[1].find_first_not_of("123456789") != string::npos)
		{
			cout << INVALID_CONVERSATION_NUMBER;
			return;
		}
		int convNum = stringToInt(cmdLineTokens[1]);
		if (convNum<1 || convNum > ConversationList_.size())
		{
			cout << INVALID_CONVERSATION_NUMBER;
			return;
		}
		list<Conversation>::iterator list_itr;
		list_itr = ConversationList_.begin();
		advance(list_itr, convNum);
		convOpen conv2open(*list_itr);
		throw conv2open;
	}
	else if (cmdLineTokens[0] == "Delete" && cmdLineTokens.size() == 2) // Delete
	{
		if (cmdLineTokens[1].find_first_not_of("123456789") != string::npos)
		{
			cout << INVALID_CONVERSATION_NUMBER;
			return;
		}
		int convNum = stringToInt(cmdLineTokens[1]);
		if (convNum<1 || convNum > ConversationList_.size())
		{
			cout << INVALID_CONVERSATION_NUMBER;
			return;
		}
		list<Conversation>::iterator list_itr;
		list_itr = ConversationList_.begin();
		advance(list_itr, convNum);
		list_itr->removeUser(activeUsrName); 
		ConversationList_.remove(*list_itr);
	}
	else if (cmdLineTokens[0] == "Search" && cmdLineTokens.size() == 2) // Search
	{
		/* TODO : 
		   throw exception and searching the main user list 
		   not sure if it possible from here without exception   */
	}
	else if (cmdLineTokens[0] == "Back") // Back
	{
		/* TODO :
		throw exception and go back in stack   */
	}
	else // INVALID_INPUT
		cout << INVALID_INPUT;
}


void MessageBox::VrtPreview(string activeUsrName)
{
	int count = 1;
	if (ConversationList_.size() == 0)
		cout << "No conversations" << endl;
	else
		cout << "Conversations:" << endl;
	list <Conversation>::iterator itr;
	for (itr = ConversationList_.begin() ; itr < ConversationList_.end() ; itr++)
	{
		cout << count << ") ";
		if ((itr)->readStateList_.find(activeUsrName) == UNREAD) // blocked because private and have no function to get this from
			cout << "(UNREAD) ";
		cout << "Participants: ";
		(itr)->DisplayParticipants();    // need to add to conversation? 
		++count;
	}
}


void MessageBox::Help() const
{
	cout << "New <user names separated by spaces>" << endl;
	cout << "Open <conversation number>" << endl;
	cout << "Delete <conversation number>" << endl;
	cout << "Search <partial user name>" << endl;
	cout << "Back" << endl;
}

