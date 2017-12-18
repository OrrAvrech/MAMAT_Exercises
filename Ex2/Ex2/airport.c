<<<<<<< HEAD
//airport.c
// airport implementation
=======
// airport.c -- Airport Implementation
>>>>>>> bb67105bf99c9f8e5dfcd6eb39d707b456bc48c9

#include <stdio.h>
#include <stdlib.h>
#include "airport.h"

<<<<<<< HEAD
Result addRunway(int rNum, FlightType rType) {

	// *** add  HERE   tests for inputs.****


}
=======
/* Globals */
pAirport g_airport = NULL;

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

Result departAirport()
{
	if (g_airport == NULL)
		return FAILURE;
	pAirport pElem;
	pElem = g_airport;
	pRunway rFlight = pElem->r;
	int tempEmergencyNum = 0;
	int tempFlightNum = 0;
	int tempRunwayNum = MAX_ID+1;
	int flagEqual = 1;
	while (pElem)
	{
		if (getEmergencyNum(pElem->r) > tempEmergencyNum)
		{
			flagEqual = 0;
			rFlight = pElem->r;
			tempEmergencyNum = getEmergencyNum(rFlight);
			tempFlightNum = getFlightNum(rFlight);
			tempRunwayNum = rFlight->Num;
		}
		else if (getEmergencyNum(pElem->r) == tempEmergencyNum || flagEqual == 1)
		{
			flagEqual = 1;
			if (getFlightNum(pElem->r) > tempFlightNum)
			{
				rFlight = pElem->r;
				tempFlightNum = getFlightNum(rFlight);
				tempRunwayNum = rFlight->Num;
			}
			else if (getFlightNum(pElem->r) == tempFlightNum)
			{
				if (pElem->r->Num < tempRunwayNum)
				{
					rFlight = pElem->r;
					tempRunwayNum = rFlight->Num;
				}
			}
		}
		pElem = pElem->pNext;
	}
	return depart(rFlight);
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

>>>>>>> bb67105bf99c9f8e5dfcd6eb39d707b456bc48c9
