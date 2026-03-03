#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SUCCESS 0
#define FILE_READING_ERROR 1
#define INPUT_ERROR 2
#define MAMORY_ERROR 3
#define PROHIBITED_VALUE_ERROR 4

#define MAX_LETTERS 11
#define MAX_KEY_LENGTH 21
#define MAX_NUMBER (0u - 1u)

typedef struct Key {
	int number;
	char letters[MAX_LETTERS];
} Key;

typedef struct Table {
	Key* keys;
	char** data;
	unsigned int* indexes;
	unsigned int size;
} Table;

Table* read_table(void) {
	/* Initialize a table and fill with data from file. Return pointer to it. */
	char c;
	// Open file
	FILE* file = fopen("/home/ix/repositories/algorithms_and_DS/lab2/test_data.txt", "r");

	if (file == NULL) {
		printf("Cannot open file.\n");
		return NULL;
	}

	// Allocate memory for the table
	unsigned int size = 0;
    unsigned int capacity = 17;

    Table* table = malloc(sizeof(Table));
    if (!table) {
        fclose(file);
        return NULL;
    }

    table->keys = malloc(sizeof(Key) * capacity);
    table->data = malloc(sizeof(char*) * capacity);
    table->indexes = (unsigned int*)malloc(sizeof(unsigned int) * capacity);
    table->size = 0;

    if (!table->keys || !table->data || !table->indexes) {
        fclose(file); free(table->keys); free(table->data);
        free(table->indexes); free(table); return NULL;
    }

    // Process file
    while (1) {

    	// Read key
        char key_buffer[MAX_KEY_LENGTH];
        if (fscanf(file, "%20s", key_buffer) != 1)
            break;

        // Extend array in two times if it is full
        if (size == capacity) {
            capacity *= 2;

            Key* new_keys = realloc(table->keys, sizeof(Key) * capacity);
            char** new_data = realloc(table->data, sizeof(char*) * capacity);
            unsigned int* new_indexes 
            = (unsigned int*)realloc(table->indexes, sizeof(unsigned int) * capacity);

            if (!new_keys || !new_data || !new_indexes) {
                fclose(file); 
                return NULL;
            }

            table->keys = new_keys;
            table->data = new_data;
            table->indexes = new_indexes;
        }

        // Split digits and letters
        unsigned int j = 0;
        while (isdigit(key_buffer[j])) j++;

        char number_part[11];
        strncpy(number_part, key_buffer, j);
        number_part[j] = '\0';

        table->keys[size].number = atoi(number_part);
        strcpy(table->keys[size].letters, key_buffer + j);

        table->indexes[size] = size;

        // Skip space
        fgetc(file);

        // Dinamically read data from file
        unsigned int data_capacity = 32;
        unsigned int len = 0;
        table->data[size] = malloc(data_capacity);
        if (!table->data[size]) { fclose(file); return NULL; }

        int ch;
        while ((ch = fgetc(file)) != '\n' && ch != EOF) {
            if (len + 1 >= data_capacity) {
                data_capacity *= 2;
                char* temp = realloc(table->data[size], data_capacity);
                if (!temp) { fclose(file); return NULL; }
                table->data[size] = temp;
            }
            table->data[size][len++] = (char)ch;
        }

        table->data[size][len] = '\0';

        size++;
    }

    if (size < 17) {
        free(table->indexes); free(table->keys); free(table->data);
        free(table); fclose(file); return NULL; 
    }


    table->size = size;

    fclose(file);
    return table;
}

int number_length(unsigned int number) {
    if (number == 0) return 0;
    int count = 0;
    while (number > 0) {
        number /= 10;
        count++;
    }
    return count;
}

int print_table(Table* table) {
	/* Display table to the terminal */
	if (!table) return INPUT_ERROR;

	int counter = 0;
	printf("||Current Table State||\n");
	for (int i = 0; i < table->size; i++) {
		// Dispay indexe
		printf("%3d ", table->indexes[i]);

		// Display key
		printf("%d", table->keys[table->indexes[i]].number);
		int j = 0;
		counter = 0;
		while (table->keys[table->indexes[i]].letters[j] != '\0') {
			putchar(table->keys[table->indexes[i]].letters[j]);
			j++;
			counter++;
		}
		// Allign key 
        // Better to use 21 here
		int remaining_length = 11 
			- strlen(table->keys[table->indexes[i]].letters) 
			- number_length(table->keys[table->indexes[i]].number);
		for (int i = 0; i < remaining_length; i++) putchar(' ');
	
		putchar(' ');
		int k = 0;
		while (table->data[table->indexes[i]][k] != '\0') {
			putchar(table->data[table->indexes[i]][k]);
			k++;
		}
		putchar('\n');
	}
	printf("||        End        ||\n");
	return SUCCESS;
}

int compare_keys(Key key1, Key key2) {
    if (key1.number < key2.number) return -1;
    if (key1.number > key2.number) return 1;
    return strcmp(key1.letters, key2.letters);
}

void sort_table_by_keys(Table* table) {
    for (unsigned int i = 0; i < table->size - 1; i++) {
        unsigned int index_min = i;

        for (unsigned int j = i + 1; j < table->size; j++) {
            if (compare_keys(table->keys[table->indexes[index_min]], table->keys[table->indexes[j]]) > 0) {
                index_min = j;
            }
        }

        unsigned int buffer = table->indexes[i];
        table->indexes[i] = table->indexes[index_min];
        table->indexes[index_min] = buffer;
    }
}

void sort_table_by_data(Table* table) {
    for (unsigned int i = 0; i < table->size - 1; i++) {
        unsigned int index_min = i;

        for (unsigned int j = i + 1; j < table->size; j++) {
            if (strcmp(table->data[table->indexes[index_min]], table->data[table->indexes[j]]) > 0) {
                index_min = j;
            }
        }
        unsigned int buffer = table->indexes[i];
        table->indexes[i] = table->indexes[index_min];
        table->indexes[index_min] = buffer;
    }
}

void search_table(Table* table, unsigned int value) {}

void process_status(int status) {
    /* Process functions statuses and print proper respose */
    switch(status) {
        case 0:
            break;
        case 1:
            printf("Failed to open or read the file with data!\n");
            break;
        case 2:
            printf("Incorrect function input!\n");
            break;
        case 3:
            printf("Failed to allocate memory!\n");
            break;
        case 4:
            printf("Prohibited value was given!\n");
            break;
        default:
            printf("Unknown error, contact the developer!\n");
    }
}

int main(void) {
	Table* table = read_table();
    print_table(table);
    sort_table_by_data(table);
    print_table(table);
    sort_table_by_keys(table);
    print_table(table);
	return 0;
}
