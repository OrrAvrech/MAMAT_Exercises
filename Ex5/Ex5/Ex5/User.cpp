#include<iostream>
#include "User.h"

// ------------------------------- User ------------------------------- //
// Constructor
User::User(string userName, string userPass, MessageBox msgBox) :
	userName_(userName), userPass_(userPass), msgBox_(msgBox) {
	adminFlag = 0;
}

User::User(string userName, string userPass) : userName_(userName), userPass_(userPass) 
{
	MessageBox msgBox_;
	adminFlag = 0;
}
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

// Interface
void User::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	if (cmdLineTokens[0] == "Messages" && cmdLineTokens.size() == 1) // Messages
	{
		msgBox_.username_ = activeUsrName;
		MySharedPtr<MessageBox> msgBox_ptr(&msgBox_);
		MySharedPtr<MessageBox> msgBox_ptr_exp(msgBox_ptr);
		throw (msgBox_ptr_exp);
	}
	else if (cmdLineTokens[0] == "Logout" && cmdLineTokens.size() == 1) // Logout
	{
		/*string user_logout = "User LogOut";
		throw user_logout;*/
		throw UserLogOut();
	}
	else // INVALID_INPUT
		cout << INVALID_INPUT;
}

void User::Preview(string activeUsrName)
{
	auto name_ = activeUsrName;
	cout << USER_PREVIEW_PART1;
	if (isNewMessages(msgBox_, activeUsrName))
		cout << USER_PREVIEW_PART2_NEW_MESSAGES;
	else
		cout << USER_PREVIEW_PART2_NO_MESSAGES ;
}

void User::Help() const
{
	cout << "Messages" << endl;
	cout << "Logout" << endl;
}

// ------------------------------- Admin ------------------------------- //

// Constructor
Admin::Admin(string userName, string userPass, MessageBox msgBox) : 
	User(userName, userPass, msgBox) {
	adminFlag = 1;
}

Admin::Admin(string userName, string userPass) :
	User(userName, userPass) {
	MessageBox msgBox;
	adminFlag =1 ;
}


// Interface
void Admin::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	if (cmdLineTokens[0] == "New" && cmdLineTokens.size() == 3) // New
	{
		Admin newAdmin(cmdLineTokens[1], cmdLineTokens[2]);
		throw newAdmin;
	}
	else if (cmdLineTokens[0] == "Delete" && cmdLineTokens.size() == 2) // Delete
	{
		string deleteAdmin = cmdLineTokens[1];
		throw deleteAdmin;
	}
	else if (cmdLineTokens[0] == "Search" && cmdLineTokens.size() == 2) // Search
	{
		string searchAdmin = cmdLineTokens[1];
		throw searchAdmin;
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