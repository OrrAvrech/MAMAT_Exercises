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

Result Office::addTeacher(string name, int age, int seniority)
{
	if (busy_ == true)
		return FAILURE;
	vector<Class>::iterator i, minTeacherClass, maxRatioClass;
	unsigned minTeachers;
	double maxRatio;
	bool ratio_flag = 0;
	for (i = classList_.begin(); i < classList_.end(); i++)
	{
		if ((*i).getNumTeachers() == 0 )
		{
			// Empty classes - add teacher by order Of classes
			(*i).addTeacher(name, age, seniority);
			return SUCCESS;
		}
	}
	for (i = classList_.begin(); i < classList_.end(); i++)
	{
		if (i == classList_.begin())
		{
			minTeachers = (*i).getNumTeachers();
			minTeacherClass = i;
			maxRatio = (*i).getRatio();
			maxRatioClass = i;
		}
		if ((*i).getRatio() != 0)
		{
			ratio_flag = 1;
		}
		if ((*i).getNumTeachers() < minTeachers)
		{
			minTeachers = (*i).getNumTeachers();
			minTeacherClass = i;
		}
		if ((*i).getRatio() > maxRatio)
		{
			maxRatio = (*i).getRatio();
			maxRatioClass = i;
		}

	}
	if (ratio_flag == 0)
	{
		(*minTeacherClass).addTeacher(name, age, seniority);
		return SUCCESS;
	}
	else
	{
		(*maxRatioClass).addTeacher(name, age, seniority);
		return SUCCESS;
	}
}

Result Office::removeChild(string name)
{
	Result r;
	vector<Class>::iterator i;
	if (busy_ == true && name.compare(sickChildName_) != 0)    // Busy and not removing the sick child
		return FAILURE;
	else if (busy_ == true && name.compare(sickChildName_) == 0)  // removing the sick child
	{
		for (i = classList_.begin(); i < classList_.end(); i++)
		{
			r = ((*i).removeChild(name));
			if (r == SUCCESS)
			{
				busy_ = false;
				return r;
			}
		}
		return FAILURE;
	}
	else // normal child removal
	{
		for (i = classList_.begin(); i < classList_.end(); i++)
		{
			r =  ((*i).removeChild(name));
			if (r == SUCCESS)
				return r;
		}
		return FAILURE;
	}
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
		if ((*i).getAge() == age)
		{
			i = classList_.erase(i);
			// delete? TODO
			return SUCCESS;
		}
	}
	return FAILURE;
}

Result Office::reportSick(string name)
{
	if (busy_ == true)
		return FAILURE;
	vector<Class>::iterator i;
	for (i = classList_.begin(); i < classList_.end(); i++)
	{
		string phoneNum = (*i).getPhone(name);
		if (phoneNum.size() == 10 && (phoneNum.substr(0, 2)).compare("05") == 0)
		{
			if ((*i).setSickChild(name) == SUCCESS)
			{
				busy_ = true;
				sickChildName_.assign(name);
				cout << "Reporting sick child :" << endl;
				cout << "Name : " << sickChildName_ << endl;
				cout << "Parent's phone number : " << phoneNum << endl;
				return SUCCESS;
			}
		}
	}
	return FAILURE;
}

void Office::print() const
{
	cout << "Printing office status : " << endl;
	cout << "========================" << endl;
	cout << "Number : 1" << endl;
	cout << "Size : 20 square meters" << endl;
	cout << "Is Occupied : " << std::boolalpha << occupied_ << endl;
	cout << "Office is busy : " << std::boolalpha << busy_ << endl;
	if(busy_)
		cout << "Sick child : " << sickChildName_ << endl;
	cout << endl;

	// vector<Class>::iterator i;
	unsigned int i;
	for (i = 0; i < classList_.size(); i++)
	{
		classList_[i].print();
	}

}

