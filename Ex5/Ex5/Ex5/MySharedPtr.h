#ifndef _MY_SHARED_PTR_H_
#define _MY_SHARED_PTR_H_

template <class T>
class MySharedPtr
{
public:
	// Constructors
	MySharedPtr(T* ptr)
	{
		ptr_ = ptr;
		counter_ = new int(1);
	}
	MySharedPtr(const MySharedPtr<T>& pNew)
	{
		ptr_ = pNew.ptr_;
		counter_ = pNew.counter_;
		(*counter_)++;
	}
	// Destructor
	~MySharedPtr()
	{
		if (counter_ != nullptr)
		{
			(*counter_)--;
			if (*counter_ == 0)
			{
				delete ptr_;
				delete counter_;
			}
		}
	}
	// Methods
	T& operator*() { return *ptr_; } // returning a class T --> return by reference
	T* operator->() { return ptr_; } // returning a pointer to T --> return by address
	MySharedPtr<T>& operator=(const MySharedPtr<T>& pNew)
	{   // passing a read-only class MySharedPtr --> pass by reference
		ptr_ = pNew.ptr_;
		counter_ = pNew.counter_;
		(*counter_)++;
		return *this;
		// returning a class MySharedPtr --> return by reference
	}
	T* get() { return ptr_; }

private:
	T * ptr_;
	int* counter_;
};

#endif // _MY_SHARED_PTR_H_
