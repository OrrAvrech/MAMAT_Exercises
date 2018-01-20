#include <iostream>
#include <stdexcept>
#include "Conversation.h"
#include "ChatNet.h"

#define NO_ACTIVE_USER "No User"







// Interface
void ChatNet::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	if (cmdLineTokens[0] == "Login" && cmdLineTokens.size() == 3) // Login
	{
		// add code here
	}
	else if (cmdLineTokens[0] == "New" && cmdLineTokens.size() == 3) // New
	{
		// add code here
	}
	else if (cmdLineTokens[0] == "Exit" && cmdLineTokens.size() == 1) // Exit
	{
		throw BackSignal();
	}
	else // INVALID_INPUT
		cout << INVALID_INPUT;
}

void ChatNet::Do(string cmd)
{
	try
	{
		// Call Do method of the currently active object.
		// When using stack (from STL) this could like something like the following line:
		// activeObjectStack_.top().Do(cmd, activeUsrName_);
	}
	catch (/* ??? */)
	{
		
	}
	catch (/* ??? */)
	{
		
	}
	// more catch phrases
}


void ChatNet::VrtPreview(string activeUsrName)
{
	cout << "Welcome to " << networkName_ << "." << endl;
}


void ChatNet::Help() const
{
	cout << "Login <user name> <password>" << endl;
	cout << "New <user name> <password>" << endl;
	cout << "Exit" << endl;
}