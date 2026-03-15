#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	SUCCESS,
	ALREADY_EXIST,
	DO_NOT_EXIST,
	MEMORY_ERROR,
	INCORRECT_KEY
} Status;

void node_init(Node** Tree) {
	/* Tree initialization */
	*Tree = NULL;
}

Node* node_create(int value) {
	/* Node creation with allocation of memory for it */
	Node* new_node = (Node*)malloc(sizeof(Node));

	// In case of memory allocation failure
	if (!new_node) return NULL;

	new_node->value = value;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

int node_display(Node* root, unsigned int indent) {
	/*Display tree elements*/
	if (root == NULL) {
		return SUCCESS;
	}
	for (int i = 0; i < indent; i++) {
		printf("   |");
	}
	printf("%d (%d)\n", root->key, root->value);
	if (root->left) {
		display(root->left, indent + 1);
	}
	if (root->right) {
		display(root->right, indent + 1);
	}
	return SUCCESS;
}