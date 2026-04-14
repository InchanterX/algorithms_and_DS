#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum
{
    SUCCESS,
    ALREADY_EXIST,
    DO_NOT_EXIST,
    MEMORY_ERROR,
    INCORRECT_KEY
} Status;

typedef enum
{
    BLACK,
    RED
} Color;

typedef struct Node
{
    char *key;
    float value;
    bool color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;

} Node;

Node *init_tree(void)
{
    Node *tree = NULL;
    return tree;
}

Node *create_node(const char *key, float value, Node *previous)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->key = (char *)malloc(strlen(key) + 1);
    strcpy(new_node->key, key);
    new_node->value = value;
    new_node->color = RED;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = previous;
    return new_node;
}

void free_node(Node *node)
{
    if (node)
    {
        free(node->key);
        free(node);
    }
}

void free_tree(Node *root)
{
    if (!root)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free_node(root);
}

bool node_exists(Node *node)
{
    if (node)
        return true;
    else
        return false;
}

int compare_keys(const char *a, const char *b)
{
    return strcmp(a, b);
}

const char *get_color(Node *node)
{
    if (!node)
        return "";
    return node->color == RED ? "(R)" : "(B)";
}

void print_tree_recursive(Node *node, int level, const char *prefix)
{
    if (!node)
        return;
    for (int i = 0; i < level; i++)
        printf("    ");
    printf("%s%s %s", prefix, node->key, get_color(node));
    if (node->parent)
        printf(" (parent: %s)", node->parent->key);
    printf("\n");

    if (node->left || node->right)
    {
        print_tree_recursive(node->left, level + 1, "L:");
        print_tree_recursive(node->right, level + 1, "R:");
    }
}

void print_tree(Node *root)
{
    if (!root)
    {
        printf("Empty tree\n");
        return;
    }

    printf("\nTree:\n");
    print_tree_recursive(root, 0, "");
}

void right_rotate(Node **root, Node *added_node)
{
    if (!(*root) || !(added_node))
        return;

    Node *buffer = added_node->left;
    if (!buffer)
        return;

    Node *parent = added_node->parent;

    buffer->parent = parent;
    if (parent)
    {
        if (parent->left == added_node)
            parent->left = buffer;
        else
            parent->right = buffer;
    }
    else
    {
        *root = buffer;
    }

    Node *temp = buffer->right;

    buffer->right = added_node;
    added_node->parent = buffer;

    added_node->left = temp;
    if (temp)
        temp->parent = added_node;
}

void left_rotate(Node **root, Node *added_node)
{
    if (!(*root) || !(added_node))
        return;

    Node *buffer = added_node->right;
    if (!buffer)
        return;

    Node *parent = added_node->parent;

    buffer->parent = parent;
    if (parent)
    {
        if (parent->left == added_node)
            parent->left = buffer;
        else
            parent->right = buffer;
    }
    else
    {
        *root = buffer;
    }

    Node *temp = buffer->left;

    buffer->left = added_node;
    added_node->parent = buffer;

    added_node->right = temp;
    if (temp)
        temp->parent = added_node;
}

void balance_tree(Node **root, Node *added_node)
{
    if (!(*root) || !(added_node))
        return;
    Node *uncle;
    while (added_node && added_node != *root && added_node->parent && added_node->parent->color == RED)
    {
        if (!added_node->parent->parent)
            break;
        if (added_node->parent == added_node->parent->parent->left)
        {
            uncle = added_node->parent->parent->right;
            if (uncle && uncle->color == RED)
            {
                added_node->parent->color = BLACK;
                uncle->color = BLACK;
                added_node->parent->parent->color = RED;
                added_node = added_node->parent->parent;
            }
            else
            {
                Node *grandfather = added_node->parent->parent;
                if (added_node == added_node->parent->right)
                {
                    added_node = added_node->parent;
                    left_rotate(root, added_node);
                }
                added_node->parent->color = BLACK;
                grandfather->color = RED;
                right_rotate(root, grandfather);
                break;
            }
        }
        else
        {
            uncle = added_node->parent->parent->left;
            if (uncle && uncle->color == RED)
            {
                added_node->parent->color = BLACK;
                uncle->color = BLACK;
                added_node->parent->parent->color = RED;
                added_node = added_node->parent->parent;
            }
            else
            {
                Node *grandfather = added_node->parent->parent;
                if (added_node == added_node->parent->left)
                {
                    added_node = added_node->parent;
                    right_rotate(root, added_node);
                }
                added_node->parent->color = BLACK;
                grandfather->color = RED;
                left_rotate(root, grandfather);
                break;
            }
        }
    }
    (*root)->color = BLACK;
}

