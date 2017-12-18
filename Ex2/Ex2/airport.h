// airport.h -- Airport Interface

#ifndef _airport_h
#define _airport_h

#include "runway.h"

typedef struct _Airport {
	pRunway r;		// element data
	struct _Airport *pNext;	// pointer to next element
} Airport, *pAirport;

// Airport Interface Functions
Result addRunway(int, FlightType);
Result removeRunway(int);
Result addFlightToAirport(int, FlightType, char*, BOOL);
Result departAirport();
Result changeDest(char*, char*);
Result delay(char*);
void printAirport();
void destroyAirport();

#endif




