#ifndef GRAPH_H_
#define GRAPH_H_

#include "set.h"
#define MAX_WEIGHT 10
#define MIN_WEIGHT 0
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
	PVertex nodeA;              // should be a pointer or vertrx?
	PVertex* nodeB;
	int weight;
} *PEdge, Edge;


PGraph GraphCreate();
void GraphDestroy(PGraph);
Bool GraphAddVertex(PGraph, int);
Bool GraphAddEdge(PGraph pGraph, int vertex1, int vertex2, int weight);
PSet GraphNeighborVertices(PGraph, int);
Bool GraphFindShortestPath(PGraph pGraph, int source, int* dist, int* prev);
int GraphGetNumberOfEdges(PGraph);
int GraphGetNumberOfVertices(PGraph);
PSet GraphVerticesStatus(PGraph);
PSet GraphEdgesStatus(PGraph);

#endif /* GRAPH_H_ */