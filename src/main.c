#include <diff.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int line_count_A, line_count_B;
    char** A;
    char** B;
    if(argc >= 2)
    {

        A = read_file_lines(argv[1], &line_count_A);
        B = read_file_lines(argv[2], &line_count_B);
    }
    else
    {
        // Read the input files as lines
        A = read_file_lines("file1.txt", &line_count_A);
        B = read_file_lines("file2.txt", &line_count_B);
    }

    

    

    Operation* operations = NULL; // Initialize the operations list

    // Call the Myers diff algorithm
    int ses_length = myer_diff(A, line_count_A, B, line_count_B, &operations);

    printf("Length of Shortest Edit Script: %d\n", ses_length);
    printf("Edit Operations:\n");
    print_operations(operations); // Print the operations

    // Free allocated memory
    free_operations(operations);
    free_lines(A, line_count_A);
    free_lines(B, line_count_B);

    return 0;
}

