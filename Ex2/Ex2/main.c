#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "airport.h"
#define MAX_LINE_SIZE 256
int main()
{
	/*
	Flight ADT Simple Test 
	int fNum = 1;
	FlightType fType = DOMESTIC;
	char* fDst= "TLV";
	BOOL fEmergency = TRUE;

	pFlight f;
	f = createFlight(fNum, fType, fDst, fEmergency);
	printFlight(f);
	destroyFlight(f);   
	destroyFlight(f);

	Runway ADT Simple Test 
	int rNum = 1;
	FlightType rType = DOMESTIC;
	pRunway r;
	r = createRunway(rNum, rType);

	pFlight f2, f3, f4, f5, f6;
	f2 = createFlight(2, fType, "YYZ", FALSE);
	f3 = createFlight(3, fType, "ELT", TRUE);
	f4 = createFlight(4, fType, "TLV", TRUE);
	f5 = createFlight(5, fType, "HFA", TRUE);
	f6 = createFlight(6, fType, "LGD", FALSE);

	addFlight(r, f2);
	addFlight(r, f3);
	addFlight(r, f4);
	addFlight(r, f5);
	addFlight(r, f6);
	printRunway(r);
	removeFlight(r, 5);
	printRunway(r);
	depart(r);
	printRunway(r);

	destroyRunway(r);
	*/

	/* Airport ADT Simple Test */
	/*
	int rNum[3] = { 1, 4, 2 };
	int rNum[3] = { 5, 4, 2 };
	FlightType rType[2] = { DOMESTIC, INTERNATIONAL };
	addRunway(rNum[0], rType[0]);
	addFlightToAirport(1, rType[0], "TLV", FALSE);
	addFlightToAirport(7, rType[0], "TLV", FALSE);
	addFlightToAirport(8, rType[0], "TLV", TRUE);
	addFlightToAirport(9, rType[0], "TLV", FALSE);
	addRunway(rNum[1], rType[1]);
	addFlightToAirport(2, rType[1], "YYZ", TRUE);
	addRunway(rNum[2], rType[1]);
	addFlightToAirport(3, rType[1], "LGD", TRUE);
	addFlightToAirport(4, rType[1], "LDN", TRUE);
	addFlightToAirport(5, rType[1], "ARL", TRUE);
	addFlightToAirport(6, rType[1], "JFK", TRUE);
	addFlightToAirport(7, rType[1], "LGD", FALSE);
	addFlightToAirport(8, rType[1], "LGD", FALSE);
	addFlightToAirport(9, rType[1], "JFK", FALSE);
	addFlightToAirport(10, rType[1], "JFK", FALSE);
	printAirport();
	delay("LGD");
	printAirport();
	changeDest("LGD", "LGG");
	printAirport();
	departAirport();
	printAirport();
	destroyAirport(); 
	*/
	char szLine[MAX_LINE_SIZE+1];
	szLine[MAX_LINE_SIZE] = '\0';
	char* delimters = " \n\t";
	//char* saveP; //for strtok_r
	char* func; 
	char* in1;
	char* in2;
	char* in3;
	char* in4;
	/*func = (char *)malloc(MAX_LINE_SIZE * sizeof(char)+1);
	if (func == NULL)
		return -1;
	in1 = (char *)malloc(MAX_LINE_SIZE * sizeof(char) + 1);
	if (in1 == NULL)
		return -1;
	in2 = (char *)malloc(MAX_LINE_SIZE * sizeof(char) + 1);
	if (in2 == NULL)
		return -1;
	in3 = (char *)malloc(MAX_LINE_SIZE * sizeof(char) + 1);
	if (in3 == NULL)
		return -1;
	in4 = (char *)malloc(MAX_LINE_SIZE * sizeof(char) + 1);
	if (in4 == NULL)
		return -1;*/
	Result Results;
	FlightType type;
	BOOL emergency;
	while (fgets(szLine, MAX_LINE_SIZE, stdin))
	{
		/*i = 1;
		strncpy(input[0], strtok(szLine, delimters));
		while (token || i < 3)
		{
			input[i] = (char *)malloc(MAX_LINE_SIZE + 1);
			token = strtok(NULL, delimters));
			i++;
		}*/
		func = strtok(szLine, delimters);
		in1 = strtok(NULL, delimters);
		in2 = strtok(NULL, delimters);
		in3 = strtok(NULL, delimters);
		in4 = strtok(NULL, delimters);
		if (func == NULL)
			continue;
		if (!strcmp(func, "Insert"))
		{
			if (in1 == NULL || in2 == NULL) 
			{
				fprintf(stderr, "%s failed: not enough parameters.\n", func);
				continue;
			}
			else
			{
				if (!strcmp(in2, "I"))
					type = INTERNATIONAL;
				else if (!strcmp(in2, "D"))
					type = DOMESTIC;
				else
				{
					fprintf(stderr, "%s execution failed.\n", func);
					continue;
				}
				Results = addRunway(atoi(in1), type);
				if (Results == FAILURE)
				{
					fprintf(stderr, "%s execution failed.\n", func);
					continue;
				}
			}
		}
		else if (!strcmp(func, "Remove"))
		{
			if (in1 == NULL)
			{
				fprintf(stderr, "%s failed: not enough parameters.\n", func);
				continue;
			}
			else
			{
				Results = removeRunway(atoi(in1));
				if (Results == FAILURE)
				{
					fprintf(stderr, "%s execution failed.\n", func);
					continue;
				}
			}
		}
		else if (!strcmp(func, "Add"))
		{
			if (in1 == NULL || in2 == NULL || in3 == NULL || in4 == NULL )
			{
				fprintf(stderr, "%s failed: not enough parameters.\n", func);
				continue;
			}
			else
			{
				if (!strcmp(in2, "I"))
					type = INTERNATIONAL;
				else if (!strcmp(in2, "D"))
					type = DOMESTIC;
				else
				{
					fprintf(stderr, "%s execution failed.\n", func);
					continue;
				}
				if (!strcmp(in4, "E"))
					emergency = TRUE;
				else if (!strcmp(in4, "R"))
					emergency = FALSE;
				else
				{
					fprintf(stderr, "%s execution failed.\n", func);
					continue;
				}
				Results = addFlightToAirport(atoi(in1),type,in3,emergency);
				if (Results == FAILURE)
				{
					fprintf(stderr, "%s execution failed.\n", func);
					continue;
				}
			}
		}
		else if (!strcmp(func, "Depart"))
		{
			Results = departAirport();
			if (Results == FAILURE)
			{
				fprintf(stderr, "%s execution failed.\n", func);
				continue;
			}
		}
		else if (!strcmp(func, "Delay"))
		{
			if (in1 == NULL)
			{
				fprintf(stderr, "%s failed: not enough parameters.\n", func);
				continue;
			}
			else
			{
				Results = delay(in1);
				if (Results == FAILURE)
				{
					fprintf(stderr, "%s execution failed.\n", func);
					continue;
				}
			}
		}
		else if (!strcmp(func, "Change"))
		{
			if (in1 == NULL || in2 == NULL)
			{
				fprintf(stderr, "%s failed: not enough parameters.\n", func);
				continue;
			}
			else
			{
				Results = changeDest(in1, in2);
				if (Results == FAILURE)
				{
					fprintf(stderr, "%s execution failed.\n", func);
					continue;
				}
			}
		}
		else if (!strcmp(func, "Print"))
		{
			printAirport();
		}
		else if (!strcmp(func, "Exit"))
		{
			break;
		}
		else fprintf(stderr, "Command not found.\n");
	}
	destroyAirport();
	return 1;
} 
