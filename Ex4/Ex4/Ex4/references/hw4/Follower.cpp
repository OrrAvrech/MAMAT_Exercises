#include <iostream>
#include "Follower.H"
#include <string>

using namespace std;

//*********************************************************************************************************
//* function name:	Follower
//* Description  :	Constructor of Follower class
//* Parameters   :	name - name of the follower
//*					email - email of the follower(must be UNIQUE)
//*					password - password of the user
//* Return Value :	None
//*********************************************************************************************************
Follower::Follower(string name, string email, string password) :
	name_(name), email_(email), password_(password), friends_(FOLLOWER), requests_(FOLLOWER) {};

//*********************************************************************************************************
//* function name:	~Follower
//* Description  :	Destructor of Follower class
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************

Follower::~Follower() {};

//*********************************************************************************************************
//* function name:	GetName
//* Description  :	Returning the name of the follower
//* Parameters   :	None
//* Return Value :	Name of the follower
//*********************************************************************************************************
string Follower::GetName() const {
	return name_;
}

//*********************************************************************************************************
//* function name:	GetEmail
//* Description  :	Returning the email of the follower
//* Parameters   :	None
//* Return Value :	email of the follower
//*********************************************************************************************************
string Follower::GetEmail() const {
	return email_;
}

//*********************************************************************************************************
//* function name:	isPassword
//* Description  :	Checking if the password entered by the user is the current one
//* Parameters   :	None
//* Return Value :	true of false
//*********************************************************************************************************
bool Follower::isPassword(string password) const {
	if (password_.compare(password) != 0) return false;
	return true;
}

//*********************************************************************************************************
//* function name:	showFriendRequests
//* Description  :	Going through the friend requests list and displaying it
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
void Follower::showFriendRequests() {
	requests_.goHead();
	int n = requests_.getSize();
	for (int i = 0; i < n; i++) {
		Follower* curRequest = static_cast<Follower*>(requests_.getValue());
		cout << SHOW_FRIEND_REQUESTS_SUCCESS << endl;
		requests_.getNext();
	}
}

//*********************************************************************************************************
//* function name:	showFriendsList
//* Description  :	Going through the friends list and displaying it
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
void Follower::showFriendsList() {
	friends_.goHead();
	int n=friends_.getSize();
	for (int i = 0; i < n; i++) {
		Follower* curFriend = static_cast<Follower*>(friends_.getValue());
		cout << SHOW_FRIEND_LIST_SUCCESS << endl;
		friends_.getNext();
	}
}

//*********************************************************************************************************
//* function name:	addFriendRequest
//* Description  :	Adding a friend request from a fellow follower. Return FAILURE if already friends or if 
//*					already sent request
//* Parameters   :	pFollower - a pointer to the friendship requesting follower
//* Return Value :	SUCCESS or FAILURE
//*********************************************************************************************************
Result Follower::addFriendRequest(Follower* pFollower) {
	if ((checkExists(friends_, pFollower->GetEmail()) == true) || // already friends
		(checkExists(requests_, pFollower->GetEmail()) == true) // already sent request
		)
		return FAILURE;
	requests_.add(pFollower);
	return SUCCESS;
}

//*********************************************************************************************************
//* function name:	AcceptFriendRequest
//* Description  :	Accepting a friend request. Return FAILURE if already friends or no friend request
//* Parameters   :	email - the email of the user accepting the friend request
//* Return Value :	SUCCESS or FAILURE
//*********************************************************************************************************
Result Follower::AcceptFriendRequest(string email) {
	if (checkExists(friends_, email) == true)
		return FAILURE; // already friends
	if (checkExists(requests_, email) == true){
		Follower* tmp = static_cast<Follower*>(requests_.getValue());
		requests_.deleteNode(); // iterator will be on the request
		friends_.add(tmp);
		return SUCCESS;
	}
	return FAILURE; // no such request
}

