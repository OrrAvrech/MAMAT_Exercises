#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "list.h"

Bool Compare_Edges(PElem pElem1, PElem pElem2);
PElem Clone_Edge(PElem org_pElem);
void Destroy_Edge(PElem pElem);
Bool Compare_Vertex(PElem pElem1, PElem pElem2);
void Destroy_Vertex(PElem pElem);
PElem Clone_Vertex(PElem org_pElem);
int GraphGetNumberOfEdges(PGraph pGraph);
int GraphGetNumberOfVertices(PGraph pGraph);
Bool GraphAddEdge(PGraph pGraph, int vertex1, int vertex2, int weight);
Bool GraphAddVertex(PGraph pGraph, int vertex_num);
void GraphDestroy(PGraph pGraph);
PGraph GraphCreate();
PSet GraphNeighborVertices(PGraph pGraph, int source_vertex);
PSet GraphEdgesStatus(PGraph pGraph);
PSet GraphVerticesStatus(PGraph pGraph);

// **************************************     Edges Function             ************************
 
/* the function compares 2 given edges
Input: pointer to Edge1, pointer to Edge2
output: BOOL TRUE if both the edges are equal and FALSE otherwise*/
Bool Compare_Edges(PElem pElem1, PElem pElem2)
{
	PEdge pEdge1 = (PEdge)pElem1;
	PEdge pEdge2 = (PEdge)pElem2;
	if (pEdge1 == NULL || pEdge2 == NULL) 
		return FALSE;
	if (Compare_Vertex((PElem)pEdge1->nodeA, (PElem)pEdge2->nodeA) && Compare_Vertex((PElem)pEdge1->nodeB, (PElem)pEdge2->nodeB))
		return TRUE;
	else if (Compare_Vertex((PElem)pEdge1->nodeA, (PElem)pEdge2->nodeB) && Compare_Vertex((PElem)pEdge1->nodeB, (PElem)pEdge2->nodeA))
		return TRUE;
	else 
		return FALSE;
}

/* the function clones a given edge and returns anothe one.
Input: ppointer to Edge
output: pointer to the new Edge*/
PElem Clone_Edge(PElem org_pElem)
{
	if (org_pElem == NULL)
	{
		return NULL;
	}
	PEdge org_pEdge = (PEdge)org_pElem;
	PEdge new_pEdge;
	new_pEdge = malloc(sizeof(Edge));
	if (new_pEdge == NULL)
	{
		return NULL;
	}
	new_pEdge->nodeA = (PVertex)Clone_Vertex((PElem)org_pEdge->nodeA);
	if (new_pEdge->nodeA == NULL)
	{
		Destroy_Edge((PElem)new_pEdge);
		return NULL;
	}
	new_pEdge->nodeB = (PVertex) Clone_Vertex((PElem) org_pEdge->nodeB);
	if (new_pEdge->nodeB == NULL)
	{
		Destroy_Vertex((PElem)new_pEdge->nodeA);
		Destroy_Edge((PElem)new_pEdge);
		return NULL;
	}
	new_pEdge->weight = org_pEdge->weight;
	return (PElem)new_pEdge;
}

/* the function destroys an edge
Input: pointer to Edge
output: none*/
void Destroy_Edge(PElem pElem)
{
	if (pElem == NULL) 
		return;
	PEdge pEdge = (PEdge)pElem;
	Destroy_Vertex((PElem)pEdge->nodeA);
	Destroy_Vertex((PElem)pEdge->nodeB);
	free(pEdge);
}

// ************************************      Vertex Functions      **************************

/* the function compares 2 given Vertices
Input: pointer to vertex1, pointer to vertex2
output: BOOL TRUE if both the vertices are equal and FALSE otherwise*/
Bool Compare_Vertex(PElem pElem1, PElem pElem2)
{
	PVertex pVertex1 = (PVertex)pElem1;
	PVertex pVertex2 = (PVertex)pElem2;
	if (pVertex1 == NULL || pVertex2 == NULL)
		return FALSE;
	if (pVertex1->serialNumber == pVertex2->serialNumber)
		return TRUE;
	else
		return FALSE;
}

/* the function destroys a vertex
Input: pointer to vertex
output: none*/
void Destroy_Vertex(PElem pElem)
{
	if (pElem == NULL)
		return;
	PVertex pVertex = (PVertex)pElem;
	free(pVertex);
}

/* the function clones a given vertex and returns anothe one.
Input: pointer to vertex
output: pointer to the new vertex*/
PElem Clone_Vertex(PElem org_pElem)
{
	if (org_pElem == NULL)
	{
		return NULL;
	}
	PVertex org_pVertex = (PVertex)org_pElem;
	PVertex new_pVertex;
	new_pVertex = malloc(sizeof(Vertex));
	if (new_pVertex == NULL)
	{
		return NULL;
	}
	new_pVertex->serialNumber = org_pVertex->serialNumber;
	return (PElem)new_pVertex;
}


// ***********************************         Graph Functions       *****************************

/* the function creates a graph
Input: none
output: pointer to the new graph*/
PGraph GraphCreate()
{
	PSet vertex_set, edge_set;
	vertex_set = SetCreate(Compare_Vertex, Clone_Vertex, Destroy_Vertex);
	if (vertex_set == NULL)
		return NULL;
	edge_set = SetCreate(Compare_Edges, Clone_Edge, Destroy_Edge);
	if (vertex_set == NULL)
	{
		SetDestroy(vertex_set);
		return NULL;
	}
	PGraph pGraph;
	pGraph = malloc(sizeof(Graph));
	if (pGraph == NULL)
	{
		SetDestroy(edge_set);
		SetDestroy(vertex_set);
		return NULL;
	}
	pGraph->vertex_set = vertex_set;
	pGraph->edges_set = edge_set;
	return pGraph;
}

