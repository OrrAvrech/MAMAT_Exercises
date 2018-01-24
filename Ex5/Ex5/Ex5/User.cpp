#include<iostream>
#include "User.h"

// ------------------------------- User ------------------------------- //
using std::string;

// Constructor
User(const string& userName, const string& userPass, MessageBox msgBox) {}

// Interface
void User::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	if (cmdLineTokens[0] == "Messages" && cmdLineTokens.size() == 1) // Messages
	{
		// add code here
	}
	else if (cmdLineTokens[0] == "Logout" && cmdLineTokens.size() == 1) // Logout
	{
		// add code here
	}
	else // INVALID_INPUT
		cout << INVALID_INPUT;
}

void User::Preview(string activeUsrName)
{

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