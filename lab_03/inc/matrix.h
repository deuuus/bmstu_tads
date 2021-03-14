#ifndef MATRIX_H
#define MATRIX_H

#include "io.h"

int prod(matrix_t matrix, vector_t vector, vector_t *res);
void usual_prod(int *matrix, int *vector, int size);
int max(int *a, int n);
void init_matrix(matrix_t *matrix);
void init_vector(vector_t *vector);

#endif