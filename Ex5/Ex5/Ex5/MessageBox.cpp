#include <iostream>
#include "Defs.h"
#include "MessageBox.h"

using namespace std;

//helper function




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
					break;
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
				break;
			}
		}
		Conversation new_conversation();
		new_conversation->participants_ = 

	}
	else if (cmdLineTokens[0] == "Open" && cmdLineTokens.size() == 2) // Open
	{
		// add code here
	}
	else if (cmdLineTokens[0] == "Delete" && cmdLineTokens.size() == 2) // Delete
	{
		// add code here
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
	vector<Conversation>::iterator itr;
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

