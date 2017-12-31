#ifndef SET_H_
#define SET_H_
typedef enum { FALSE, TRUE } Bool;


/*User functions*/
typedef Bool(*COMP_FUNC)(PElem, PElem);

typedef struct _Set
{
	PList setElements;
	COMP_FUNC cmpFunc;
} *PSet, Set;


/*Interface functions*/
PSet SetCreate(COMP_FUNC, CLONE_FUNC, DESTROY_FUNC);
void SetDestroy(PSet);
Bool SetAdd(PSet, PElem);
PElem SetFindElement(PSet, PElem);
PElem SetGetFirst(PSet);
PElem SetGetNext(PSet);
int SetGetSize(PSet);
Bool SetRemoveElement(PSet, PElem);

#endif /* SET_H_ */
