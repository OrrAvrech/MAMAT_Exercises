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

bool User::del(string username)
{
	for (auto itr = msgBox_.ConversationList_.begin(); itr != msgBox_.ConversationList_.end(); ++itr)
		(*itr)->removeUser(username);
	return true;
}

// Interface
void User::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	if (cmdLineTokens[0] == "Messages" && cmdLineTokens.size() == 1) // Messages
	{
		msgBox_.username_ = activeUsrName;
		//throw (this->msgBox_);
		//MySharedPtr<MessageBox> msgBox_ptr(&msgBox_);
		//MySharedPtr<MessageBox> msgBox_ptr_exp(msgBox_ptr);
		ActiveObj activeMsgBox(&msgBox_);
		throw (activeMsgBox);
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

// Constructors
Admin::Admin(string userName, string userPass, MessageBox msgBox) : 
	User(userName, userPass, msgBox) {}

Admin::Admin(string userName, string userPass) :
	User(userName, userPass) {}

bool Admin::del(string username)
{
	cout << REMOVE_USER_FAIL;
	return false;
}

// Interface
void Admin::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	if (cmdLineTokens[0] == "New" && cmdLineTokens.size() == 3) // New
	{
		newAdmin new_admin(cmdLineTokens[1], cmdLineTokens[2]);
		throw (new_admin);
	}
	else if (cmdLineTokens[0] == "Delete" && cmdLineTokens.size() == 2) // Delete
	{
		deleteUser delete_user(cmdLineTokens[1]);
		throw (delete_user);
	}
	else if (cmdLineTokens[0] == "Search" && cmdLineTokens.size() == 2) // Search
	{
		searchAdmin search_admin(cmdLineTokens[1]);
		throw (search_admin);
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