#include <iostream>
#include "Defs.h"
#include "Conversation.h"


// Constructor
Conversation::Conversation(vector<string> participants, vector<Message> messageList, map<string, ConversationStatus> readStateList, SysTime lastTime) :
	participants_(participants), messageList_(messageList), readStateList_(readStateList), lastTime_(lastTime) {}

// Helper Functions
void printMessageList(vector<Message> list)
{
	vector<Message>::iterator it;
	for (it = list.begin(); it != list.end(); it++)
		(*it).Print();
}

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

void Conversation::Preview(string activeUsrName)
{
	// Mark that user read the conversation and display the conversation on screen
	if (participants_.find(activeUsrName) != participants_.end())
	{
		// Found
		readStateList_[activeUsrName] = READ;
		cout << PARTICIPANTS_TITLE;
		// Printing the set of conversation participants
		set<string>::iterator it;
		for (it = participants_.begin(); it != participants_.end(); it++)
		{
			// set is already sorted
			cout << (*it) << PARTICIPANT_READ_STATUS << COMMA_SPACE;
			if ((*it).end()[-1])
				cout << (*it) << PARTICIPANT_READ_STATUS;
			printMessageList(messageList_);
		}
	}
	else
		// Not Found
		cout << activeUsrName << NOT_IN_THE_CONVERSATION;
}

void Conversation::Help() const
{
	cout << "Write <message>" << endl;
	cout << "Back" << endl;
}
