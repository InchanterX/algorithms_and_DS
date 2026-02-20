#include <stdio.h>
#include <stdlib.h>

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

void init(Node** Tree) {
	*Tree = NULL;
}

Node* create_node(int key, int value) {
	// printf("%d %d\n", key, value);
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node) {
		new_node->key = key;
		new_node->value = value;
		new_node->left = NULL;
		new_node->right = NULL;
	}
	return new_node;
}

void delete_node(Node* element) {
	// ASK if it realy necessary to reset vars that will be freed 
	// element->key = 0;
	// element->value = 0;
	// element->left = NULL;
	// element->right = NULL;
	free(element);
}

int is_empty(Node* root) {
	return (root == NULL);
}

Status destroy(Node** root) {
	if (*root == NULL) {
		return DO_NOT_EXIST;
	}
	destroy(&(*root)->left);
	destroy(&(*root)->right);
	delete_node(*root);
	*root = NULL;
	return SUCCESS;
}

// TODO a function to find the depth of the tree
int depth(Node* root) {

}

// Функция для рекурсивного отображения дерева
void print_tree_recursive(Node* root, int space, int indent) {
    if (root == NULL) {
        return;
    }
    
    space += indent;
    
    // Сначала выводим правое поддерево (будет сверху)
    print_tree_recursive(root->right, space, indent);
    
    // Выводим текущий узел
    printf("\n");
    for (int i = indent; i < space; i++) {
        printf(" ");
    }
    printf("%d(%d)\n", root->key, root->value);
    
    // Выводим левое поддерево (будет снизу)
    print_tree_recursive(root->left, space, indent);
}

// Функция для отображения дерева в консоли
void print_tree(Node* root) {
    printf("\n=== ДЕРЕВО ===\n");
    if (root == NULL) {
        printf("Дерево пустое\n");
    } else {
        printf("(ключ:значение)\n");
        print_tree_recursive(root, 0, 4);
    }
    printf("==============\n");
}

Status add_node(Node** root, int key, int value) {
	if (*root == NULL) {
		*root = create_node(key, value);
		return (*root) ? SUCCESS : MEMORY_ERROR;
	}
	Node* current_node = *root;
	while (1) {
        	if (current_node->key == key) {
            		return ALREADY_EXIST;
        	} else if (current_node->key > key) {
            		if (current_node->left) {
                		current_node = current_node->left;
            		} else {
                		Node* new_node = create_node(key, value);
                		if (!new_node)
    					return MEMORY_ERROR;
				current_node->left = new_node;
				break;
            		}
        	} else {
            		if (current_node->right) {
                		current_node = current_node->right;
            		} else {
                		Node* new_node = create_node(key, value);
				current_node-> right = new_node;
				if (!new_node)
    					return MEMORY_ERROR;
				break;
            		}
        	}
	}
	return SUCCESS;
}

// TODO graceful deletion / forceful deletion of all nested elements
// by 2nd function input
// TODO need to solve the problem of removing the root node
Status remove_node(Node** root, int key) {
	if (*root == NULL) {
		return DO_NOT_EXIST;
	}
	Node* current_node = *root;
	Node* previous_node = NULL;
	int previous_direction = -1;
	while(1) {
		if (current_node->key == key) {
			break;
		} else if (current_node->key > key) {
			if (current_node->left) {
				previous_node = current_node;
				previous_direction = 0;
				current_node = current_node->left;
			} else {
				return DO_NOT_EXIST;
			}
		} else if (current_node->key < key) {
			if (current_node->right) {
				previous_node = current_node;
				previous_direction = 1;
				current_node = current_node->right;
			} else {
				return DO_NOT_EXIST;
			}
		} else {
			return INCORRECT_KEY;
		}
	}

	if (!(current_node->left || current_node->right)) {
		if (previous_direction == 0) {
			previous_node->left = NULL;
		} else {
			previous_node->right = NULL;
		}
		delete_node(current_node);
		return SUCCESS;
	} else if ((current_node->left == NULL) != (current_node->right == NULL)) {
		Node* child_node = current_node->left ? current_node->left : current_node->right;
		delete_node(current_node);
		if (previous_direction == 0) {
			previous_node->left = child_node;
		} else {
			previous_node->right = child_node;
		}
		return SUCCESS;
	} else {
		Node* child_left = current_node->left;
		Node* substitution_node = child_left;
		Node* last_node = NULL;

		while (substitution_node->right) {
		    last_node = substitution_node;
		    substitution_node = substitution_node->right;
		}

		current_node->key = substitution_node->key;
		current_node->value = substitution_node->value;

		if (last_node == NULL) {
		    current_node->left = substitution_node->left;
		} else {
		    last_node->right = substitution_node->left;
		}

		delete_node(substitution_node);
		return SUCCESS;
	}
}

