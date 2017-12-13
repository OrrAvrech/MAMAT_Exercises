// runway.c -- Runway Implementation

#include <stdio.h>
#include <stdlib.h>
#include "runway.h"

pRunway createRunway(int rNum, FlightType rType)
{
	if (rNum < 1 || rNum > MAX_ID)
		// Runway Number is Out of Range
		return NULL;

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
		return;
	Node *pElem;
	while (r->Head)
	{
		pElem = r->Head;
		r->Head = r->Head->pNext;
		free(pElem);
	}
	free(r);
}

BOOL isFlightExists(pRunway r, int fNum)
{
	if (r == NULL || fNum < 1 || fNum > MAX_ID)
		return FALSE;
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
	if (r == NULL)
		return -1;
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
	if (r == NULL)
		return -1;
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

Node* listAppend(Node* headRef, pFlight fCopy)
{
	/* (Helper function)
		Inserts a new flight <fCopy> in the last node
	*/
	Node *newNode;
	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return;
	newNode->f = fCopy;
	newNode->pNext = NULL; // Since it's the last node on the list
	if (headRef == NULL)
	{	// Empty list case
		headRef = newNode;
		return headRef;
	}
	Node *pElem;
	pElem = headRef;
	while (pElem->pNext)
	{
		pElem = pElem->pNext;
	}
	pElem->pNext = newNode;
	return headRef;
}

Node* listInsertIn(Node* headRef, int count, pFlight fCopy)
{
	/* (Helper function)
		Inserts a new flight <fCopy> after node #<count>
	*/
	Node *newNode;
	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return;
	newNode->f = fCopy;
	if (count == 0)
	{	
		newNode->pNext = headRef;
		headRef = newNode;
		return headRef;
	}
	Node *pElem;
	pElem = headRef;
	while (count>1)
	{	//Count elements
		count--;
		pElem = pElem->pNext;
	}
	//Insert newNode after element #<count>
	newNode->pNext = pElem->pNext;
	pElem->pNext = newNode;
	return headRef;
}

Result addFlight(pRunway r, pFlight f)
{
	if (r == NULL || f == NULL || (r->Type != f->Type))
		return FAILURE;

	// Create Flight copy
	pFlight fCopy;
	fCopy = (pFlight)malloc(sizeof(Flight));
	if (fCopy == NULL)
		return FAILURE;
	fCopy = createFlight(f->Num, f->Type, f->Dest, f->IsEmergency);
	free(f);

	if ((fCopy->Type != r->Type) || (isFlightExists(r, fCopy->Num) == TRUE))
		return FAILURE;

	int Emergency_count = getEmergencyNum(r);
	int Flight_count = getFlightNum(r);
	if (!fCopy->IsEmergency)
		// New Regular flights always goes to the end of the list
		r->Head = listAppend(r->Head, fCopy);
	else if (Emergency_count == Flight_count)
		r->Head = listAppend(r->Head, fCopy);
	else
		// New Emergency flights goes after the last E flight 
		r->Head = listInsertIn(r->Head, Emergency_count, fCopy);
	return SUCCESS;
}

Result removeFlight(pRunway r, int fNum)
{
	if ((r == NULL) || (r->Head == NULL) || (isFlightExists(r, fNum) == FALSE))
		return FAILURE;
	Node *pElem, *pPrev;
	pElem = r->Head;
	pPrev = pElem;
	if (pElem->f->Num == fNum)
	{	// FlightNum is in Head
		r->Head = pElem->pNext;
		free(pElem);
		return SUCCESS;
	}
	pElem = pElem->pNext;
	while (pElem && pElem->f->Num != fNum)
	{
		pPrev = pElem;
		pElem = pElem->pNext;
	}
	pPrev->pNext = pElem->pNext;
	free(pElem);
	return SUCCESS;
}

Result depart(pRunway r)
{
	if (r == NULL || r->Head == NULL)
		return FAILURE;
	Node *pElem;
	pElem = r->Head;
	r->Head = pElem->pNext;
	free(pElem);
	return SUCCESS;
}

void printRunway(pRunway r)
{
	if (r == NULL)
		return;

	char strI[] = "international";
	char strD[] = "domestic";
	if (r->Type == INTERNATIONAL)
		printf("Runway %d %s\n", r->Num, strI);
	else
		printf("Runway %d %s\n", r->Num, strD);

	printf("%d flights are waiting:\n", getFlightNum(r));

	Node *pElem;
	pElem = r->Head;
	while (pElem)
	{
		printFlight(pElem->f);
		pElem = pElem->pNext;
	}
}
