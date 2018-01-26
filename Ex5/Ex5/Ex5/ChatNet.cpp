#include <iostream>
#include <stdexcept>
#include "Conversation.h"
#include "ChatNet.h"
#include "MessageBox.h"
#include "User.h"
#define NO_ACTIVE_USER "No User"
using namespace std;
// helper functions
//vector<string> ChatNet::getUserList()
//{
//	User user;   
//	vector<string> StringV;
//	string userName;
//	set<MySharedPtr<User>>::iterator itr;
//	for (itr = UserList_.begin(); itr != UserList_.end(); ++itr)
//	{
//		user = *(itr->get());
//		userName = user.getName();
//		StringV.push_back(userName) ;
//	}
//	return StringV;
//}
//
//User ChatNet::findUserByName(string NeededUsername) // assuming the user exsist in the userlist
//{
//	User user;   
//	string userName;
//	for (auto itr = UserList_.begin(); itr != UserList_.end(); ++itr)
//	{
//		user = *(itr->get());
//		userName = user.getName();
//		if (userName == NeededUsername)
//			return user;
//	}
//}

// Constructor
ChatNet::ChatNet(const string& networkName, const string& adminName, const string& adminPass)
{
	networkName_ = networkName;
	Admin initAdmin(adminName, adminPass);
	currentUser_ = adminName;
	Preview(currentUser_);
	objStack_.push(this);
}

// Interface
void ChatNet::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	if (cmdLineTokens[0] == "Login" && cmdLineTokens.size() == 3) // Login
	{
		bool find_flag = 0;
		list<MySharedPtr<User>>::iterator itr;
		for (itr = UserList_.begin(); itr != UserList_.end(); ++itr)
		{
			if ((*itr)->getName() == cmdLineTokens[1])
			{
				if ((*itr)->getPassword() != cmdLineTokens[2])
				{
					cout << WRONG_PASSWORD;
					return;
				}
				find_flag = 1;
				break;
			}
		}
		if (find_flag == 0)
		{
			cout << USER_DOES_NOT_EXIST;
			return;
		}
		/* making the user the new obj */
		currentUser_ = (*itr)->getName();
		ActiveObj activeUserObj((*itr).get());
		objStack_.push(activeUserObj);
	}
	else if (cmdLineTokens[0] == "New" && cmdLineTokens.size() == 3) // New
	{
		list<MySharedPtr<User>>::iterator itr;
		for (itr = UserList_.begin(); itr != UserList_.end(); ++itr)
		{
			if ((*itr)->getName() == cmdLineTokens[1])
			{
				cout << USER_ALREADY_EXISTS;
				return;
			}
		}
		MySharedPtr<User> pNewUser(new User(cmdLineTokens[1], cmdLineTokens[2]));
		UserList_.push_back(pNewUser);
	}
	else if (cmdLineTokens[0] == "Exit" && cmdLineTokens.size() == 1) // Exit
	{
		throw BackSignal();
	}
	else // INVALID_INPUT
		cout << INVALID_INPUT;
}

