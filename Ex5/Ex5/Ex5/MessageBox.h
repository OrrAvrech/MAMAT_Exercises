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
	list<MySharedPtr<Conversation>> ConversationList_; 
public:
	MessageBox(string username, list<MySharedPtr<Conversation>> ConversationList);
	MessageBox(string username);
	MessageBox();
	void VrtDo(string cmdLine, string activeUsrName);
	void Preview(string activeUsrName);
	void Help() const;
	list<MySharedPtr<Conversation>>* getConversationList() { return &ConversationList_; }
	void addConv(MySharedPtr<Conversation> convPtr);  
};


//class newConv   // will be thrown as exception in new conversation
//{
//public : 
//	set<string> userList;
//	newConv(set<string> userList)
//	{
//		this->userList = userList;
//	}
//};
//
//class convOpen   // will be thrown as exception in conversation open
//{
//public:
//	MySharedPtr<Conversation> convPtr;
//	convOpen(MySharedPtr<Conversation> convPtr)
//	{
//		this->convPtr = convPtr;
//	}
//};

class newConv   // will be thrown as exception in new conversation
{
	set<string> userList_;
public:
	newConv(set<string> userList) : userList_(userList) {}
};

class convOpen   // will be thrown as exception in conversation open
{
	MySharedPtr<Conversation> pConv_;
public:
	convOpen(MySharedPtr<Conversation> pConv) : pConv_(pConv) {}
};


#endif

