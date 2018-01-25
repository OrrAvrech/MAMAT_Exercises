#include <iostream>
#include <exception>
#include <string>
#include "ChatNet.h"
using namespace std;

int main() {
	string line;
	ChatNet MamatChat("MamatChat", "Admin", "1234");
	while (!cin.eof())
	{
		try
		{
			getline(cin, line);
			MamatChat.Do(line);
		}
		catch (BackSignal&) // Exit
		{
			break;
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "Unexpected Error" << endl;
			return 1;
		}
	}

	//// Network
	//list<MySharedPtr<User>> ChatUsers;
	//map<string, string> UsersMap = {
	//	{"dean", "1234"}, 
	//	{"marina", "4333"}, 
	//	{"eyal", "1111"},
	//	{"moti", "2222"},
	//	{"rami", "3333"}
	//};

	//SysTime lastTime = chrono::system_clock::now();

	//// Conv1
	//set<string> c1_p = { "dean", "marina", "eyal" };
	//map<string, ConversationStatus> c1_cs = {
	//	{ "dean", UNREAD },
	//	{ "marina", UNREAD },
	//	{ "eyal", UNREAD }
	//};
	//Conversation conv1(c1_p, c1_cs, lastTime);

	//// Conv2
	//set<string> c2_p = { "dean", "moti" };
	//map<string, ConversationStatus> c2_cs = {
	//	{ "dean", UNREAD },
	//	{ "moti", UNREAD }
	//};
	//Conversation conv2(c2_p, c2_cs, lastTime);

	//// Conv3
	//set<string> c3_p = { "rami", "moti", "eyal" };
	//map<string, ConversationStatus> c3_cs = {
	//	{ "rami", UNREAD },
	//	{ "moti", UNREAD },
	//	{ "eyal", UNREAD }
	//};
	//Conversation conv3(c3_p, c3_cs, lastTime);

	//// ActiveUser: moti
	//string activeUserName = "moti";
	//conv1.Preview(activeUserName);
	//cout << endl;
	//conv2.Preview(activeUserName); //Lex Order ok
	//cout << endl;
	//conv2.VrtDo("Write Hi! it's moti here", activeUserName);
	//conv2.Preview(activeUserName);
	//cout << endl;
	///*conv3.Preview(activeUserName);
	//cout << endl;*/
	//
	//MySharedPtr<Conversation> pConv2(new Conversation(c2_p, c2_cs, lastTime));
	//MySharedPtr<Conversation> pConv3(new Conversation(c3_p, c3_cs, lastTime));
	//*pConv2 = conv2;
	//*pConv3 = conv3;
	//list<MySharedPtr<Conversation>> mb_list = { pConv2, pConv3 };
	//MessageBox mb(activeUserName, mb_list);
	//mb.Preview(activeUserName);

	//MySharedPtr<User> pUser1(new User("moti", "2222", mb));
	//ChatUsers = { pUser1 };
	//pUser1->Preview(activeUserName);

	return 0;
};
