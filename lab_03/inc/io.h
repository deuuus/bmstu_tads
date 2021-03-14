#ifndef IO_H
#define IO_H

#include "codes.h"
#include <string.h>

int input_objects(matrix_t *matrix, vector_t *vector);
int usual_input(matrix_t *matrix, vector_t *vector);
int read_file(matrix_t *matrix, vector_t *vector, FILE **f);
int index_usual_input(matrix_t *matrix, vector_t *vector);
int usual_read_file(int **matrix, int **vector, int *size, FILE **f);
void output_matrix(matrix_t matrix);
void output_vector(vector_t vector);
int read_pos(int *item);

#endif