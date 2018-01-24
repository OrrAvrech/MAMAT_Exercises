#ifndef _USER_H_
#define _USER_H_

#include "ObjectInterface.h"
#include "MessageBox.h"

// ------------------------------- User ------------------------------- //
class User : public ObjectInterface {

public:
	// Constructor
	User(std::string userName, std::string userPass, MessageBox msgBox);

	// Methods
	void Preview(std::string activeUsrName);
	void VrtDo(std::string cmdLine, std::string activeUsrName);
	void Help() const;

protected:
	std::string userName_;
	std::string userPass_;
	MessageBox msgBox_;

};



// ------------------------------- Admin ------------------------------- //



#endif

