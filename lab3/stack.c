#include "stack.h"
#include "tree.h"

#include <stdlib.h>

#define STACK_OK 0
#define STACK_EMPTY 1
#define STACK_FULL 2
#define STACK_ALLOC_FAILED 3
#define INCORRECT_INPUT 4

int char_stack_init(CharStack *s, int initial_capacity) {
	if (!s) return INCORRECT_INPUT;
    	if (initial_capacity <= 0) return STACK_ALLOC_FAILED;

	s->data = malloc(initial_capacity * sizeof(char));
    	if (s->data == NULL) return STACK_ALLOC_FAILED;

    	s->top = -1;
    	s->capacity = initial_capacity;
	return STACK_OK;
}

int char_stack_free(CharStack *s) {
	if (!s) return INCORRECT_INPUT;
	free(s->data);
	s->data = NULL;
	s->top = -1;
	s->capacity = 0;
	return STACK_OK;
}

int char_stack_is_empty(const CharStack *s) {
	if (!s) return INCORRECT_INPUT;
	return s->top == -1;
}

int char_stack_is_full(const CharStack *s) {
	if (!s) return INCORRECT_INPUT;
	return s->top == s->capacity - 1;
}

int char_stack_push(CharStack *s, char value) {
    	if (!s) return INCORRECT_INPUT;

	if (char_stack_is_full(s)) {
	        int new_capacity = s->capacity * 2;
        	char* new_data = realloc(s->data, new_capacity * sizeof(char));
        	if (!new_data) return STACK_ALLOC_FAILED;
		s->data = new_data;
        	s->capacity = new_capacity;
    	}

    	s->top++;
    	s->data[s->top] = value;
    	return STACK_OK;
}

int char_stack_pop(CharStack* s, char* value) {
    if (!s) return INCORRECT_INPUT;
	if (char_stack_is_empty(s)) return STACK_EMPTY;
	*value = s->data[s->top];
	s->top--;
	if (s->capacity > MIN_CAPACITY && (s->top + 1) * 4 < s->capacity) {
    	int new_capacity = s->capacity / 2;
    	if (new_capacity < MIN_CAPACITY) {
        		new_capacity = MIN_CAPACITY;
    	}
        if (new_capacity < s->top + 1) {
    		 new_capacity = s->top + 1;
    	}
    	char* new_data = realloc(s->data, new_capacity * sizeof(char));
    	if (new_data) {
        		s->data = new_data;
        		s->capacity = new_capacity;
    	}
	}
	return STACK_OK;
}


int char_stack_top(const CharStack *s, char *value) {
    if (!s) return INCORRECT_INPUT;
	if (char_stack_is_empty(s)) return STACK_EMPTY;

	*value = s->data[s->top];
	return STACK_OK;
}

int node_stack_init(NodeStack *s, int initial_capacity) {
	if (!s) return INCORRECT_INPUT;
	if (initial_capacity <= 0) return STACK_ALLOC_FAILED;

	s->data = (Node**)malloc(initial_capacity * sizeof(Node*));
	if (s->data == NULL) return STACK_ALLOC_FAILED;

	s->top = -1;
	s->capacity = initial_capacity;
	return STACK_OK;
}

int node_stack_free(NodeStack *s) {
	if (!s) return INCORRECT_INPUT;
	free(s->data);
	s->data = NULL;
	s->top = -1;
	s->capacity = 0;
	return STACK_OK;
}

int node_stack_is_empty(const NodeStack *s) {
	if (!s) return INCORRECT_INPUT;
	return s->top == -1;
}

int node_stack_is_full(const NodeStack *s) {
	if (!s) return INCORRECT_INPUT;
	return s->top == s->capacity - 1;
}

int node_stack_push(NodeStack *s, Node* value) {
	if (!s) return INCORRECT_INPUT;

	if (node_stack_is_full(s)) {
        int new_capacity = s->capacity * 2;
    	Node** new_data = (Node**)realloc(s->data, new_capacity * sizeof(Node*));
    	if (!new_data) return STACK_ALLOC_FAILED;
		s->data = new_data;
        	s->capacity = new_capacity;
    	}

    	s->top++;
    	s->data[s->top] = value;
    	return STACK_OK;
}

int node_stack_pop(NodeStack* s, Node** value) {
    if (!s) return INCORRECT_INPUT;
	if (node_stack_is_empty(s)) return STACK_EMPTY;
	*value = s->data[s->top];
	s->top--;
	if (s->capacity > MIN_CAPACITY && (s->top + 1) * 4 < s->capacity) {
    	int new_capacity = s->capacity / 2;
    	if (new_capacity < MIN_CAPACITY) {
        		new_capacity = MIN_CAPACITY;
    	}
        if (new_capacity < s->top + 1) {
    		 new_capacity = s->top + 1;
    	}
    	Node** new_data = (Node**)realloc(s->data, new_capacity * sizeof(Node*));
    	if (new_data) {
        		s->data = new_data;
        		s->capacity = new_capacity;
    	}
	}
	return STACK_OK;
}


int node_stack_top(const NodeStack *s, Node** value) {
    if (!s) return INCORRECT_INPUT;
	if (node_stack_is_empty(s)) return STACK_EMPTY;

	*value = s->data[s->top];
	return STACK_OK;
}