/* the function clears a graph and all his elements from memory
Input: pointer to graph
output: none*/
void GraphDestroy(PGraph pGraph)
{
	if (pGraph == NULL)
		return;
	SetDestroy(pGraph->edges_set);
	SetDestroy(pGraph->vertex_set);
	free(pGraph);
}

/* the function adds a vertex to a graph
Input: pointer to graph, the vertex number (must be the next number, or in other words: the vertices nums)
output: BOOL TRUE if managed to add the vertex and FALSE otherwise*/
Bool GraphAddVertex(PGraph pGraph, int vertex_num)
{
	if (pGraph == NULL)
		return FALSE;
	if (vertex_num != GraphGetNumberOfVertices(pGraph))
		return FALSE;
	PVertex pVertex;
	pVertex = malloc(sizeof(Vertex));
	pVertex->serialNumber = vertex_num;
	PElem pElem = (PElem)pVertex;
	Bool result = SetAdd(pGraph->vertex_set, pElem);
	free(pElem);
	return result;
}

/* the function adds an edge to a graph
Input: pointer to graph, vertex1, vertex2, weight
output: BOOL TRUE if managed to add the edge and FALSE otherwise*/
Bool GraphAddEdge(PGraph pGraph, int vertex1, int vertex2, int weight)
{
	Bool result;
	if (pGraph == NULL)
		return FALSE;
	if (weight > MAX_WEIGHT || weight < MIN_WEIGHT || vertex1 == vertex2)
		return FALSE;
	PEdge pEdge;
	pEdge = malloc(sizeof(Edge));
	PVertex pVertex1, pVertex2 ;
	pVertex1 = malloc(sizeof(Vertex));
	pVertex2 = malloc(sizeof(Vertex));
	pVertex1->serialNumber = vertex1;
	pVertex2->serialNumber = vertex2;
	pEdge->nodeA = pVertex1;
	pEdge->nodeB = pVertex2;
	if (SetFindElement(pGraph->vertex_set, (PElem)pVertex1) == NULL || SetFindElement(pGraph->vertex_set, (PElem)pVertex2) == NULL)
	{
		Destroy_Edge((PElem)pEdge);
		return FALSE;
	}
	
	pEdge->weight = weight;
	result = (SetAdd(pGraph->edges_set, (PElem)pEdge));
	Destroy_Edge((PElem)pEdge);
	return result;
}

/* the function return the number of edges in the graph
Input: pointer to graph
output: number of edges*/
int GraphGetNumberOfEdges(PGraph pGraph)
{
	if (pGraph == NULL)
		return 0;
	return SetGetSize(pGraph->edges_set);
}

/* the function return the number of verticess in the graph
Input: pointer to graph
output: number of vertices*/
int GraphGetNumberOfVertices(PGraph pGraph)
{
	if (pGraph == NULL)
		return 0;
	return SetGetSize(pGraph->vertex_set);
}

/* the function returns a list(set) of all the vertices that have an edge connection with the source vertex
Input: pointer to graph , source vertex
output: set of neighbor vertices*/
PSet GraphNeighborVertices(PGraph pGraph, int source_vertex)
{
	if (pGraph == NULL)
		return NULL;
	PSet pSet;
	PEdge pEdge;
	PVertex src_pVertex;
	src_pVertex = malloc(sizeof(Vertex));
	src_pVertex->serialNumber = source_vertex;
	pSet = SetCreate(Compare_Vertex, Clone_Vertex, Destroy_Vertex);
	if (pSet == NULL)
	{
		Destroy_Vertex((PElem)src_pVertex);
		return NULL;
	}
	PElem pElem_v, pElem_e;
	pElem_e = SetGetFirst(pGraph->edges_set);
	if (pElem_e == NULL)
	{
		Destroy_Vertex((PElem)src_pVertex);
		SetDestroy(pSet);
		return NULL;
	}
	if (!SetFindElement(pGraph->vertex_set, (PElem)src_pVertex))
	{
		Destroy_Vertex((PElem)src_pVertex);
		SetDestroy(pSet);
		return NULL;
	}
	while (pElem_e)
	{
		pEdge = (PEdge)pElem_e;
		if (Compare_Vertex((PElem) src_pVertex, (PElem)pEdge->nodeA))
		{
			pElem_v = (PElem)pEdge->nodeB;
			if (!SetAdd(pSet, pElem_v))
			{
				Destroy_Vertex((PElem)src_pVertex);
				SetDestroy(pSet);
				return NULL;
			}
		}
		else if (Compare_Vertex((PElem)src_pVertex, (PElem)pEdge->nodeB))
		{
			pElem_v = (PElem)pEdge->nodeA;
			if (!SetAdd(pSet, pElem_v))
			{
				Destroy_Vertex((PElem)src_pVertex);
				SetDestroy(pSet);
				return NULL;
			}
		}
		pElem_e = SetGetNext(pGraph->edges_set);
	}
	Destroy_Vertex((PElem)src_pVertex);
	return pSet;
}
/* the function returns a pointer to the vertecies set of the graph
Input: pointer to graph
output: set of vertices*/
PSet GraphVerticesStatus(PGraph pGraph)
{
	if (pGraph == NULL)
		return NULL;
	return pGraph->vertex_set;
}

/* the function returns a pointer to the edges set of the graph
Input: pointer to graph
output: set of edges*/
PSet GraphEdgesStatus(PGraph pGraph)
{
	if (pGraph == NULL)
		return NULL;
	return pGraph->edges_set;
}