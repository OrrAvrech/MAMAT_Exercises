#ifndef _SOCIAL_NET_H_
#define _SOCIAL_NET_H_

#include "Defs.h"
#include "ObjectInterface.h"
#include <stack>
#include "User.h"


class ChatNet : public ObjectInterface 
{
	string netName;
	string currentUser;
	stack<ActiveObj> objStack;
	vector<MySharedPtr<User>> UserList;
public:
	ChatNet(const string& networkName, const string& adminName, const string& adminPass);
	vector<string> getUserList();

	
};


#endif

