#include <stdio.h>
#include "flight.h"

int main()
{
	/* Flight ADT Simple Test */
	int fNum = 1;
	FlightType fType = DOMESTIC;
	char *fDst= "TLV";
	BOOL fEmergency = TRUE;

	pFlight f;
	f = createFlight(fNum, fType, fDst, fEmergency);
	printFlight(f);
	destroyFlight(f);
}