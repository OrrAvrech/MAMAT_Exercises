#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "Conversation.h"
#include "ChatNet.h"
#include "MessageBox.h"
#include "User.h"
#define NO_ACTIVE_USER "No User"

using namespace std;

// helper functions
vector<string> ChatNet::getUserList()
{
	User user;
	vector<string> StringV;
	string userName;
	for (auto itr = UserList_.begin(); itr != UserList_.end(); ++itr)
		StringV.push_back((*itr).get()->getName());
	return StringV;
}

//User ChatNet::findUserByName(const string& NeededUsername) // assuming the user exsist in the userlist
//{
//	User user;
//	string userName;
//	for (auto itr = UserList_.begin(); itr != UserList_.end(); ++itr)
//	{
//		userName = (*itr).get()->getName();
//		if (userName == NeededUsername)
//			return user;
//	}
//}

// Constructor
ChatNet::ChatNet(const string& networkName, const string& adminName, const string& adminPass)
{
	networkName_ = networkName;
	MySharedPtr<User> pInitAdmin(new Admin(adminName, adminPass));
	UserList_.push_back(pInitAdmin);
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
		activeUserObj.Preview(currentUser_);
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

	catch (newConv(conv_participants)) // from MessageBox
	{
		newConv newConv1 = newConv(conv_participants);
		set<string> conv_users = newConv1.userList_;
		//checking if all users exsist in the ChatNet
		bool find_flag;
		map<string, ConversationStatus> read_map;
		for (auto itr1 = conv_users.begin(); itr1 != conv_users.end(); ++itr1)
		{
			find_flag = 0;
			for (auto itr2 = UserList_.begin(); itr2 != UserList_.end(); ++itr2)
			{
				if ((*itr1) == (*itr2).get()->getName())
				{
					find_flag = 1;
					read_map[(*itr1)] = READ;
					break;
				}
			}
		}
		if (!find_flag)
		{
			cout << CONVERSATION_FAIL_NO_USER;
			return;
		}
		else
		{
			conv_users.insert(currentUser_);
			read_map[currentUser_] = READ;
			MySharedPtr<Conversation> newConversation(new Conversation(conv_users, read_map, chrono::system_clock::now()));
			for (auto itr1 = conv_users.begin(); itr1 != conv_users.end(); ++itr1)
			{
				for (auto itr2 = UserList_.begin(); itr2 != UserList_.end(); ++itr2)
				{
					if ((*itr1) == (*itr2).get()->getName())
					{
						(*itr2).get()->addConv2msgBox(newConversation);
						break;
					}
				}
			}
		}

	}

	catch (BackConversation) // from Conversation
	{
		objStack_.pop();
		objStack_.top().Preview(currentUser_);
	}

	catch (const MBsearch& PartialName)   // from MessageBox  
	{
		// PartialName is a reference to the thrown class argument
		const string substr = PartialName.partName_;
		vector<string> userlist;
		userlist = getUserList();
		sort(userlist.begin(), userlist.end());
		bool find_flag = 0;
		for (auto itr = userlist.begin(); itr != userlist.end(); ++itr)
		{
			if (find_flag == 0 && itr->find(substr) != string::npos)
			{
				find_flag = 1;
				cout << SEARCH_FOUND_TITLE;
				cout << *itr << endl;
			}
			else if (itr->find(substr) != string::npos)
				cout << *itr << endl;
		}
		if (find_flag == 0)
			cout << SEARCH_NOT_FOUND_TITLE;
	}

	catch (convOpen conv_open)  // from MessageBox
	{
		objStack_.push(conv_open.activeConv_);
		conv_open.activeConv_.Preview(currentUser_);
		// conv_open is passed by value since Preview is a non-const method
		// Cannot use pass by non-const reference since an anonymous object is passed
		// An anonymous object is treated as a r-value
	}

	catch (BackMessageBox) // from MessageBox
	{
		objStack_.pop();
		objStack_.top().Preview(currentUser_);
	}

	catch (ActiveObj& activeMsgBox) // from User
	{
		objStack_.push(activeMsgBox);
		activeMsgBox.Preview(currentUser_);
	}

	catch (UserLogOut) // from User
	{
		objStack_.pop();
		currentUser_ = NO_ACTIVE_USER;
		objStack_.top().Preview(currentUser_);
	}

	catch (const newAdmin& new_admin) // from Admin
	{
		string adminName = new_admin.adminName_;
		string adminPass = new_admin.adminPass_;
		for (auto itr = UserList_.begin(); itr != UserList_.end(); ++itr)
		{
			if ((*itr)->getName() == adminName)
			{
				cout << USER_ALREADY_EXISTS;
				break;
			}
		}
		MySharedPtr<User> pAdmin(new Admin(adminName, adminPass));
		UserList_.push_back(pAdmin);
	}

	catch (const searchAdmin& PartialName) // from Admin
	{
		const string substr = PartialName.partName_;
		vector<string> userlist;
		userlist = getUserList();
		sort(userlist.begin(), userlist.end());
		bool find_flag = 0;
		for (auto itr = userlist.begin(); itr != userlist.end(); ++itr)
		{
			if (find_flag == 0 && itr->find(substr) != string::npos)
			{
				find_flag = 1;
				cout << SEARCH_FOUND_TITLE;
				cout << *itr << endl;
			}
			else if (itr->find(substr) != string::npos)
				cout << *itr << endl;
		}
		if (find_flag == 0)
			cout << SEARCH_NOT_FOUND_TITLE;
	}

	catch (const deleteUser& delete_user)    //from Admin
	{
		string username = delete_user.userName_;
		for (auto itr = UserList_.begin(); itr != UserList_.end(); ++itr)
		{
			if (itr->get()->getName() == username)
			{
				// Delete user from Conversation list
				if (((itr->get())->del(username)) == true) // Dynamic binding --> will delete accordingly
					// Delete user from ChatNet users list
					UserList_.erase(itr);
				return;
			}
		}
		cout << USER_DOES_NOT_EXIST;
	}

	catch (BackSignal)   // from ChatNet
	{
		throw BackSignal();
	}
	
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