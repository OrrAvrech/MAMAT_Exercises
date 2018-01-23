#ifndef _SOCIAL_NET_H_
#define _SOCIAL_NET_H_

#include "Defs.h"
#include "ObjectInterface.h"



class ChatNet : public ObjectInterface {
public:
	ChatNet(const string& networkName, const string& adminName, const string& adminPass);
	vector<string> getUserList(/*not sure about inputs*/);
	
};


#endif

