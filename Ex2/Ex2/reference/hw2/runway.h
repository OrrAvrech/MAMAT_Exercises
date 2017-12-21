/* runway.h - interface to an ADT which implements a runway */

#ifndef RUNWAY_H_
#define RUNWAY_H_

typedef struct node_t { // linked list of flights
	PFLIGHT pFlight;
	struct node_t* next;
} NODE;

typedef struct runway_t {
	long int runway_id;
	FlightType run_type;
	NODE* head; // head of the linked list //
	long int num_of_flights;
}RUNWAY, *PRUNWAY;

PRUNWAY createRunway(long int id , FlightType run_type);
void destroyRunway(PRUNWAY pRunway);
BOOL isFlightExists(PRUNWAY pRunway, long int id);
long int getFlightNum(PRUNWAY pRunway);
Result addFlight(PRUNWAY pRunway, PFLIGHT pFlight);
Result removeFlight(PRUNWAY pRunway, long int id);
Result depart(PRUNWAY pRunway);
Result printRunway(PRUNWAY pRunway);

#endif /* RUNWAY_H_ */