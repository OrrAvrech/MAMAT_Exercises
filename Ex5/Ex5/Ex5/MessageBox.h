#ifndef _MESSAGEBOX_H_
#define _MESSAGEBOX_H_

#include "ObjectInterface.h"
#include "Conversation.h"
#include <list>
#include "MySharedPtr.h"

using namespace std;

class MessageBox : public ObjectInterface
{
	friend class User;
private:
	string username_;
	list<MySharedPtr<Conversation>> ConversationList_;    //need to be a list of MySharedPtr????
public:
	MessageBox(string username, list<MySharedPtr<Conversation>> ConversationList);
	MessageBox() = default;
	void VrtDo(string cmdLine, string activeUsrName);
	void Preview(string activeUsrName);
	void Help() const;
	void addConv(MySharedPtr<Conversation> convPtr);   //TODO: add a conversation ptr to conversationList_ and sort by date
};


class newConv   // will be thrown as exception in new conversation
{
public : 
	set<string> userList;
	newConv(set<string> userList)
	{
		this->userList = userList;
	}
};

class convOpen   // will be thrown as exception in conversation open
{
public:
	MySharedPtr<Conversation> convPtr;
	convOpen(MySharedPtr<Conversation> convPtr)
	{
		this->convPtr = convPtr;
	}
};

#endif

