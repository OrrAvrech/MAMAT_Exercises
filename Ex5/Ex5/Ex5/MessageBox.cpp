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

bool compareByTime(MySharedPtr<Conversation> r, MySharedPtr<Conversation> l)
{
	SysTime r_time = r->getTime;
	SysTime l_time = l->getTime;
	return r_time < l_time;
}

MessageBox::MessageBox(string username, list<MySharedPtr<Conversation>> ConversationList) :
	username_(username), ConversationList_(ConversationList) {}


void MessageBox::addConv(MySharedPtr<Conversation> convPtr)
{
	ConversationList_.push_back(convPtr);
	ConversationList_.sort(compareByTime);
}


void MessageBox::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	vector<string>::iterator itr, itr2;
	if (cmdLineTokens[0] == "New" && cmdLineTokens.size() > 1) // New
	{
		set<string> chatusers;
		// checking for duplicates and making the chatusers list
		for (itr = cmdLineTokens.begin() + 1; itr < cmdLineTokens.end(); itr++)
		{
			if (chatusers.insert(*itr).second == false)
			{
				cout << CONVERSATION_FAIL_USER_REPETITION;
				return;
			}
		}
		newConv newConv1(chatusers);
		throw newConv1;
	}
	else if (cmdLineTokens[0] == "Open" && cmdLineTokens.size() == 2) // Open
	{
		if (cmdLineTokens[1].find_first_not_of("123456789") != string::npos)
		{
			cout << INVALID_CONVERSATION_NUMBER ;
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
		list<MySharedPtr<Conversation>>::iterator list_itr;
		list_itr = ConversationList_.begin();
		advance(list_itr, convNum);
		list_itr->get()->removeUser(activeUsrName);
		ConversationList_.remove(*list_itr);
	}
	else if (cmdLineTokens[0] == "Search" && cmdLineTokens.size() == 2) // Search
	{
		string substr = cmdLineTokens[1];
		throw substr;
	}
	else if (cmdLineTokens[0] == "Back") // Back
	{
		string MessageBox_back = "MessageBox_back";
		throw MessageBox_back;
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
		if (itr->get()->IsRead(activeUsrName) == UNREAD)
			cout << "(UNREAD) ";
		cout << "Participants: ";
		itr->get()->DisplayParticipants();   
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