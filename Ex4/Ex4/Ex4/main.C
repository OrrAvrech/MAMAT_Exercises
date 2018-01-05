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
	vector<string> tokens;
	string line;
	unsigned int lineNumber = 1;

	while (!cin.eof()) {
	  getline(cin, line);
	  tokens = tokenize(line, delims);
	  if (tokens.size() == 0) { //empty line
	    continue;
	  }
	  
	  if (tokens[0] == "addClass") {
	    //Add your code here ...
	  }
	  if (tokens[0] == "removeClass") {
	    //Add your code here ...
	  }
	  if (tokens[0] == "addChild") {
	    //Add your code here ...
	  }
	  
	  if (tokens[0] == "addTeahcer") {
	    //Add your code here ...
	  }
	  
	  if (tokens[0] == "removeChild") {
	    //Add your code here ...
	  }
	  
	  if (tokens[0] == "removeTeacher") {
	    //Add your code here ...
	  }
	  
	  if (tokens[0] == "PrintKindergarten") {
	    //Add your code here ...
	  }
	  
	  if (tokens[0] == "sickChild") {
	    //Add your code here ...
	  }
	  
	  lineNumber++;
	}
	return 0; 
};
