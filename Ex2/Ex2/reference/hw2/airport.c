/* airport.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "ex2.h"
#include "flight.h"
#include "runway.h"
#include "airport.h"

static PNODEAIR Airport = NULL;

PNODEAIR CreateAirport();
PRUNWAY findLeastLoadedRunway(FlightType run_type);
BOOL isFlightExistsDest(PRUNWAY pRunway, char* dest);
Result CopyFlightsStorm(PRUNWAY pRunway1, PRUNWAY pRunway2, char* dest);
Result readdStormFlights(PRUNWAY pRunway1, PRUNWAY pRunway2, char* dest);

//*********************************************************************************************************
//* function name:	CreateAirport
//* Description  :	Allocs the struct to the first elem on the linked list when adding the first runway
//* Parameters   :	None
//* Return Value :	Airport - a pointer to the airport
//*********************************************************************************************************
PNODEAIR CreateAirport() {
	if ((Airport = (PNODEAIR)malloc(sizeof(NODEAIR)))) {
		Airport->next = NULL;
		Airport->pRunway = NULL;
	}
	return Airport;
}
//*********************************************************************************************************
//* function name:	isRunwayExists
//* Description  :	Gets a runway id and check if it exists in the airport
//* Parameters   :	id - runway id
//* Return Value :	TRUE or FALSE is the runway is in the airport
//*********************************************************************************************************
BOOL isRunwayExists(long int id) {
	PNODEAIR tmp = Airport;
	while (tmp != NULL) {
		if (tmp->pRunway->runway_id == id)
			return TRUE;// runway with the same id exists
		else
			tmp = tmp->next;
	}
	return FALSE;
}

//*********************************************************************************************************
//* function name:	addRunway
//* Description  :	Gets the runway parameters and adds it to the airport. Return SUCCESS if added or
//*					FAILURE if not(illegal parameters or a runway with the same id already exists)
//* Parameters   :	id - runway id 
//*					flight_type - runway type(D or I)
//* Return Value :	Result - SUCCESS or FAILURE of adding the runway to the airport 
//*********************************************************************************************************
Result addRunway(long int id, FlightType run_type) {
	if (Airport == NULL) {  // airport does not exist
		Airport = CreateAirport();
	}
	if (id <= 0 || id > MAX_ID || ((run_type != DOMESTIC) && (run_type != INTERNATIONAL)))
		return FAILURE; // illegal parameters
	PNODEAIR tmp;
	tmp = Airport;
	if (tmp->pRunway == NULL) {// adding first runway
		tmp->pRunway = createRunway(id, run_type);
		return SUCCESS;
	}
	if (isRunwayExists(id) == TRUE)
		return FAILURE; // runway with the same id already exists
	while (tmp->next != NULL)
		tmp = tmp->next; // gets the pointer to the end of the list
	tmp->next = (PNODEAIR)malloc(sizeof(NODEAIR));
	tmp->next->pRunway= createRunway(id, run_type);
	tmp->next->next = NULL;
	return SUCCESS;
}

//*********************************************************************************************************
//* function name:	removeRunway
//* Description  :	Gets a runway id and removes it from the airport. Return SUCCESS if removed or
//*					FAILURE if not(illegal parameters or a runway with the given id doesn't exist)
//* Parameters   :	id - runway id 
//* Return Value :	Result - SUCCESS or FAILURE of removing the runway from the airport 
//*********************************************************************************************************
Result removeRunway(long int id) {
	if (Airport == NULL || (Airport->pRunway == NULL))
		return FAILURE; // airport doesn't exist or no runways
	if (id <= 0 || id > MAX_ID)
		return FAILURE; // illegal parameters
	PNODEAIR tmp;
	tmp = Airport;
	if (tmp->pRunway->runway_id == id) {
		// case first runway
		destroyRunway(tmp->pRunway);
		Airport = tmp->next;
		free(tmp);
		return SUCCESS;
	}
	while (tmp->next != NULL) {
		// not first runway
		if (tmp->next->pRunway->runway_id != id)
			tmp = tmp->next;
		else {
			PNODEAIR requested_node = tmp->next;
			destroyRunway(requested_node->pRunway);
			tmp->next = tmp->next->next;
			free(requested_node);
			return SUCCESS;
		}
	}
	return FAILURE; // runway with the given id doesn't exist
}

//*********************************************************************************************************
//* function name:	findLeastLoadedRunway
//* Description  :	Gets a runway type and finds the leasted load runway by the ruleset given on HW2
//* Parameters   :	flight_type - runway type( domestic or international)
//* Return Value :	Result - SUCCESS or FAILURE of removing the runway from the airport 
//*********************************************************************************************************
PRUNWAY findLeastLoadedRunway(FlightType run_type) {
	long int minimum_flights = -1;
	PRUNWAY target = NULL;
	PNODEAIR tmp = Airport;
	while (tmp != NULL) {
		if (tmp->pRunway->run_type == run_type) {
			if (minimum_flights == -1) { // first runway of the same flight type
				minimum_flights = tmp->pRunway->num_of_flights;
				target = tmp->pRunway;
			}
			if (tmp->pRunway->num_of_flights < minimum_flights) {
				// case the current checked runway has less flights then the minimum
				minimum_flights = tmp->pRunway->num_of_flights;
				target = tmp->pRunway;
			}
			else if (tmp->pRunway->num_of_flights == minimum_flights &&
				tmp->pRunway->runway_id < target->runway_id) {
				// case the current checked runway has the SAME flights as minimum but has lower runway id
				target = tmp->pRunway;
			}
		}
		tmp = tmp->next;
	}
	return target;
}

//*********************************************************************************************************
//* function name:	addFlightToAirport
//* Description  :	Gets the flight parameters and add the flight to the airport by the ruleset given on HW2.
//*					Return if succeeded adding the flight
//* Parameters   :	id - flight id 
//*					flight_type - flight type(D or I)
//*					dest - destination (three upper case letters. Example: JFK)
//*					emergency - is it an emergency flight or not ( TRUE or FALSE)
//* Return Value :	Result - FAILURE or SUCCESS (FAILURE can be caused by illegal parameters, flight creating
//*					is failed or a flight with the same id is already in the airport)
//*********************************************************************************************************
Result addFlightToAirport(long int id, FlightType flight_type, char* dest, BOOL emergency) {
	//
	PFLIGHT pFlight;
	PNODEAIR tmp = Airport;
	if (Airport == NULL || tmp->pRunway == NULL)
		return FAILURE; // airport is empty or doesn't exist
	if (id <= 0 || id > MAX_ID || ((flight_type != DOMESTIC) && (flight_type != INTERNATIONAL))
		|| (dest == NULL || strlen(dest) != NUM_DEST_LETTERS || !isUpperCase(dest))
		|| (emergency != TRUE && emergency != FALSE))
		return FAILURE; // illegal parameters
	while (tmp != NULL) {
		if (isFlightExists(tmp->pRunway, id)) { return FAILURE; } //checks if flight already exists in Airport
		tmp = tmp->next;
	}
	if ((pFlight = createFlight(id, flight_type, dest, emergency)) == NULL)
		return FAILURE; // creating flight failed
	PRUNWAY target = findLeastLoadedRunway(flight_type);
	if (target == NULL) { // no runway with the same flight type as the flight was found
		destroyFlight(pFlight);
		return FAILURE; 
	}
	if (addFlight(target, pFlight) == FAILURE) {
		destroyFlight(pFlight);
		return FAILURE; // failed to alloc flight
	}
	destroyFlight(pFlight); // free the flight copy that was used to send to addFlight function 
	return SUCCESS;
}

//*********************************************************************************************************
//* function name:	departFromRunway
//* Description  :	Gets a runway id and depart the first flight from the list. Return if succeeded or not
//* Parameters   :	id - runway id
//* Return Value :	Result - SUCCESSS or FAILURE in removing the first flight in the runway
//*********************************************************************************************************
Result departFromRunway(long int id) {
	//
	PNODEAIR tmp = Airport;
	while ((tmp != NULL) && (tmp->pRunway != NULL)) {
		if (tmp->pRunway->runway_id == id)
			return depart(tmp->pRunway);
		tmp = tmp->next;
	}
	return FAILURE;
}

//*********************************************************************************************************
//* function name:	isFlightExistsDest
//* Description  :	Gets a runway pointer and destination and checks if a flight to that destination exists.
//*					helper func for stormAlert
//* Parameters   :	pRunway - a pointer to runway
//*					dest - a pointer to a string of destination
//* Return Value :	BOOL - TRUE or FALSE (if flight to dest exists)
//*********************************************************************************************************
BOOL isFlightExistsDest(PRUNWAY pRunway, char* dest) {
	if (pRunway == NULL)
		return FALSE; // Runway pointer is empty
	if (dest == NULL || strlen(dest) != NUM_DEST_LETTERS || !isUpperCase(dest))
		return FAILURE; // illegal destination
	NODE* tmp;
	for (tmp = pRunway->head; tmp; tmp = tmp->next)  // check all flights on the runway list
		if (!strcmp(tmp->pFlight->dest, dest))
			return TRUE;
	return FALSE;
}

//*********************************************************************************************************
//* function name:	CopyFlightsStorm
//* Description  :	Gets two runways pointers and a destination and copied all the flight to that destination
//*					from the first runway to the second one
//* Parameters   :	pRunway1 - a pointer to the runway to be copied FROM
//*					pRunway2 - a pointer to the runway to be copied TO
//*					dest - a pointer to a string of destination
//* Return Value :	BOOL - TRUE or FALSE (if succeeded or failed to copy all the flights)
//*********************************************************************************************************
Result CopyFlightsStorm(PRUNWAY pRunway1, PRUNWAY pRunway2, char* dest) {
	//
	if (pRunway1 == NULL || pRunway2 == NULL)
		return FAILURE;
	if (dest == NULL || strlen(dest) != NUM_DEST_LETTERS || !isUpperCase(dest))
		return FAILURE; // illegal destination
	NODE* tmp;
	for (tmp = pRunway1->head; tmp; tmp = tmp->next)  // check all flights on the runway list
		if (!strcmp(tmp->pFlight->dest, dest)) {
			Result res;
			if ((res = addFlight(pRunway2, tmp->pFlight)) == FAILURE)
				return FAILURE;
		}
	return SUCCESS;
}

//*********************************************************************************************************
//* function name:	readdStormFlights
//* Description  :	Gets two runways pointers and a destination. Remove and add all the flights on the SECOND
//*					runway that also exists in the FIRST runway
//* Parameters   :	pRunway1 - a pointer to the runway to remove and re-add the flights
//*					pRunway2 - a pointer to the runway with the flights targeted at Runway1
//*					dest - a pointer to a string of destination
//* Return Value :	BOOL - TRUE or FALSE (if succeeded or failed to re-add the flights)
//*********************************************************************************************************

Result readdStormFlights(PRUNWAY pRunway1, PRUNWAY pRunway2, char* dest) {
	//
	if (pRunway1 == NULL || pRunway2 == NULL)
		return FAILURE;
	NODE* tmp;
	for (tmp = pRunway2->head; tmp; tmp = tmp->next) {
		Result res;
		if ((res = removeFlight(pRunway1, tmp->pFlight->flight_id)) == FAILURE)
			return FAILURE;
		if ((res = addFlight(pRunway1, tmp->pFlight)) == FAILURE)
			return FAILURE;
	}
	return SUCCESS;
}

//*********************************************************************************************************
//* function name:	stormAlert
//* Description  :	Gets two runways pointers and a destination. Remove and add all the flights on the SECOND
//*					runway that also exists in the FIRST runway.
//* Parameters   :	dest - a pointer to a string of destination
//* Return Value :	Result - SUCCESS or FAILURE (if succeeded or failed. FAILURE can be caused by illegal
//*					destination or failure to re-add the flights)
//*********************************************************************************************************
Result stormAlert(char *dest) {
	//
	
	if (dest == NULL || !isUpperCase(dest) || strlen(dest) != NUM_DEST_LETTERS)
		return FAILURE; // illegal destination
	PNODEAIR tmp = Airport;
	while ((tmp != NULL) && (tmp->pRunway != NULL)) {
		if (isFlightExistsDest(tmp->pRunway, dest) == TRUE) { // There's a flight to the storm destination
			PRUNWAY ghostRunway = createRunway(1, tmp->pRunway->run_type); 
			// id = 1 is arbitrary, the runway is temp("ghost") and is NOT connected to the airport
			if (CopyFlightsStorm(tmp->pRunway, ghostRunway, dest) == FAILURE)
				return FAILURE;
			if (readdStormFlights(tmp->pRunway, ghostRunway, dest) == FAILURE)
				return FAILURE;
			destroyRunway(ghostRunway);
		}
		tmp = tmp->next;
	}
	return SUCCESS;
}

//*********************************************************************************************************
//* function name:	printAirport
//* Description  :	Print the airport data by the ruleset given on HW2
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
void printAirport() {
	//
	printf("Airport status:\n");
	PNODEAIR tmp = Airport;
	while (tmp != NULL) {
		printRunway(tmp->pRunway);
		tmp = tmp->next;
	}
	printf("\n");
}

//*********************************************************************************************************
//* function name:	destroyAirport
//* Description  :	Destroys all the runways (including the flights in them) in the airport and the airport
//*					itself
//* Parameters   :	None
//* Return Value :	None
//*********************************************************************************************************
void destroyAirport() {
	//
	PNODEAIR tmp = Airport;
	while ((tmp != NULL) && (tmp->pRunway != NULL)) {
		removeRunway(tmp->pRunway->runway_id);
		tmp = Airport;
	}
	free(Airport);
}


