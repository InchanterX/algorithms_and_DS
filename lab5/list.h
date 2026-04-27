// list.h
#ifndef LIST_H
#define LIST_H

#define SUCCESS 0
#define INVALID_INPUT 1
#define MEMORY_ERROR 2

typedef struct
{
    int source;
    int destination;
    int weight;
} GraphEdge;

typedef struct
{
    GraphEdge *data;
    int size;
    int capacity;
} EdgeList;

int edge_list_init(EdgeList *list);
int edge_list_destroy(EdgeList *list);
int edge_list_add(EdgeList *list, int source, int destination, int weight);
int edge_list_insert(EdgeList *list, int index, int source, int destination, int weight);
int edge_list_remove_at(EdgeList *list, int index);
GraphEdge edge_list_get(EdgeList *list, int index);
int edge_list_set(EdgeList *list, int index, int source, int destination, int weight);
int edge_list_size(EdgeList *list);
int edge_list_clear(EdgeList *list);
int edge_list_print(EdgeList *list);
int edge_list_find_cross_edge(EdgeList *list, int *in_mst, int vertices_count);
int edge_list_sort_by_weight(EdgeList *list);

#endif