Status add(Node **root, const char *key, float value)
{
    if (!(*root))
    {
        *root = create_node(key, value, NULL);
        (*root)->color = BLACK;
        return SUCCESS;
    }

    Node *current = *root;
    Node *previous = NULL;
    int direction;

    while (current)
    {
        int cmp = strcmp(key, current->key);
        if (cmp == 0)
        {
            return ALREADY_EXIST;
        }

        previous = current;

        if (cmp < 0)
        {
            direction = 0;
            current = current->left;
        }
        else
        {
            direction = 1;
            current = current->right;
        }
    }

    Node *new_node = create_node(key, value, previous);

    if (direction)
    {
        previous->right = new_node;
    }
    else
    {
        previous->left = new_node;
    }
    balance_tree(root, new_node);
    return SUCCESS;
}

Node *find(Node *root, const char *key)
{
    if (!root)
        return NULL;
    Node *current = root;
    while (current)
    {
        int cmp = strcmp(key, current->key);
        if (cmp == 0)
        {
            return current;
        }
        else if (cmp < 0)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return NULL;
}

int get_children_count(Node *node)
{
    if (!node)
        return 0;
    int count = 0;
    if (node_exists(node->left))
        count += 1;
    if (node_exists(node->right))
        count += 1;
    return count;
}

Node *get_child_or_another(Node *node)
{
    if (!node)
        return NULL;
    if (node->left)
        return node->left;
    if (node->right)
        return node->right;
    return NULL;
}

void transit_node(Node **root, Node *destination, Node *origin)
{
    if (!(root) || !destination)
        return;

    if (destination->parent)
    {
        if (destination == destination->parent->left)
            destination->parent->left = origin;
        else
            destination->parent->right = origin;
    }
    else
    {
        *root = origin;
    }

    if (origin)
        origin->parent = destination->parent;
}

Node *get_min(Node *root)
{
    if (!root)
        return NULL;

    while (root->left)
    {
        root = root->left;
    }
    return root;
}

void fix_tree(Node **root, Node *node)
{
    while (node != *root && node && node->color == BLACK)
    {
        Node *brother;
        if (node == node->parent->left)
        {
            brother = node->parent->right;
            if (brother && brother->color == RED)
            {
                brother->color = BLACK;
                node->parent->color = RED;
                left_rotate(root, node->parent);
                brother = node->parent->right;
            }
            if (!brother || (!brother->left || brother->left->color == BLACK) && (!brother->right || brother->right->color == BLACK))
            {
                if (brother)
                    brother->color = RED;
                node = node->parent;
            }
            else
            {
                if (brother && (!brother->right || brother->right->color == BLACK))
                {
                    if (brother->left)
                        brother->left->color = BLACK;
                    brother->color = RED;
                    right_rotate(root, brother);
                    brother = node->parent->right;
                }
                if (brother)
                {
                    brother->color = node->parent->color;
                    if (brother->right)
                        brother->right->color = BLACK;
                    brother = node->parent->right;
                }
                node->parent->color = BLACK;
                left_rotate(root, node->parent);
                node = *root;
            }
        }
        else
        {
            brother = node->parent->left;
            if (brother && brother->color == RED)
            {
                brother->color = BLACK;
                node->parent->color = RED;
                right_rotate(root, node->parent);
                brother = node->parent->left;
            }
            if (!brother || (!brother->left || brother->left->color == BLACK) && (!brother->right || brother->right->color == BLACK))
            {
                if (brother)
                    brother->color = RED;
                node = node->parent;
            }
            else
            {
                if (brother && (!brother->left || brother->left->color == BLACK))
                {
                    if (brother->right)
                        brother->right->color = BLACK;
                    brother->color = RED;
                    left_rotate(root, brother);
                    brother = node->parent->left;
                }
                if (brother)
                {
                    brother->color = node->parent->color;
                    if (brother->left)
                        brother->left->color = BLACK;
                    brother = node->parent->left;
                }
                node->parent->color = BLACK;
                right_rotate(root, node->parent);
                node = *root;
            }
        }
    }
    if (node)
        node->color = BLACK;
}

Status remove_node(Node **root, const char *key)
{
    if (!(*root))
        return DO_NOT_EXIST;

    Node *node_to_delete = find(*root, key);
    if (!node_to_delete)
        return DO_NOT_EXIST;

    Color remove_node_color = node_to_delete->color;
    Node *child;

    if (get_children_count(node_to_delete) < 2)
    {
        child = get_child_or_another(node_to_delete);
        transit_node(root, node_to_delete, child);
    }
    else
    {
        Node *min_node = get_min(node_to_delete->right);
        free(node_to_delete->key);
        node_to_delete->key = (char *)malloc(strlen(min_node->key) + 1);
        strcpy(node_to_delete->key, min_node->key);
        node_to_delete->value = min_node->value;
        remove_node_color = min_node->color;
        child = get_child_or_another(min_node);
        transit_node(root, min_node, child);
        node_to_delete = min_node;
    }

    if (remove_node_color == BLACK)
        fix_tree(root, child);

    free_node(node_to_delete);
    return SUCCESS;
}

void process_commands_from_file(Node **root, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error: failed to open the file %s\n", filename);
        return;
    }

    int op;
    char key[256];
    float value;

    printf("\n Command procession from file: %s \n", filename);

    while (fscanf(fp, "%d", &op) == 1)
    {
        switch (op)
        {
        case 1:
            if (fscanf(fp, "%255s %f", key, &value) == 2)
            {
                Status st = add(root, key, value);
                if (st == SUCCESS)
                    printf("Added: %s\n", key);
                else if (st == ALREADY_EXIST)
                    printf("Key %s already exists\n", key);
                else
                    printf("Failed to add %s\n", key);
            }
            else
                printf("Format error: wait for 1 <key> <value>\n");
            break;

        case 2:
            if (fscanf(fp, "%255s", key) == 1)
            {
                Status st = remove_node(root, key);
                if (st == SUCCESS)
                    printf("Deleted: %s\n", key);
                else
                    printf("Key %s wasn't found\n", key);
            }
            else
                printf("Format error: wait for 2 <key>\n");
            break;

        case 3:
            print_tree(*root);
            break;

        case 4:
            if (fscanf(fp, "%255s", key) == 1)
            {
                Node *found = find(*root, key);
                if (found)
                    printf("Found: %s = %.2f\n", found->key, found->value);
                else
                    printf("Key %s wasn't found\n", key);
            }
            else
                printf("Format error: wait for 4 <key>\n");
            break;

        default:
            printf("Unknown operator: %d\n", op);
            break;
        }
    }
    fclose(fp);
}

