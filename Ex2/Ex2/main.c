#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "airport.h"
#define MAX_LINE_SIZE 256
int main()
{
	char szLine[MAX_LINE_SIZE+1];
	szLine[MAX_LINE_SIZE] = '\0';
	char* delimters = " \n\t";
	char* func; 
	char* in1;
	char* in2;
	char* in3;
	char* in4;
	Result Results;
	FlightType type;
	BOOL emergency;
	while (fgets(szLine, MAX_LINE_SIZE, stdin))
	{
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
