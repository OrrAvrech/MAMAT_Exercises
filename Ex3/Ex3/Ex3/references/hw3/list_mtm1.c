/*
 * list_mtm1.c
 *
 *  Created on: 3 בדצמ 2014
 *      Author: omer
 */
#include "list_mtm1.h"
#include <stdio.h>
#include <stdlib.h>

#define BAD_ALLOC(P) if(!P) return NULL
#define CHECK_NULL(P) if(!P) return NULL
#define IS_NULL_ARG(P) if(!P) return LIST_NULL_ARGUMENT
#define CHECK_NULL_ARG_INT(P) if (!P) return -1
#define IS_BAD_ALLOC(P) if (!P) return LIST_OUT_OF_MEMORY

struct node_t{
	ListElement data;
	struct node_t* next;
};

typedef struct node_t* Node;

struct List_t{
	int sizeOfList;
	Node head;
	Node iterator;
	CopyListElement copyElement;
	FreeListElement freeElement;
};

List listCreate(CopyListElement copyElement, FreeListElement freeElement){
	if (!copyElement || !freeElement){
		return NULL;
	}
	List newList = malloc(sizeof(*newList));
	BAD_ALLOC(newList);
	newList->sizeOfList = 0;
	newList->iterator = NULL;
	newList->head= malloc(sizeof(struct node_t));
	if(!newList->head){
		free(newList);
		return NULL;
	}
	newList->head->next = NULL;
	newList->head->data = NULL;
	newList->copyElement = copyElement;
	newList->freeElement = freeElement;
	return newList;
}

ListElement listGetFirst(List list){
	CHECK_NULL(list);
	if (list->sizeOfList == 0){
		return NULL;
	}
	list->iterator=list->head->next;
	ListElement element = list->iterator->data;
	return element;
}

ListElement listGetNext(List list){
	CHECK_NULL(list);
	Node temp=list->iterator;
	CHECK_NULL(list->iterator);
	list->iterator = list->iterator->next;
	if(!list->iterator){
		list->iterator=temp;
		return NULL;
	}
	ListElement element = list->iterator->data;
	return element;
}

int listGetSize(List list){
	CHECK_NULL_ARG_INT(list);
	return list->sizeOfList;
}

ListElement listGetCurrent(List list){
	CHECK_NULL(list);
	if (list->sizeOfList == 0){
		return NULL;
	}
	CHECK_NULL(list->iterator);
	ListElement element = list->iterator->data;
	return element;
}

ListResult listInsertLast(List list, ListElement element){
	IS_NULL_ARG(list);
	Node newNode = malloc(sizeof(*newNode));
	IS_BAD_ALLOC(newNode);
	ListElement newElement = list->copyElement(element);
	IS_BAD_ALLOC(newElement);
	newNode->data = newElement;
	newNode->next = NULL;
	Node ptr = list->head;
	Node temp=ptr;
	while(ptr){
		temp=ptr;
		ptr = ptr->next;
	}
	temp->next = newNode;
	list->sizeOfList++;
	return LIST_SUCCESS;
}

ListResult listInsertFirst(List list, ListElement element){
	IS_NULL_ARG(list);
	Node newNode = malloc(sizeof(*newNode));
	IS_BAD_ALLOC(newNode);
	ListElement newElement = list->copyElement(element);
	IS_BAD_ALLOC(newElement);
	newNode->data = newElement;
	newNode->next = list->head->next;
	list->head->next = newNode;
	list->sizeOfList++;
	return LIST_SUCCESS;
}

ListResult listInsertBeforeCurrent(List list, ListElement element){
	IS_NULL_ARG(list);
	if(!list->iterator){
		return LIST_INVALID_CURRENT;
	}
	Node newNode = malloc(sizeof(*newNode));
	IS_BAD_ALLOC(newNode);
	ListElement newElement = list->copyElement(element);
	IS_BAD_ALLOC(newElement);
	newNode->data = newElement;
	Node ptr = list->head;
	Node prevPtr = NULL;
	while(ptr != list->iterator){
		prevPtr = ptr;
		ptr = ptr->next;
	}
	newNode->next = list->iterator;
	prevPtr->next = newNode;
	list->sizeOfList++;
	return LIST_SUCCESS;
}

ListResult listInsertAfterCurrent(List list, ListElement element){
	IS_NULL_ARG(list);
	if(!list->iterator){
			return LIST_INVALID_CURRENT;
		}
	if(!list->iterator->next){
		return listInsertLast(list , element);
	}
	Node newNode = malloc(sizeof(*newNode));
	IS_BAD_ALLOC(newNode);
	ListElement newElement = list->copyElement(element);
	IS_BAD_ALLOC(newElement);
	newNode->data = newElement;
	newNode->next = list->iterator->next;
	list->iterator->next = newNode;
	list->sizeOfList++;
	return LIST_SUCCESS;
}

