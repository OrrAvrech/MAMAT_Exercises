/* flight.h - interface to an ADT which implements a flight */

#ifndef FLIGHT_H_
#define FLIGHT_H_
#define NUM_DEST_LETTERS 3

typedef struct flight_t {
	long int flight_id;
	FlightType ftype;
	char dest[3];
	BOOL emergency;
}FLIGHT, *PFLIGHT;

BOOL isUpperCase(const char *String);
PFLIGHT createFlight(long int id , FlightType ftype , char* dest, BOOL emergency);
void destroyFlight(PFLIGHT pFlight);
Result printFlight(PFLIGHT pFlight);

#endif /* FLIGHT_H_ */