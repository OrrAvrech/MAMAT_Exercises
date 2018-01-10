#include "Teacher.H"
using std::string;
using std::cout;
using std::endl;

Teacher::Teacher(string name, int age, int seniority)
	:Person(name, age)
{
	this->seniority = seniority;
}

int Teacher::getSeniority() const
{
	return this->seniority;
}

void Teacher::Print() const
{
	Person::Print();
	cout << "Seniority : " << this->seniority << endl;
}
