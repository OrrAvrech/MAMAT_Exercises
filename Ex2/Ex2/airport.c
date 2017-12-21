// airport.c -- Airport Implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airport.h"

/* Globals */
pAirport g_airport = NULL;

/* Data Types */
typedef struct _depart_nums {
	int EmergencyNum;
	int FlightNum;
	int RunwayID;
} depart_nums;

/* Helper Function Declarations */

int getRunwayNum();
pRunway findRunway(int rNum);
int compare_EmergencyNum(const void* a, const void* b);
int compare_FlightNum(const void* a, const void* b);
int compare_RunwayID(const void* a, const void* b);

/*	 INPUTS: runway number and runway type
OUTPUT: SUCCESS if managed to add the runway to the airport, else, FAILURE
*/
Result addRunway(int rNum, FlightType rType)
{
	if (rNum < 1 || rNum > MAX_ID)
		return FAILURE;
	pRunway runw;
	runw = createRunway(rNum, rType);
	if (runw == NULL)
		return FAILURE;

	pAirport newNode;
	newNode = (pAirport)malloc(sizeof(Airport));
	if (newNode == NULL)
		return FAILURE;
	newNode->r = runw;
	newNode->pNext = NULL;
	if (g_airport == NULL)
	{
		g_airport = newNode;
		return SUCCESS;
	}
	pAirport pElem;
	pElem = g_airport;
	while (pElem)
	{
		if (pElem->r->Num == rNum)
			return FAILURE;
		pElem = pElem->pNext;
	}
	pElem = g_airport;
	while (pElem->pNext)
	{
		pElem = pElem->pNext;
	}
	pElem->pNext = newNode;
	return SUCCESS;
}

/*	 INPUTS: runway number and runway type
OUTPUT: SUCCESS if managed to add the runway to the airport, else, FAILURE
*/
Result removeRunway(int rNum)
{
	if (g_airport == NULL || rNum < 1 || rNum > MAX_ID)
		return FAILURE;
	pAirport pElem, pPrev;
	pElem = g_airport;
	pPrev = pElem;
	if (pElem->r->Num == rNum)
	{	// Runway is in airport head
		g_airport = pElem->pNext;
		destroyRunway(pElem->r);
		free(pElem);
		return SUCCESS;
	}
	while (pElem)
	{
		pPrev = pElem;
		pElem = pElem->pNext;
		if (pElem->r->Num == rNum)
		{
			pPrev->pNext = pElem->pNext;
			destroyRunway(pElem->r);
			free(pElem);
			return SUCCESS;
		}
	}
	return FAILURE; // No runway has been found
}

/*	 INPUTS: flight number, flight type, flight destination, emergency(BOOL)
OUTPUT: SUCCESS if managed to add the flight to the airport, else, FAILURE
adds a flight to the airport and putting it in the correct runway in the correct order
*/
Result addFlightToAirport(int fNum, FlightType fType, char* fDest, BOOL fEmergency)
{
	pFlight f;
	f = createFlight(fNum, fType, fDest, fEmergency);
	if (f == NULL || g_airport == NULL)
		return FAILURE;
	pAirport pElem;
	pElem = g_airport;
	pRunway rFlight = NULL;
	int temp = MAX_ID+1;
	int count = 0;
	while (pElem)
	{
		if (isFlightExists(pElem->r, fNum))
			return FAILURE;
		if (f->Type == pElem->r->Type)
		{
			count++;
			if (getFlightNum(pElem->r) < temp)
			{ // Add flight to a suitable runway with minimum flights
				rFlight = pElem->r;
				temp = getFlightNum(rFlight);
			}
			else if (getFlightNum(pElem->r) == temp)
			{ // In case of equality, choose the smallest runway number
				if (pElem->r->Num < rFlight->Num)
					rFlight = pElem->r;
			}
		}
		pElem = pElem->pNext;
	}
	if (count == 0)
		// No runway exists with the given flight type
		return FAILURE;
	else
	{
		return addFlight(rFlight, f);
	}
}

