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
	r->Head = NULL;

	return r;
}

void destroyRunway(pRunway r)
{
	if (r == NULL)
		printf("Runway is empty");
	free(r->Head);
	free(r);
}

BOOL isFlightExists(pRunway r, int fNum)
{
	// check valid params
	Node *pElem;
	pElem = r->Head;
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
	pElem = r->Head;
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
	pElem = r->Head;
	int Emergency_count = 0;
	while (pElem)
	{
		if (pElem->f->IsEmergency == TRUE)
			Emergency_count++;
		pElem = pElem->pNext;
	}
	return Emergency_count;
}

void listAppend(Node** headRef, pFlight fCopy)
{
	Node *newNode;
	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return;
	newNode->f = fCopy;
	newNode->pNext = NULL; // Since it's the last node on the list
	if (*headRef == NULL)
	{	// Empty list case
		*headRef = newNode;
		return;
	}
	Node *pElem;
	pElem = *headRef;
	while (pElem)
	{
		pElem = pElem->pNext;
	}
	pElem = newNode;
	return;
}

void listInsertIn(Node** headRef, int count, pFlight fCopy)
{
	Node *newNode;
	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return;
	newNode->f = fCopy;
	if (count == 0)
	{	//Empty list case (Emergency Flight)
		newNode->pNext = NULL;
		*headRef = newNode;
		return;
	}
	Node *pElem;
	pElem = *headRef;
	while (count)
	{	//Count elements
		count--;
		pElem = pElem->pNext;
	}
	//Insert newNode after element #<count>
	newNode->pNext = pElem->pNext;
	pElem->pNext = newNode;
	return;
}

Result addFlight(pRunway r, pFlight f)
{
	// create Flight copy
	pFlight fCopy;
	fCopy = (pFlight)malloc(sizeof(Flight));
	if (fCopy == NULL)
		return FAILURE;
	fCopy = createFlight(f->Num, f->Type, f->Dest, f->IsEmergency);
	free(f);

	// check valid params
	if ((fCopy->Type != r->Type) || (isFlightExists(r, fCopy->Num) == TRUE))
		return FAILURE;

	if (!fCopy->IsEmergency)
		


		
}
