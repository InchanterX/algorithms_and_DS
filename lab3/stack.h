#ifndef STACK_H
#define STACK_H
#include <stddef.h>

#define STACK_OK 0
#define STACK_EMPTY 1
#define STACK_FULL 2
#define STACK_ALLOC_FAILED 3
#define INCORRECT_INPUT 4

#define MIN_CAPACITY 4

typedef struct {
    	char *data;
    	int top;
    	int capacity;
} DStack;

int stack_init(DStack *s, int initial_capacity);
int stack_free(DStack *s);
int stack_is_empty(const DStack *s);
int stack_is_full(const DStack *s);
int stack_push(DStack *s, char value);
int stack_pop(DStack* s, char* value);
int stack_top(const DStack *s, char* value);

#endif