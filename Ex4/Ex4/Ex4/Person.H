#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include <iostream>

using std::string;

class Person {
public:
	Person(string name, int age);
  // do i need a destructor for string and int
	string getName() const;
	int getAge() const;
	void Print();
private:
	string name;
	int age;
};

#endif
