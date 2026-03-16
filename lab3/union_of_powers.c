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

	Node* output;
	int i = 0;
	while (str[i] != '\0') {
		if (!(str[i] == '^' 
			|| str[i] == '*' 
			|| str[i] == '/' 
			|| str[i] == '+' 
			|| str[i] == '-' )) {
			Node* parent_node = node_create(str[i]);
			node_stack_pop(&nodes, &output);
			Node* right_node = output;
			node_stack_pop(&nodes, &output);
			Node* left_node = output;
			parent_node->right = right_node;
			parent_node->left = left_node;
			node_stack_push(&nodes, parent_node);
		} else {
			Node* node = node_create(str[i]);
			node_stack_push(&nodes, node);
		}
	}
	node_stack_pop(&nodes, &output);
	return output;
}

int main(void) {
	char* input = input_expression();
	if (!input) printf("unluck\n");
	print_expression(input);
	char* result = convert_to_polin(input);
	print_expression(result);
	Node* tree_root = build_tree(result);
	node_display(tree_root, 4);
	return 0;
}
