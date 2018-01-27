#include <iostream>
#include "Defs.h"
#include "Conversation.h"


// Constructor
Conversation::Conversation(set<string> participants, map<string, ConversationStatus> readStateList, SysTime lastTime) :
	participants_(participants), readStateList_(readStateList), lastTime_(lastTime) {}


// Helper Functions
void printMessageList(vector<Message> list)
{
	for (auto it = list.begin(); it != list.end(); ++it)
		(*it).Print();
}

//Interface
bool Conversation::IsRead(string participant) const
{
	if (readStateList_.at(participant) == READ)
		return true;
	else
		return false;
}

void Conversation::removeUser(string user)
{
	participants_.erase(user);  
}


void Conversation::DisplayParticipants()
{
	for (auto itr = participants_.begin(); itr != participants_.end(); ++itr)
	{
		if ((++itr) == participants_.end())
		{
			--itr;
			cout << (*itr) << endl;
		}
		else
		{
			--itr;
			cout << (*itr) << COMMA_SPACE;
		}
	}
}

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
		throw BackConversation();
	}
	else // INVALID_INPUT
		cout << INVALID_INPUT;
}

void Conversation::Preview(string activeUsrName)
{
	// Mark that user read the conversation and display the conversation on screen
	if (participants_.find(activeUsrName) != participants_.end())
	{
		// activeUsrName is found as a participant
		readStateList_[activeUsrName] = READ;
		cout << PARTICIPANTS_TITLE;
		// Printing the set of conversation participants
		for (auto itr = participants_.begin(); itr != participants_.end(); ++itr)
		{
			// set is already sorted
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
