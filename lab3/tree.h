#ifndef TREE_H
#define TREE_H
#include <stddef.h>

typedef enum {
	SUCCESS,
	ALREADY_EXIST,
	DO_NOT_EXIST,
	MEMORY_ERROR,
	INCORRECT_KEY
} Status;

typedef struct Node {
	int key;
	int value;
	struct Node* left;
	struct Node* right;
} Node;

void node_init(Node** Tree);
Node* node_create(int value);
int node_display(Node* root, unsigned int indent);

#endif