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
	void addConv(MySharedPtr<Conversation> convPtr);
};

// Exception Classes
class newConv   // new conversation
{
public : 
	newConv(set<string> userList) : userList_(userList) {}
	set<string> userList_;
};

class convOpen   // conversation open
{
public:
	convOpen(ActiveObj activeConv) : activeConv_(activeConv) {}
	ActiveObj activeConv_;
};

class MBsearch	// MessageBox search
{
public:
	MBsearch(string partName) : partName_(partName) {}
	string partName_;
};

class BackMessageBox {
};




#endif

