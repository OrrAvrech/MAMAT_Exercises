// runway.h -- Runway Interface

#ifndef _runway_h
#define _runway_h

#include "flight.h"

typedef struct _Node {
	pFlight f;		// element data
	struct _Node *pNext;	// pointer to next element
} Node;

typedef struct _Runway {
	int Num;
	FlightType Type;
	Node *List;
} Runway, *pRunway;

typedef enum _Result { FAILURE, SUCCESS } Result;

// Runway Interface Functions
pRunway createRunway(int, FlightType);
void	destroyRunway(pRunway);
BOOL	isFlightExists(pRunway, int);
int		getFlightNum(pRunway);
int		getEmergencyNum(pRunway);
Result  addFlight(pRunway, pFlight);
Result  removeFlight(pRunway, int);
Result  depart(pRunway);
void	printRunway(pRunway);

#endif



