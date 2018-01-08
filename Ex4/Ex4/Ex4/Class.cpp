#include "Class.H"
#include "defs.H"
#include <iostream>

using std::cout;
using std::endl;

Class::Class(unsigned int num, unsigned int size, double maxRatio, unsigned int maxChildren, unsigned int ageChildren) :
	Room(num, size), maxRatio_(maxRatio), maxChildren_(maxChildren), ageChildren_(ageChildren) {}

unsigned int Class::getNumTeachers() const { return teacherList_.size(); }

unsigned int Class::getAge() const { return ageChildren_; }

double Class::getRatio() const
{
	if (teacherList_.size() == 0)
		return 0;
	else
		return (childList_.size() / teacherList_.size());
}

string Class::getPhone() const


