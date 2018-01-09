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

double stringToDouble(const string s1,const string s2) {
  
  istringstream istr1(s1);
  istringstream istr2(s2);
  int i; //integer part
  int j; //fraction part
  double a = 0;
  istr1 >> i;
  istr2 >> j;
  a = double(i)+double(j)/1000; //assuming fraction part is alwways 3 digits
  return a;
}

vector<string> tokenize(string line, const char* delim) {
	unsigned int i, j; 
	vector<string> tokens;
	while (!line.empty()) {
		i = line.find_first_not_of(delim);
		j = line.find_first_of(delim, i+1);
		tokens.push_back(line.substr(i, j-i));
		if (j > line.size()-1)
			line = "";
		else
			line = line.substr(j+1,line.size()-j-1);
	}
	return tokens;
}

int main() {

	Office KG_Office; //KinderGarten Office
	const char* delims = " \t\n";
	const char* dotDelim = ".";
	vector<string> tokens , small_tokens;
	string line ,name , phone;
	unsigned int lineNumber = 1;
	int size , age , childMax, seniority;
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
		  if (empty(tokens[1]) || empty(tokens[2]) || empty(tokens[3]) || empty(tokens[4]) || !empty(tokens[5]))
		  {
			  cerr << "Failed - " << line << endl;
			  continue;
		  }
		  size = stringToInt(tokens[1]);
		  small_tokens = tokenize(tokens[2], dotDelim);
		  ratio = stringToDouble(small_tokens[0] , small_tokens[1]);
		  childMax = stringToInt(tokens[3]);
		  age = stringToInt(tokens[4]);
		 // ********************          still missing all the code        ****************************
	  }
	  if (tokens[0] == "removeClass")
	  {
		  if (empty(tokens[1]) || !empty(tokens[2]))
		  {
			  cerr << "Failed - " << line << endl;
			  continue;
		  }
		  age = stringToInt(tokens[1]);
		  if (Office::removeClass(age) == FAILURE)     // ************* need to check in office      *******************
			  cerr << "Failed - " << line << endl;
	  }
	  if (tokens[0] == "addChild") 
	  {
		  if (empty(tokens[1]) || empty(tokens[2]) || empty(tokens[3]) || !empty(tokens[4]))
		  {
			  cerr << "Failed - " << line << endl;
			  continue;
		  }
		  age = stringToInt(tokens[1]);
		  name = tokens[2];
		  phone = tokens[3];
		  if (Office::addChild(age , name , phone) == FAILURE)     // ************* need to check in office      *******************
			  cerr << "Failed - " << line << endl;
	  }
	  if (tokens[0] == "addTeahcer") 
	  {
		  if (empty(tokens[1]) || empty(tokens[2]) || empty(tokens[3]) || !empty(tokens[4]))
		  {
			  cerr << "Failed - " << line << endl;
			  continue;
		  }
		  age = stringToInt(tokens[1]);
		  name = tokens[2];
		  seniority = stringToInt(tokens[3]);
		  if (Office::addTeacher(age, name, seniority) == FAILURE)     // ************* need to check in office      *******************
			  cerr << "Failed - " << line << endl;
	  }
	  if (tokens[0] == "removeChild") 
	  {
		  if (empty(tokens[1]) || !empty(tokens[2]))
		  {
			  cerr << "Failed - " << line << endl;
			  continue;
		  }
		  name = tokens[1];
		  if (Office::removeChild(name) == FAILURE)     // ************* need to check in office      *******************
			  cerr << "Failed - " << line << endl;
	  }
	  if (tokens[0] == "removeTeacher") 
	  {
		  if (empty(tokens[1]) || !empty(tokens[2]))
		  {
			  cerr << "Failed - " << line << endl;
			  continue;
		  }
		  name = tokens[1];
		  if (Office::removeTeacher(name) == FAILURE)     // ************* need to check in office      *******************
			  cerr << "Failed - " << line << endl;
	  }
	  if (tokens[0] == "PrintKindergarten") {
		  if (!empty(tokens[1]))
		  {
			  cerr << "Failed - " << line << endl;
			  continue;
		  }
		  Office::print();
	  }
	  if (tokens[0] == "sickChild") {
		  if (empty(tokens[1]) || !empty(tokens[2]))
		  {
			  cerr << "Failed - " << line << endl;
			  continue;
		  }
		  name = tokens[1];
		  if (Office::setSick(name) == FAILURE)     // ************* need to check in office      *******************
			  cerr << "Failed - " << line << endl;
	  }
	  
	  lineNumber++;
	}
	return 0; 
};
