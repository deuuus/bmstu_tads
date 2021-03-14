#include "analys.h"
#include <sys/time.h>
#include <inttypes.h>

int mem(matrix_t matrix)
{
    return sizeof(matrix.rows) + sizeof(matrix.n) + matrix.n * (sizeof(matrix.a) + sizeof(matrix.ja))
        + sizeof(matrix.rows) * sizeof(matrix.ia);
}

int vect_mem(vector_t vector)
{
    return sizeof(vector.n) + vector.n * (sizeof(vector.a) + sizeof(vector.ia));
}

void print_test(char *p, int g)
{
    struct timeval t_start, t_end;
    size_t time_u[4] = { 0 };
    size_t time_o[4] = { 0 };
    size_t mem_u[4] = { 0 };
    size_t mem_o[4] = { 0 };
    matrix_t matrixx;
    vector_t vectorr, res;
    init_matrix(&matrixx);
    init_vector(&vectorr);
    init_vector(&res);
    FILE *f = NULL;
    int size;
    int *matrix = NULL;
    int *vector = NULL;

    int rep = 500;

    char str[30] = "shared/usual_10_";
    strcat(str, p);

    for (int i = 0; i < 5 * rep; i++)
    {
        f = fopen(str, "r");
        gettimeofday(&t_start, NULL);
        usual_read_file(&matrix, &vector, &size, &f);
        usual_prod(matrix, vector, size);
        gettimeofday(&t_end, NULL);
        time_u[0] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_u[0] = sizeof(*matrix) * size * size + 2 * sizeof(*vector) * size;


    strcpy(str, "shared/objects_10_");
    strcat(str, p);
    for (int i = 0; i < 5 * rep; i++)
    {
        f = fopen(str, "r");
        gettimeofday(&t_start, NULL);
        read_file(&matrixx, &vectorr, &f);
        prod(matrixx, vectorr, &res);
        gettimeofday(&t_end, NULL);
        time_o[0] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_o[0] = mem(matrixx) + vect_mem(vectorr);

    strcpy(str, "shared/usual_50_");
    strcat(str, p);
    for (int i = 0; i < rep; i++)
    {
        f = fopen(str, "r");
        gettimeofday(&t_start, NULL);
        usual_read_file(&matrix, &vector, &size, &f);
        usual_prod(matrix, vector, size);
        gettimeofday(&t_end, NULL);
        time_u[1] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_u[1] = sizeof(*matrix) * size * size + 2 * sizeof(*vector) * size;

    strcpy(str, "shared/objects_50_");
    strcat(str, p);
    for (int i = 0; i < rep; i++)
    {
        f = fopen(str, "r");
        gettimeofday(&t_start, NULL);
        read_file(&matrixx, &vectorr, &f);
        prod(matrixx, vectorr, &res);
        gettimeofday(&t_end, NULL);
        time_o[1] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_o[1] = mem(matrixx) + vect_mem(vectorr);

    strcpy(str, "shared/usual_100_");
    strcat(str, p);
    for (int i = 0; i < rep; i++)
    {
        f = fopen(str, "r");
        gettimeofday(&t_start, NULL);
        usual_read_file(&matrix, &vector, &size, &f);
        usual_prod(matrix, vector, size);
        gettimeofday(&t_end, NULL);
        time_u[2] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_u[2] = sizeof(*matrix) * size * size + 2 * sizeof(*vector) * size;

    strcpy(str, "shared/objects_100_");
    strcat(str, p);
    for (int i = 0; i < rep; i++)
    {
        f = fopen(str, "r");
        gettimeofday(&t_start, NULL);
        read_file(&matrixx, &vectorr, &f);
        prod(matrixx, vectorr, &res);
        gettimeofday(&t_end, NULL);
        time_o[2] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_o[2] = mem(matrixx) + vect_mem(vectorr);

    strcpy(str, "shared/usual_200_");
    strcat(str, p);
    for (int i = 0; i < rep / 5; i++)
    {
        f = fopen(str, "r");
        gettimeofday(&t_start, NULL);
        usual_read_file(&matrix, &vector, &size, &f);
        usual_prod(matrix, vector, size);
        gettimeofday(&t_end, NULL);
        time_u[3] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_u[3] = sizeof(*matrix) * size * size + 2 * sizeof(*vector) * size;

    strcpy(str, "shared/objects_200_");
    strcat(str, p);
    for (int i = 0; i < rep / 5; i++)
    {
        f = fopen(str, "r");
        gettimeofday(&t_start, NULL);
        read_file(&matrixx, &vectorr, &f);
        prod(matrixx, vectorr, &res);
        gettimeofday(&t_end, NULL);
        time_o[3] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_o[3] = mem(matrixx) + vect_mem(vectorr);

    time_u[0] /= 5 * rep;
    time_u[1] /= rep;
    time_u[2] /= rep;
    time_u[3] /= rep / 5;
    time_o[0] /= 5 * rep;
    time_o[1] /= rep;
    time_o[2] /= rep;
    time_o[3] /= rep / 5;
    printf("┃%8d%%        ┃", g);
    for (int i = 0; i < 4; i++)
        printf("%10zu ms┃%10zu ms┃", time_u[i], time_o[i]);
    printf("\n┃                 ┃");
    for (int i = 0; i < 4; i++)
        printf("%11zu b┃%11zu b┃", mem_u[i], mem_o[i]);
    printf("\n");
}

void analys(void)
{
    printf("┏━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃ Размер матрицы  ┃           10х10           ┃           50x50           ┃          100x100          ┃          200x200          ┃\n");
    printf("┃       /         ┣━━━━━━━━━━━━━┳━━━━━━━━━━━━━╋━━━━━━━━━━━━━┳━━━━━━━━━━━━━╋━━━━━━━━━━━━━┳━━━━━━━━━━━━━╋━━━━━━━━━━━━━┳━━━━━━━━━━━━━┫\n");
    printf("┃    процент      ┃   Обычная   ┃ Разреженная ┃   Обычная   ┃ Разреженная ┃   Обычная   ┃ Разреженная ┃   Обычная   ┃ Разреженная ┃\n");
    printf("┃  разреженности  ┃   матрица   ┃   матрица   ┃   матрица   ┃   матрица   ┃   матрица   ┃   матрица   ┃   матрица   ┃   матрица   ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━┫\n");
    
    char p[30] = "0.txt";
    print_test(p, 0);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━┫\n");
    strcpy(p, "10.txt");
    print_test(p, 10);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━┫\n");
    strcpy(p, "20.txt");
    print_test(p, 20);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━┫\n");
    strcpy(p, "30.txt");
    print_test(p, 30);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━┫\n");
    strcpy(p, "40.txt");
    print_test(p, 40);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━┫\n");
    strcpy(p, "50.txt");
    print_test(p, 50);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━┫\n");
    strcpy(p, "60.txt");
    print_test(p, 60);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━┫\n");
    strcpy(p, "70.txt");
    print_test(p, 70);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━┫\n");
    strcpy(p, "80.txt");
    print_test(p, 80);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━┫\n");
    strcpy(p, "90.txt");
    print_test(p, 90);
    printf("┗━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┛\n");
}

void eff_print_test(char *p, int g)
{
    struct timeval t_start, t_end;
    size_t time_u[4] = { 0 };
    size_t time_o[4] = { 0 };
    size_t mem_u[4] = { 0 };
    size_t mem_o[4] = { 0 };
    matrix_t matrixx;
    vector_t vectorr, res;
    init_matrix(&matrixx);
    init_vector(&vectorr);
    init_vector(&res);
    FILE *f = NULL;
    int size;
    int *matrix = NULL;
    int *vector = NULL;

    int rep = 500;

    char str[30] = "shared/usual_10_";
    strcat(str, p);

    for (int i = 0; i < 5 * rep; i++)
    {
        f = fopen(str, "r");
        gettimeofday(&t_start, NULL);
        usual_read_file(&matrix, &vector, &size, &f);
        usual_prod(matrix, vector, size);
        gettimeofday(&t_end, NULL);
        time_u[0] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_u[0] = sizeof(*matrix) * size * size + 2 * sizeof(*vector) * size;


    strcpy(str, "shared/objects_10_");
    strcat(str, p);
    for (int i = 0; i < 5 * rep; i++)
    {
        f = fopen(str, "r");
        gettimeofday(&t_start, NULL);
        read_file(&matrixx, &vectorr, &f);
        prod(matrixx, vectorr, &res);
        gettimeofday(&t_end, NULL);
        time_o[0] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_o[0] = mem(matrixx) + vect_mem(vectorr);

    strcpy(str, "shared/usual_50_");
    strcat(str, p);
    for (int i = 0; i < rep; i++)
    {
        f = fopen(str, "r");
        gettimeofday(&t_start, NULL);
        usual_read_file(&matrix, &vector, &size, &f);
        usual_prod(matrix, vector, size);
        gettimeofday(&t_end, NULL);
        time_u[1] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_u[1] = sizeof(*matrix) * size * size + 2 * sizeof(*vector) * size;

    strcpy(str, "shared/objects_50_");
    strcat(str, p);
    for (int i = 0; i < rep; i++)
    {
        f = fopen(str, "r");
        gettimeofday(&t_start, NULL);
        read_file(&matrixx, &vectorr, &f);
        prod(matrixx, vectorr, &res);
        gettimeofday(&t_end, NULL);
        time_o[1] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_o[1] = mem(matrixx) + vect_mem(vectorr);

    strcpy(str, "shared/usual_100_");
    strcat(str, p);
    for (int i = 0; i < rep; i++)
    {
        f = fopen(str, "r");
        gettimeofday(&t_start, NULL);
        usual_read_file(&matrix, &vector, &size, &f);
        usual_prod(matrix, vector, size);
        gettimeofday(&t_end, NULL);
        time_u[2] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_u[2] = sizeof(*matrix) * size * size + 2 * sizeof(*vector) * size;

    strcpy(str, "shared/objects_100_");
    strcat(str, p);
    for (int i = 0; i < rep; i++)
    {
        f = fopen(str, "r");
        gettimeofday(&t_start, NULL);
        read_file(&matrixx, &vectorr, &f);
        prod(matrixx, vectorr, &res);
        gettimeofday(&t_end, NULL);
        time_o[2] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_o[2] = mem(matrixx) + vect_mem(vectorr);

    strcpy(str, "shared/usual_200_");
    strcat(str, p);
    for (int i = 0; i < rep / 5; i++)
    {
        f = fopen(str, "r");
        gettimeofday(&t_start, NULL);
        usual_read_file(&matrix, &vector, &size, &f);
        usual_prod(matrix, vector, size);
        gettimeofday(&t_end, NULL);
        time_u[3] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_u[3] = sizeof(*matrix) * size * size + 2 * sizeof(*vector) * size;

    strcpy(str, "shared/objects_200_");
    strcat(str, p);
    for (int i = 0; i < rep / 5; i++)
    {
        f = fopen(str, "r");
        gettimeofday(&t_start, NULL);
        read_file(&matrixx, &vectorr, &f);
        prod(matrixx, vectorr, &res);
        gettimeofday(&t_end, NULL);
        time_o[3] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_o[3] = mem(matrixx) + vect_mem(vectorr);

    time_u[0] /= 5 * rep;
    time_u[1] /= rep;
    time_u[2] /= rep;
    time_u[3] /= rep / 5;
    time_o[0] /= 5 * rep;
    time_o[1] /= rep;
    time_o[2] /= rep;
    time_o[3] /= rep / 5;
    printf("┃%8d%%        ┃", g);
    for (int i = 0; i < 4; i++)
        printf("        Время: %10ld %%┃", (long) ((double) time_u[i] / (double) time_o[i] * 100));
    printf("\n┃                 ┃");
    for (int i = 0; i < 4; i++)
        printf("        Память: %9ld %%┃", (long)((double)mem_u[i]/(double)mem_o[i] * 100));
    printf("\n");
}

void eff(void)
{
    printf("┏━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃ Размер матрицы  ┃           10х10           ┃           50x50           ┃          100x100          ┃          200x200          ┃\n");
    printf("┃       /         ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃    процент      ┃   Обычная  / Разреженная  ┃   Обычная  / Разреженная  ┃   Обычная  / Разреженная  ┃   Обычная  / Разреженная  ┃\n");
    printf("┃  разреженности  ┃           матрица         ┃           матрица         ┃           матрица         ┃           матрица         ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    char p[30] = "0.txt";
    eff_print_test(p, 0);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    strcpy(p, "10.txt");
    eff_print_test(p, 10);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    strcpy(p, "20.txt");
    eff_print_test(p, 20);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    strcpy(p, "30.txt");
    eff_print_test(p, 30);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    strcpy(p, "40.txt");
    eff_print_test(p, 40);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    strcpy(p, "50.txt");
    eff_print_test(p, 50);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    strcpy(p, "60.txt");
    eff_print_test(p, 60);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    strcpy(p, "70.txt");
    eff_print_test(p, 70);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    strcpy(p, "80.txt");
    eff_print_test(p, 80);
    printf("┣━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    strcpy(p, "90.txt");
    eff_print_test(p, 90);
    printf("┗━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}