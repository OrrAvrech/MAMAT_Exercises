#include<iostream>
#include "User.h"

// ------------------------------- User ------------------------------- //
// Constructor
User::User(string userName, string userPass, MessageBox msgBox) :
	userName_(userName), userPass_(userPass), msgBox_(msgBox) {}

User::User(string userName, string userPass) :
	userName_(userName), userPass_(userPass) {}

// Hepler Functions
bool User::isNewMessages(MessageBox msgBox, string userName) const
{
	for (auto itr = msgBox.ConversationList_.begin(); itr != msgBox.ConversationList_.end(); ++itr)
	{
		if (!((*itr)->IsRead(userName)))
			// Found a conversation with an UNREAD message --> found new message for User
			return true;
	}
	return false;
}

string User::getName()
{
	return userName_;
}

string User::getPassword()
{
	return userPass_;
}

// Interface
void User::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	if (cmdLineTokens[0] == "Messages" && cmdLineTokens.size() == 1) // Messages
	{
		throw UserMessages(this->msgBox_); // TODO
	}
	else if (cmdLineTokens[0] == "Logout" && cmdLineTokens.size() == 1) // Logout
	{
		throw UserLogOut();
	}
	else // INVALID_INPUT
		cout << INVALID_INPUT;
}

void User::Preview(string activeUsrName)
{
	auto name_ = activeUsrName;
	cout << USER_PREVIEW_PART1 << endl;
	if (isNewMessages(msgBox_, activeUsrName))
		cout << USER_PREVIEW_PART2_NEW_MESSAGES << endl;
	else
		cout << USER_PREVIEW_PART2_NO_MESSAGES << endl;
}

void User::Help() const
{
	cout << "Messages" << endl;
	cout << "Logout" << endl;
}

// ------------------------------- Admin ------------------------------- //

// Constructors
Admin::Admin(string userName, string userPass, MessageBox msgBox) : 
	User(userName, userPass, msgBox) {}

Admin::Admin(string userName, string userPass) :
	User(userName, userPass) {}

// Interface
void Admin::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	if (cmdLineTokens[0] == "New" && cmdLineTokens.size() == 3) // New
	{
		throw "Admin New to ChatNet";
	}
	else if (cmdLineTokens[0] == "Delete" && cmdLineTokens.size() == 2) // Delete
	{
		throw "Admin Delete to ChatNet";
	}
	else if (cmdLineTokens[0] == "Search" && cmdLineTokens.size() == 2) // Search
	{
		throw "Admin Search to ChatNet";
	}
	else // User command
	{
		User::VrtDo(cmdLine, activeUsrName);
	}
}

void Admin::Help() const
{
	cout << "New <admin name> <admin password>" << endl;
	cout << "Delete <user name>" << endl;
	cout << "Search <partial user name>" << endl;
	User::Help(); // User commands
}