Status display_node(Node* root, int key) {
	if (root == NULL) {
		return DO_NOT_EXIST;
	}
	Node* current_node = root;
	while(1) {
		if (current_node->key == key) {
			break;
		} else if (current_node->key > key) {
			if (current_node->left) {
				current_node = current_node->left;
			} else {
				return DO_NOT_EXIST;
			}
		} else if (current_node->key < key) {
			if (current_node->right) {
				current_node = current_node->right;
			} else {
				return DO_NOT_EXIST;
			}
		} else {
			return DO_NOT_EXIST;
		}
	}
	printf("Key: %d\nValue: %d\n",
		current_node->key, current_node->value);
	if (current_node->left) {
		printf("Left node key and value: %d %d\n", current_node->left->key, current_node->left->value);
	}
	if (current_node->right) {
		printf("Right node key and value: %d %d\n", current_node->right->key, current_node->right->value);
	}
	return SUCCESS;
}

// TODO yet to be done
int display(Node* root) {
	printf("Yea. It is definetly a tree.\n");
}

int depth_of_min(Node* root) {
	if (root == NULL) {
		return 0;
	}
	int depth = 0;
	Node* current_node = root;
	while(1) {
		if (current_node->left) {
			current_node = current_node->left;
			depth++;
		} else {
			break;
		}
	}
	return depth;
}

void print_status(Status state) {
	switch(state) {
		case 0:
			break;
		case 1:
			printf("Node with this key already exist!\n");
			break;
		case 2:
			printf("Node with this key do not exist!\n");
			break;
		case 3:
			printf("Failed to allocate memory!\n");
			break;
		case 4:
			printf("Incorrect key was given!\n");
			break;
		default:
			printf("Unknown error, contact the developer!\n");
	}
}

int main(void) {
	// Node* Tree = init();
	Node* Tree;
	init(&Tree);
	printf("Tree initilized!");
	int user_input = 0;
	while (1) {
		printf("You can interact with tree via using this numbers:\n1 - add   2 - remove   3 - display tree   4 - display node   5 - find   6 - is empty?   7 - destroy   8 - exit\n");
		scanf("%d", &user_input);
		int key, value;
		switch (user_input) {
			case 1:
				printf("Input key and value of your node: ");
				// scanf("%d %d", &key, &value);
				// Status add_status = add_node(&Tree, key, value);
				scanf("%d", &key);
				Status add_status = add_node(&Tree, key, 0);
				print_status(add_status);
				break;
			case 2:
				printf("Input key of the node you want to delete: ");
                                scanf("%d", &key);
                                Status remove_status = remove_node(&Tree, key);
                                print_status(remove_status);
				break;
			case 3:
				// display(Tree);
				print_tree(Tree);
				break;
			case 4:
				printf("Input key of the node you want to display: ");
                                scanf("%d", &key);
                                Status display_node_status = display_node(Tree, key);
                                print_status(display_node_status);
                                break;
			case 5:
				int depth = depth_of_min(Tree);
				printf("Depth of the least element: %d", depth);
				break;
			case 6:
				if (is_empty(Tree)) {
					printf("The tree is empty.\n");
				} else {
					printf("The tree is not empty.\n");
				}
				break;
			case 7:
				Status destroy_status = destroy(&Tree);
                                print_status(destroy_status);
				break;
			case 8:
				return 0;
			default:
				printf("Incorrect input!\n");
		}
	}
	return 0;
}
