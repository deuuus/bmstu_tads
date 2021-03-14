#include "io.h"

int input_objects(matrix_t *matrix, vector_t *vector)
{
    free(matrix->a);
    free(matrix->ja);
    free(matrix->ia);
    free(vector->a);
    free(vector->ia);
    printf("Введите количество ненулевых элементов в матрице: ");
    if (scanf("%d", &matrix->n) != 1 || matrix->n <= 0 || getchar() != '\n')
    {
        printf("Ошибка: количество выражается целым неотрицательным числом.\n");
        return ERR_POS;
    }
    matrix->a = malloc(matrix->n * sizeof(int));
    while (!matrix->a)
        matrix->a = malloc(matrix->n * sizeof(int));
    printf("Введите ненулевые элементы матрицы(вектор A)):\n");
    int k = 0;
    while (k < matrix->n && scanf("%d", (matrix->a + k)) == 1)
        k++;
    if (getchar() != '\n' || k != matrix->n)
    {
        printf("Ошибка ввода: должно быть введено %d целых чисел.", matrix->n);
        free(matrix->a);
        return ERR_LINE;
    }
    printf("\nВектор А успешно введен.\n\nВведите номера столбцов для элементов вектора А(вектор JA):\n");
    matrix->ja = malloc(matrix->n * sizeof(int));
    while (!matrix->ja)
        matrix->ja = malloc(matrix->n * sizeof(int));
    k = 0;
    while (k < matrix->n && scanf("%d", (matrix->ja + k)) == 1 && *(matrix->ja + k) > 0)
        k++;
    if (getchar() != '\n' || k != matrix->n)
    {
        printf("Ошибка ввода: должно быть введено %d целых чисел.", matrix->n);
        free(matrix->a);
        free(matrix->ja);
        return ERR_LINE;
    }
    printf("\nВектор JA успешно введен.\n\n");
    printf("Введите количество элементов в векторе IA:\n");
    if (scanf("%d", &matrix->rows) != 1 || matrix->rows <= 0 || getchar() != '\n')
    {
        printf("Ошибка: количество выражается целым неотрицательным числом.\n");
        free(matrix->a);
        free(matrix->ja);
        return ERR_POS;
    }
    matrix->ia = malloc((matrix->rows + 1) * sizeof(int));
    while (!matrix->ia)
        matrix->ia = malloc((matrix->rows + 1) * sizeof(int));
    k = 0;
    printf("Введите количество элеменов вектора IA: ");
    while (k <= matrix->rows && scanf("%d", (matrix->ia + k)) == 1 && *(matrix->ia + k) > 0)
        k++;
    if (getchar() != '\n' || k != (matrix->rows + 1))
    {
        printf("Ошибка ввода: должно быть введено %d целых чисел.", matrix->rows + 1);
        free(matrix->a);
        free(matrix->ja);
        free(matrix->ia);
        return ERR_LINE;
    }

    printf("Матрица успешно введена. \nВведите количество ненулевых элементов в векторе-столбце: ");
    if (scanf("%d", &vector->n) != 1 || vector->n <= 0 || getchar() != '\n')
    {
        printf("Ошибка: количество выражается целым неотрицательным числом.\n");
        free(matrix->a);
        free(matrix->ja);
        free(matrix->ia);
        return ERR_POS;
    }
    vector->a = malloc(vector->n * sizeof(int));
    while (!vector->a)
        vector->a = malloc(vector->n * sizeof(int));
    printf("Введите ненулевые элементы вектора-столбца(вектор A)):\n");
    k = 0;
    while (k < vector->n && scanf("%d", (vector->a + k)) == 1)
        k++;
    if (getchar() != '\n' || k != vector->n)
    {
        printf("Ошибка ввода: должно быть введено %d целых чисел.", vector->n);
        free(matrix->a);
        free(matrix->ja);
        free(matrix->ia);
        free(vector->a);
        return ERR_LINE;
    }
    printf("\nВектор A успешно введен.\n\n");
    printf("Введите элементы вектора IA для вектора-столбца:\n");
    vector->ia = malloc(vector->n * sizeof(int));
    while (!vector->ia)
        vector->ia = malloc(vector->n * sizeof(int));
    k = 0;
    while (k <= vector->n && scanf("%d", (vector->ia + k)) == 1)
        k++;
    if (getchar() != '\n' || k != vector->n)
    {
        printf("Ошибка ввода: должно быть введено %d целых чисел.", vector->n);
        free(matrix->a);
        free(matrix->ja);
        free(matrix->ia);
        free(vector->a);
        free(vector->ia);
        return ERR_LINE;
    }
    printf("\n\nДанные успешно введены.\n\n");
    return EXIT_SUCCESS;
}

