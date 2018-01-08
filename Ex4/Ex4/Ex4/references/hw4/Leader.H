#ifndef _LEADER_H_
#define _LEADER_H_

#include "defs.H"
#include "Follower.H"
#include "Lists.H"

class Leader : public Follower {
public:
	Leader(string name, string email, string password);
	~Leader();
	Result AddFollower(Follower* pFollower);
	Result RemoveFollower(string email);
	int GetNumOfFollower() const;
	void BroadcastMessageToAll(string subject, string content);
protected:
	List followlist_;
};

#endif
