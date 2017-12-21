#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ex2.h"
#include "flight.h"
#include "runway.h"
#include "airport.h"

//#define _DEBUG 
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

void main(){
	/* 
	PRUNWAY pRunway1;
	pRunway1 = createRunway(2, DOMESTIC);
	PFLIGHT pFlight1 = createFlight(1, DOMESTIC, "TLV", TRUE);
	PFLIGHT pFlight2 = createFlight(2, DOMESTIC, "JFK", FALSE);
	PFLIGHT pFlight3 = createFlight(3, DOMESTIC, "JRS", TRUE);
	PFLIGHT pFlight4 = createFlight(4, DOMESTIC, "JUV", FALSE);
	PFLIGHT pFlight99 = createFlight(99, INTERNATIONAL, "JUV", FALSE);
	addFlight(pRunway1, pFlight1);
	addFlight(pRunway1, pFlight2);
	addFlight(pRunway1, pFlight3);
	addFlight(pRunway1, pFlight4);

	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//1 3 2 4
	//Result rm = removeFlight(pRunway1, 75);
	//rm = removeFlight(pRunway1, 1);
	Result dep;
	//rm = removeFlight(pRunway1, 3);
	//dep=depart(pRunway1);
	//rm = removeFlight(pRunway1, 4);
	//dep=depart(pRunway1);
	//dep=depart(pRunway1); // right now it's a success
	//rm = removeFlight(pRunway1, 2);
	//destroyRunway(pRunway1);
	//int exists1 = isFlightExists(pRunway1, 1);
	//int exists2 = isFlightExists(pRunway1, 2);
	//int exists3 = isFlightExists(pRunway1, 3);
	//int exists4 = isFlightExists(pRunway1, 4);
	//int exists99 = isFlightExists(pRunway1, 99);
	//int d = removeFlight(pRunway1, 1);
	//int e = removeFlight(pRunway1, 2);
	printRunway(pRunway1);
	destroyRunway(pRunway1);
	destroyFlight(pFlight1);
	destroyFlight(pFlight2);
	destroyFlight(pFlight3);
	destroyFlight(pFlight4);
	destroyFlight(pFlight99);
	*/
	
	// airport //
	
	Result suc, fsuc, ssuc;
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	suc = addRunway(1, INTERNATIONAL);
	suc = addRunway(2, INTERNATIONAL);
	suc = addRunway(3, DOMESTIC);
	suc = addRunway(4, DOMESTIC);

	fsuc = addFlightToAirport(1, DOMESTIC, "TLV", FALSE);
	fsuc = addFlightToAirport(2, INTERNATIONAL, "BAR", TRUE);
	fsuc = addFlightToAirport(3, DOMESTIC, "TLV", TRUE);
	fsuc = addFlightToAirport(4, DOMESTIC, "ELT", FALSE);
	fsuc = addFlightToAirport(5, INTERNATIONAL, "JFK", FALSE);
	fsuc = addFlightToAirport(6, DOMESTIC, "TLV", FALSE);
	fsuc = addFlightToAirport(7, INTERNATIONAL, "BAR", FALSE);
	fsuc = addFlightToAirport(8, DOMESTIC, "ELT", TRUE);
	fsuc = addFlightToAirport(9, INTERNATIONAL, "KAR", TRUE);
	fsuc = addFlightToAirport(10, DOMESTIC, "ELT", FALSE);
	fsuc = addFlightToAirport(11, INTERNATIONAL, "KAR", FALSE);
	/*
	dsuc = departFromRunway(1);
	dsuc = departFromRunway(2);
	dsuc = departFromRunway(2);
	dsuc = departFromRunway(2);
	dsuc = departFromRunway(3);
	dsuc = departFromRunway(3);
	dsuc = departFromRunway(1);
	*
	printAirport();
	ssuc = stormAlert("TLV");
	printAirport();
	ssuc = stormAlert("KAR");
	printAirport();
	ssuc = stormAlert("BAR");
	printAirport();
	ssuc = stormAlert("JFK");
	printAirport();
	//*/
	//destroyAirport();
	int stop;
	scanf("%d", &stop);
}