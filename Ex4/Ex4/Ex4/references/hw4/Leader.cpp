#include<iostream>
#include "Leader.H"

using namespace std;

//*********************************************************************************************************
//* function name:	Leader
//* Description  :	Constructor of Leader class
//* Parameters   :	name - name of the Leader
//*					email - email of the Leader(must be UNIQUE)
//*					password - password of the Leader
//* Return Value :	None
//*********************************************************************************************************
Leader::Leader(string name, string email, string password):
	Follower(name, email, password), followlist_(FOLLOWER) {};

//*********************************************************************************************************
//* function name:	~Leader
//* Description  :	Destructor of Leader class
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
Leader::~Leader() {}

//*********************************************************************************************************
//* function name:	AddFollower
//* Description  :	Adding a follower to the leader. If already exists return FAILURE
//* Parameters   :	pFollower - a pointer to the follower
//* Return Value :	SUCCESS or FAILURE
//*********************************************************************************************************
Result Leader::AddFollower(Follower* pFollower) {
	if (checkExists(followlist_, pFollower->GetEmail())) return FAILURE; // Already following
	return followlist_.add(pFollower);
}

//*********************************************************************************************************
//* function name:	RemoveFollower
//* Description  :	Removing a follower from the leader's list. If does not exists return FAILURE
//* Parameters   :	pFollower - a pointer to the follower
//* Return Value :	SUCCESS or FAILURE
//*********************************************************************************************************
Result Leader::RemoveFollower(string email) {
	if (checkExists(followlist_, email) == false ) return FAILURE; // not following
	return followlist_.deleteNode(); // iterator should be on the requested follower to be removed
}

//*********************************************************************************************************
//* function name:	GetNumOfFollower
//* Description  :	returning the number of followers the leader has
//* Parameters   :	None
//* Return Value :	Number of followers (int)
//*********************************************************************************************************
int Leader::GetNumOfFollower() const {
	return followlist_.getSize();
}

//*********************************************************************************************************
//* function name:	BroadcastMessageToAll
//* Description  :	Broadcasting all followers a message with <subject> and <content>
//* Parameters   :	subject - message's subject
//*					content - message's content
//* Return Value :	None
//*********************************************************************************************************
void Leader::BroadcastMessageToAll(string subject, string content) {
	Message newMessage(this->email_, subject, content);
	followlist_.goHead();
	int i;
	int n = followlist_.getSize();
	for (i = 0; i < n; i++) {
		(static_cast<Follower*>(followlist_.getValue()))->addMessage(newMessage);
		followlist_.getNext();
	}
}
