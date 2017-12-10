// runway.c -- Runway Implementation

#include <stdio.h>
#include <stdlib.h>
#include "runway.h"

pRunway createRunway(int rNum, FlightType rType)
{
	// check valid params

	pRunway r;
	r = (pRunway)malloc(sizeof(Runway));
	if (r == NULL)
		return NULL;
	r->Num  = rNum;
	r->Type = rType;
	r->List = NULL;

	return r;
}

void destroyRunway(pRunway r)
{
	if (r == NULL)
		printf("Runway is empty");
	free(r->List);
	free(r);
}

BOOL isFlightExists(pRunway r, int fNum)
{
	// check valid params
	Node *pElem;
	pElem = r->List;
	while (pElem)
	{
		if (pElem->f->Num == fNum)
			return TRUE;
		else
			pElem = pElem->pNext;
	}
	return FALSE;
}

int getFlightNum(pRunway r)
{
	// check valid params
	Node *pElem;
	pElem = r->List;
	int count = 0;
	while (pElem)
	{
		count++;
		pElem = pElem->pNext;
	}
	return count;
}

int getEmergencyNum(pRunway r)
{
	//check valid params
	Node *pElem;
	pElem = r->List;
	int Emergency_count = 0;
	while (pElem)
	{
		if (pElem->f->IsEmergency == TRUE)
			Emergency_count++;
		pElem = pElem->pNext;
	}
	return Emergency_count;
}


