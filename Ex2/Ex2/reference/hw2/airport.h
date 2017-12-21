/* airport.h - interface to an ADT which implements a flight */

#ifndef AIRPORT_H_
#define AIRPORT_H_

typedef struct node_air { // linked list of runways
	PRUNWAY pRunway;
	struct node_air* next;
} NODEAIR, *PNODEAIR;

PNODEAIR CreateAirport();
Result addRunway(long int id , FlightType run_type);
Result removeRunway(long int id);
Result addFlightToAirport(long int id, FlightType flight_type, char* dest, BOOL emergency);
Result departFromRunway(long int id);
Result stormAlert(char *dest);
void printAirport();
void destroyAirport();

#endif /* AIRPORT_H_ */