void print_tree_recursive_file(Node *node, int level, const char *prefix, FILE *fp)
{
    if (!node)
        return;

    for (int i = 0; i < level; i++)
        fprintf(fp, "    ");

    fprintf(fp, "%s%s %s", prefix, node->key, node->color == RED ? "(R)" : "(B)");
    if (node->parent)
        fprintf(fp, " (parent: %s)", node->parent->key);
    fprintf(fp, "\n");

    if (node->left || node->right)
    {
        print_tree_recursive_file(node->left, level + 1, "L:", fp);
        print_tree_recursive_file(node->right, level + 1, "R:", fp);
    }
}

void print_tree_to_file(Node *root, FILE *fp)
{
    if (!root)
    {
        fprintf(fp, "Tree is empty\n");
        return;
    }

    fprintf(fp, "\nTree:\n");
    print_tree_recursive_file(root, 0, "", fp);
    fprintf(fp, "\n");
}

void process_commands_from_file_to_file(Node **root, const char *in_filename, const char *out_filename)
{
    FILE *in_fp = fopen(in_filename, "r");
    if (!in_fp)
    {
        printf("Error: cannot open input file %s\n", in_filename);
        return;
    }

    FILE *out_fp = fopen(out_filename, "w");
    if (!out_fp)
    {
        printf("Error: cannot open output file %s\n", out_filename);
        fclose(in_fp);
        return;
    }

    char line[1024];
    printf("\n=== Processing commands from file: %s ===\n", in_filename);
    fprintf(out_fp, "=== Command processing started ===\n");

    while (fgets(line, sizeof(line), in_fp))
    {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        if (line[0] == '\0')
            continue;

        fprintf(out_fp, "%s\n", line);

        int op;
        char key[256];
        float value;

        if (sscanf(line, "%d", &op) != 1)
        {
            printf("Format error: %s\n", line);
            fprintf(out_fp, "Error: invalid command format\n\n");
            continue;
        }

        switch (op)
        {
        case 1:
            if (sscanf(line, "%*d %255s %f", key, &value) == 2)
            {
                Status st = add(root, key, value);
                if (st == SUCCESS)
                {
                    printf("Added: %s\n", key);
                    fprintf(out_fp, "Added: %s\n\n", key);
                }
                else if (st == ALREADY_EXIST)
                {
                    printf("Key %s already exists\n", key);
                    fprintf(out_fp, "Key %s already exists\n\n", key);
                }
                else
                {
                    printf("Error adding %s\n", key);
                    fprintf(out_fp, "Error adding %s\n\n", key);
                }
            }
            else
            {
                printf("Format error: expected 1 <key> <value>\n");
                fprintf(out_fp, "Format error: expected 1 <key> <value>\n\n");
            }
            break;

        case 2:
            if (sscanf(line, "%*d %255s", key) == 1)
            {
                Status st = remove_node(root, key);
                if (st == SUCCESS)
                {
                    printf("Deleted: %s\n", key);
                    fprintf(out_fp, "Deleted: %s\n\n", key);
                }
                else
                {
                    printf("Key %s not found for deletion\n", key);
                    fprintf(out_fp, "Key %s not found for deletion\n\n", key);
                }
            }
            else
            {
                printf("Format error: expected 2 <key>\n");
                fprintf(out_fp, "Format error: expected 2 <key>\n\n");
            }
            break;

        case 3:
            print_tree(*root);
            print_tree_to_file(*root, out_fp);
            fprintf(out_fp, "\n");
            break;

        case 4:
            if (sscanf(line, "%*d %255s", key) == 1)
            {
                Node *found = find(*root, key);
                if (found)
                {
                    printf("Found: %s = %.2f\n", found->key, found->value);
                    fprintf(out_fp, "Found: %s = %.2f\n\n", found->key, found->value);
                }
                else
                {
                    printf("Key %s not found\n", key);
                    fprintf(out_fp, "Key %s not found\n\n", key);
                }
            }
            else
            {
                printf("Format error: expected 4 <key>\n");
                fprintf(out_fp, "Format error: expected 4 <key>\n\n");
            }
            break;

        default:
            printf("Unknown operation: %d\n", op);
            fprintf(out_fp, "Unknown operation: %d\n\n", op);
            break;
        }
    }

    printf("=== Processing completed ===\n\n");
    fprintf(out_fp, "=== Processing completed ===\n");
    fclose(in_fp);
    fclose(out_fp);
}

int main(void)
{
    Node *tree = init_tree();
    // process_commands_from_file(&tree, "commands.txt");
    process_commands_from_file_to_file(&tree, "in.txt", "out.txt");
    free_tree(tree);
    return 0;
}
