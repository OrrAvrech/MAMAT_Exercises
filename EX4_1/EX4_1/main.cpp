#include "Office.H"
#include "Class.H"
#include "Child.H"
#include "Teacher.H"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>


using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::istringstream;

int stringToInt(const string s) {
	istringstream istr(s);
	int i = 0;
	istr >> i;
	return i;
}

double stringToDouble(const string s1, const string s2) {

	istringstream istr1(s1);
	istringstream istr2(s2);
	int i; //integer part
	int j; //fraction part
	double a = 0;
	istr1 >> i;
	istr2 >> j;
	a = double(i) + double(j) / 1000; //assuming fraction part is alwways 3 digits
	return a;
}

vector<string> tokenize(string line, const char* delim) {
	unsigned int i, j;
	vector<string> tokens;
	while (!line.empty()) {
		i = line.find_first_not_of(delim);
		j = line.find_first_of(delim, i + 1);
		tokens.push_back(line.substr(i, j - i));
		if (j > line.size() - 1)
			line = "";
		else
			line = line.substr(j + 1, line.size() - j - 1);
	}
	return tokens;
}


int main()
{
	Office KG_Office; //KinderGarten Office
	const char* delims = " \t\n";
	const char* dotDelim = ".";
	vector<string> tokens, small_tokens;
	string line, name, phone;
	unsigned int lineNumber = 1;

	int size, age, childMax, seniority;
	double ratio;
	while (!cin.eof()) {
		getline(cin, line);
		tokens = tokenize(line, delims);
		if (tokens.size() == 0) //empty line
		{
			continue;
		}
		if (tokens[0] == "addClass")
		{
			if (tokens.size() != 5)
			{
				cerr << "Failed - " << line << endl;
				continue;
			}
			size = stringToInt(tokens[1]);
			small_tokens = tokenize(tokens[2], dotDelim);
			if (small_tokens.size() != 2)
			{
				cerr << "Failed - " << line << endl;
				continue;
			}
			ratio = stringToDouble(small_tokens[0], small_tokens[1]);
			childMax = stringToInt(tokens[3]);
			age = stringToInt(tokens[4]);
			KG_Office.addClass(size, ratio, childMax, age);
		}
		if (tokens[0] == "removeClass")
		{
			if (tokens.size() != 2)
			{
				cerr << "Failed - " << line << endl;
				continue;
			}
			age = stringToInt(tokens[1]);
			if (KG_Office.removeClass(age) == FAILURE) 
				cerr << "Failed - " << line << endl;
		}
		if (tokens[0] == "addChild")
		{
			if (tokens.size() != 4)
			{
				cerr << "Failed - " << line << endl;
				continue;
			}
			age = stringToInt(tokens[1]);
			name = tokens[2];
			phone = tokens[3];
			if (KG_Office.addChild(name, age, phone) == FAILURE) 
				cerr << "Failed - " << line << endl;
		}
		if (tokens[0] == "addTeacher")
		{
			if (tokens.size() != 4)
			{
				cerr << "Failed - " << line << endl;
				continue;
			}
			age = stringToInt(tokens[1]);
			name = tokens[2];
			seniority = stringToInt(tokens[3]);
			if (KG_Office.addTeacher(name, age, seniority) == FAILURE)   
				cerr << "Failed - " << line << endl;
		}
		if (tokens[0] == "removeChild")
		{
			if (tokens.size() != 2)
			{
				cerr << "Failed - " << line << endl;
				continue;
			}
			name = tokens[1];
			if (KG_Office.removeChild(name) == FAILURE)  
				cerr << "Failed - " << line << endl;
		}
		if (tokens[0] == "removeTeacher")
		{
			if (tokens.size() != 2)
			{
				cerr << "Failed - " << line << endl;
				continue;
			}
			name = tokens[1];
			if (KG_Office.removeTeacher(name) == FAILURE)  
				cerr << "Failed - " << line << endl;
		}
		if (tokens[0] == "PrintKindergarten")
		{
			if (tokens.size() != 1)
			{
				cerr << "Failed - " << line << endl;
				continue;
			}
			KG_Office.print();
		}
		if (tokens[0] == "sickChild")
		{
			if (tokens.size() != 2)
			{
				cerr << "Failed - " << line << endl;
				continue;
			}
			name = tokens[1];
			if (KG_Office.reportSick(name) == FAILURE)    
				cerr << "Failed - " << line << endl;
		}
		lineNumber++;
	}
	return 0;
}



//#include "Room.H"

//int main() {

	//Room r(15, 60);
	//r.print();
	//r.setOccupy();
	//r.print();

	//Class c(2, 40, 3.25, 20, 1);
	//c.setOccupy();
	//c.addTeacher("Michle", 45, 5);
	//c.addTeacher("Sarah", 48, 5);
	//c.addChild("Tom", 3, "05056", true);
	//c.removeTeacher("Bla");
	//c.removeTeacher("Sarah");
	//c.print();
	//c.removeTeacher("Michle");
	//c.print();
	//return 0;
//}

