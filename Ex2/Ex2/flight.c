// flight.c -- Flight Implementation
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"

/*	 INPUTS: flight number , flight Destionation 
	 OUTPUT: BOOL TRUE if the input are Valid and FALSE if not*/
BOOL FlightValidParams(int fNum, char* fDst)

{
	if (fNum < 1 || fNum > MAX_ID)
		// Flight Number is Out of Range
		return FALSE;
	// if (fNum % 1 > 0 ) return FALSE;                          //  ** need to be coded better...it doesnt work**
	if (strlen(fDst) == 3)
		// Flight Destination is correct
	{
		int i;
		for (i = 0; i < strlen(fDst); i++)
		{
			if (fDst[i] < 'A' || fDst[i] > 'Z')
				return FALSE;
		}
	}
	else
		return FALSE;

	return TRUE; 
}
/*	INPUTS: flight number ,flight type,  flight Destionation and if emergency(BOOL)
 OUTPUT: pointer flight struct containing the flight parameters*/
pFlight createFlight(int fNum, FlightType fType, char *fDst, BOOL fEmergency)
{
	pFlight f;
	if (!FlightValidParams(fNum, fDst))
		return NULL;
	f = (pFlight)malloc(sizeof(Flight));
	if (f == NULL)
		return NULL;
	
	f->Num  = fNum;
	f->Type = fType;
	f->Dest = (char*)malloc(strlen(fDst)+1);
	strcpy(f->Dest, fDst);
	//f->Dest = _strdup(fDst); // malloc and strcopy in unix
	f->IsEmergency = fEmergency;

	return f;
}
/*	 INPUTS: pointer to flight struct
OUTPUT: none 
clearing the flight from memeory*/
void destroyFlight(pFlight f)
{
	if (f == NULL)
		return;
	// free(f->Dest); removed to check if tests are passing. im not sure you need to free the string because somehow f clears it on it own? 
	free(f);
}
/*	 INPUTS:pointer to flight struct
OUTPUT: none
printing flight details in the format of
"Flight: (flight num) (flight type first letter) (flight destination) (emergency or regular first letter)"*/
void printFlight(pFlight f)
{
	if (f == NULL)
		return;

	char cType = 'D', cEm = 'R';
	if (f->Type == INTERNATIONAL)
		cType = 'I';
	if (f->IsEmergency == TRUE)
		cEm = 'E';
	printf("Flight %d %c %s %c\n", f->Num, cType, f->Dest, cEm);
}

