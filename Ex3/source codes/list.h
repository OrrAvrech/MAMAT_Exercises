typedef void* PElem;

typedef struct _Node {
	PElem pElem;		// element data
	struct _Node *pNext;	// pointer to next element
} Node, *pNode;

typedef struct List_
{
	pNode *head;
	pNode *iterator;
}*PList;


typedef enum{FAIL, SUCCESS} Result;

/*User functions*/
typedef PElem (*CLONE_FUNC)(PElem);
typedef void (*DESTROY_FUNC)(PElem);

/*Interface functions*/
PList ListCreate(CLONE_FUNC, DESTROY_FUNC);
void ListDestroy(PList);
Result ListAdd(PList, PElem);
PElem ListGetFirst(PList);
PElem ListGetNext(PList);

Result ListRemove(PList);
int ListGetSize(PList);

