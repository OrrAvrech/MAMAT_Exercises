<<<<<<< HEAD
#ifndef GRAPH_H_
#define GRAPH_H_
typedef struct _Graph* PGraph;
=======
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
>>>>>>> a0d25591a9a6b48c5806d5114f50587ea71316fe

typedef struct _Vertex
{
	int serialNumber;
} Vertex;

typedef struct _Edge
{
	struct _Vertex* nodeA;
	struct _Vertex* nodeB;
	int weight;
} Edge;

typedef struct _Vertex* PVertex;
typedef struct _Edge* PEdge;

PGraph GraphCreate();
void GraphDestroy(PGraph);
Bool GraphAddVertex(PGraph, int);
Bool GraphAddEdge(PGraph pGraph, int vertex1, int vertex2, int weight);
PSet GraphNeighborVertices(PGraph, int);
<<<<<<< HEAD
Bool GraphFindShortestPath(PGraph pGraph, int source, int* dist, int* prev);

=======
Bool GraphFindShortestPath(PGraph, int, int*, int*);    //need to be written
>>>>>>> a0d25591a9a6b48c5806d5114f50587ea71316fe
int GraphGetNumberOfEdges(PGraph);
int GraphGetNumberOfVertices(PGraph);

PSet GraphVerticesStatus(PGraph);
PSet GraphEdgesStatus(PGraph);

#endif /* GRAPH_H_ */
