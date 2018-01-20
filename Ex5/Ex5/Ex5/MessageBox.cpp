#include "MessageBox.h"






//Interface




void MessageBox::VrtDo(string cmdLine, string activeUsrName)
{
	size_t idx;
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	if (cmdLineTokens[0] == "New" && cmdLineTokens.size() > 1) // New
	{
		// add code here
	}
	else if (cmdLineTokens[0] == "Open" && cmdLineTokens.size() == 2) // Open
	{
		// add code here
	}
	else if (cmdLineTokens[0] == "Delete" && cmdLineTokens.size() == 2) // Delete
	{
		// add code here
	}
	else if (cmdLineTokens[0] == "Search" && cmdLineTokens.size() == 2) // Search
	{
		// add code here
	}
	else if (cmdLineTokens[0] == "Back") // Back
	{
		// add code here
	}
	else // INVALID_INPUT
		cout << INVALID_INPUT;
}


void MessageBox::VrtPreview(string activeUsrName)
{
	int count = 1;
	if (/* There are no conversations in MessageBox */)
		cout << "No conversations" << endl;
	else
		cout << "Conversations:" << endl;
	// ?????????????
	for (/* iterate over conversations with iterator called itr */)
	{
		cout << count << ") ";
		if (/* the user did not read the current message */)
			cout << "(UNREAD) ";
		cout << "Participants: ";
		(*itr)->DisplayParticipants();
		++count;
	}
}


void MessageBox::Help() const
{
	cout << "New <user names separated by spaces>" << endl;
	cout << "Open <conversation number>" << endl;
	cout << "Delete <conversation number>" << endl;
	cout << "Search <partial user name>" << endl;
	cout << "Back" << endl;
}

