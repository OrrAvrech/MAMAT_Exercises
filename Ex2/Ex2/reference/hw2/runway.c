/* runway.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "ex2.h"
#include "flight.h"
#include "runway.h"

//*********************************************************************************************************
//* function name:	createRunway
//* Description  :	Gets the runway parameters, allocs a RUNWAY struct to the runway and returns a pointer
//*					to the runway
//* Parameters   :	id - runway id 
//*					run_type - runway type(D or I)
//* Return Value :	pRunway - a pointer to the created struct of the runway
//*********************************************************************************************************
PRUNWAY createRunway(long int id , FlightType run_type){
	PRUNWAY pRunway = NULL;
	if (id <= 0 || id > MAX_ID) // illegal parameters check
		return pRunway;
	if ((pRunway = (PRUNWAY) malloc(sizeof(RUNWAY)))){
		pRunway-> runway_id = id;
		pRunway-> run_type = run_type;
		pRunway-> num_of_flights = 0;
		pRunway-> head = NULL; 
	}
	return pRunway;
}

//*********************************************************************************************************
//* function name:	destroyRunway
//* Description  :	Gets the pointer to a runway and frees the alloced struct for the runway
//* Parameters   :	pRunway - a pointer to a runway
//* Return Value :	None
//*********************************************************************************************************
void destroyRunway(PRUNWAY pRunway){ 
	if (pRunway == NULL)
		return; // pointer is empty
	NODE* tmp;
	tmp = pRunway->head;
	while (tmp!=NULL ){ // destroy all COPIES of flights on the runway
		NODE* requested_node = tmp;
		destroyFlight(tmp->pFlight); 
		tmp = tmp->next;
		free(requested_node);
	}
	free(pRunway);
}

//*********************************************************************************************************
//* function name:	isFlightExists
//* Description  :	Gets a pointer to the runway and a flight id, returns if a flight is there (TRUE or FALSE)
//* Parameters   :	pRunway - a pointer to a runway
//*					id - flight id
//* Return Value :	TRUE or FALSE
//*********************************************************************************************************
BOOL isFlightExists(PRUNWAY pRunway, long int id){
	if (pRunway == NULL || id <= 0 || id > MAX_ID || pRunway->head == NULL)
		return FALSE; // parameters check
	NODE* tmp;
	for (tmp = pRunway->head;tmp;tmp=tmp->next)  // check all flights on the runway list
		if (tmp->pFlight->flight_id == id)
			return TRUE; // flight found!
	return FALSE; // flight not found
}

//*********************************************************************************************************
//* function name:	getFlightNum
//* Description  :	Gets a pointer to the runway and returns the amount of flights in the runway
//* Parameters   :	pRunway - a pointer to a runway
//* Return Value :	num_of_flights - number of flights 
//*********************************************************************************************************
long int getFlightNum(PRUNWAY pRunway){
	if (pRunway == NULL)
		return -1; // illegal runway id
	return pRunway->num_of_flights;
}

//*********************************************************************************************************
//* function name:	addFlight
//* Description  :	Gets a pointer to a runway and a pointer to a flight, COPY the flight and enters it to
//*					the runway by the ruleset given on HW2. The function returns SUCCESS if the flight was 
//*					added and FAILURE if it failed.
//* Parameters   :	pRunway - runway pointer
//*					pFlight - flight pointer
//* Return Value :	Result - SUCCESS or FAILURE of adding the flight to the runway
//*********************************************************************************************************
Result addFlight(PRUNWAY pRunway, PFLIGHT pFlight){ 
	if (pRunway == NULL || pFlight == NULL )
		return FAILURE; // illegal pointers
	if (pRunway->run_type != pFlight->ftype)
		return FAILURE; // flight type isn't the same of runway type
	NODE* tmp;
	tmp = pRunway->head;
	if (isFlightExists(pRunway, pFlight->flight_id))// flight already exists on runway
		return FAILURE;
	//////////////////////////////////////////
	// case it's the first flight on runway //
	//////////////////////////////////////////
	if (pRunway->num_of_flights == 0 ){
		
		tmp = (NODE*)malloc(sizeof(NODE));
		tmp->pFlight = createFlight(pFlight->flight_id , pFlight->ftype , pFlight->dest, pFlight->emergency);
		tmp->next = NULL;
		pRunway->head = tmp;
		(pRunway->num_of_flights)++;
		return SUCCESS;
	}
	////////////////////////////////////////////////////////////////
	// case the first flight is REGULAR and entering is EMERGENCY //
	////////////////////////////////////////////////////////////////
	if (tmp->pFlight->emergency == FALSE && pFlight->emergency == TRUE) {
		
		NODE* tmp_emer=(NODE*)malloc(sizeof(NODE));
		tmp_emer->pFlight = createFlight(pFlight->flight_id, pFlight->ftype, pFlight->dest, pFlight->emergency);
		tmp_emer->next = tmp;
		pRunway->head = tmp_emer;
		(pRunway->num_of_flights)++;
		return SUCCESS;
	}
	////////////////// goes until the first regular flight or until list ends
	while (tmp->next != NULL && tmp->next->pFlight->emergency == TRUE)
		tmp=tmp->next; 
	//////////////////////////////////////////////////////////////
	// case when emergency flight or no other flights on runway //
	//////////////////////////////////////////////////////////////
	if (pFlight->emergency == TRUE){
		NODE* current_next = tmp->next;
		tmp->next = (NODE*)malloc(sizeof(NODE));
		tmp->next->pFlight = createFlight(pFlight->flight_id, pFlight->ftype, pFlight->dest, pFlight->emergency);
		tmp->next->next = current_next; // re-links to the next flight
		(pRunway->num_of_flights)++;
		return SUCCESS;
		}
	/////////////////////////////////////////
	// case when there are regular flights //
	/////////////////////////////////////////
	while (tmp->next != NULL) 
		tmp=tmp->next; // goes to the end of the list
	tmp->next = (NODE*)malloc(sizeof(NODE));
	tmp->next->pFlight = createFlight(pFlight->flight_id , pFlight->ftype , pFlight->dest, pFlight->emergency);
	tmp->next->next = NULL;
	(pRunway->num_of_flights)++;
	return SUCCESS;
}

//*********************************************************************************************************
//* function name:	removeFlight
//* Description  :	Gets the pointer to a runway and flight id and removes it if exist on runway
//* Parameters   :	pRunway - a pointer to a runway
//*					id - flight id
//* Return Value :	Result - SUCCESSS or FAILURE in removing the flight with the given id
//*********************************************************************************************************
Result removeFlight(PRUNWAY pRunway, long int id){
	if (pRunway == NULL)
		return FAILURE; // illegal pointer
	if (isFlightExists(pRunway, id) == FALSE)
		return FAILURE; // flight isn't on runway
	NODE* tmp;
	tmp = pRunway->head;	
	if (tmp->pFlight->flight_id == id){
		// case it's the first flight
		destroyFlight(tmp->pFlight); 
		pRunway->head = tmp->next;
		free(tmp);
		(pRunway->num_of_flights)--;
		return SUCCESS;
	}
	
	while (tmp->next->pFlight->flight_id != id)
		// case elsewise
		tmp=tmp->next; // goes to the flight linked before to the requested flight
	NODE* requested_node = tmp->next;
	destroyFlight(requested_node->pFlight);
	tmp->next = tmp->next->next;
	free(requested_node);
	(pRunway->num_of_flights)--;
	return SUCCESS;
}

//*********************************************************************************************************
//* function name:	depart
//* Description  :	Gets the pointer to a runway and removes the first flight
//* Parameters   :	pRunway - a pointer to a runway
//* Return Value :	Result - SUCCESSS or FAILURE in removing the first flight in the runway
//*********************************************************************************************************
Result depart(PRUNWAY pRunway){ 
	if (pRunway == NULL)
		return FAILURE; // illegal pointer
	if (pRunway->num_of_flights == 0)
		return FAILURE; // no flights on runway
	NODE* tmp;
	tmp = pRunway->head;
	destroyFlight(tmp->pFlight); 
	pRunway->head = tmp->next;
	free(tmp);
	(pRunway->num_of_flights)--;
	return SUCCESS;
}

//*********************************************************************************************************
//* function name:	printRunway
//* Description  :	Gets the pointer to a runway and prints the data of it(id, type, num of flights waiting
//*					and flights' data)
//* Parameters   :	pRunway - a pointer to a runway
//* Return Value :	Result - SUCCESSS or FAILURE in printing the runway data
//*********************************************************************************************************
Result printRunway(PRUNWAY pRunway){
//
	if (pRunway != NULL){
		printf("Runway %ld ", pRunway->runway_id);
		char run_type;
		run_type =( pRunway->run_type == DOMESTIC) ? 'D' : 'I';
		if (run_type == 'D')
			printf("domestic\n");
		else
			printf("international\n");
		printf("%ld flights are waiting:\n", pRunway->num_of_flights);
		NODE* tmp;
		tmp = pRunway->head;
		while (tmp!=NULL){ 
			char flight_urgence;
			flight_urgence =(tmp->pFlight->emergency == TRUE) ? 'E' : 'R';
			printf("Flight %ld %c %s %c\n", tmp->pFlight->flight_id, run_type, tmp->pFlight->dest, flight_urgence);
			tmp=tmp->next;
		}
		return SUCCESS;
		}
  return FAILURE;
}


