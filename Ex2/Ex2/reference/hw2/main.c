#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ex2.h"
#include "flight.h"
#include "runway.h"
#include "airport.h"

#define MAX_LINE_SIZE 256
#define INSERT 1
#define REMOVE 2
#define ADD 3
#define DEPART 4
#define STORM 5
#define PRINT 6
#define EXIT 7

typedef char* PCHAR;
const int hash(const char *str);
const char *errorMessage(int err_id);

//*********************************************************************************************************
//* function name: hash
//* Description  : transform the command string into and integer to be used on switch
//* Parameters   : str - a pointer to the string of the message
//* Return Value : hash - the id of the command to be used on the switch
//*********************************************************************************************************
const int hash(const char *str) {	
	if (!strcmp(str, "Insert"))
		return INSERT;
	if (!strcmp(str, "Remove"))
		return REMOVE;
	if (!strcmp(str, "Add"))
		return ADD;
	if (!strcmp(str, "Depart"))
		return DEPART;
	if (!strcmp(str, "Storm"))
		return STORM;
	if (!strcmp(str, "Print"))
		return PRINT;
	if (!(strcmp(str, "Exit")))
		return EXIT;
	return 0; // not a valid commmand
}

//*********************************************************************************************************
//* function name: errorMessage
//* Description  :	The function recieves an error id and returns the correct message to print
//*					Messages' list:
//*					1 - <command> failed: not enough parameters.
//*					2 - Command not found.
//*					3 - <command> execution failed.
//* Parameters   : err_id - error id recieved
//* Return Value : a string with an error message
//*********************************************************************************************************
const char *errorMessage(int err_id) {
	switch (err_id) {
		case 1:
			return "failed: not enough parameters.\n";
			break;
		case 2:
			return "Command not found.\n";
			break;
		case 3:
			return "execution failed.\n";
			break;
	}
	return "Illegal Error id. If printed then a KAMTAN ate the PC wires :P"; 
	// never reaches it, just for compilation to pass and the gigs
}

//*********************************************************************************************************
//* function name:	Main
//* Description  :	The main function of the airport program. Gets the commands from the user
//*					by stdin and control the airport.
//*					Each runway and flight type can be either domestic (D) or international (I). 
//*					Each flight urgence can also be regular (R) or emergency (E)
//*					For each flight the destination is represented in three capital letters. Examples: TLV, JFK
//*					Commands list:
//*					Insert - Adds a runway to the airport. Usage: Add <runway id> <runway type>
//*					Remove - Remove a runway and all flights on it from the airport. Usage: Remove <runway id>
//*					Add - Add a new flight to the airport and put it in a runway according to the ruleset given
//*						on HW2 file. Usage: Add <flight id> <flight type> <destination> <urgence>
//*					Depart - Departs the first flight on a given runway. Usage: Depart <runway id>
//*					Storm - Alerts on a storm on a given destination, flights on each runway are re-entered to 
//*							the same runway. usage: Storm <destination>
//*					Print - Prints the airport status as described on HW2
//*					Exit - Destroys the airport (free all alloced data) and exit the program
//* Parameters   :	None
//* Return Value :	0
//*********************************************************************************************************
int main() {
	char szLine[MAX_LINE_SIZE];
	const PCHAR delimiters = " \t\n";
	PCHAR pszCommand, pszVar1, pszVar2, pszVar3, pszVar4;
	long int id;	
	FlightType Obj_type;
	BOOL Emergency;
	while (fgets(szLine, MAX_LINE_SIZE, stdin)) {
		// getting the command and parameters
		pszCommand = strtok(szLine, delimiters);
		pszVar1 = strtok(NULL, delimiters);
		pszVar2 = strtok(NULL, delimiters);
		pszVar3 = strtok(NULL, delimiters);
		pszVar4 = strtok(NULL, delimiters);
		//
		if (pszCommand == NULL)
			continue; // ignore empty lines and move to the next command
		switch (hash(pszCommand)) {
			case 1: //Insert
				if (pszVar1 == NULL || pszVar2 == NULL) { // checks for enough parameters
					fprintf(stderr, "%s %s", pszCommand, errorMessage(1));
					continue;
				}
				id = (long)atoi(pszVar1);
				if ((strcmp(pszVar2,"D")) == 0) // transforms the string to FTYPE
					Obj_type = DOMESTIC;
				else if ((strcmp(pszVar2, "I")) == 0)
					Obj_type = INTERNATIONAL;
				else {
					fprintf(stderr, "%s %s", pszCommand, errorMessage(3));
					break;
				}
				if ((addRunway(id, Obj_type)) == FAILURE) 
					fprintf(stderr, "%s %s", pszCommand, errorMessage(3));
				break;	
			case 2: //Remove
				if (pszVar1 == NULL) { // checks for enough parameters
					fprintf(stderr, "%s %s", pszCommand, errorMessage(1));
					continue;
				}
				id = (long)atoi(pszVar1);
				if ((removeRunway(id)) == FAILURE) 
					fprintf(stderr, "%s %s", pszCommand, errorMessage(3));
				break;
			case 3: //Add
				if (pszVar1 == NULL || pszVar2 == NULL || pszVar3 == NULL || pszVar4 == NULL) {
					// checks for enough parameters
					fprintf(stderr, "%s %s", pszCommand, errorMessage(1));
					continue;
				}
				id = (long)atoi(pszVar1);
				if ((strcmp(pszVar2, "D")) == 0) // transforms the string to FTYPE
					Obj_type = DOMESTIC;
				else if ((strcmp(pszVar2, "I")) == 0)
					Obj_type = INTERNATIONAL;
				else {
					fprintf(stderr, "%s %s", pszCommand, errorMessage(3));
					break;
				}
				if ((strcmp(pszVar4, "E")) == 0) // transforms the string to BOOL
					Emergency = TRUE;
				else if ((strcmp(pszVar4, "R")) == 0)
					Emergency = FALSE;
				else {
					fprintf(stderr, "%s %s", pszCommand, errorMessage(3));
					break;
				}
				if ((addFlightToAirport(id, Obj_type, pszVar3, Emergency)) == FAILURE) 
					fprintf(stderr, "%s %s", pszCommand, errorMessage(3));
				break;
			case 4: //Depart
				if (pszVar1 == NULL) { // checks for enough parameters
					fprintf(stderr, "%s %s", pszCommand, errorMessage(1));
					continue;
				}
				id = (long)atoi(pszVar1);
				if ((departFromRunway(id)) == FAILURE)
					fprintf(stderr, "%s %s", pszCommand, errorMessage(3));
				break;

			case 5: //Storm				
				if (pszVar1 == NULL) { // checks for enough parameters
					fprintf(stderr, "%s %s", pszCommand, errorMessage(1));
					continue;
				}
				if ((stormAlert(pszVar1)) == FAILURE)
					fprintf(stderr, "%s %s", pszCommand, errorMessage(3));
				break;
			case 6: //Print
				printAirport();
				break;
			case 7: //Exit
				destroyAirport();
				return 0;
				break;
			case 0: //Not a valid command
				fprintf(stderr, "%s", errorMessage(2));
				continue;
				break;
		}	
	}
	//reached EOF
	destroyAirport();
	return 0;
}