#ifndef _USER_H_
#define _USER_H_

#include "ObjectInterface.h"
#include "MessageBox.h"

// ------------------------------- User ------------------------------- //
class User : public ObjectInterface {

public:
	// Constructor
	User() = default;
	User(string userName, string userPass, MessageBox msgBox);
	User(string userName, string userPass);
	// Methods
	void Preview(string activeUsrName);
	void VrtDo(string cmdLine, string activeUsrName);
	void Help() const;
	bool isNewMessages(MessageBox msgBox, string userName) const;
	string getName() { return userName_; }
	string getPassword() { return userPass_; }
	void addConv2msgBox(MySharedPtr<Conversation> convPtr) { msgBox_.addConv(convPtr); }
	bool isAdmin() { return adminFlag; }
	MessageBox* getMsgBox() { return &msgBox_ ; }
protected:
	string userName_;
	string userPass_;
	MessageBox msgBox_;
	bool adminFlag;
};

// ------------------------------- Admin ------------------------------- //
class Admin : public User {
public:
	// Constructor
	Admin(string userName, string userPass, MessageBox msgBox);
	Admin(string userName, string userPass);
	// Methods
	// Preview() is inherited from User
	void VrtDo(string cmdLine, string activeUsrName);
	void Help() const;
};


#endif

