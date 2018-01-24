#ifndef _USER_H_
#define _USER_H_

#include "ObjectInterface.h"
#include "MessageBox.h"

// ------------------------------- User ------------------------------- //
class User : public ObjectInterface {

public:
	// Constructor
	User(string userName, string userPass, MessageBox msgBox);
	User() = default;
	// Methods
	void Preview(string activeUsrName);
	void VrtDo(string cmdLine, string activeUsrName);
	void Help() const;
	bool isNewMessages(MessageBox msgBox, string userName) const;
	string getName(); // TODO: returns the name of the user
	string getPassword(); // TODO: returns the password of the user
protected:
	string userName_;
	string userPass_;
	MessageBox msgBox_;

};



// ------------------------------- Admin ------------------------------- //



#endif

