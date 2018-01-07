#ifndef _LISTS_H_
#define _LISTS_H_

#include "defs.H"

class Follower;
class Leader;
class Message;

struct Node {
	Follower* pFollower;
	Leader* pLeader;
	Message* pMessage;
	Node* next;
};

class List {
public:
	List(Type type);
	~List();
	void goHead();
	Result add(void* data);
	Result deleteNode();
	Result getNext();
	void* getValue() const;
	int getSize() const;

private:
	Type type_;
	Node* head_;
	Node* iterator_;
	int size_;
};

#endif
