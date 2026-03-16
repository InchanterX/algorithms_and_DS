#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "tree.h"

#define MAX_INPUT_SIZE 1000
#define STACK_BASE_SIZE 100

char* input_expression(void) {
	char* result = (char*)malloc((MAX_INPUT_SIZE + 1) * sizeof(char));
	if (!result) return NULL;

	char c;
	int i = 0;
	while (((c = getchar()) != '\n') && (i < MAX_INPUT_SIZE)) {
		if (c != ' ' && c != '\t') {
			result[i++] = c;;
		}
	}
	result[i] = '\0';
	return result;
}

void print_expression(char* str) {
	int i = 0;
	while (str[i] != '\0') {
		printf("%c", str[i++]);
	}
	printf("\n");
}

int priority(char sign) {
	int priority = 0;
	if (sign == '^') priority = 4;
	else if (sign == '*' || sign == '/') priority = 3;
	else if (sign == '+' || sign == '-') priority = 2;
	if (sign == ')') priority = 1;
	return priority;
}

char* convert_to_polin(char* str) {
	char* result = (char*)malloc((MAX_INPUT_SIZE + 1) * sizeof(char));
	if (!result) return NULL;
	CharStack buffer;
	char_stack_init(&buffer, STACK_BASE_SIZE);

	int i = 0;
	int ri = 0;
	char output;	
	while (str[i] != '\0') {
		if (!(str[i] == '^' 
			|| str[i] == '*' 
			|| str[i] == '/' 
			|| str[i] == '+' 
			|| str[i] == '-' 
			|| str[i] == '(' 
			|| str[i] == ')')) {
			result[ri] = str[i];
			ri++;
		} else {
			if (str[i] == '(') {
				char_stack_push(&buffer, str[i]);
			} else if (str[i] == ')') {
				while (!char_stack_is_empty(&buffer)) {
					char_stack_pop(&buffer, &output);
					if (output == '(') break;
					result[ri++] = output;
				}
			}
			else if (!char_stack_is_empty(&buffer)) {
				char top;
				char_stack_top(&buffer, &top);
				
				while (!char_stack_is_empty(&buffer) && top != '(' && priority(str[i]) <= priority(top)) {	
					char_stack_pop(&buffer, &output);
					result[ri++] = output;
					if (!char_stack_is_empty(&buffer)) char_stack_top(&buffer, &top);
					else top = '\0';
				}
				char_stack_push(&buffer, str[i]);
			} else {
				char_stack_push(&buffer, str[i]);
			}
		}
		i++;
	}
	while (!char_stack_is_empty(&buffer)) {
		char_stack_pop(&buffer, &output);
		if (output != '(') result[ri++] = output;
	}
	result[ri] = '\0';
	return result;
}

Node* build_tree(char* str) {
    NodeStack nodes;
    node_stack_init(&nodes, MAX_INPUT_SIZE);

    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '^' || str[i] == '*' || str[i] == '/' 
            || str[i] == '+' || str[i] == '-') {
            
            Node* operator_node = node_create(str[i]);
            Node* right_operand = NULL;
            Node* left_operand = NULL;
            
            if (node_stack_pop(&nodes, &right_operand) != STACK_OK) {
                node_stack_free(&nodes);
                return NULL;
            }
            
            if (node_stack_pop(&nodes, &left_operand) != STACK_OK) {
                node_stack_free(&nodes);
                return NULL;
            }

            operator_node->left = left_operand;
            operator_node->right = right_operand;
            node_stack_push(&nodes, operator_node);
        } 
        else {
            Node* operand_node = node_create(str[i]);
            node_stack_push(&nodes, operand_node);
        }
        i++;
    }
    
    Node* root = NULL;
    if (node_stack_pop(&nodes, &root) != STACK_OK) {
        node_stack_free(&nodes);
        return NULL;
    }
    
    node_stack_free(&nodes);
    return root;
}

void tree_simplification(Node* root) {
	if (!root) return;

	if (root->left) tree_simplification(root->left);
	if (root->right) tree_simplification(root->right);

	if ((root->value == '*') && root->left && root->right 
		&& ((root->left->value == '^') && (root->right->value == '^'))
		&& (root->left->left->value == root->right->left->value)) {
		
		root->value = '^';
		root->right->value = '+';
		root->right->left = root->left->right;
		root->left = root->left->left;
		root->left->left = NULL;
		free(root->left->left);
		root->left->right = NULL;
		free(root->left->right);
	}
}

int is_sign(char value) {
	if (value == '*' || value == '/' || value == '+' || value == '-' || value == '^') return 1;
	return 0;
}

void build_result(Node* root, char* result) {
	if (!result) return;
	static int i = 0;

	if (!root->left || !root->right) {
		result[i++] = root->value; 
		return;
	}
	
	if (root->left) build_result(root->left, result);
	result[i++] = root->value;
	if (root->right) {
		if (is_sign(root->right->value) && (priority(root->value) >priority(root->right->value))) {
			result[i++] = '(';
			build_result(root->right, result);
			result[i++] = ')';
		} else { 
			build_result(root->right, result);
		}
	}

	result[i] = '\0'; 
}

int main(void) {
	char* input = input_expression();
	if (!input) printf("unluck\n");
	print_expression(input);
	char* result = convert_to_polin(input);
	print_expression(result);
	Node* tree_root = build_tree(result);
	node_display(tree_root, 0);
	tree_simplification(tree_root);
	node_display(tree_root, 0);
	char* final_result = (char*)malloc((MAX_INPUT_SIZE + 1) * sizeof(char));
	if (!final_result) return 1;
	build_result(tree_root, final_result);
	print_expression(final_result);
	return 0;
}
