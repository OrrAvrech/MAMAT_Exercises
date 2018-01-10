#ifndef _OFFICE_H_
#define _OFFICE_H_

#include <string>
#include <vector>

#include "Room.H"
#include "defs.H"
#include "Class.H"

using std::string;
using std::vector;

class Office : public Room {
public:
	// Constructor
	Office();

	// Methods
	Result addClass(unsigned int size, double maxRatio, unsigned int maxChildren, unsigned int ageChildren);
	Result addChild(string name, int age, string phone, bool sick_flag);
	Result addTeacher(string name, int age, int seniority);
	Result removeChild(string name);
	Result removeTeacher(string name);
	Result removeClass(unsigned int age);
	void reportSick(string name);
	void print() const;

private:
	bool busy_;
	string sickChildName_;
	vector<Class> classList_;
};

#endif
