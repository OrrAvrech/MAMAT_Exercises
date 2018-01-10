#ifndef _CHILD_H_
#define _CHILD_H_
#include "Person.H"
#include "defs.H"
#include <string>
#include <iostream>

using std::string;

class Child : public Person {
public:
	Child(string name, int age, string phone, bool sick_flag);
	string getPhone() const;
	void setPhone(string new_phone);
	Result setSick();
	void Print() const;
private:
	string name;
	int age;
	string phone;
	bool sick_flag;
};

#endif
