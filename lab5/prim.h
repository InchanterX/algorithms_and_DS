#ifndef PRIM_H
#define PRIM_H

#include "graph.h"

typedef struct
{
    int source;
    int destination;
    int weight;
} Minimum_spanning_treeEdge;

typedef struct
{
    Minimum_spanning_treeEdge *edges;
    int count;
    int capacity;
} Minimum_spanning_treeResult;

Minimum_spanning_treeResult *prim_algorithm(Graph *graph);
void minimum_spanning_tree_result_destroy(Minimum_spanning_treeResult *result);
void minimum_spanning_tree_result_print(Minimum_spanning_treeResult *result);

#endif