#include <iostream>
#include <exception>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <chrono>
#include "Conversation.h"
using namespace std;

int main() {
	//string line;
	//chatnet mamatchat("mamatchat", "admin", "1234");
	//while (!cin.eof())
	//{
	//	try
	//	{
	//		getline(cin, line);
	//		mamatchat.do(line);
	//	}
	//	catch (backsignal&) // exit
	//	{
	//		break;
	//	}
	//	catch (exception& e)
	//	{
	//		cout << e.what() << endl;
	//	}
	//	catch (...)
	//	{
	//		cout << "unexpected error" << endl;
	//		return 1;
	//	}
	//}
	set<string> part = { "user_23", "bla", "maso" };
	vector<Message> msgList;
	msgList.clear();
	map<string, ConversationStatus> readLst = {
		{"user_23", UNREAD},
		{"bla", UNREAD},
		{"maso", UNREAD}
	};
	SysTime lastTime;

	Conversation c(part, msgList, readLst, lastTime);
	c.VrtDo("Write whatup?", "bla");
	c.VrtDo("Write ok!", "maso");
	c.Preview("user_23");
	return 0;
};
