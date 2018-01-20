#include <iostream>
#include "Defs.h"
#include "Conversation.h"
















//Interface
void Conversation::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES, 1);
	if (cmdLineTokens[0] == "Write" && cmdLineTokens.size() == 2) // Write
	{
		// add code here
	}
	else if (cmdLineTokens[0] == "Back" && cmdLineTokens.size() == 1) // Back
	{
		// add code here
	}
	else // INVALID_INPUT
		cout << INVALID_INPUT;
}


void Conversation::VrtPreview(string activeUsrName)
{
	// Mark that user read the conversation and display the conversation on screen
}


void Conversation::Help() const
{
	cout << "Write <message>" << endl;
	cout << "Back" << endl;
}
