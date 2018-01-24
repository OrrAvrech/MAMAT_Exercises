#include<iostream>
#include "User.h"

// ------------------------------- User ------------------------------- //
// Constructor

// Hepler Functions
bool User::isNewMessages(MessageBox msgBox, string userName) const
{
	for (auto itr = msgBox.ConversationList_.begin(); itr != msgBox.ConversationList_.end(); ++itr)
	{
		if (!((*itr).IsRead(userName)))
			// Found a conversation with an UNREAD message --> found new message for User
			return true;
	}
	return false;
}

// Interface
void User::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	if (cmdLineTokens[0] == "Messages" && cmdLineTokens.size() == 1) // Messages
	{
		throw "User to MessageBox";
	}
	else if (cmdLineTokens[0] == "Logout" && cmdLineTokens.size() == 1) // Logout
	{
		throw "User LogOut";
	}
	else // INVALID_INPUT
		cout << INVALID_INPUT;
}

void User::Preview(string activeUsrName)
{
	auto name_ = activeUsrName;
	cout << name_ << USER_PREVIEW_PART1;
	if (isNewMessages(msgBox_, activeUsrName))
		cout << USER_PREVIEW_PART2_NEW_MESSAGES;
	else
		cout << USER_PREVIEW_PART2_NO_MESSAGES;
}

void User::Help() const
{
	cout << "Messages" << endl;
	cout << "Logout" << endl;
}

// ------------------------------- Admin ------------------------------- //
void Admin::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	if (cmdLineTokens[0] == "New" && cmdLineTokens.size() == 3) // New
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
	else // User command
	{
		// add code here
	}
}

void Admin::Help() const
{
	cout << "New <admin name> <admin password>" << endl;
	cout << "Delete <user name>" << endl;
	cout << "Search <partial user name>" << endl;
	User::Help(); // User commands
}