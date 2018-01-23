
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
		// userslist = getUserList(); //  should be in CHATNET, removed for now because of errors
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
		MySharedPtr ptr1(*new_conversation);
		/* TO DO:
		   for each user in the chatusers: 
		   make a local copy of ptr1 in his
		   messagebox::ConversationList_.
		   need to sort the ConversationList_ 
		   after inserting new element        */
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
		/* TO DO: 
		   throw exception 
		   need to update stack to conversation 
		   and preview conversation 
		   is it done here or in the ChatNet?    */
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
		list_itr->removeUser(activeUsrName); / / TO DO : need to write this function. 
		ConversationList_.remove(*list_itr);
	}
	else if (cmdLineTokens[0] == "Search" && cmdLineTokens.size() == 2) // Search
	{
		// add code here
	}
	else if (cmdLineTokens[0] == "Back") // Back
	{
		// add code here
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

