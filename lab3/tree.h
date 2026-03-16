#ifndef TREE_H
#define TREE_H
#include <stddef.h>

typedef enum {
	SUCCESS_TREE
} Status_Tree;

typedef struct Node {
	char value;
	struct Node* left;
	struct Node* right;
} Node;

void node_init(Node** Tree);
Node* node_create(int value);
int node_display(Node* root, unsigned int indent);

#endif