List listCopy(List list){
	CHECK_NULL(list);
	List newList = listCreate(list->copyElement,list->freeElement);
	BAD_ALLOC(newList);
	if(list->sizeOfList==0){
		return newList;
	}
	Node ptr=list->head->next;
	while(ptr){
		if(listInsertLast(newList, ptr->data) !=  LIST_SUCCESS){
			return NULL;
		}
		ptr=ptr->next;
	}
	newList->sizeOfList = list->sizeOfList;
	newList->iterator = list->iterator;
	return newList;
}

ListResult listRemoveCurrent(List list){
	IS_NULL_ARG(list);
	if(list->iterator == NULL){
		return LIST_INVALID_CURRENT;
	}
	Node ptr = list->head->next;
	Node prevPtr = list->head;
	while(ptr != list->iterator){
		prevPtr = ptr;
		ptr = ptr->next;
	}
	if(!list->iterator->next){
		prevPtr->next = NULL;
	}else{
	prevPtr->next = list->iterator->next;
	}
	list->freeElement(list->iterator->data);
	free(list->iterator);
	list->iterator = NULL;
	list->sizeOfList--;
	return LIST_SUCCESS;
}

static Node listGetLast(List list){
	if(list->sizeOfList==0){
		return NULL;
	}
	Node ptr = list->head;
	Node temp=ptr;
		while(ptr){
			temp=ptr;
			ptr = ptr->next;
		}
		return temp;
}

static Node listGetBeforeLast(List list){
	if(list->sizeOfList<=1){
		return NULL;
	}
	Node ptr = list->head;
	Node temp=ptr;
		while(ptr->next){
			temp=ptr;
			ptr = ptr->next;
		}
		return temp;
}

ListResult listClear(List list){
	IS_NULL_ARG(list);
	if(list->sizeOfList==0){
		return LIST_SUCCESS;
	}
	int counter=list->sizeOfList;
	Node last=NULL;
	Node beLast=NULL;
	while(counter>0){
		last=listGetLast(list);
		beLast=listGetBeforeLast(list);
		if(!beLast){
			list->freeElement(last->data);
			free(last);
			list->sizeOfList--;
			break;
		}
		list->freeElement(last->data);
		free(beLast->next);
		beLast->next = NULL;
		counter--;
		list->sizeOfList--;
	}
	list->head->next =NULL;
	list->iterator=NULL;
	return LIST_SUCCESS;
}

void listDestroy(List list){
	listClear(list);
	free(list->head);
	free(list);
}

List listFilter(List list, FilterListElement filterElement, ListFilterKey key){
	CHECK_NULL(list);
	CHECK_NULL(filterElement);
	List newList = listCreate(list->copyElement,list->freeElement);
	BAD_ALLOC(newList);
	if(list->sizeOfList==0){
		return newList;
	}
	int counter=0;
	Node ptr=list->head->next;
	while(ptr){
		if(filterElement(ptr->data,key)){
			if(listInsertLast(newList, ptr->data) !=  LIST_SUCCESS){
				return NULL;
			}
			counter++;
		}
		ptr=ptr->next;
	}
	newList->sizeOfList=counter;
	newList->iterator =NULL;
	return newList;
}






int swapData(List list,Node node1, Node node2){
	if(!node1 || !node2){
		return -1;
	}
	ListElement temp = list->copyElement(node1->data);
	if(!temp){
		return -1;
	}
	list->freeElement(node1->data);
	node1->data = node2->data;
	node2->data = temp;
	return 1;
}

int bubble(List list, int n, CompareListElements compareElement) {
	int i, swapped = 0;
	if(listGetSize(list)<=1){
		return 1;
	}
	Node ptr2=list->head->next;
	Node ptr1=ptr2->next;
	for(i =1; i < n; i++){
			if(compareElement(ptr2->data, ptr1->data)>0) {
				if(swapData(list, ptr2, ptr1)==-1){
					return -1;
				}
				swapped = 1;
			}
			ptr1=ptr1->next;
			ptr2=ptr2->next;
	}
	return swapped;
}

int bubble_sort(List list, CompareListElements compareElement) {
	int not_sorted = 1;
	int n=list->sizeOfList;
	while( (n> 1) && not_sorted){
		not_sorted = bubble(list, n--, compareElement);
		if(not_sorted==-1){
			return -1;
		}
	}
	return 0;
}

ListResult listSort(List list, CompareListElements compareElement){
	IS_NULL_ARG(list);
	IS_NULL_ARG(compareElement);
	List justInCase = listCopy(list);
	if(bubble_sort(list, compareElement)==-1){
		listDestroy(list);
		list=justInCase;
		return LIST_OUT_OF_MEMORY;
	}
	listDestroy(justInCase);
	return LIST_SUCCESS;
}

