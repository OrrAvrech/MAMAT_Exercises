#ifndef graph_h_
#define graph_h_

#include "set.h"
#define MAX_WEIGHT 10
#define MIN_WEIGHT 0
#define UNDEFINED -1
typedef struct _Graph
{
	PSet vertex_set;
	PSet edges_set;
} *PGraph, Graph;

typedef struct _Vertex
{
	int serialNumber;
} *PVertex, Vertex;

typedef struct _Edge
{
	PVertex nodeA;              
	PVertex nodeB;
	int weight;
} *PEdge, Edge;


PGraph GraphCreate();
void GraphDestroy(PGraph);
Bool GraphAddVertex(PGraph, int);
Bool GraphAddEdge(PGraph pGraph, int vertex1, int vertex2, int weight);
PSet GraphNeighborVertices(PGraph, int);
Bool GraphFindShortestPath(PGraph, int, int*, int*);    //need to be written
int GraphGetNumberOfEdges(PGraph);
int GraphGetNumberOfVertices(PGraph);
PSet GraphVerticesStatus(PGraph);
PSet GraphEdgesStatus(PGraph);

#endif /* GRAPH_H_ */
