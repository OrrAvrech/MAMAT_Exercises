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
	string currentUser_;
	stack<ActiveObj> objStack_;
	list<MySharedPtr<User> > UserList_;
public:
	ChatNet(const string& networkName, const string& adminName, const string& adminPass);
	vector<string> getUserList();
	void VrtDo(string cmdLine, string activeUsrName);
	void Preview(string activeUsrName);
	void Help() const;
	void Do(string cmd);
	User findUserByName(const string& NeededUsername);
	//User findUserByName(const string& NeededUsername);
};


#endif

