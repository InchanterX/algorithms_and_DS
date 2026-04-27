// prim.c
#include "prim.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

static void mst_result_init(MstResult *result)
{
    if (!result)
        return;

    result->capacity = 10;
    result->count = 0;
    result->edges = (MstEdge *)malloc(result->capacity * sizeof(MstEdge));
}

static void mst_result_add(MstResult *result, int source, int destination, int weight)
{
    if (!result)
        return;

    if (result->count >= result->capacity)
    {
        result->capacity *= 2;
        result->edges = (MstEdge *)realloc(result->edges, result->capacity * sizeof(MstEdge));
    }

    result->edges[result->count].source = source;
    result->edges[result->count].destination = destination;
    result->edges[result->count].weight = weight;
    result->count++;
}

MstResult *prim_algorithm(Graph *graph)
{
    if (!graph)
        return NULL;

    EdgeList *edges = graph_get_edges(graph);
    if (!edges)
        return NULL;

    int vertices = graph_get_vertex_count(graph);
    if (vertices <= 0)
        return NULL;

    bool *in_mst = (bool *)calloc(vertices, sizeof(bool));
    if (!in_mst)
        return NULL;

    MstResult *result = (MstResult *)malloc(sizeof(MstResult));
    if (!result)
    {
        free(in_mst);
        return NULL;
    }

    mst_result_init(result);
    if (!result->edges)
    {
        free(in_mst);
        free(result);
        return NULL;
    }

    in_mst[0] = true;
    int edges_in_mst = 0;

    while (edges_in_mst < vertices - 1)
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

            if (in_mst[source] != in_mst[destination] && weight < min_weight)
            {
                min_weight = weight;
                min_index = i;
                min_source = source;
                min_destination = destination;
            }
        }

        if (min_index == -1)
            break;

        in_mst[min_source] = true;
        in_mst[min_destination] = true;
        mst_result_add(result, min_source, min_destination, min_weight);
        edges_in_mst++;
    }

    free(in_mst);

    if (edges_in_mst != vertices - 1)
    {
        mst_result_destroy(result);
        return NULL;
    }

    return result;
}

void mst_result_destroy(MstResult *result)
{
    if (!result)
        return;

    if (result->edges != NULL)
        free(result->edges);

    free(result);
}

void mst_result_print(MstResult *result)
{
    if (!result)
    {
        printf("MST result is NULL\n");
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