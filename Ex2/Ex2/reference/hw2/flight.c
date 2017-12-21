/* flight.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "ex2.h"
#include "flight.h"

//*********************************************************************************************************
//* function name:	isUpperCase
//* Description  :	Gets a string and checks if it contaions only english upper case characters(A...Z)
//* Parameters   :	String - a pointer to the string
//* Return Value :	TRUE or FALSE
//*********************************************************************************************************
BOOL isUpperCase(const char *String)
{
	long int i;
	long int n = strlen(String);
	for (i = 0; i < n; i++)
		if (!(String[i] >= 'A' && String[i] <= 'Z'))
			return FALSE;
	return TRUE;
}

//*********************************************************************************************************
//* function name:	createFlight
//* Description  :	Gets the flight parameters, allocs a FLIGHT struct to the flight and returns a pointer
//*					to the flight
//* Parameters   :	id - flight id 
//*					flight_type - flight type(D or I)
//*					dest - destination (three upper case letters. Example: JFK)
//*					emergency - is it an emergency flight or not ( TRUE or FALSE)
//* Return Value :	pFlight - a pointer to the created struct of the flight
//*********************************************************************************************************
PFLIGHT createFlight(long int id , FlightType flight_type , char* dest, BOOL emergency){ 
  PFLIGHT pFlight = NULL;
  if (id <= 0 || id > MAX_ID || (flight_type != DOMESTIC && flight_type != INTERNATIONAL)
	  || (dest == NULL || strlen(dest) != NUM_DEST_LETTERS || !isUpperCase(dest))
	  || (emergency != TRUE && emergency != FALSE))
	  return pFlight; // illegal parameters checks
  if ((pFlight = (PFLIGHT) malloc(sizeof(FLIGHT)))){
    pFlight->flight_id = id;
    pFlight->ftype = flight_type;
    strcpy(pFlight->dest, dest);
    pFlight->emergency = emergency;
  }
  return pFlight;
}

//*********************************************************************************************************
//* function name:	destroyFlight
//* Description  :	Gets the pointer to a flight and frees the alloced struct for the flight
//* Parameters   :	pFlight - a pointer to a flight
//* Return Value :	None
//*********************************************************************************************************
void destroyFlight(PFLIGHT pFlight){
  free(pFlight);
}

//*********************************************************************************************************
//* function name:	printFlight
//* Description  :	Gets the pointer to a flight prints the information on the flight. If the pointer to
//*					the flight is NULL then it will return FAILURE, otherwise SUCCESS
//* Parameters   :	pFlight - a pointer to a flight
//* Return Value :	SUCCESS or FAILURE
//*********************************************************************************************************
Result printFlight(PFLIGHT pFlight) {
  if (pFlight != NULL){
    char dest_type, flight_urgence;
	dest_type = (pFlight->ftype == DOMESTIC) ? 'D' : 'I';
	flight_urgence =(pFlight->emergency == TRUE) ? 'E' : 'R';
    printf("Flight %ld %c %s %c\n", pFlight->flight_id, dest_type, pFlight->dest, flight_urgence);
    return SUCCESS;
    }
  return FAILURE;
}