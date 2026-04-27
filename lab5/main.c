#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "prim.h"

int main()
{
    Graph *graph = graph_create(5);
    if (!graph)
    {
        printf("Failed to create graph\n");
        return 1;
    }

    graph_add_edge(graph, 0, 1, 2);
    graph_add_edge(graph, 0, 2, 3);
    graph_add_edge(graph, 0, 3, 6);
    graph_add_edge(graph, 1, 2, 2);
    graph_add_edge(graph, 1, 3, 8);
    graph_add_edge(graph, 2, 3, 4);
    graph_add_edge(graph, 2, 4, 5);
    graph_add_edge(graph, 3, 4, 7);

    graph_print(graph);
    printf("\n");

    MstResult *mst = prim_algorithm(graph);
    mst_result_print(mst);

    graph_destroy(graph);
    mst_result_destroy(mst);

    return 0;
}