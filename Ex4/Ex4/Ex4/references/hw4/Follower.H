#ifndef _FOLLOWER_H_
#define _FOLLOWER_H_

#include "defs.H"
#include "Message.H"
#include "Lists.H"

using namespace std;
bool checkExists(List& list, string email);

class Follower {
public:
	Follower(string name, string email, string password);
	~Follower();
	string GetName() const;
	string GetEmail() const;
	bool isPassword(string password) const;
	void showFriendRequests();
	void showFriendsList();
	Result addFriendRequest(Follower* pFollower); 
	Result AcceptFriendRequest(string email); 
	void RemoveFriendRequest(string email); 
	Result RemoveFriend(string email); 
	int NumFriendRequests() const; 
	void showMessages(); 
	void addMessage(Message newMessage); 
	Result ReadMessage(int messageNum); 
	Result SendMessage(string email, string subject, string content); 
	int NumUnreadMessages(); 
	Result AddFriend(Follower* pFollower);
protected:
	string name_;
	string email_;
	string password_;
	List friends_;
	List requests_;
	MessageBox Inbox_;
};

#endif
