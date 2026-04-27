#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2

int edge_list_init(EdgeList *list)
{
    if (!list)
        return INVALID_INPUT;

    list->data = (GraphEdge *)malloc(INITIAL_CAPACITY * sizeof(GraphEdge));
    if (!list->data)
    {
        list->size = 0;
        list->capacity = 0;
        return MEMORY_ERROR;
    }

    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    return SUCCESS;
}

int edge_list_destroy(EdgeList *list)
{
    if (!list)
        return INVALID_INPUT;

    if (list->data != NULL)
    {
        free(list->data);
        list->data = NULL;
    }

    list->size = 0;
    list->capacity = 0;
    return SUCCESS;
}

static int edge_list_ensure_capacity(EdgeList *list)
{
    if (!list)
        return INVALID_INPUT;

    if (list->size >= list->capacity)
    {
        int new_capacity = list->capacity * GROWTH_FACTOR;
        if (new_capacity < INITIAL_CAPACITY)
        {
            new_capacity = INITIAL_CAPACITY;
        }

        GraphEdge *new_data = (GraphEdge *)realloc(list->data, new_capacity * sizeof(GraphEdge));
        if (!new_data)
            return MEMORY_ERROR;

        list->data = new_data;
        list->capacity = new_capacity;
    }
    return SUCCESS;
}

int edge_list_add(EdgeList *list, int source, int destination, int weight)
{
    if (!list)
        return INVALID_INPUT;

    if (source < 0 || destination < 0 || weight < 0)
        return INVALID_INPUT;

    int result = edge_list_ensure_capacity(list);
    if (result != SUCCESS)
        return result;

    if (!list->data)
        return MEMORY_ERROR;

    list->data[list->size].source = source;
    list->data[list->size].destination = destination;
    list->data[list->size].weight = weight;
    list->size++;
    return SUCCESS;
}

int edge_list_insert(EdgeList *list, int index, int source, int destination, int weight)
{
    if (!list)
        return INVALID_INPUT;

    if (!list->data)
        return MEMORY_ERROR;

    if (index < 0 || index > list->size)
        return INVALID_INPUT;

    if (source < 0 || destination < 0 || weight < 0)
        return INVALID_INPUT;

    int result = edge_list_ensure_capacity(list);
    if (result != SUCCESS)
        return result;

    for (int i = list->size; i > index; i--)
    {
        list->data[i] = list->data[i - 1];
    }

    list->data[index].source = source;
    list->data[index].destination = destination;
    list->data[index].weight = weight;
    list->size++;
    return SUCCESS;
}

int edge_list_remove_at(EdgeList *list, int index)
{
    if (!list)
        return INVALID_INPUT;

    if (!list->data)
        return MEMORY_ERROR;

    if (index < 0 || index >= list->size)
        return INVALID_INPUT;

    for (int i = index; i < list->size - 1; i++)
    {
        list->data[i] = list->data[i + 1];
    }

    list->size--;

    if (list->size > 0 && list->size <= list->capacity / 4 && list->capacity > INITIAL_CAPACITY)
    {
        int new_capacity = list->capacity / 2;
        GraphEdge *new_data = (GraphEdge *)realloc(list->data, new_capacity * sizeof(GraphEdge));
        if (!new_data)
        {
            list->data = new_data;
            list->capacity = new_capacity;
        }
    }
    return SUCCESS;
}

GraphEdge edge_list_get(EdgeList *list, int index)
{
    GraphEdge dummy = {-1, -1, -1};

    if (!list || !list->data)
        return dummy;

    if (index < 0 || index >= list->size)
        return dummy;

    return list->data[index];
}

int edge_list_set(EdgeList *list, int index, int source, int destination, int weight)
{
    if (!list)
        return INVALID_INPUT;

    if (!list->data)
        return MEMORY_ERROR;

    if (index < 0 || index >= list->size)
        return INVALID_INPUT;

    if (source < 0 || destination < 0 || weight < 0)
        return INVALID_INPUT;

    list->data[index].source = source;
    list->data[index].destination = destination;
    list->data[index].weight = weight;
    return SUCCESS;
}

int edge_list_size(EdgeList *list)
{
    if (!list)
        return -1;
    return list->size;
}

int edge_list_clear(EdgeList *list)
{
    if (!list)
        return INVALID_INPUT;
    list->size = 0;
    return SUCCESS;
}

int edge_list_print(EdgeList *list)
{
    if (!list)
    {
        printf("EdgeList is NULL\n");
        return INVALID_INPUT;
    }

    if (!list->data)
    {
        printf("EdgeList data is NULL\n");
        return MEMORY_ERROR;
    }

    printf("EdgeList (size=%d, capacity=%d):\n", list->size, list->capacity);
    for (int i = 0; i < list->size; i++)
    {
        printf("  %d: (%d, %d) weight=%d\n", i, list->data[i].source, list->data[i].destination, list->data[i].weight);
    }
    return SUCCESS;
}

int edge_list_find_cross_edge(EdgeList *list, int *in_mst, int vertices_count)
{
    if (!list || !list->data || !in_mst)
        return -1;

    int min_weight = INT_MAX;
    int min_index = -1;

    for (int i = 0; i < list->size; i++)
    {
        int value = list->data[i].source;
        int destination = list->data[i].destination;
        int weight = list->data[i].weight;

        if (value >= 0 && value < vertices_count && destination >= 0 && destination < vertices_count)
        {
            if (in_mst[value] != in_mst[destination] && weight < min_weight)
            {
                min_weight = weight;
                min_index = i;
            }
        }
    }

    return min_index;
}

static int edge_compare_weight(const void *edge1, const void *edge2)
{
    GraphEdge *edge1_copy = (GraphEdge *)edge1;
    GraphEdge *edge2_copy = (GraphEdge *)edge2;
    return edge1_copy->weight - edge2_copy->weight;
}

int edge_list_sort_by_weight(EdgeList *list)
{
    if (!list)
        return INVALID_INPUT;

    if (!list->data)
        return MEMORY_ERROR;

    if (list->size <= 1)
        return SUCCESS;

    qsort(list->data, list->size, sizeof(GraphEdge), edge_compare_weight);
    return SUCCESS;
}