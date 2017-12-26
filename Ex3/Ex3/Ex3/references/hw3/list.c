/*
* list.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

typedef struct Node_t { // linked list nodes
	PElem current_elem;
	struct Node_t* next;

} NODE, *PNode;

typedef struct List_  {// linked list struct
	PNode Iterator;
	PNode head;
	int LSize; // num of nodes 				  
	CLONE_FUNC cloneFunc;
	DESTROY_FUNC destroyFunc;

} List;


//*********************************************************************************************************
//* function name:	ListCreate
//* Description  :	Given a clone and destroy functions from the user, the fucntion creates a general ADT list
//* Parameters   :	cloneFunc - function given by user to copy 
//*					destroyFunc - function given by user to destroy 
//* Return Value :	PList - a pointer to the list
//*********************************************************************************************************
PList ListCreate(CLONE_FUNC cloneFunc, DESTROY_FUNC destroyFunc) {
	PList pList = NULL;
	if ((pList = (PList)malloc(sizeof(List)))) {
		pList->Iterator = NULL;
		pList->head = NULL;
		pList->LSize = 0;
		pList->cloneFunc = cloneFunc;
		pList->destroyFunc = destroyFunc;
	}
	return pList;
}

//*********************************************************************************************************
//* function name:	ListDestroy
//* Description  :	Destroys and free alloced memory to a given list
//* Parameters   :	pList - a pointer to a list
//* Return Value :	None
//*********************************************************************************************************
void ListDestroy(PList pList) {
	if ((pList == NULL)) return; // no list or empty list
	while (pList->head) {
		pList->destroyFunc(pList->head->current_elem);
		pList->Iterator = pList->head;
		pList->head = pList->head->next;
		free(pList->Iterator);
		(pList->LSize)--;
	}
	free(pList);
}

//*********************************************************************************************************
//* function name:	ListAdd
//* Description  :	Gets an element to copy in the given list
//* Parameters   :	pList - a pointer to the list
//*					pElem - a poiinter to the element that needs to be COPIED to the list
//* Return Value :	SUCCESS or FAIL - adding the element to the list ( FAIL can be caused by invalid parameters
//*					or failing to allocate memory)
//*********************************************************************************************************
Result ListAdd(PList pList, PElem pElem) {
	if ((pList == NULL) || (pElem == NULL)) return FAIL;
	PElem new_elem = pList->cloneFunc(pElem);
	if (new_elem == NULL) return FAIL; // failed to clone the elem
	PNode new_node;
	if ((new_node = (PNode)malloc(sizeof(NODE))) == NULL) {
		free(new_elem);
		return FAIL; // failed to alloc a Node;
	}
	new_node->current_elem = new_elem;
	new_node->next = pList->head;
	pList->head = new_node;
	(pList->LSize)++;
	pList->Iterator = NULL;
	return SUCCESS;
}

//*********************************************************************************************************
//* function name:	ListGetFirst
//* Description  :	points iterator to the head of the list and returns a pointer to it
//* Parameters   :	pList - a pointer to the list
//* Return Value :	PElem - pointer to the first element in the list
//*********************************************************************************************************
PElem ListGetFirst(PList pList) {
	if ((pList == NULL) || (pList->LSize == 0))
		return NULL; // no list or empty list
	pList->Iterator = pList->head;
	return pList->Iterator->current_elem;

}

//*********************************************************************************************************
//* function name:	ListGetNext
//* Description  :	returns a pointer to the next elem in the list.
//* Parameters   :	pList - a pointer to the list
//* Return Value :	PElem - pointer to the next element in the list(NULL if fails / pointing at NULL / list ended)
//*********************************************************************************************************
PElem ListGetNext(PList pList) {
	if ((pList == NULL) || (pList->Iterator == NULL))
		return NULL; // no list or iterator is pointing at NULL
	pList->Iterator = pList->Iterator->next;
	if ((pList->Iterator == NULL))
		return NULL;
	return pList->Iterator->current_elem;
}

//*********************************************************************************************************
//* function name:	ListRemove
//* Description  :	Deletes the node the iterator currently pointing at
//* Parameters   :	pList - a pointer to the list
//* Return Value :	SUCCESS or FAIL - SUCCESS if node is deleted or FAIL if not(iterator at NULL or deleting failed
//*********************************************************************************************************
Result ListRemove(PList pList) {
	if ((pList == NULL) || (pList->Iterator == NULL) || (pList->head == NULL))
		return FAIL; // no list/empty list or illegal iterator
	if (pList->head == pList->Iterator) { // case it's the head of the list
		pList->destroyFunc(pList->Iterator->current_elem);
		pList->head = pList->Iterator->next;
		free(pList->Iterator);
		pList->Iterator = NULL;
		(pList->LSize)--;
		return SUCCESS;
	}
	PNode tmp = pList->head;
	while (tmp->next != pList->Iterator) { // advance to the one before the requested node
		tmp = tmp->next;
	}
	pList->destroyFunc(pList->Iterator->current_elem);
	tmp->next = pList->Iterator->next;
	free(pList->Iterator);
	pList->Iterator = NULL;
	(pList->LSize)--;
	return SUCCESS;
}

//*********************************************************************************************************
//* function name:	ListGetSize
//* Description  :	return the size of the list(in int)
//* Parameters   :	pList - a pointer to the list
//* Return Value :	List Size - (int)
//*********************************************************************************************************
int ListGetSize(PList pList) {
	if (pList == NULL)
		return 0; // no list or empty list
	return pList->LSize;
}