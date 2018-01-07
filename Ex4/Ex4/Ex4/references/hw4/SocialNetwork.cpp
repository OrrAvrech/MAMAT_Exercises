#include "SocialNetwork.H"
#include <iostream>


//*********************************************************************************************************
//* function name:	SocialNetwork
//* Description  :	Constructor of SocialNetwork class
//* Parameters   :	name - the social network name
//*					password - the admin password for the network
//* Return Value :	None
//*********************************************************************************************************
SocialNetwork::SocialNetwork(string name, string password) : 
	name_(name), password_(password), leaders_(LEADER), followers_(FOLLOWER),connectedtype_(NONE), currentuser_(NULL) {}

//*********************************************************************************************************
//* function name:	~SocialNetwork
//* Description  :	Destructor of SocialNetwork class
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
SocialNetwork::~SocialNetwork() {
	followers_.goHead();
	int n = followers_.getSize();
	
	for (int i = 0; i < n; i++) {
		delete static_cast<Follower*>(followers_.getValue());
		followers_.getNext();
	}
	leaders_.goHead();
	n = leaders_.getSize();
	for (int i = 0; i < n; i++) {
		delete static_cast<Leader*>(leaders_.getValue());
		leaders_.getNext();
	}
}

//*********************************************************************************************************
//* function name:	AdminLogin
//* Description  :	Login for admin
//* Parameters   :	password - password input
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::AdminLogin(string password) {
	if (password.empty())
		cout << ADMIN_LOGIN_FAIL << endl; // no pass entered
	if (password.compare(password_) == 0) {
		connectedtype_ = ADMIN;
		cout << ADMIN_LOGIN_SUCCESS << endl;
	}
	else cout << ADMIN_LOGIN_FAIL << endl; // wrong pass
}

//*********************************************************************************************************
//* function name:	Login
//* Description  :	Login to the network ( Leader of Follower)
//* Parameters   :	email - user's email
//*					password - password
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::Login(string email, string password) {
	Type usertype = NONE;
	// login user type
	if (checkExists(followers_, email) == true) usertype = FOLLOWER;
	if (checkExists(leaders_, email) == true) usertype = LEADER;
	if (usertype != NONE) {
		Follower* activeFollower;
		if (usertype == FOLLOWER) activeFollower = (static_cast<Follower*>(followers_.getValue()));
		else activeFollower = (static_cast<Leader*>(leaders_.getValue()));
		if (activeFollower->isPassword(password)){
			connectedtype_ = usertype;
			currentuser_ = activeFollower;
			cout << LOGIN_SUCCESS << endl;
			return;
		}
	}
	cout << LOGIN_FAIL << endl; 
}

//*********************************************************************************************************
//* function name:	Logout
//* Description  :	Logging out the user
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::Logout() {
	if (connectedtype_ == NONE)
		cout << LOGOUT_FAIL << endl; // no one connected!
	else {
		connectedtype_ = NONE;
		currentuser_ = NULL;
		cout << LOGOUT_SUCCESS << endl;
	}
}

/////////////////////
/// Admin actions ///
/////////////////////

//*********************************************************************************************************
//* function name:	CreateLeader
//* Description  :	Create a leader with the given parameters. Must have a unique email and an admin must
//*					be logged.
//* Parameters   :	name - the leader name
//*					email - the leader meail
//*					password - the leader password
//* Return Value :	
//*********************************************************************************************************
void SocialNetwork::CreateLeader(string name, string email, string password) {
	if ((connectedtype_ != ADMIN) || // admin not logged
		(checkExists(followers_, email) == true) || // follower with the same mail exists
		(checkExists(leaders_, email) == true) // already a leader!
		) {
		cout << CREATE_LEADER_FAIL << endl;
		return;
	}
	Leader* newLeader = new Leader(name, email, password);
	leaders_.add(newLeader);
	cout << CREATE_LEADER_SUCCESS << endl;
}

