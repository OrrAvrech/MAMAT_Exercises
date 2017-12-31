
typedef struct List_* PList;
typedef void* PElem;
typedef enum { FAIL, SUCCESS } Result;

/*User functions*/
<<<<<<< HEAD
typedef PElem(*CLONE_FUNC)(PElem);
typedef void(*DESTROY_FUNC)(PElem);
=======
typedef PElem (*CLONE_FUNC)(PElem);
typedef void (*DESTROY_FUNC)(PElem);
typedef enum { FAIL, SUCCESS } Result;

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
}List, *PList;

>>>>>>> a0d25591a9a6b48c5806d5114f50587ea71316fe

/*Interface functions*/
PList ListCreate(CLONE_FUNC, DESTROY_FUNC);
void ListDestroy(PList);
Result ListAdd(PList, PElem);
PElem ListGetFirst(PList);
PElem ListGetNext(PList);

Result ListRemove(PList);
int ListGetSize(PList);
