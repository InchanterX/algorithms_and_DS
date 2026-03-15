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
	DStack buffer;
	stack_init(&buffer, STACK_BASE_SIZE);

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
				stack_push(&buffer, str[i]);
			} else if (str[i] == ')') {
				while (!stack_is_empty(&buffer)) {
					stack_pop(&buffer, &output);
					if (output == '(') break;
					result[ri++] = output;
				}
			}
			else if (!stack_is_empty(&buffer)) {
				char top;
				stack_top(&buffer, &top);
				
				while (!stack_is_empty(&buffer) && top != '(' && priority(str[i]) <= priority(top)) {	
					stack_pop(&buffer, &output);
					result[ri++] = output;
					if (!stack_is_empty(&buffer)) stack_top(&buffer, &top);
					else top = '\0';
				}
				stack_push(&buffer, str[i]);
			} else {
				stack_push(&buffer, str[i]);
			}
		}
		i++;
	}
	while (!stack_is_empty(&buffer)) {
		stack_pop(&buffer, &output);
		if (output != '(') result[ri++] = output;
	}
	result[ri] = '\0';
	return result;
}

Node* build_tree(char* str) {
	DStack nodes;
	stack_init(&nodes, MAX_INPUT_SIZE);

	Node* output;
	int i = 0;
	while (str[i] != '\0') {
		if (!(str[i] == '^' 
			|| str[i] == '*' 
			|| str[i] == '/' 
			|| str[i] == '+' 
			|| str[i] == '-' )) {
			Node* parent_node = node_create(str[i]);
			stack_pop(&nodes, output);
			Node* right_node = output;
			stack_pop(&nodes, &output);
			Node* left_node = output;
			parent_node->right = right_node;
			parent_node->left = left_node;
			stack_push(&nodes, parent_node);
		} else {
			Node* node = node_create(str[i]);
			stack_push(&nodes, node);
		}
	}
	stack_pop(&nodes, output);
	return output;
}

int main(void) {
	char* input = input_expression();
	if (!input) printf("unluck\n");
	print_expression(input);
	char* result = convert_to_polin(input);
	print_expression(result);
	Node* tree_root = build_tree(result);
	node_display(&tree_root, 4);
	return 0;
}