//*********************************************************************************************************
//* function name:	RemoveFromLists
//* Description  :	Given an email, deletes the user from his friends' lists and all friend requests.
//*					If it's a leader then also remove his followers from following him. (help func)
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::RemoveFromLists(string email, Type type) {
	List *target = (type == LEADER) ? &leaders_ : &followers_;
	target->goHead();
	int n = target->getSize();
	for (int i = 0; i < n; i++) {
		Leader* tmp = static_cast<Leader*>(target->getValue());
		if (tmp->GetEmail().compare(email) != 0) {
			tmp->RemoveFriend(email);
			tmp->RemoveFriendRequest(email);
			if (type == LEADER) tmp->RemoveFollower(email);
		}
		target->getNext();
	}
}

//*********************************************************************************************************
//* function name:	DeleteUser
//* Description  :	Given an email, deletes the user(follower or leader). Afterwards broadcast the news to
//*					all of the friends and leaders of the fallen comarade. Fail if email does not exist 
//*					or admin is not logged in.
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::DeleteUser(string email) {
	if ((connectedtype_ != ADMIN) || // admin not logged
		((checkExists(followers_, email) == false) && (checkExists(leaders_, email) == false))
		// user doesn't exists 
		) {
		cout << DELETE_USER_FAIL << endl;
		return;
	}
	RemoveFromLists(email, FOLLOWER);
	RemoveFromLists(email, LEADER);
	if (checkExists(followers_, email)) { // case Follower
		delete (static_cast<Follower*>(followers_.getValue()));
		followers_.deleteNode(); // iterator should be on the requested node
	}
	if (checkExists(leaders_, email)) { // case Leader
		delete (static_cast<Leader*>(leaders_.getValue()));
		leaders_.deleteNode(); // iterator should be on the requested node
	}
	cout << DELETE_USER_SUCCESS << endl;
}

//////////////////////
/// Leader actions ///
//////////////////////

//*********************************************************************************************************
//* function name:	BroadcastMessage
//* Description  :	Send a message with <subject> and <content> to all followers of the logged Leader
//*					Returns a failure message if not logged in as a Leader
//* Parameters   :	subject - message subject
//*					content - message content
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::BroadcastMessage(string subject, string content) {
	if (connectedtype_ != LEADER) { // not connected as a leader
		cout << BROADCAST_MESSAGE_FAIL << endl;
		return;
	}
	(static_cast<Leader*>(currentuser_))->BroadcastMessageToAll(subject, content);
	cout << BROADCAST_MESSAGE_SUCCESS << endl;
}

//////////////////////////////////////////////
/// Follower actions (also leader actions) ///
//////////////////////////////////////////////

//*********************************************************************************************************
//* function name:	CreateFollower
//* Description  :	Adds a new follower user to the network. Fails if a user with the same email exists
//* Parameters   :	name - the new follower name 
//*					email - the new follower email(Must be unique
//*					password - the new follower password
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::CreateFollower(string name, string email, string password) {
	if ((checkExists(followers_, email) == true) ||
		(checkExists(leaders_, email) == true)){ // user already exists 
		cout << CREATE_FOLLOWER_FAIL << endl;
		return;
	}
	Follower* newFollower = new Follower(name, email, password);
	followers_.add(newFollower);
	cout << CREATE_FOLLOWER_SUCCESS << endl;
}

//*********************************************************************************************************
//* function name:	ShowFriendRequests
//* Description  :	Showing the friend requests of the logged user
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::ShowFriendRequests() {
	if ((connectedtype_ != LEADER) && (connectedtype_ != FOLLOWER)) {
		cout << SHOW_FRIEND_REQUESTS_FAIL << endl;
		return;
	}
	(static_cast<Follower*>(currentuser_))->showFriendRequests();
}

//*********************************************************************************************************
//* function name:	ShowFriendList
//* Description  :	Showing the friend list of the logged user
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::ShowFriendList() {
	if ((connectedtype_ != LEADER) && (connectedtype_ != FOLLOWER)) {
		cout << SHOW_FRIEND_LIST_FAIL << endl;
		return;
	}
	(static_cast<Follower*>(currentuser_))->showFriendsList();
}