//*********************************************************************************************************
//* function name:	RemoveFriendRequest
//* Description  :	Removing a friend request of a given email if exists
//* Parameters   :	email - email of the follower to be removed
//* Return Value :	None
//*********************************************************************************************************
void Follower::RemoveFriendRequest(string email) {
	if (checkExists(requests_, email))
		requests_.deleteNode(); // iterator will be on the request
}

//*********************************************************************************************************
//* function name:	RemoveFriend
//* Description  :	Removing a friend :'(
//* Parameters   :	email - email of the friend to be removed
//* Return Value :	SUCCESS or FAILURE
//*********************************************************************************************************
Result Follower::RemoveFriend(string email) {
	if (checkExists(friends_, email)) {
		return friends_.deleteNode(); // iterator will be on the request
	}
	return FAILURE; // not friends
}

//*********************************************************************************************************
//* function name:	NumOfFriendRequests
//* Description  :	Getting the amount of friend requests
//* Parameters   :	None
//* Return Value :	Number of friends request (int)
//*********************************************************************************************************
int Follower::NumFriendRequests() const {
	return requests_.getSize();
}

//*********************************************************************************************************
//* function name:	showMessages
//* Description  :	Printing the inbox messages
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
void Follower::showMessages() {
	Inbox_.Print();
}

//*********************************************************************************************************
//* function name:	addMessage
//* Description  :	adding a new message
//* Parameters   :	message - the new message to the inbox
//* Return Value :	None
//*********************************************************************************************************
void Follower::addMessage(Message newMessage) {
	Inbox_.Add(newMessage);
}

//*********************************************************************************************************
//* function name:	ReadMessage
//* Description  :	Reading a message of a given id. Returning FAILURE of no message to be fetched
//* Parameters   :	serial - message id
//* Return Value :	SUCCESS or FAILURE
//*********************************************************************************************************
Result Follower::ReadMessage(int messageNum) {
	return Inbox_.ReadMessage(messageNum);
}

//*********************************************************************************************************
//* function name:	SendMessage
//* Description  :	Sending a message with <subject> and <content> to a user with <email>
//* Parameters   :	email - the destination user email
//*					subject - message's subject
//*					content - message's content
//* Return Value :	SUCCESS or FAILURE
//*********************************************************************************************************
Result Follower::SendMessage(string email, string subject, string content) {
	if (checkExists(friends_, email)) {
		Message newMessage((this->email_), subject, content);
		(static_cast<Follower*>(friends_.getValue()))->addMessage(newMessage);
		return SUCCESS;
	}
	return FAILURE;
}

//*********************************************************************************************************
//* function name:	NumUnreadMessages
//* Description  :	returning the number of unread message the follower has
//* Parameters   :	None
//* Return Value :	Number of unread messages (int)
//*********************************************************************************************************
int Follower::NumUnreadMessages() {
	return Inbox_.UnreadSize();
}

//*********************************************************************************************************
//* function name:	AddFriend
//* Description  :	Adding pfollower to the friendlist directly without a request(helper func)
//* Parameters   :	pFollower - a pointer to the follower to add to the friendlist
//* Return Value :	SUCCESS or FAILURE
//*********************************************************************************************************
Result Follower::AddFriend(Follower* pFollower) {
	if (checkExists(friends_, (pFollower->GetEmail())) == true) return FAILURE; // already friends
	if (checkExists(requests_, (pFollower->GetEmail())) == true) requests_.deleteNode();
	friends_.add(pFollower);
	return SUCCESS;
}

//*********************************************************************************************************
//* function name:	checkExists
//* Description  :	checking if a follower with the given email is already in the list(helper func)
//*					*IMPORTANT NOTE*: If finding the follower in the list, the iterator will be on him
//* Parameters   :	list - the list to check in
//*					string - the follower email
//* Return Value :	true or false
//*********************************************************************************************************
bool checkExists(List& list, string email) {
	list.goHead();
	Follower* tmp = static_cast<Follower*>(list.getValue());
	while ((tmp != NULL)) {
		if (tmp->GetEmail().compare(email) == 0) return true;
		list.getNext();
		tmp = static_cast<Follower*>(list.getValue());
	}
	return false; // not found in list
}
