#ifndef PRIM_H
#define PRIM_H

#include "graph.h"

typedef struct
{
    int source;
    int destination;
    int weight;
} MstEdge;

typedef struct
{
    MstEdge *edges;
    int count;
    int capacity;
} MstResult;

MstResult *prim_algorithm(Graph *graph);
void mst_result_destroy(MstResult *result);
void mst_result_print(MstResult *result);

#endif