int index_usual_input(matrix_t *matrix, vector_t *vector)
{
    printf("Введите количество ненулевых элементов матрицы: ");
    int n, rc;
    if ((rc = read_pos(&n)))
        return rc;
    matrix->n = n;
    matrix->a = calloc(n, sizeof(int));
    while (!matrix->a)
        matrix->a = calloc(n, sizeof(int));
    matrix->ja = calloc(n, sizeof(int));
    while (!matrix->ja)
        matrix->ja = calloc(n, sizeof(int));
    matrix->ia = calloc(1, sizeof(int));
    while (!matrix->ia)
        matrix->ia = calloc(1, sizeof(int));
    int item, row, col;
    int max_row = 0;
    for (int i = 0; i < n; i++)
    {
        printf("Введите номер строки %d-ого ненулевого элемента: ", i + 1);
        if ((rc = read_pos(&row)))
            return rc;
        printf("Введите номер столбца %d-ого ненулевого элемента: ", i + 1);
        if ((rc = read_pos(&col)))
            return rc;
        printf("Введите значение ненулевого элемента A[%d][%d]: ", row, col);
        if (scanf("%d", &item) != 1)
        {
            printf("\nОшибка ввода целого числа.\n\n");
            return ERR_READ;
        }
        *(matrix->a + i) = item;
        *(matrix->ja + i) = col;
        if (row > max_row)
        {
            matrix->ia = realloc(matrix->ia, (row + 1) * sizeof(int));
            *(matrix->ia + row - 1) = i + 1;
            max_row = row;
        }
    }
    matrix->rows = max_row;
    *(matrix->ia + max_row) = n + 1;
    int i = 0;
    while (i <= matrix->rows)
    {
        if (*(matrix->ia + i) != 0)
        {
            int j = i - 1;
            while (j >= 0 && *(matrix->ia + j) == 0)
                *(matrix->ia + j--) = *(matrix->ia + i);
        }
        i++;
    }
    printf("Введите количество ненулевых элементов вектора-столбца: ");
    if ((rc = read_pos(&n)))
        return rc;
    vector->a = calloc(n, sizeof(int));
    while (!vector->a)
        vector->a = calloc(n, sizeof(int));
    vector->n = n;
    vector->ia = calloc(1, sizeof(int));
    while (!vector->ia)
        vector->ia = calloc(1, sizeof(int));
    max_row = 0;
    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        printf("Введите номер строки %d-ого ненулевого элемента вектора-столбца: ", i + 1);
        if ((rc = read_pos(&row)))
            return rc;
        printf("Введите значение ненулевого элемента V[%d]: ", row);
        if (scanf("%d", &item) != 1)
        {
            printf("\nОшибка во время ввода целого числа.\n\n");
            return ERR_READ;
        }
        *(vector->a + i) = item;
        if (row > max_row)
        {
            vector->ia = realloc(vector->ia, row * sizeof(int));
            *(vector->ia + i) = row;
            max_row = row;
            flag++;
        }
    }
    return EXIT_SUCCESS;
}

int usual_input(matrix_t *matrix, vector_t *vector)
{
    printf("Введите количество строк и столбцов матрицы: ");
    int rows, cols;
    if (scanf("%d%d", &rows, &cols) != 2 || rows <= 0 || cols <= 0)
    {
        printf("Ошибка: количество выражается целым неотрицательным числом.");
        return ERR_POS;
    }
    int *buf = malloc(rows * cols * sizeof(int));
    while (!buf)
        buf = malloc(rows * cols * sizeof(int));
    for (int i = 0; i < rows; i++)
    {
        printf("Введите %d-ую строку матрицы: ", i + 1);
        for (int j = 0; j < cols; j++)
            if (scanf("%d", buf + i * rows + j) != 1)
            {
                printf("Ошибка записи целых чисел.");
                free(buf);
                return ERR_READ;
            }
    }
    printf("Матрица успешно введена.\n");
    int vect_k = cols;
    int *buf_vect = malloc(vect_k * sizeof(int));
    printf("Введите элементы вектора-столбца: ");
    for (int i = 0; i < vect_k; i++)
        if (scanf("%d", buf_vect + i) != 1)
        {
            printf("Ошибка записи целых чисел.");
            free(buf);
            free(buf_vect);
            return ERR_READ;
        }
    
    matrix->n = 0;
    matrix->rows = rows;
    matrix->a = malloc(rows * cols * sizeof(int));
    while (!matrix->a)
        matrix->a = malloc(rows * cols * sizeof(int));
    matrix->ja = malloc(rows * cols * sizeof(int));
    while (!matrix->ja)
        matrix->ja = malloc(rows * cols * sizeof(int));
    matrix->ia = calloc(rows + 1, sizeof(int));
    while (!matrix->ia)
        matrix->ia = calloc(rows  + 1, sizeof(int));
    for (int i = 0; i < rows; i++)
    {
        int flag = 0;
        for (int j = 0; j < cols; j++)
            if (*(buf + i * rows + j) != 0)
            {
                *(matrix->a + matrix->n) = *(buf + i * rows + j);
                *(matrix->ja + matrix->n) = j + 1;
                if (flag == 0)
                {
                    *(matrix->ia + i) = matrix->n + 1;
                    flag = 1;
                }
                matrix->n += 1;
            }
    }
    *(matrix->ia + rows) = matrix->n + 1;
    int i = 0;
    while (i <= rows)
    {
        if (*(matrix->ia + i) != 0)
        {
            int j = i - 1;
            while (j >= 0 && *(matrix->ia + j) == 0)
                *(matrix->ia + j--) = *(matrix->ia + i);
        }
        i++;
    }

    vector->n = 0;
    vector->a = malloc(vect_k * sizeof(int));
    while (!vector->a)
        vector->a = malloc(vect_k * sizeof(int));
    vector->ia = calloc(vect_k + 1, sizeof(int));
    while (!vector->ia)
        vector->ia = calloc(vect_k + 1, sizeof(int));
    for (int i = 0; i < vect_k; i++)
    {
        if (*(buf_vect + i) != 0)
        {
            *(vector->a + vector->n) = *(buf_vect + i);
            *(vector->ia + vector->n) = i + 1;
            vector->n += 1;
        }
    }
    return EXIT_SUCCESS;
}

