#ifndef _CONVERSATION_H_
#define _CONVERSATION_H_

#include "ObjectInterface.h"

#include <iostream>
#include <chrono>
#include <set>
#include <string>
#include <vector>
#include <map>

using namespace std;

enum ConversationStatus { READ, UNREAD };

typedef chrono::system_clock::time_point SysTime;

// ------------------------------- Message ------------------------------- //
class Message {
public:
	Message(const string& by, const string& content) : by_(by), content_(content) {}
	void Print() const { cout << by_ << " : " << content_ << endl; }
private:
	string by_;
	string content_;
};
// ------------------------------- Conversation ------------------------------- //
class Conversation : public ObjectInterface {

public:
	// Constructor
	Conversation(set<string> participants, map<string, ConversationStatus> readStateList, SysTime lastTime);
	Conversation(const Conversation& pConv)
	{
		participants_ = pConv.participants_;
		messageList_ = pConv.messageList_;
		readStateList_ = pConv.readStateList_;
		lastTime_ = pConv.lastTime_;
	}
	Conversation() = default;
	// Methods
	void Preview(string activeUsrName);
	void VrtDo(string cmdLine, string activeUsrName);
	void Help() const;
	void removeUser(string user); // remove user from participants
	bool IsRead(string participant) const;
	void DisplayParticipants(); // print participants list.
	SysTime getTime() { return lastTime_; }
	
private:
	set<string> participants_; // participants set contains a string as user name (not User class)
	vector<Message> messageList_;
	map<string, ConversationStatus> readStateList_;
	SysTime lastTime_;
};

// Exception Classes
class BackConversation {
};
class SortConv {
public:
	set<string> participants;
};
#endif
