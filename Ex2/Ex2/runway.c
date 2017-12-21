// runway.c -- Runway Implementation

#include <stdio.h>
#include <stdlib.h>
#include "runway.h"


/* Helper Function Declarations */
Node* listAppend(Node* head, pFlight fCopy);
Node* listInsertIn(Node* head, int count, pFlight fCopy);

/*	 INPUTS: runway number and runway type
OUTPUT: pointer to runway struct 
creating a runway*/
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
/*	 INPUTS: pointer runway struct
OUTPUT: none
clearing a runway and all the flights in it from memory*/
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
/*	 INPUTS: pointer runway struct and flight number
OUTPUT: BOOL True if the flight number is already in the runway, else FALSE 
*/
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

/*	 INPUTS: pointer runway struct
OUTPUT: the number of total flights in the runway
*/
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
/*	 INPUTS: pointer runway struct
OUTPUT: the number of emergency flights in the runway
*/
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

/* (Helper function)
Inserts a new flight <fCopy> in the last node
*/
Node* listAppend(Node* head, pFlight fCopy)
{
	Node *newNode;
	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return NULL;
	newNode->f = fCopy;
	newNode->pNext = NULL; // Since it's the last node on the list
	if (head == NULL)
	{	// Empty list case
		head = newNode;
		return head;
	}
	Node *pElem;
	pElem = head;
	while (pElem->pNext)
		pElem = pElem->pNext;
	pElem->pNext = newNode;
	return head;
}

/* (Helper function)
Inserts a new flight <fCopy> after node #<count>
*/
Node* listInsertIn(Node* head, int count, pFlight fCopy)
{
	Node *newNode;
	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return NULL;
	newNode->f = fCopy;
	if (count == 0)
	{	
		newNode->pNext = head;
		head = newNode;
		return head;
	}
	Node *pElem;
	pElem = head;
	while (count>1)
	{	//Count elements
		count--;
		pElem = pElem->pNext;
	}
	//Insert newNode after element #<count>
	newNode->pNext = pElem->pNext;
	pElem->pNext = newNode;
	return head;
}
/*	 INPUTS: pointer to runway struct and pointer to flight struct
OUTPUT: SUCCESS if managed to add the flight and FAILURE else
*/
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
	//free(f);                             //doesnt it delete the original flight?

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

/*	 INPUTS: pointer to runway struct and flight number
OUTPUT: SUCCESS if managed to remove the flight and FAILURE else
*/
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

/*	 INPUTS: pointer to runway struct 
OUTPUT: SUCCESS if managed to the flight that was next to depart and FAILURE else
*/
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

/*	 INPUTS: pointer to runway struct 
OUTPUT: none
prints the runway details, number of flights waiting and all the flights in the runway*/
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
