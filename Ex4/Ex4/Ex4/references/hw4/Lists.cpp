#include<iostream>
#include "Lists.H"

//*********************************************************************************************************
//* function name:	List
//* Description  :	Constructor of list class
//* Parameters   :	type - type of list(Follower, Leader or Message)
//* Return Value :	None
//*********************************************************************************************************
List::List(Type type) : type_(type), head_(NULL), iterator_(NULL),size_(0) {};

//*********************************************************************************************************
//* function name:	~List
//* Description  :	Destructor of list class
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
List::~List() {
	while (head_ != NULL) {
		iterator_ = head_->next;
		delete head_;
		head_ = iterator_;
	}
}

//*********************************************************************************************************
//* function name:	goHead
//* Description  :	setting the iterator on the head of the list
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
void List::goHead() {
	iterator_ = head_;
}

//*********************************************************************************************************
//* function name:	add
//* Description  :	adding a new data node to the head of the list
//* Parameters   :	data - a pointer to the added data
//* Return Value :	SUCCESS or FAILURE 
//*********************************************************************************************************
Result List::add(void* data) {
	if (data == NULL) return FAILURE; // no data
	Node* tmp = head_;
	head_ = new Node;
	head_->pFollower = NULL;
	head_->pLeader = NULL;
	head_->pMessage = NULL;
	switch (type_)
	{
	case FOLLOWER:	head_->pFollower = (Follower*)data; 
					break;
	case LEADER:	head_->pLeader = (Leader*)data; 
					break;
	case MESSAGE:	head_->pMessage = (Message*)data; 
					break;
	}
	head_->next = tmp;
	size_++;
	iterator_ = head_;
	return SUCCESS;	
}

//*********************************************************************************************************
//* function name:	deleteNode
//* Description  :	Delete the node the iterator points at. For illegal iterator return FAILURE
//* Parameters   :	None
//* Return Value :	SUCCESS or FAILURE
//*********************************************************************************************************
Result List::deleteNode() {
	if (iterator_ == NULL) return FAILURE; // illegal iterator_
	if (iterator_ == head_) { // case head_ of the list
		iterator_ = head_->next;
		delete head_;
		head_ = iterator_;
		size_--;
		return SUCCESS;
	}
	Node* tmp = head_;
	while (tmp->next != iterator_)
		tmp = tmp->next; // go to node before the requested one
	tmp->next = iterator_->next;
	delete iterator_;
	iterator_ = head_;
	size_--;
	return SUCCESS;
}

//*********************************************************************************************************
//* function name:	getNext
//* Description  :	Moves the iterator to the next item on the list. Return FAILURE if the iterator is illegal
//* Parameters   :	None
//* Return Value :	SUCCESS or FAILURE 
//*********************************************************************************************************
Result List::getNext() {
	if (iterator_ == NULL) return FAILURE;
	iterator_ = iterator_->next;
	return SUCCESS;
}

//*********************************************************************************************************
//* function name:	getValue
//* Description  :	Returns a pointer to the data in the node that the iterator is currently pointing at
//* Parameters   :	None
//* Return Value :	a pointer to the data
//*********************************************************************************************************
void* List::getValue() const {
	if (iterator_ == NULL) return NULL;
	switch (type_){
	case FOLLOWER:	return iterator_->pFollower;
	case LEADER:	return iterator_->pLeader;
	case MESSAGE:	return iterator_->pMessage;
	}
	return NULL;
}
//*********************************************************************************************************
//* function name:	getSize
//* Description  :	Returns the number of items in the list
//* Parameters   :	None
//* Return Value :	size_ (int)
//*********************************************************************************************************
int List::getSize() const{
	return size_;
}