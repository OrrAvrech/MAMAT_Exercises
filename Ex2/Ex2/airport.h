<<<<<<< HEAD
// airport.h 
// airport interface
=======
// airport.h -- Airport Interface
>>>>>>> bb67105bf99c9f8e5dfcd6eb39d707b456bc48c9

#ifndef _airport_h
#define _airport_h

<<<<<<< HEAD
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
=======
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



>>>>>>> bb67105bf99c9f8e5dfcd6eb39d707b456bc48c9

