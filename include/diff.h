#ifndef DIFF_H
#define DIFF_H

typedef struct Operation {
    char type; // 'M' for match, 'I' for insert, 'D' for delete
    char* line;   // Character involved in the operation
    struct Operation* next;
} Operation;

char** read_file_lines(const char* filename, int* line_count);

void free_lines(char** lines, int line_count);

void free_operations(Operation* head);

void print_operations(Operation* operations);

int myer_diff(char** A, int N, char** B, int M, Operation** operations);


#endif