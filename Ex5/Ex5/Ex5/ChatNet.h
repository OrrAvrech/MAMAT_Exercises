#ifndef _SOCIAL_NET_H_
#define _SOCIAL_NET_H_

#include "Defs.h"
#include "ObjectInterface.h"
#include <stack>
#include "User.h"
#include <set>

class ChatNet : public ObjectInterface 
{
	string networkName_;
	string currentUser;
	stack<ActiveObj> objStack;
	set<MySharedPtr<User>> UserList_;
public:
	ChatNet(const string& networkName, const string& adminName, const string& adminPass);
	vector<string> getUserList();
	void VrtDo(string cmdLine, string activeUsrName);
	void VrtPreview(string activeUsrName);
	void Help() const;
	User findUserByName(string NeededUsername);
};


#endif

