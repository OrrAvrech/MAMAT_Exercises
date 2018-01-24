#ifndef _MESSAGEBOX_H_
#define _MESSAGEBOX_H_

#include "ObjectInterface.h"
#include "Conversation.h"
#include <list>
#include "MySharedPtr.h"

using namespace std;

class MessageBox
{
private:
	string username_;
	list<Conversation> ConversationList_;    //need to be a list of MySharedPtr????
public:
	MessageBox(string username, list<Conversation> ConversationList);
	void VrtDo(string cmdLine, string activeUsrName);
	void VrtPreview(string activeUsrName);
	void Help() const;
};


class newConv   // will be thrown as exception in new conversation
{
	MySharedPtr<Conversation> ptr;
	set<string> userList;
public : 
	newConv(MySharedPtr<Conversation> ptr, set<string> userList)
	{
		this->ptr = ptr;
		this->userList = userList;
	}
};

class convOpen   // will be thrown as exception in conversation open
{
	Conversation c;
public:
	convOpen(Conversation c)
	{
		this->c = c;
	}
};

#endif

