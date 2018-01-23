#ifndef _MESSAGEBOX_H_
#define _MESSAGEBOX_H_

#include "ObjectInterface.h"
#include "Conversation.h"
#include <list>

using namespace std;

class MessageBox
{
private:
	string username_;
	list<Conversation> ConversationList_;
public:
	MessageBox(string username, list<Conversation> ConversationList);
	void VrtDo(string cmdLine, string activeUsrName);
	void VrtPreview(string activeUsrName);
	void Help() const;
};

#endif

