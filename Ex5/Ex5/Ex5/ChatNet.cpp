#include <iostream>
#include <stdexcept>
#include "Conversation.h"
#include "ChatNet.h"
#include "MessageBox.h"

#define NO_ACTIVE_USER "No User"



/* TODO: 
   vector<string> getUserList() - returns the Chatnet userlist as a vector<string>     */



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
	catch (newConv) // from MessageBox
	{
		/* TODO:
		for each user in the chatusers:
		make a local copy of newconv.ptr in his
		messagebox::ConversationList_.
		than sort his the ConversationList_ */
	}
	catch (convOpen)  // from MessageBox
	{
		/* TODO:
		update stack to conv2open.c conversation
		and preview conversation */
	} 
	catch (string substr)   // from MessageBox
	{
		/* TODO : 
		   search in userList if theres a name containing
		   str substring.   */
	}
	catch (string MessageBox_back)    // from MessageBox
	{
		/* TODO :
		   back to previous object in the stack
		   and preview it  */
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