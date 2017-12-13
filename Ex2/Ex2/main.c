#include <stdio.h>
#include <string.h>
#include "runway.h"

int main()
{
	/* Flight ADT Simple Test */
	int fNum = 1;
	FlightType fType = DOMESTIC;
	char* fDst= "TLV";
	BOOL fEmergency = TRUE;

	pFlight f;
	f = createFlight(fNum, fType, fDst, fEmergency);
	printFlight(f);
	destroyFlight(f);

	/* Runway ADT Simple Test */
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
}