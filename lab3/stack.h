#ifndef STACK_H
#define STACK_H
#include <stddef.h>
#include "tree.h"

#define STACK_OK 0
#define STACK_EMPTY 1
#define STACK_FULL 2
#define STACK_ALLOC_FAILED 3
#define INCORRECT_INPUT 4

#define MIN_CAPACITY 4

typedef struct {
	char* data;
	int top;
	int capacity;
} CharStack;

typedef struct {
	Node** data;
	int top;
	int capacity;
} NodeStack;

int char_stack_init(CharStack *s, int initial_capacity);
int char_stack_free(CharStack *s);
int char_stack_is_empty(const CharStack *s);
int char_stack_is_full(const CharStack *s);
int char_stack_push(CharStack *s, char value);
int char_stack_pop(CharStack* s, char* value);
int char_stack_top(const CharStack *s, char* value);

int node_stack_init(NodeStack *s, int initial_capacity);
int node_stack_free(NodeStack *s);
int node_stack_is_empty(const NodeStack *s);
int node_stack_is_full(const NodeStack *s);
int node_stack_push(NodeStack *s, Node* value);
int node_stack_pop(NodeStack* s, Node** value);
int node_stack_top(const NodeStack *s, Node** value);

#endif