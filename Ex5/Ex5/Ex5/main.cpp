#include <iostream>
#include <exception>
#include <string>
#include "ChatNet.h"
using namespace std;

int main() {
	string line;
	ChatNet MamatChat("MamatChat", "Admin", "1234");
	while (!cin.eof())
	{
		try
		{
			getline(cin, line);
			MamatChat.Do(line);
		}
		catch (BackSignal&) // Exit
		{
			break;
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "Unexpected Error" << endl;
			return 1;
		}
	}
	return 0;
};
