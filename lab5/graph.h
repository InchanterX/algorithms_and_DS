#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"

typedef struct
{
    EdgeList *edges;
    int vertex_count;
    int edge_count;
} Graph;

Graph *graph_create(int vertices);
void graph_destroy(Graph *graph);
int graph_add_edge(Graph *graph, int source, int destination, int weight);
int graph_get_vertex_count(Graph *graph);
int graph_get_edge_count(Graph *graph);
EdgeList *graph_get_edges(Graph *graph);
void graph_print(Graph *graph);

#endif