void ChatNet::Do(string cmd)
{
	try
	{
		// Call Do method of the currently active object.
		// When using stack (from STL) this could like something like the following line:
		objStack_.top().Do(cmd, currentUser_);
	}
	//catch (newConv newConv1) // from MessageBox
	//{
	//	vector<string>  userslist;
	//	userslist = getUserList();
	//	set<string> chatusers = newConv1.userList; 
	//	vector<string>::iterator itr2;
	//	//checking if all users exsist in the ChatNet
	//	bool find_flag;
	//	for (auto itr = chatusers.begin(); itr != chatusers.end(); ++itr)
	//	{
	//		find_flag = 0;
	//		for (itr2 = userslist.begin() + 1; itr2 < userslist.end(); itr2++)
	//		{
	//			if (*itr == *itr2)
	//				find_flag = 1;
	//		}
	//		if (!find_flag)
	//		{
	//			cout << CONVERSATION_FAIL_NO_USER;
	//			return;
	//		}
	//	}
	//	map<string, ConversationStatus> read_map;
	//	for (auto itr = chatusers.begin(); itr != chatusers.end(); ++itr)
	//	{
	//		read_map[*itr] = READ;
	//	}
	//	Conversation new_conversation(chatusers, read_map, chrono::system_clock::now());
	//	MySharedPtr<Conversation> ptr1(&new_conversation);
	//	User user;
	//	for (auto itr = chatusers.begin(); itr != chatusers.end(); ++itr)
	//	{
	//		user = findUserByName(*itr);
	//		MySharedPtr<Conversation> convPtr(ptr1); // not sure it will realy make a new ptr each run and update counter
	//		user.addConv2msgBox(convPtr);
	//	}
	//}
	//catch (convOpen)  // from MessageBox
	//{
	//	/* TODO:
	//	update stack to conv2open.c conversation
	//	and preview conversation */
	//} 
	//catch (string substr)   // from MessageBox     // not sure it will print in alphabetical order
	//{
	//	vector<string> userlist;
	//	userlist = getUserList();
	//	bool find_flag = 0;
	//	for (auto itr = userlist.begin(); itr != userlist.end(); ++itr)
	//	{
	//		if (find_flag == 0 && itr->find(substr) != string::npos)
	//		{
	//			find_flag = 1;
	//			cout << SEARCH_FOUND_TITLE;
	//			cout << *itr << endl;
	//		}
	//		else if (itr->find(substr) != string::npos)
	//			cout << *itr << endl;
	//	}
	//	if (find_flag == 0)
	//		cout << SEARCH_NOT_FOUND_TITLE;
	//}
	//catch (char const* MessageBox_back)    // from MessageBox
	//{
	//	/* TODO :
	//	   back to previous object in the stack
	//	   and preview it  */
	//}
	//catch (string user2msgBox)  // from user
	//{
	//	/* TODO :
	//	users messagebox is the new object
	//	and preview it  */
	//}
	//catch (string user_logout)    //from user
	//{
	//	currentUser_ = "";
	//	/* TODO :
	//	chatnet is the new object */ 
	//	Preview(currentUser_);
	//}
	//catch (Admin newAdmin)    //from admin
	//{
	//	string username = newAdmin.getName();
	//	string password = newAdmin.getPassword();
	//	vector<string> userlist = getUserList();
	//	for (auto itr = userlist.begin(); itr != userlist.end(); ++itr)
	//	{
	//		if (*itr == username)
	//		{
	//			cout << USER_ALREADY_EXISTS;
	//			return;

	//		}
	//		MySharedPtr<User> adminPtr(&newAdmin);
	//		UserList_.insert(adminPtr);
	//	}
	//}
	//catch (string deleteAdmin)    //from admin
	//{
	//	string username = deleteAdmin;
	//	for (auto itr = UserList_.begin(); itr != UserList_.end(); ++itr)
	//	{
	//		if (itr->get()->getName() == username)
	//		{
	//			if (!itr->get()->isAdmin())
	//			{
	//				cout << REMOVE_USER_FAIL;
	//				return;
	//			}
	//			else
	//			{
	//				for (auto itr2 = UserList_.begin(); itr2 != UserList_.end(); ++itr2)
	//				{
	//					MessageBox*  msgbox = itr2->get()->getMsgBox();
	//					list<MySharedPtr<Conversation>>* convList = msgbox->getConversationList();
	//					for (auto itr3 = (*convList).begin(); itr3 != (*convList).end(); ++itr3)
	//					 {
	//						(*itr3)->removeUser(username);    //hoping it doesnt return error if it doesnt exist in the participant list
	//					 }
	//					if ((*itr2).get()->getName == username)
	//					{
	//						UserList_.erase(itr2);
	//					}
	//				}
	//				return;
	//			}
	//		}
	//	}
	//	cout << USER_DOES_NOT_EXIST;
	//}
	//catch (string searchAdmin)    //from admin
	//{
	//	vector<string> userlist;
	//	userlist = getUserList();
	//	bool find_flag = 0;
	//	for (auto itr = userlist.begin(); itr != userlist.end(); ++itr)
	//	{
	//		if (find_flag == 0 && itr->find(searchAdmin) != string::npos)
	//		{
	//			find_flag = 1;
	//			cout << SEARCH_FOUND_TITLE;
	//			cout << *itr << endl;
	//		}
	//		else if (itr->find(searchAdmin) != string::npos)
	//			cout << *itr << endl;
	//	}
	//	if (find_flag == 0)
	//		cout << SEARCH_NOT_FOUND_TITLE;
	//}
	catch (BackSignal)   // from ChatNet
	{
		/* TODO :
		   exit Chat  */
	}  

	catch (MessageBox msgBox) // from User
	{
		ActiveObj activeMsgBox(&msgBox);
		objStack_.push(activeMsgBox);
		msgBox.Preview(currentUser_);
	}

	catch (UserLogOut) // from User
	{
		objStack_.pop();
		currentUser_ = NO_ACTIVE_USER;
		objStack_.top().Preview(currentUser_);
	}

	// more catch phrases
}


void ChatNet::Preview(string activeUsrName)
{
	cout << "Welcome to " << networkName_ << "." << endl;
}


void ChatNet::Help() const
{
	cout << "Login <user name> <password>" << endl;
	cout << "New <user name> <password>" << endl;
	cout << "Exit" << endl;
}