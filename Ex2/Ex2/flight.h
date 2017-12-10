// flight.h -- Flight Interface

#ifndef _flight_h
#define _flight_h

#include "ex2.h"

#define DSTRING_SIZE 4

typedef struct _Flight {
	int Num;
	FlightType Type;
	char* Dest;
	BOOL IsEmergency;
} Flight, *pFlight;

// Flight Interface Functions
pFlight createFlight(int, FlightType, char*, BOOL);
void	destroyFlight(pFlight);
void	printFlight(pFlight);

#endif


