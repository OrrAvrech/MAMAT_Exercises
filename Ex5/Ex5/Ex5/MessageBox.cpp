#include "Defs.h"
#include "MessageBox.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Constructors
MessageBox::MessageBox() {}
MessageBox::MessageBox(string username) : username_(username) {}
MessageBox::MessageBox(string username, list<MySharedPtr<Conversation>> ConversationList) :
	username_(username), ConversationList_(ConversationList) {}


//helper function
int stringToInt(const string s) {
	istringstream istr(s);
	int i = 0;
	istr >> i;
	return i;
}

bool compareByTime(MySharedPtr<Conversation> r, MySharedPtr<Conversation> l)
{
	SysTime r_time = r->getTime();
	SysTime l_time = l->getTime();
	return r_time < l_time;
}

void MessageBox::addConv(MySharedPtr<Conversation> convPtr)
{
	ConversationList_.push_back(convPtr);
	ConversationList_.sort(compareByTime);
}

void MessageBox::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	if (cmdLineTokens[0] == "New" && cmdLineTokens.size() > 1) // New
	{
		set<string> conv_participants;
		// checking for duplicates and making the chatusers list
		for (auto itr = cmdLineTokens.begin() + 1; itr != cmdLineTokens.end(); ++itr)
		{
			if (conv_participants.insert(*itr).second == false)
			{
				// Element already exists
				cout << CONVERSATION_FAIL_USER_REPETITION << endl;
				return;
			}
		}
		throw newConv(conv_participants);
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
		list<MySharedPtr<Conversation>>::iterator list_itr;
		list_itr = ConversationList_.begin();
		if (ConversationList_.size() > convNum)
			advance(list_itr, convNum);
		throw convOpen((*list_itr).get()); // pass anonymous object to ChatNet catch
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

		list<MySharedPtr<Conversation>>::iterator list_itr_Del;
		list_itr_Del = ConversationList_.begin();
		if (ConversationList_.size() > convNum)
			advance(list_itr_Del, convNum);
		(*list_itr_Del)->removeUser(activeUsrName);
		ConversationList_.erase(list_itr_Del);
	}
	else if (cmdLineTokens[0] == "Search" && cmdLineTokens.size() == 2) // Search
	{
		string partName = cmdLineTokens[1];
		throw (MBsearch(partName));
	}
	else if (cmdLineTokens[0] == "Back") // Back
	{
		throw BackMessageBox();
	}
	else // INVALID_INPUT
		cout << INVALID_INPUT;
}


void MessageBox::Preview(string activeUsrName)
{
	int count = 1;
	if (ConversationList_.size() == 0)
		cout << "No conversations" << endl;
	else
		cout << "Conversations:" << endl;
	list<MySharedPtr<Conversation>>::iterator itr;
	for (itr = ConversationList_.begin(); itr != ConversationList_.end(); ++itr)
	{
		cout << count << ") ";
		if (!((*itr)->IsRead(activeUsrName)))
			cout << "(UNREAD) ";
		cout << "Participants: ";
		(*itr)->DisplayParticipants();   
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