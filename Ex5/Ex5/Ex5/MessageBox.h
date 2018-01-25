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
	void VrtDo(string cmdLine, string activeUsrName);
	void Preview(string activeUsrName);
	void Help() const;
};


//class newConv   // will be thrown as exception in new conversation
//{
//	
//	set<string> userList;
//public : 
//	newConv(MySharedPtr<Conversation> ptr, set<string> userList)
//	{
//		this->ptr = ptr;
//		this->userList = userList;
//	}
//};

//class convOpen   // will be thrown as exception in conversation open
//{
//	Conversation c;
//public:
//	convOpen(Conversation c)
//	{
//		this->c = c;
//	}
//};

#endif

