#include <string.h>
#include <diff.h>
#include <stdio.h>
#include <stdlib.h>

// Function to add an operation to the list
void add_operation(Operation** head, char type, const char* line) {
    Operation* new_op = malloc(sizeof(Operation));
    if (!new_op) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    new_op->type = type;
    new_op->line = strdup(line); // Duplicate the line
    if (!new_op->line) {
        perror("strdup failed");
        exit(EXIT_FAILURE);
    }
    new_op->next = *head;
    *head = new_op;
}

// Function to free the operations list
void free_operations(Operation* head) {
    while (head) {
        Operation* temp = head;
        head = head->next;
        free(temp->line); // Free the duplicated line
        free(temp);
    }
}

// Function to print the operations list
void print_operations(Operation* operations) {
    Operation* current = operations;
    while (current) {
        if (current->type == 'M') {
            printf("Match: %s", current->line);
        } else if (current->type == 'I') {
            printf("Insert: %s", current->line);
        } else if (current->type == 'D') {
            printf("Delete: %s", current->line);
        }
        current = current->next;
    }
}

char** read_file_lines(const char* filename, int* line_count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    int capacity = 1024;
    char** lines = malloc(capacity * sizeof(char*)); // Allocate space for up to 1024 lines initially
    if (!lines) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    *line_count = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        if (*line_count >= capacity) {
            capacity *= 2; // Double the capacity
            lines = realloc(lines, capacity * sizeof(char*));
            if (!lines) {
                perror("realloc failed");
                exit(EXIT_FAILURE);
            }
        }
        lines[*line_count] = strdup(buffer); // Duplicate the line
        if (!lines[*line_count]) {
            perror("strdup failed");
            exit(EXIT_FAILURE);
        }
        (*line_count)++;
    }

    fclose(file);
    return lines;
}

void free_lines(char** lines, int line_count) {
    for (int i = 0; i < line_count; i++) {
        free(lines[i]);
    }
    free(lines);
}

int myer_diff(char** A, int N, char** B, int M, Operation** operations) {
    int MAX = N + M;
    int* V = calloc(MAX * 2 + 1, sizeof(int)); // Allocate dynamically to avoid stack overflow
    if (!V) {
        perror("calloc failed");
        exit(EXIT_FAILURE);
    }
    memset(V, 0, (MAX * 2 + 1) * sizeof(int));
    int offset = MAX; // Offset to handle negative indices

    for (int D = 0; D <= MAX; D++) {
        for (int k = -D; k <= D; k += 2) {
            int x, y;
            if ((k == -D) || (k != D && V[offset + k - 1] < V[offset + k + 1])) {
                // Move down (Insertion)
                x = V[offset + k + 1];
                y = x - k;
                if (y < M) {
                    add_operation(operations, 'I', B[y]); // Record insertion
                }
            } else {
                // Move right (Deletion)
                x = V[offset + k - 1] + 1;
                y = x - k;
                if (x <= N) {
                    add_operation(operations, 'D', A[x - 1]); // Record deletion
                }
            }

            // Match lines along the diagonal
            while (x < N && y < M && strcmp(A[x], B[y]) == 0) {
                add_operation(operations, 'M', A[x]); // Record match
                x++;
                y++;
            }

            V[offset + k] = x;

            // If we reach the bottom-right corner, return the result
            if (x >= N && y >= M) {
                free(V);
                return D; // Return the length of the shortest edit script
            }
        }
    }

    free(V);
    return MAX; // Return MAX if no path is found (shouldn't happen)
}
