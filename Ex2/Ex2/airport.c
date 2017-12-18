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
	while (pElem->pNext)
	{
		if (pElem->r->Num == rNum)
			return FAILURE;
		pElem = pElem->pNext;
	}
	pElem->pNext = newNode;
	return SUCCESS;
}

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
}

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

