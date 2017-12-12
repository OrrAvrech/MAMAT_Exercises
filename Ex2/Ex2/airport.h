// airport.h 
// airport interface

#ifndef _airport_h
#define _airport_h

#include "flight.h"
#include "runway.h"

typedef struct _Node {
	Runway r;   //runaways' element data
	struct _Node *nextR;    //pointer to next runaway
};

typedef struct _Airport {
	Node *head
};

typedef enum _Result { FAILURE , SUCCESS } Result;

// interfaces' functions
Result addRunway(int, FlightType);
Result removeRunway(int);
Result addFlightToAirport(int, FlightType, char*);
Result depart;
Result changeDest(char*, char*);
Result delay;
void printAirport;
void destroyAirport

#endif // !_airport_h

