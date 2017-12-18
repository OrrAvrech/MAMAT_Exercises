// flight.c -- Flight Implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"

BOOL FlightValidParams(int fNum, char* fDst)
{
	if (fNum < 1 || fNum > MAX_ID)
		// Flight Number is Out of Range
		return FALSE;
	if (strlen(fDst) == 3)
		// Flight Destination is wrong
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
	f->Dest = _strdup(fDst); // malloc and strcopy in unix
	f->IsEmergency = fEmergency;

	return f;
}

void destroyFlight(pFlight f)
{
	if (f == NULL)
		return;
	free(f->Dest);
	free(f);
}

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

