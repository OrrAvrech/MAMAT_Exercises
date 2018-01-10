#include "Person.H"

using std::string;
using std::cout;
using std::endl;

Person::Person(string name, int age) {
	this->name = name;
	this->age = age;
}

string Person::getName() const{
	return this->name;
}

int Person::getAge() const {
	return this->age;
}

void Person::Print() const {
	cout << "Name : " << this->name << endl;
	cout << "Age : " << this->age << endl;
}