#include "Office.H"
#include "defs.H"
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::boolalpha;

Office::Office() : Room(1, 20)
{
	occupied_ = true;
	busy_ = false;
}

Result Office::addClass(unsigned int size, double maxRatio, unsigned int maxChildren, unsigned int ageChildren)
{
	if (busy_ == true)
		return FAILURE;
	unsigned int classNum;
	classNum = classList_.size() + 2;
	vector<Class>::iterator i;
	for (i = classList_.begin(); i < classList_.end(); i++)
	{
		if ((*i).getAge() == ageChildren)
			// Age already exists in class list
			return FAILURE;
	}
	Class newClass(classNum, size, maxRatio, maxChildren, ageChildren);
	classList_.push_back(newClass);
	return SUCCESS;
}

Result Office::addChild(string name, int age, string phone, bool sick_flag)
{
	if (busy_ == true)
		return FAILURE;
	vector<Class>::iterator i;
	for (i = classList_.begin(); i < classList_.end(); i++)
	{
		if ((*i).getAge() == age)
			return ((*i).addChild(name, age, phone, sick_flag));
	}
	return FAILURE; // Child's age does not exist in classList
}

Result Office::addTeacher(string name, int age, int seniority) //TODO
{
	if (busy_ == true)
		return FAILURE;
	vector<Class>::iterator i;
	for (i = classList_.begin(); i < classList_.end(); i++)
	{
		if ((*i).getNumTeachers() == 0 || ((*i).getRatio == 0 && (*i).getNumTeachers != 0))
		{
			// Empty classes - add teacher by order
			(*i).addTeacher(name, age, seniority);
			return SUCCESS;
		}
	}
}

Result Office::removeChild(string name)
{
	if (busy_ == true && name.compare(sickChildName_) != 0)
		// Busy and not removing the sick child
		return FAILURE;

	// Any other case: ~busy or (busy + removing sick child)
	vector<Class>::iterator i;
	for (i = classList_.begin(); i < classList_.end(); i++)
		return ((*i).removeChild(name));
}

Result Office::removeTeacher(string name)
{
	if (busy_ == true)
		return FAILURE;
	vector<Class>::iterator i;
	for (i = classList_.begin(); i < classList_.end(); i++)
		return ((*i).removeTeacher(name));
}

Result Office::removeClass(unsigned int age)
{
	if (busy_ == true)
		return FAILURE;
	vector<Class>::iterator i;
	for (i = classList_.begin(); i < classList_.end(); i++)
	{
		if ((*i).getAge == age)
		{
			i = classList_.erase(i);
			// delete? TODO
			return SUCCESS;
		}
	}
	return FAILURE;
}

void Office::reportSick(string name)
{
	if (busy_ == true)
		return;
	vector<Class>::iterator i;
	for (i = classList_.begin(); i < classList_.end(); i++)
	{
		string phoneNum = (*i).getPhone(name);
		if (phoneNum.size() == 10 && (phoneNum.substr(0, 2)).compare("05") == 0)
		{
			if ((*i).setSickChild == SUCCESS)
			{
				busy_ = true;
				sickChildName_.assign(name);
				cout << "Reporting sick child :" << endl;
				cout << "Name : " << sickChildName_ << endl;
				cout << "Parent's phone number : " << phoneNum << endl;
			}
		}
		else
			return;
	}
}

void Office::print() const
{
	//TODO
}

