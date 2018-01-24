#include <iostream>
#include "Defs.h"
#include "Conversation.h"


// Constructor
Conversation::Conversation(vector<string> participants, vector<Message> messageList, map<string, ConversationStatus> readStateList, SysTime lastTime) :
Conversation::Conversation(set<string> participants, vector<Message> messageList, map<string, ConversationStatus> readStateList, SysTime lastTime) :
	participants_(participants), messageList_(messageList), readStateList_(readStateList), lastTime_(lastTime) {}

// Helper Functions
void printMessageList(vector<Message> list)
{
	vector<Message>::iterator it;
	for (it = list.begin(); it != list.end(); it++)
	for (auto it = list.begin(); it != list.end(); ++it)
		(*it).Print();
}

bool Conversation::IsRead(string participant) const
{
	if (readStateList_.at(participant) == READ)
		return true;
	else
		return false;
}

//Interface
void Conversation::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES, 1);
	if (cmdLineTokens[0] == "Write" && cmdLineTokens.size() == 2) // Write
	{
		if (participants_.find(activeUsrName) != participants_.end())
		{
			// activeUsrName is found as a participant
			Message newMessage(activeUsrName, cmdLineTokens[1]);
			messageList_.push_back(newMessage);
			for (auto itr = readStateList_.begin(); itr != readStateList_.end(); ++itr)
				// All participants in map --> UNREAD
				readStateList_[itr->first] = UNREAD;
			// Except activeUsrName --> READ
			readStateList_[activeUsrName] = READ;
			// Last conversation time update
			lastTime_ = chrono::system_clock::now();
		}
		else
			// Not Found
			cout << activeUsrName << NOT_IN_THE_CONVERSATION;
	}
	else if (cmdLineTokens[0] == "Back" && cmdLineTokens.size() == 1) // Back
	{
		// add code here
		throw "Run MessageBox Preview";
		/* Deal with this exception in ChatNet:
		 try: Conversation
		 catch: MessageBox.Preview */
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
		// activeUsrName is found as a participant
		readStateList_[activeUsrName] = READ;
		cout << PARTICIPANTS_TITLE;
		// Printing the set of conversation participants
		set<string>::iterator it;
		for (it = participants_.begin(); it != participants_.end(); it++)
		for (auto itr = participants_.begin(); itr != participants_.end(); ++itr)
		{
			// set is already sorted
			cout << (*it) << PARTICIPANT_READ_STATUS << COMMA_SPACE;
			if ((*it).end()[-1])
				cout << (*it) << PARTICIPANT_READ_STATUS;
			printMessageList(messageList_);
			if ((++itr) == participants_.end())
			{
				--itr;
				cout << (*itr) << PARTICIPANT_READ_STATUS << endl;
			}
			else
			{
				--itr;
				cout << (*itr) << PARTICIPANT_READ_STATUS << COMMA_SPACE;
			}
		}
		printMessageList(messageList_);
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