//*********************************************************************************************************
//* function name:	SendFriendRequest
//* Description  :	Sending a friend request to your (hopefully) new amigo
//* Parameters   :	friendEmail - the friend's email whom you send the request to
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::SendFriendRequest(string friendEmail) {
	if (((connectedtype_ != LEADER) && (connectedtype_ != FOLLOWER)) || // A user is not connected
		((checkExists(followers_, friendEmail) == false) &&
		(checkExists(leaders_, friendEmail) == false)) || // Your friend is imaginary
		((static_cast<Follower*>(currentuser_))->GetEmail().compare(friendEmail) == 0) // trying to become afriend with yourself
		) { 
		cout << SEND_FRIEND_REQUEST_FAIL << endl;
		return;
	}
	Follower* currentuser = static_cast<Follower*>(currentuser_);
	if (checkExists(followers_, friendEmail)) { // case follower
		Follower* tmp = static_cast<Follower*>(followers_.getValue()); // iterator should be on the friend
		if (tmp->addFriendRequest(currentuser))	cout << SEND_FRIEND_REQUEST_SUCCESS << endl;
		else cout << SEND_FRIEND_REQUEST_FAIL << endl;
	}
	else if (checkExists(leaders_, friendEmail)) { // case leader
		Leader* tmp = static_cast<Leader*>(leaders_.getValue()); // iterator should be on the friend
		if (tmp->addFriendRequest(currentuser))	cout << SEND_FRIEND_REQUEST_SUCCESS << endl;
		else cout << SEND_FRIEND_REQUEST_FAIL << endl;
	}
	else cout << SEND_FRIEND_REQUEST_FAIL << endl; // friend request already exists
}

//*********************************************************************************************************
//* function name:	AcceptFriendRequest
//* Description  :	Accept a friend request from the user with <email>. Removes your own request if exists
//*					Fail if no such request.
//* Parameters   :	friendEmail - the friend's email whom you accept his friendship
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::AcceptFriendRequest(string friendEmail) {
	if (((connectedtype_ != LEADER) && (connectedtype_ != FOLLOWER))){ // A user is not connected
		cout << ACCEPT_FRIEND_REQUEST_FAIL << endl;
		return;
	}
	Follower* currentuser = static_cast<Follower*>(currentuser_);
	if (currentuser->AcceptFriendRequest(friendEmail)) {
		// now add the current user as a friend as well		
		if (checkExists(followers_, friendEmail)) { // case the new friend is a follower
			Follower* tmp = static_cast<Follower*>(followers_.getValue());
			tmp->AddFriend(currentuser);
			cout << ACCEPT_FRIEND_REQUEST_SUCCESS << endl;
		}
		if (checkExists(leaders_, friendEmail)) { // case the new friend is a leader
			Leader* tmp = static_cast<Leader*>(leaders_.getValue());
			tmp->AddFriend(currentuser);
			cout << ACCEPT_FRIEND_REQUEST_SUCCESS << endl;
		}
		
	}
	else cout << ACCEPT_FRIEND_REQUEST_FAIL << endl; // no friend request
}

//*********************************************************************************************************
//* function name:	RemoveFriend
//* Description  :	Removing the user with the given email from the logged user friends list
//* Parameters   :	friendEmail - the removed friend email
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::RemoveFriend(string friendEmail) {
	if (((connectedtype_ != LEADER) && (connectedtype_ != FOLLOWER))) { // A user is not connected
		cout << REMOVE_FRIEND_FAIL << endl;
		return;
	}
	Follower* currentuser = static_cast<Follower*>(currentuser_);
	string email = currentuser->GetEmail();
	if (currentuser->RemoveFriend(friendEmail) == SUCCESS) {
		// friend removed from OWN list, now remove yourself from his friends list
		if (checkExists(followers_, friendEmail)) {// case the ex-friend is a follower
			Follower* tmp = static_cast<Follower*>(followers_.getValue());
			tmp->RemoveFriend(email);
			cout << REMOVE_FRIEND_SUCCESS << endl;
		}
		if (checkExists(leaders_, friendEmail)) {// case the ex-friend is a leader
			Leader* tmp = static_cast<Leader*>(leaders_.getValue());
			tmp->RemoveFriend(email);
			cout << REMOVE_FRIEND_SUCCESS << endl;
		}
	}
	else cout << REMOVE_FRIEND_FAIL << endl;
}

