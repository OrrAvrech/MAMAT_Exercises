#include <stdio.h>
#include <stdlib.h>
#ifndef FLAG_LIST      //used to not redifine
#define FLAG_LIST
#include "list.h"
#endif

typedef struct _Node {
	PElem pElem;		// element data
	struct _Node *pNext;	// pointer to next element
} Node, *pNode;

typedef struct List_
{
	pNode head;
	pNode iterator;
	CLONE_FUNC clone_func;
	DESTROY_FUNC dest_func;
	int list_size; // will be updated on every change in order to skip counting all the elements everytime we need the list number
}List;


/* the function create a list and assign it the specific clone and destroy function
Input: clone func , destroy func
Output: list */
PList ListCreate(CLONE_FUNC clone_func, DESTROY_FUNC dest_func)
{
	PList list;
	list = malloc(sizeof(List));
	list->head = NULL;
	list->iterator = NULL;
	list->clone_func = clone_func;
	list->dest_func = dest_func;
	list->list_size = 0;
	return list;
}

/* the function clearing a list and all it contaions from memory
Input: list
Output: none */
void ListDestroy(PList list)
{
	pNode node, temp;
	node = list->head;
	while (node)
	{
		list->dest_func(node->pElem);
		temp = node;
		node = node->pNext;
		free(temp);
	}
	free(list);   // need to free head and iterator?
}
/* the function adds a Pelem as the first element of list
Input: list , pElem
Output Success if managed to insert the pElem and Fail otherwise */
Result ListAdd(PList list, PElem pElem)
{
	if (list == NULL || pElem == NULL) return FAIL;
	pNode new_node;
	PElem new_pElem;
	new_node = malloc(sizeof(Node));
	new_pElem = list->clone_func(pElem);
	new_node->pElem = new_pElem;
	new_node->pNext = list->head;
	list->head = new_node;
	list->iterator = NULL;
	list->list_size++;
	return SUCCESS;
}

/* the function moves the iterator to the head of the list and return its updated value
Input: list
output: node of the first element*/
PElem ListGetFirst(PList list)
{
	if (list == NULL || list->head == NULL) return NULL;
	list->iterator = list->head;
	return list->iterator->pElem;
}

/* the function moves the iterator to the next element and returns its updated value
Input: list
output: node of the next pElem*/
PElem ListGetNext(PList list)
{
	if (list == NULL || list->iterator->pNext == NULL) return NULL;
	list->iterator = list->iterator->pNext;
	return list->iterator->pElem;
}

/* the function removes the element the iterator of list points at.
Input: list 
Output Success if managed to remove the pElem and Fail otherwise */
Result ListRemove(PList list)
{
	if (list == NULL || list->iterator == NULL) return FAIL;
	pNode temp , prev_node;
	temp = list->head;
	while (temp->pNext != list->iterator && temp->pNext != NULL)
	{
		temp = temp->pNext;
	}
	prev_node = temp;
	temp = list->iterator;
	prev_node->pNext = temp->pNext;
	list->dest_func(temp->pElem);
	free(temp);
	list->iterator = NULL;
	list->list_size--;
	return SUCCESS;
}

/* the function returns the size of list
Input: list
Output: list size*/
int ListGetSize(PList list)
{
	return list->list_size;
}