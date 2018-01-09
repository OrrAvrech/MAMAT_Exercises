#ifndef _CLASS_H_
#define _CLASS_H_

#include <string>
#include <iostream>
#include <vector>
#include "defs.H"
#include "Room.H"
#include "Child.H"
#include "Teacher.H"

using std::string;
using std::vector;

class Class : public Room{
public:
	// Constructor
	Class(unsigned int num, unsigned int size, double maxRatio, unsigned int maxChildren, unsigned int ageChildren);

	// Methods
	unsigned int getNumTeachers() const;
	unsigned int getAge() const;
	double getRatio() const;
	string getPhone(string childName) const;
	void addTeacher(string name, int age, int seniority);
	Result addChild(string name, int age, string phone, bool sick_flag);
	Result removeTeacher(string name);
	Result removeChild(string name);
	Result setSickChild(string name);
	void print() const;

private:
	double maxRatio_;
	unsigned int maxChildren_;
	unsigned int ageChildren_;
	vector<Child> childList_;
	vector<Teacher> teacherList_;
};

#endif
