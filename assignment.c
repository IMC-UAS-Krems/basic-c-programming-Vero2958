#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

// Function to check if a string represents a positive integer (including 0).
int is_positive_integer(const char *str) {
    if (str == NULL || *str == '\0') return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

// Function to create a dynamically allocated matrix
int** create_matrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        printf("Memory allocation failed for matrix rows.\n");
        exit(1);
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed for matrix columns.\n");
            exit(1);
        }
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100 + 1; // Random number between 1 and 100
        }
    }
    return matrix;
}

// Function to write the matrix to a file
void write_matrix_to_file(int** matrix, int rows, int cols) {
    FILE *file = fopen("matrix.txt", "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        exit(1);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d", matrix[i][j]);
            if (j < cols - 1) {
                fprintf(file, " ");
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

// Function to free the dynamically allocated matrix
void free_matrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Main function
int main(int argc, char *argv[]) {
    // Check argument count
    if (argc != 3) {
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", argc - 1);
        return 1;
    }

    // Validate arguments
    if (!is_positive_integer(argv[1]) || !is_positive_integer(argv[2])) {
        printf("Incorrect usage. The parameters you provided are not positive integers\n");
        return 1;
    }

    // Parse dimensions
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    // Check dimensions
    if (rows <= 0 || cols <= 0) {
        printf("Incorrect usage. The parameters you provided are not positive integers\n");
        return 1;
    }

    // Seed random number generator
    srand(time(NULL));

    // Create and populate the matrix
    int** matrix = create_matrix(rows, cols);

    // Write the matrix to a file
    write_matrix_to_file(matrix, rows, cols);

    // Free the allocated memory
    free_matrix(matrix, rows);

    printf("Matrix of size %dx%d created and written to 'matrix.txt'.\n", rows, cols);
    return 0;
}
