#ifndef _TEACH_H_
#define _TEACH_H_
#include "Person.H"
#include <string>
#include <iostream>

class Teacher : public Person{
public:
	Teacher(string name, int age, int seniority);
	int getSeniority() const;
	void Print() const;
private:
	string name;
	int age;
	int seniority;
};

#endif
