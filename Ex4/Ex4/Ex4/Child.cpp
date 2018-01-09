#include "Child.H"

using std::cout;
using std::endl;
using std::boolalpha;

Child::Child(string name, int age, string phone, bool sick_flag = false) 
	:Person(name, age)
{
	this->phone = phone;
	this->sick_flag = sick_flag;
}

string Child::getPhone() const
{
	return this->phone;
}

void Child::setPhone(string new_phone)
{
	this->phone = new_phone;
}

Result Child::setSick()
{
	if (this->sick_flag == true) return FAILURE;
	this->sick_flag = true;
	return SUCCESS;
}

void Child::Print() const
{
	Person::Print();
	cout << "Parent's Phone : " << this->phone << endl;
	cout << "Is sick : " << sick_flag << endl;
}