int read_file(matrix_t *matrix, vector_t *vector, FILE **f)
{
    free(matrix->a);
    free(matrix->ja);
    free(matrix->ia);
    free(vector->a);
    free(vector->ia);
    if (!*f)
    {
        getchar();
        printf("\nВведите имя файла, содержащего информацию о матрице и векторе-столбце: ");
        char file[MAX_STR_LEN + 2];
        if (!fgets(file, sizeof(file), stdin))
        {
            printf("Ошибка: некорректная строка.\n");
            return ERR_FOPEN;
        }
        if (file[strlen(file) - 1] != '\n')
        {
            printf("Ошибка: превышена максимальная длина строки.");
            return ERR_TOO_MUCH_DATA;
        }
        else
            file[strlen(file) - 1] = '\0';
        if (!strlen(file))
        {
            printf("Ошибка: имя файла не введено.");
            return ERR_NO_DATA;
        }
        *f = fopen(file, "r");
        if (!*f)
        {
            printf("Ошибка во время открытия файла.");
            return ERR_FOPEN;
        }
    }
    int k_a = 0, k_j = 0, k_i = 0, v_a = 0, v_i = 0, item;
    while (fscanf(*f, "%d", &item) == 1)
    {
        k_a++;
        if (fgetc(*f) == '\n')
            break;
    }
    if (feof(*f))
    {
        printf("Ошибка во время чтения вектора А для матрицы.\n");
        fclose(*f);
        return ERR_NO_DATA;
    }
    while (fscanf(*f, "%d", &item) == 1)
    {
        k_j++;
        if (item <= 0)
        {
            printf("Ошибка: элементы вектора JA должны быть положительными.\n");
            fclose(*f);
            return ERR_COLS;
        }
        if (fgetc(*f) == '\n')
            break;
    }
    if (feof(*f))
    {
        printf("Ошибка во время чтения вектора JA для матрицы.\n");
        fclose(*f);
        return ERR_NO_DATA;
    }
    if (k_a != k_j)
    {
        printf("Ошибка: количество элементов в векторе А должно совпадать с количеством элементов в векторе JA.\n");
        fclose(*f);
        return ERR_COLS;
    }
    while (fscanf(*f, "%d", &item) == 1)
    {
        k_i++;
        if (item <= 0)
        {
            printf("Ошибка: элементы вектора IA должны быть положительными.\n");
            fclose(*f);
            return ERR_COLS;
        }
        if (fgetc(*f) == '\n')
            break;
    }
    if (feof(*f))
    {
        printf("Ошибка во время чтения вектора IA для матрицы.\n");
        fclose(*f);
        return ERR_NO_DATA;
    }

    while (fscanf(*f, "%d", &item) == 1)
    {
        v_a++;
        if (fgetc(*f) == '\n')
            break;
    }
    if (feof(*f))
    {
        printf("Ошибка во время чтения вектора A для вектора-столбца.\n");
        fclose(*f);
        return ERR_NO_DATA;
    }
    while (fscanf(*f, "%d", &item) == 1)
    {
        if (item <= 0)
        {
            printf("Ошибка: элементы вектора IA должны быть положительными.\n");
            fclose(*f);
            return ERR_COLS;
        }
        v_i++;
    }
    if (!feof(*f))
    {
        printf("Ошибка во время чтения вектора IA для вектора-столбца.\n");
        fclose(*f);
        return ERR_NO_DATA;
    }
    if (v_i != v_a)
    {
        printf("Ошибка: количество элементов в векторе А должно совпадать"
            " с количеством элементов в векторе IA для вектора-столбца.\n");
        fclose(*f);
        return ERR_COLS;
    }
    matrix->n = k_a;
    matrix->rows = k_i - 1;
    matrix->a = malloc(matrix->n * sizeof(int));
    while (!matrix->a)
        matrix->a = malloc(matrix->n * sizeof(int));
    matrix->ja = malloc(matrix->n * sizeof(int));
    while (!matrix->ja)
        matrix->ja = malloc(matrix->n * sizeof(int));
    matrix->ia = malloc(matrix->n* sizeof(int) + sizeof(int));
    while (!matrix->a)
        matrix->ia = malloc(matrix->n * sizeof(int) + sizeof(int));
    vector->n = v_a;
    vector->a = malloc(vector->n * sizeof(int));
    while (!vector->a)
        vector->a = malloc(vector->n * sizeof(int));
    vector->ia = malloc(vector->n * sizeof(int));
    while (!vector->ia)
        vector->ia = malloc(vector->n * sizeof(int));
    rewind(*f);
    int k = 0;
    while (k < matrix->n && fscanf(*f, "%d", matrix->a + k) == 1)
        k++;
    k = 0;
    while (k < matrix->n && fscanf(*f, "%d", matrix->ja + k) == 1)
        k++;    
    k = 0;
    while (k <= matrix->rows && fscanf(*f, "%d", matrix->ia + k) == 1)
        k++;
    k = 0;
    while (k < vector->n && fscanf(*f, "%d", vector->a + k) == 1)
        k++;
    k = 0;
    while (k < vector->n && fscanf(*f, "%d", vector->ia + k) == 1)
        k++;
    fclose(*f);
    return EXIT_SUCCESS;
}

