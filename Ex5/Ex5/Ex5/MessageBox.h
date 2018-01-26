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
	MessageBox();
	MessageBox(string username);
	MessageBox(string username, list<MySharedPtr<Conversation>> ConversationList);
	void VrtDo(string cmdLine, string activeUsrName);
	void Preview(string activeUsrName);
	void Help() const;
};

class newConv   // will be thrown as exception in new conversation
{
	set<string> userList_;
public : 
	newConv(set<string> userList) : userList_(userList) {}
};

class convOpen   // will be thrown as exception in conversation open
{
	MySharedPtr<Conversation> pConv_;
public:
	convOpen(MySharedPtr<Conversation> pConv) : pConv_(pConv) {}
};

#endif