//*********************************************************************************************************
//* function name:	ShowMessageList
//* Description  :	If a user is logged then prints his messages. If not then prints FAIL message
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::ShowMessageList() {
	if (((connectedtype_ != LEADER) && (connectedtype_ != FOLLOWER))) { // A user is not connected
		cout << SHOW_MESSAGE_LIST_FAIL << endl;
		return;
	}
	(static_cast<Follower*>(currentuser_))->showMessages();
}

//*********************************************************************************************************
//* function name:	ReadMessage
//* Description  :	Reads a messages of a given serial number
//* Parameters   :	messageNum - message serial number
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::ReadMessage(int messageNum) {
	if (((connectedtype_ != LEADER) && (connectedtype_ != FOLLOWER)) || // A user is not connected
		(static_cast<Follower*>(currentuser_))->ReadMessage(messageNum) == FAILURE) { 
		cout << READ_MESSAGE_FAIL << endl;
		return;
	}
}

//*********************************************************************************************************
//* function name:	SendMessage
//* Description  :	Sending a message with <subject> and <content> to a user with <email>
//* Parameters   :	email - the destination user email
//*					subject - message's subject
//*					content - message's content
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::SendMessage(string email, string subject, string content) {
	if (((connectedtype_ != LEADER) && (connectedtype_ != FOLLOWER))) { // A user is not connected
		cout << SEND_MESSAGE_FAIL << endl;
		return;
	}
	if ((static_cast<Follower*>(currentuser_))->SendMessage(email, subject, content) == SUCCESS )
		cout << SEND_MESSAGE_SUCCESS << endl;
	else
		cout << SEND_MESSAGE_FAIL << endl;
}

//*********************************************************************************************************
//* function name:	Follow
//* Description  :	Adding the logged user to the followers list of a leader. Fail if a user is not logged
//*					(Follower or Leader) or there is no leader with the given <leaderemail> or the user is
//*					already following the leader.
//* Parameters   :	leaderEmail - the email of the leader you want to follow 
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::Follow(string leaderEmail){
	if ((connectedtype_ != LEADER) && (connectedtype_ != FOLLOWER)){// A user is not connected
		cout << FOLLOW_FAIL << endl;
		return;
	}
	if (checkExists(leaders_, leaderEmail) == true) {
		Follower* currentuser = static_cast<Follower*>(currentuser_); // the iterator should be on the leader
		if ((static_cast<Leader*>(leaders_.getValue()))->AddFollower(currentuser)) {
			cout << FOLLOW_SUCCESS << endl;
			return;
		}
	}
	cout << FOLLOW_FAIL << endl;// No such leader or already following
}


///////////////////////
/// General actions ///
///////////////////////

//*********************************************************************************************************
//* function name:	FindUser
//* Description  :	print all the users that have the wanted partial name 
//* Parameters   :	partialName - a string of a partial name
//* Return Value :	None
//*********************************************************************************************************
void SocialNetwork::FindUser(string partialName)
{
	cout << "Followers:" << endl;
	// Loop over all followers in network
	followers_.goHead();
	for (int i = 0; i<followers_.getSize(); ++i)
	{
		Follower* curFollower = static_cast<Follower*>(followers_.getValue());
		if (curFollower->GetName().find(partialName) != string::npos)
			cout << i + 1 << ") " << curFollower->GetName() << ": " << curFollower->GetEmail() << endl;
		followers_.getNext();
	}

	cout << "Leaders:" << endl;
	// Loop over all leaders in network
	leaders_.goHead();
	for (int i = 0; i<leaders_.getSize(); ++i)
	{
		Leader* curLeader = static_cast<Leader*>(leaders_.getValue());
		if (curLeader->GetName().find(partialName) != string::npos)
			cout << i + 1 << ") " << curLeader->GetName() << ": " << curLeader->GetEmail() << endl;
		leaders_.getNext();
	}
}





