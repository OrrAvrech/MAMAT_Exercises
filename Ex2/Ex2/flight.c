// flight.c -- Flight Implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"

/*int ValidParams(int fNum)
{
	if (fNum < 1 || fNum > MAX_ID)
		// Flight Number is Out of Range
		return 0;
	else
		return 1;
}*/

pFlight createFlight(int fNum, FlightType fType, char *fDst, BOOL fEmergency)
{
	pFlight f;
	/*if (!ValidParams(fNum))
		return NULL;*/
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

