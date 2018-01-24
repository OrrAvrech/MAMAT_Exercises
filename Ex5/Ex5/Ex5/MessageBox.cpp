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

//only for debugging
vector<string> getUserList()
{
	vector<string> str = { "dean", "marina", "eyal", "or", "ray", "chika", "zeus" };
	return str;
}

MessageBox::MessageBox(string username, list<Conversation> ConversationList) :
	username_(username), ConversationList_(ConversationList) {}


void MessageBox::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	vector<string>::iterator itr, itr2;
	if (cmdLineTokens[0] == "New" && cmdLineTokens.size() > 1) // New
	{
		vector<string>  userslist;
		set<string> chatusers;
		// checking for duplicates and making the chatusers list
		for (itr = cmdLineTokens.begin() + 1; itr < cmdLineTokens.end(); itr++)
		{
			if (chatusers.insert(*itr).second == false)
			{
				cout << CONVERSATION_FAIL_USER_REPETITION << endl;
				return;
			}
		}
		userslist = getUserList();
		//checking if all users exsist in the ChatNet
		bool find_flag;
		for (auto itr = chatusers.begin(); itr != chatusers.end(); ++itr)
		{
			find_flag = 0;
			for (itr2 = userslist.begin() + 1; itr2 < userslist.end(); itr2++)
			{
				if (*itr == *itr2)
					find_flag = 1;
			}
			if (!find_flag)
			{
				cout << CONVERSATION_FAIL_NO_USER << endl;
				return;
			}
		}
		map<string, ConversationStatus> read_map;
		for (auto itr = chatusers.begin(); itr != chatusers.end(); ++itr)
		{
			read_map[*itr] = READ;
		}
		Conversation new_conversation(chatusers, read_map, chrono::system_clock::now());
		MySharedPtr<Conversation> ptr1;
		ptr1 = &new_conversation;
		newConv newConv1(ptr1, chatusers);
		throw newConv1;
	}
	else if (cmdLineTokens[0] == "Open" && cmdLineTokens.size() == 2) // Open
	{
		if (cmdLineTokens[1].find_first_not_of("123456789") != string::npos)
		{
			cout << INVALID_CONVERSATION_NUMBER << endl;
			return;
		}
		int convNum = stringToInt(cmdLineTokens[1]);
		if (convNum<1 || convNum > ConversationList_.size())
		{
			cout << INVALID_CONVERSATION_NUMBER << endl;
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
			cout << INVALID_CONVERSATION_NUMBER << endl;
			return;
		}
		int convNum = stringToInt(cmdLineTokens[1]);
		if (convNum<1 || convNum > ConversationList_.size())
		{
			cout << INVALID_CONVERSATION_NUMBER << endl;
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
	list <Conversation>::iterator itr;
	for (itr = ConversationList_.begin(); itr != ConversationList_.end(); ++itr)
	{
		cout << count << ") ";
		if (itr->IsRead(activeUsrName) == UNREAD)
			cout << "(UNREAD) ";
		cout << "Participants: ";
		itr->DisplayParticipants();    // need to add to conversation? 
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