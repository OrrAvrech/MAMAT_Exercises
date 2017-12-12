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

	pFlight f2, f3;
	f2 = createFlight(2, fType, "YYZ", FALSE);
	f3 = createFlight(3, fType, "ELT", TRUE);

	addFlight(r, f2);
	addFlight(r, f3);

	printRunway(r);
	destroyRunway(r);
}