/* helper function
counts the number of runways in the airport
*/
int getRunwayNum()
{
	if (g_airport == NULL)
		return -1;
	pAirport pElem;
	pElem = g_airport;
	int count = 0;
	while (pElem)
	{
		count++;
		pElem = pElem->pNext;
	}
	return count;
}

/* helper function
gets a runway number and return a pointer to the runway struct
*/
pRunway findRunway(int rNum)
{
	pAirport pElem;
	pElem = g_airport;
	while (pElem)
	{
		if (pElem->r->Num == rNum)
			return pElem->r;
		pElem = pElem->pNext;
	}
	return NULL;
}

/* helper function
compares the number of emergency flights and returns -1,0,1 if the first number is smaller,equal,larger
than the other number
*/
int compare_EmergencyNum(const void *a, const void *b) 
{	// Decreasing Order
	depart_nums* pElem_a = (depart_nums*) a;
	depart_nums* pElem_b = (depart_nums*) b;

	if (pElem_a->EmergencyNum < pElem_b->EmergencyNum)
		return 1;
	else if (pElem_a->EmergencyNum < pElem_b->EmergencyNum)
		return 0;
	else 
		return -1;
}

/* helper function
compares the number of flights and returns -1,0,1 if the first number is smaller,equal,larger
than the other number
*/
int compare_FlightNum(const void *a, const void *b)
{	// Decreasing Order
	depart_nums* pElem_a = (depart_nums*)a;
	depart_nums* pElem_b = (depart_nums*)b;

	if (pElem_a->FlightNum < pElem_b->FlightNum)
		return 1;
	else if (pElem_a->FlightNum < pElem_b->FlightNum)
		return 0;
	else
		return -1;
}

/* helper function
compares the runway number and returns -1,0,1 if the first number is larger,equal,smaller
than the other number
*/
int compare_RunwayID(const void *a, const void *b)
{	// Increasing Order
	depart_nums* pElem_a = (depart_nums*)a;
	depart_nums* pElem_b = (depart_nums*)b;

	if (pElem_a->RunwayID > pElem_b->RunwayID)
		return 1;
	else if (pElem_a->RunwayID < pElem_b->RunwayID)
		return 0;
	else
		return -1;
}

