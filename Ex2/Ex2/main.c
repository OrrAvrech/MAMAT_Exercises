#include <stdio.h>
#include <string.h>
#include "airport.h"

int main()
{
	/*
	/* Flight ADT Simple Test 
	int fNum = 1;
	FlightType fType = DOMESTIC;
	char* fDst= "TLV";
	BOOL fEmergency = TRUE;

	pFlight f;
	f = createFlight(fNum, fType, fDst, fEmergency);
	printFlight(f);
<<<<<<< HEAD
	destroyFlight(f);   
=======
	destroyFlight(f);

	/* Runway ADT Simple Test 
	int rNum = 1;
	FlightType rType = DOMESTIC;
	pRunway r;
	r = createRunway(rNum, rType);

	pFlight f2, f3, f4, f5, f6;
	f2 = createFlight(2, fType, "YYZ", FALSE);
	f3 = createFlight(3, fType, "ELT", TRUE);
	f4 = createFlight(4, fType, "TLV", TRUE);
	f5 = createFlight(5, fType, "HFA", TRUE);
	f6 = createFlight(6, fType, "LGD", FALSE);

	addFlight(r, f2);
	addFlight(r, f3);
	addFlight(r, f4);
	addFlight(r, f5);
	addFlight(r, f6);
	printRunway(r);
	removeFlight(r, 5);
	printRunway(r);
	depart(r);
	printRunway(r);

	destroyRunway(r);
	*/

	/* Airport ADT Simple Test */
	int rNum[3] = { 5, 4, 2 };
	FlightType rType[2] = { DOMESTIC, INTERNATIONAL };
	addRunway(rNum[0], rType[0]);
	addFlightToAirport(1, rType[0], "TLV", FALSE);
	addFlightToAirport(7, rType[0], "TLV", FALSE);
	addFlightToAirport(8, rType[0], "TLV", TRUE);
	addFlightToAirport(9, rType[0], "TLV", FALSE);
	addRunway(rNum[1], rType[1]);
	addFlightToAirport(2, rType[1], "YYZ", TRUE);
	addRunway(rNum[2], rType[1]);
	addFlightToAirport(3, rType[1], "LGD", TRUE);
	addFlightToAirport(4, rType[1], "LDN", TRUE);
	addFlightToAirport(5, rType[1], "ARL", TRUE);
	addFlightToAirport(6, rType[1], "JFK", TRUE);
	//removeRunway(rNum[1]);
	departAirport();
	printAirport();
	destroyAirport();
>>>>>>> bb67105bf99c9f8e5dfcd6eb39d707b456bc48c9
}