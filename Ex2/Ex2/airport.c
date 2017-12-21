// airport.c -- Airport Implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airport.h"

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
	printf("\n");
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
	pFlight flight, temp_flight;
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
