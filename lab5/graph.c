#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph* graph_create(int vertices) {
    if (vertices <= 0) {
        return NULL;
    }

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph)
        return NULL;

    graph->edges = (EdgeList*)malloc(sizeof(EdgeList));
    if (!graph->edges) {
        free(graph);
        return NULL;
    }

    edge_list_init(graph->edges);
    graph->vertex_count = vertices;
    graph->edge_count = 0;

    return graph;
}

void graph_destroy(Graph* graph) {
    if (!graph)
        return;

    if (!graph->edges) {
        edge_list_destroy(graph->edges);
        free(graph->edges);
    }

    free(graph);
}

int graph_add_edge(Graph* graph, int value, int destination, int weight) {
    if (!graph)
        return -1;

    if (value < 0 || value >= graph->vertex_count || destination < 0 || destination >= graph->vertex_count) {
        return -1;
    }

    if (weight <= 0) {
        return -1;
    }

    edge_list_add(graph->edges, value, destination, weight);
    graph->edge_count++;

    return 0;
}

int graph_get_vertex_count(Graph* graph) {
    if (!graph)
        return -1;
    return graph->vertex_count;
}

int graph_get_edge_count(Graph* graph) {
    if (!graph)
        return -1;
    return graph->edge_count;
}

EdgeList* graph_get_edges(Graph* graph) {
    if (!graph)
        return NULL;
    return graph->edges;
}

void graph_print(Graph* graph) {
    if (!graph) {
        printf("Graph is NULL\n");
        return;
    }

    printf("Graph with %d vertices and %d edges:\n",graph->vertex_count, graph->edge_count);

    if (graph->edges != NULL) {
        edge_list_print(graph->edges);
    }
}