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
	void addConv2msgBox(MySharedPtr<Conversation> convPtr) { msgBox_.addConv(convPtr); }
protected:
	string userName_;
	string userPass_;
	MessageBox msgBox_;
};

// Exception Classes
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

// Exception Classes
class newAdmin   // new admin
{
public:
	newAdmin(string adminName, string adminPass) : adminName_(adminName), adminPass_(adminPass) {}
	newAdmin() = default;
	string adminName_;
	string adminPass_;
};

class searchAdmin	// search admin
{
public:
	searchAdmin(string partName) : partName_(partName) {}
	searchAdmin() = default;
	string partName_;
};

#endif