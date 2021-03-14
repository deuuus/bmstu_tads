#include "matrix.h"

int is_valid(matrix_t matrix, vector_t vector);

int prod(matrix_t matrix, vector_t vector, vector_t *res)
{
    if (is_valid(matrix, vector))
        return ERR_PROD;
    res->n = vector.n;
    res->a = calloc(vector.n, sizeof(int));
    while (!res->a)
        res->a = calloc(vector.n, sizeof(int));
    res->ia = calloc(vector.n, sizeof(int));
    while (!res->ia)
        res->ia = calloc(vector.n, sizeof(int));
    for (int i = 0; i < vector.n; i++)
        *(res->ia + i) = *(vector.ia + i);
    for (int k = 0; k < matrix.rows; k++)
        for (int i = 0; i < vector.n; i++)
        {
            int j_index = *(vector.ia + i) - 1;
            for (int j = *(matrix.ia + k) - 1; j < *(matrix.ia + k + 1) - 1; j++)
                if ((*(matrix.ja + j) - 1) == j_index)
                    *(res->a + i) += (*(vector.a + i)) * (*(matrix.a + j));
        }
    return EXIT_SUCCESS;
}

int is_valid(matrix_t matrix, vector_t vector)
{
    int max_v_row = *vector.ia;
    for (int i = 1; i < vector.n; i++)
        if (*(vector.ia + i) > max_v_row)
            max_v_row = *(vector.ia + i);
    int max_m_col = *matrix.ja;
    for (int i = 1; i < matrix.n; i++)
        if (*(matrix.ja + i) > max_m_col)
            max_m_col = *(matrix.ja + i);
    if (max_m_col < max_v_row)
    {
        printf("\n%d %d\n", max_m_col, max_v_row);
        printf("\nНевозможно выполнить умножение: количество столбцов в матрице больше, "
            "чем количество строк в векторе.\n\nЗавершение работы.");
        return ERR_PROD;
    }
    return EXIT_SUCCESS;
}

void usual_prod(int *matrix, int *vector, int size)
{
    int *res;
    res = malloc(size * sizeof(int));
    while (!res)
        res = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        int elem = 0;
        for (int j = 0; j < size; j++)
            elem += *(matrix + i * size + j) * *(vector + j);
        *(res + i) = elem;
    }
    free(res);
}

void init_matrix(matrix_t *matrix)
{
    matrix->a = NULL;
    matrix->ia = NULL;
    matrix->ja = NULL;
}

void init_vector(vector_t *vector)
{
    vector->a = NULL;
    vector->ia = NULL;
    vector->n = 0;
}