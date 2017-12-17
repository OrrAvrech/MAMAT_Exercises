// airport.c -- Airport Implementation

#include <stdio.h>
#include <stdlib.h>
#include "airport.h"

/* Globals */
pAirport g_airport = NULL;

Result addRunway(int rNum, FlightType rType)
{
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

Result addFlightToAirport(int fNum, FlightType fType, char* fDest, BOOL fEmergency)
{
	pFlight f;
	f = createFlight(fNum, fType, fDest, fEmergency);
	if (f == NULL || g_airport == NULL)
		return FAILURE;
	pAirport pElem;
	pElem = g_airport;
	pRunway rFlight = NULL;
	int temp = 0;
	int count = 0;
	while (pElem)
	{
		if (isFlightExists(pElem->r, fNum))
			return FAILURE;
		if (f->Type == pElem->r->Type)
		{
			rFlight = pElem->r;
			temp = getFlightNum(rFlight);
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

