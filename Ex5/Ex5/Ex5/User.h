#ifndef _USER_H_
#define _USER_H_

#include "ObjectInterface.h"
#include "MessageBox.h"

// ------------------------------- User ------------------------------- //
class User : public ObjectInterface {

public:
	// Constructor
	User(string userName, string userPass, MessageBox msgBox);
    User(string userName, string userPass);
	User() = default;
	// Methods
	void Preview(string activeUsrName);
	void VrtDo(string cmdLine, string activeUsrName);
	void Help() const;
	bool isNewMessages(MessageBox msgBox, string userName) const;
	string getName(); 
	string getPassword();
protected:
	string userName_;
	string userPass_;
	MessageBox msgBox_;
};

// Exception Classes
class UserMessages {
protected:
	MySharedPtr<MessageBox> pMsgBox_;
public:
	UserMessages(MySharedPtr<MessageBox> pMsgBox) : pMsgBox_(pMsgBox) {}
};

class UserLogOut {
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