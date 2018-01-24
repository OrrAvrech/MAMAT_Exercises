#ifndef _MY_SHARED_PTR_H_
#define _MY_SHARED_PTR_H_

#include "Conversation.h"

template <class T>
class MySharedPtr
{
public:
	T * ptr;
	int* counter;
     MySharedPtr()
	{
		this->ptr = new T*;
		this->counter = new int*;
		this->counter = 0;
	}
	~MySharedPtr() 
	{
		if (this->counter == 1)
		{
			delete this->ptr;
			delete this->counter;
		}
		else
			this->counter--;
	}
	T& operator*() { return *ptr; }
	T* operator->() { return ptr; }
	T* operator=(T* new_ptr) 
	{
		this->counter++;
		this->ptr = new_ptr;
	}
	T* get() { return ptr; }
};

#endif // _MY_SHARED_PTR_H_
