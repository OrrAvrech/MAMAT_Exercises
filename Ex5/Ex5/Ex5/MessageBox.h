#ifndef _MESSAGEBOX_H_
#define _MESSAGEBOX_H_

#include "ObjectInterface.h"

using namespace std;

class MessegeBox
{
private:
	string UserName_;
	vector<Conversation> ConversationList_;
public:
	MessegeBox();
	~MessegeBox();
	void VrtDo(string cmdLine, string activeUsrName);
	void VrtPreview(string activeUsrName);
	void help() const;

};

#endif

