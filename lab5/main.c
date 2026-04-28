#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "prim.h"

void example_1(void) {
    Graph *graph = graph_create(5);
    if (!graph)
    {
        printf("Failed to create graph\n");
        return;
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

    Minimum_spanning_treeResult *minimum_spanning_tree = prim_algorithm(graph);
    minimum_spanning_tree_result_print(minimum_spanning_tree);

    graph_destroy(graph);
    minimum_spanning_tree_result_destroy(minimum_spanning_tree);
}

void example_2(void) {
    Graph *graph = graph_create(1);
    if (!graph)
    {
        printf("Failed to create graph\n");
        return;
    }

    graph_add_edge(graph, 0, 0, 1);

    graph_print(graph);
    printf("\n");

    Minimum_spanning_treeResult *minimum_spanning_tree = prim_algorithm(graph);
    minimum_spanning_tree_result_print(minimum_spanning_tree);

    graph_destroy(graph);
    minimum_spanning_tree_result_destroy(minimum_spanning_tree);
}

void example_3(void) {
    Graph *graph = graph_create(12);
    if (!graph)
    {
        printf("Failed to create graph\n");
        return;
    }

    graph_add_edge(graph, 0, 1, 4);
    graph_add_edge(graph, 0, 3, 1);
    graph_add_edge(graph, 0, 4, 5);
    graph_add_edge(graph, 1, 7, 2);
    graph_add_edge(graph, 1, 11, 3);
    graph_add_edge(graph, 1, 2, 1);
    graph_add_edge(graph, 2, 11, 1);
    graph_add_edge(graph, 2, 8, 7);
    graph_add_edge(graph, 2, 10, 3);
    graph_add_edge(graph, 3, 5, 6);
    graph_add_edge(graph, 4, 5, 8);
    graph_add_edge(graph, 4, 6, 2);
    graph_add_edge(graph, 5, 8, 3);
    graph_add_edge(graph, 6, 8, 4);
    graph_add_edge(graph, 6, 10, 4);
    graph_add_edge(graph, 6, 9, 2);
    graph_add_edge(graph, 9, 10, 2);
    graph_add_edge(graph, 9, 11, 3);
    graph_print(graph);
    printf("\n");

    Minimum_spanning_treeResult *minimum_spanning_tree = prim_algorithm(graph);
    minimum_spanning_tree_result_print(minimum_spanning_tree);

    graph_destroy(graph);
    minimum_spanning_tree_result_destroy(minimum_spanning_tree);
}

int main()
{
    example_1();
    printf("------------------\n");
    example_2();
    printf("------------------\n");
    example_3();

    return 0;
}