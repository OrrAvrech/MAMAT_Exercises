#ifndef _MY_SHARED_PTR_H_
#define _MY_SHARED_PTR_H_

template <class T>
class MySharedPtr
{
	T* ptr;
	int* counter;
public:
	MySharedPtr(T* p = 0) : ptr(NULL) , counter(NULL) 
	{
		if (p.ptr)
		{
			this->ptr = p.ptr;
			this->counter = p.counter;
			counter++;
		}
		else
		{
			this->ptr = new T*;
			this->counter = new int*;
			this->counter = 1;
		}
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
	T& MySharedPtr::operator*() { return *ptr; }
	T* MySharedPtr::operator->() { return ptr; }
	T* MySharedPtr::opertator=(MySharedPtr new_ptr)
	{
		this->counter++;
		new_ptr->counter = this->counter;
		new_ptr->ptr = this->ptr;
	}
	T* get() { return ptr; }
};

#endif // _MY_SHARED_PTR_H_