/*	 INPUTS: none
OUTPUT: SUCCESS if managed to depart the flight from the airport, else, FAILURE
choose a flight to depart and remove it from the airport 
*/
Result departAirport()
{
	if (g_airport == NULL)
		return FAILURE;
	depart_nums* helper_arr;
	helper_arr = (depart_nums*)malloc(getRunwayNum() * sizeof(depart_nums));
	if (helper_arr == NULL)
		return FAILURE;
	pAirport pElem;
	pElem = g_airport;
	int i = 0;
	pRunway rFlight = NULL;
	while (pElem)
	{
		helper_arr[i].EmergencyNum = getEmergencyNum(pElem->r);
		helper_arr[i].FlightNum	= getFlightNum(pElem->r);
		helper_arr[i].RunwayID = pElem->r->Num;
		i++;
		pElem = pElem->pNext;
	}
	qsort(helper_arr, getRunwayNum(), sizeof(depart_nums), compare_EmergencyNum); //decreasing
	if (helper_arr[0].EmergencyNum > helper_arr[1].EmergencyNum)
	{
		rFlight = findRunway(helper_arr[0].RunwayID);
		return depart(rFlight);
	}
	else
	{
		qsort(helper_arr, getRunwayNum(), sizeof(depart_nums), compare_FlightNum); //decreasing
		if (helper_arr[0].FlightNum > helper_arr[1].FlightNum)
		{
			rFlight = findRunway(helper_arr[0].RunwayID);
			return depart(rFlight);
		}
		else
		{
			qsort(helper_arr, getRunwayNum(), sizeof(depart_nums), compare_RunwayID); //increasing
			rFlight = findRunway(helper_arr[0].RunwayID);
			return depart(rFlight);
		}
	}
	free(helper_arr);
}
/*	 INPUTS: none
OUTPUT: none
print all the information about the airports, runways and flights
*/
void printAirport()
{
	printf("Airport status:\n");
	pAirport pElem;
	pElem = g_airport;
	while (pElem)
	{
		printRunway(pElem->r);
		pElem = pElem->pNext;
	}
	printf("\n");
}
/*	 INPUTS: none
OUTPUT: none
clear all the runways and flights from memory
*/
void destroyAirport()
{
	if (g_airport == NULL)
		return;
	pAirport pElem;
	while (g_airport)
	{
		pElem = g_airport;
		g_airport = g_airport->pNext;
		destroyRunway(pElem->r);
	}
	free(g_airport);
}
/*	 INPUTS: old flight destination, new flight destionation
OUTPUT: SUCCESS if managed to change the flight destionation, else, FAILURE
finds all the flight to a old destination and change their destionation to new destionation
*/
Result changeDest(char* old_dest, char* new_dest) 
{
	if (g_airport == NULL)
		return FAILURE;

	if (strlen(old_dest) != 3 || strlen(new_dest) != 3) return FAILURE;
	else
	{
		int i;
		for (i = 0; i < 3; i++)
		{
			if (old_dest[i] < 'A' || old_dest[i] > 'Z' || new_dest[i] < 'A' || new_dest[i] > 'Z')
				return FAILURE;
		}
	}

	pAirport pElem = g_airport;
	pRunway rRunway; 
	pNode flight_Node; 
	pFlight flight;
	while(pElem)
	{ 
		rRunway = pElem->r;
		flight_Node = rRunway->Head;
		while (flight_Node)
		{
			flight = flight_Node->f;
			if (!strcmp(flight->Dest, old_dest))
				flight->Dest = new_dest;
			flight_Node = flight_Node->pNext;
		}

		pElem = pElem->pNext;
	}
	return SUCCESS;
}
/*	 INPUTS: flight destination
OUTPUT: SUCCESS if managed to delay the flights to the  destionation, else, FAILURE
*/
Result delay(char* fDst)
{
	if (g_airport == NULL)
		return FAILURE;
	if (strlen(fDst) != 3 ) return FAILURE;
	else
	{
		int i;
		for (i = 0; i < 3; i++)
		{
			if (fDst[i] < 'A' || fDst[i] > 'Z')
				return FAILURE;
		}
	}

	pAirport pElem = g_airport;
	pRunway rRunway, eme_runaway_delayed, reg_runaway_delayed;
	pNode flight_Node;
	pFlight flight;
	int i;
	while (pElem)
	{
		rRunway = pElem->r;
		eme_runaway_delayed = createRunway(rRunway->Num, rRunway->Type);
		if (eme_runaway_delayed == NULL) return FAILURE;
		reg_runaway_delayed = createRunway(rRunway->Num, rRunway->Type);
		if (reg_runaway_delayed == NULL) return FAILURE;
		flight_Node = rRunway->Head;
		while (flight_Node)
		{
			flight = flight_Node->f;
			if (!strcmp(flight->Dest, fDst))
			{
				if (flight->IsEmergency)
					addFlight(eme_runaway_delayed, flight);
				else
					addFlight(reg_runaway_delayed, flight);
				flight_Node = flight_Node->pNext;
				removeFlight(rRunway, flight->Num);
			}
			else flight_Node = flight_Node->pNext;
		}
		if (eme_runaway_delayed != NULL)
		{
			flight_Node = eme_runaway_delayed->Head;
			for (i = 0; i < getFlightNum(eme_runaway_delayed); i++)
			{
				addFlight(rRunway, flight_Node->f);
				flight_Node = flight_Node->pNext;
			}
			destroyRunway(eme_runaway_delayed);
		}
		if (reg_runaway_delayed != NULL)
		{
			flight_Node = reg_runaway_delayed->Head;
			for (i = 0; i < getFlightNum(reg_runaway_delayed); i++)
			{
				addFlight(rRunway, flight_Node->f);
				flight_Node = flight_Node->pNext;
			}
			destroyRunway(reg_runaway_delayed);
		}
		pElem = pElem->pNext;
	}
	return SUCCESS;
}
