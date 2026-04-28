#include "prim.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

static void minimum_spanning_tree_result_init(Minimum_spanning_treeResult *result)
{
    if (!result)
        return;

    result->capacity = 10;
    result->count = 0;
    result->edges = (Minimum_spanning_treeEdge *)malloc(result->capacity * sizeof(Minimum_spanning_treeEdge));
}

static void minimum_spanning_tree_result_add(Minimum_spanning_treeResult *result, int source, int destination, int weight)
{
    if (!result)
        return;

    if (result->count >= result->capacity)
    {
        result->capacity *= 2;
        result->edges = (Minimum_spanning_treeEdge *)realloc(result->edges, result->capacity * sizeof(Minimum_spanning_treeEdge));
    }

    result->edges[result->count].source = source;
    result->edges[result->count].destination = destination;
    result->edges[result->count].weight = weight;
    result->count++;
}

Minimum_spanning_treeResult *prim_algorithm(Graph *graph)
{
    if (!graph)
        return NULL;

    EdgeList *edges = graph_get_edges(graph);
    if (!edges)
        return NULL;

    int vertices = graph_get_vertex_count(graph);
    if (vertices <= 0)
        return NULL;

    if (vertices == 1)
    {
        Minimum_spanning_treeResult *result = (Minimum_spanning_treeResult *)malloc(sizeof(Minimum_spanning_treeResult));
        if (!result)
            return NULL;

        minimum_spanning_tree_result_init(result);
        return result;
    }

    bool *in_minimum_spanning_tree = (bool *)calloc(vertices, sizeof(bool));
    if (!in_minimum_spanning_tree)
        return NULL;

    Minimum_spanning_treeResult *result = (Minimum_spanning_treeResult *)malloc(sizeof(Minimum_spanning_treeResult));
    if (!result)
    {
        free(in_minimum_spanning_tree);
        return NULL;
    }

    minimum_spanning_tree_result_init(result);
    if (!result->edges)
    {
        free(in_minimum_spanning_tree);
        free(result);
        return NULL;
    }

    in_minimum_spanning_tree[0] = true;
    int edges_in_minimum_spanning_tree = 0;

    while (edges_in_minimum_spanning_tree < vertices - 1)
    {
        int min_weight = INT_MAX;
        int min_index = -1;
        int min_source = -1;
        int min_destination = -1;

        for (int i = 0; i < edge_list_size(edges); i++)
        {
            GraphEdge graph_edge = edge_list_get(edges, i);
            int source = graph_edge.source;
            int destination = graph_edge.destination;
            int weight = graph_edge.weight;

            if (in_minimum_spanning_tree[source] != in_minimum_spanning_tree[destination] && weight < min_weight)
            {
                min_weight = weight;
                min_index = i;
                min_source = source;
                min_destination = destination;
            }
        }

        if (min_index == -1)
            break;

        in_minimum_spanning_tree[min_source] = true;
        in_minimum_spanning_tree[min_destination] = true;
        minimum_spanning_tree_result_add(result, min_source, min_destination, min_weight);
        edges_in_minimum_spanning_tree++;
    }

    free(in_minimum_spanning_tree);

    if (edges_in_minimum_spanning_tree != vertices - 1)
    {
        minimum_spanning_tree_result_destroy(result);
        return NULL;
    }

    return result;
}

void minimum_spanning_tree_result_destroy(Minimum_spanning_treeResult *result)
{
    if (!result)
        return;

    if (result->edges != NULL)
        free(result->edges);

    free(result);
}

void minimum_spanning_tree_result_print(Minimum_spanning_treeResult *result)
{
    if (!result)
    {
        printf("MINIMUM_SPANNING_TREE result is NULL\n");
        return;
    }

    printf("Minimum Spanning Tree (Prim's Algorithm):\n");
    printf("Total edges: %d\n", result->count);
    int total_weight = 0;

    for (int i = 0; i < result->count; i++)
    {
        printf("  (%d, %d) weight = %d\n", result->edges[i].source, result->edges[i].destination, result->edges[i].weight);
        total_weight += result->edges[i].weight;
    }

    printf("Total weight: %d\n", total_weight);
}