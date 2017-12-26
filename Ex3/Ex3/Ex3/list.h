#ifndef _list_h
#define _list_h

typedef void* PElem;
/*User functions*/
typedef PElem(*CLONE_FUNC)(PElem);
typedef void(*DESTROY_FUNC)(PElem);
typedef enum { FAIL, SUCCESS } Result;

typedef struct _Node {
	PElem pElem;		// element data
	struct _Node *pNext;	// pointer to next element
} Node, *pNode;

typedef struct List_
{
	pNode *head;
	pNode *iterator;
	CLONE_FUNC clone_func;
	DESTROY_FUNC dest_func;
	int list_size // will be updated on every change in order to skip counting all the elements everytime we need the list number
}List, *PList;


/*Interface functions*/
PList ListCreate(CLONE_FUNC, DESTROY_FUNC);
void ListDestroy(PList);
Result ListAdd(PList, PElem);
PElem ListGetFirst(PList);
PElem ListGetNext(PList);
Result ListRemove(PList);
int ListGetSize(PList);
#endif // !_list_h