int usual_read_file(int **matrix, int **vector, int *size, FILE **f)
{
    free(*matrix);
    free(*vector);
    if (!*f)
    {
        printf("Ошибка во время открытия файла.");
        return ERR_FOPEN;
    }
    int k = 0, item;
    while (fscanf(*f, "%d", &item) == 1)
    {
        k++;
        if (fgetc(*f) == '\n')
            break;
    }
    if (feof(*f))
    {
        printf("Ошибка во время чтения данных из файла.\n");
        fclose(*f);
        return ERR_NO_DATA;
    }
    rewind(*f);
    *size = k;
    *matrix = malloc(k * k * sizeof(int));
    while (!*matrix)
        *matrix = malloc(k * k * sizeof(int));
    *vector = malloc(k * sizeof(int));
    while (!*vector)
        *vector = malloc(k * sizeof(int));
    k = 0;
    while (k < *size * *size)
        if (fscanf(*f, "%d", *matrix + k++) != 1)
        {
            printf("Ошибка ввода целого числа.\n");
            fclose(*f);
            return ERR_READ;
        }
    k = 0;
    while (k < *size)
        if (fscanf(*f, "%d", *vector + k++) != 1)
            {
                printf("Ошибка ввода целого числа.\n");
                fclose(*f);
                return ERR_READ;
            }
    fclose(*f);
    return EXIT_SUCCESS;
}

void output_matrix(matrix_t matrix)
{
    printf("\nВектор А матрицы: ");
    for (int i = 0; i < matrix.n; i++)
        printf("%d ", *(matrix.a + i));
    printf("\nВектор JA матрицы: ");
    for (int i = 0; i < matrix.n; i++)
        printf("%d ", *(matrix.ja + i));
    printf("\nВектор IA матрицы: ");
    for (int i = 0; i <= matrix.rows; i++)
        printf("%d ", *(matrix.ia + i));
    printf("\n\n");
}

void output_vector(vector_t vector)
{
    printf("\n\nВектор А вектора-столбца: ");
    for (int i = 0; i < vector.n; i++)
        printf("%d ", *(vector.a + i));
    printf("\nВектор IA вектора-столбца: ");
    for (int i = 0; i < vector.n; i++)
        printf("%d ", *(vector.ia + i));
    printf("\n\n");
}

int read_pos(int *item)
{
    if (scanf("%d", item) != 1)
    {
        printf("\nОшибка во время чтения целого числа.\n\n");
        return ERR_READ;
    }
    if (*item < 1)
    {
        printf("\nОшибка: должно быть введено целое положительное число.\n\n");
        return ERR_READ;
    }
    return EXIT_SUCCESS;
}