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

string Class::getPhone(string childName) const
{
	int i;
	for (i = 0; i < childList_.size(); i++)
	{
		if (childName.compare(childList_[i].getName()) == 0)
			return childList_[i].getPhone();
	}
	string strNotFound = "No Child";
	return strNotFound;
}

void Class::addTeacher(string name, int age, int seniority)
{
	Teacher t(name, age, seniority);
	teacherList_.push_back(t);
}

Result Class::addChild(string name, int age, string phone, bool sick_flag)
{
	// Check if inserting a child is valid
	double afterAddRatio = (childList_.size() + 1) / teacherList_.size();
	if (afterAddRatio > maxRatio_) 
		// Ratio after adding a child should be less than or equal maxRatio
		return FAILURE;
	else if (childList_.size() >= maxChildren_) 
		// Current number of children should be less than maxChildren
		return FAILURE;
	else
	{
		Child c(name, age, phone, sick_flag);
		childList_.push_back(c);
		return SUCCESS;
	}
}

Result Class::removeTeacher(string name)
{
	// Check if removing a teacher is valid
	double afterRemoveRatio = childList_.size() / (teacherList_.size() - 1); // handle the case of teacherList_.size equals 1
	if (afterRemoveRatio > maxRatio_)
		// Ratio after removing a teacher should be less than or equal maxRatio
		return FAILURE;
}


