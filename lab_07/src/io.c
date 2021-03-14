#include "../inc/io.h"

int read_city(char *name)
{
    if (!fgets(name, sizeof(name), stdin))
    {
        printf("\nОшибка во время считывания названия города.\n");
        return EXIT_FAILURE;
    }
    if (name[strlen(name) - 1] == '\n')
        name[strlen(name) - 1] = '\0';
    if (!strlen(name))
    {
        printf("\nОшибка во время считывания названия города.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int read_name(FILE **f)
{
    char name[MAX_WORD_LEN + 1];
    printf("\nВведите название файла, в котором содержится информация: ");
    if (!fgets(name, sizeof(name), stdin))
    {
        printf("\nОшибка: имя файла записано некорректно. Возможно, вы ввели пустую строку или\n"
        "превысили максимально допустимую длину названия файла(50 символов). Попробуйте еще раз.\n");
        return EXIT_FAILURE;
    }
    if (name[strlen(name) - 1] == '\n')
        name[strlen(name) - 1] = '\0';
    *f = fopen(name, "r");
    if (!(*f))
    {
        printf("\nОшибка: невозможно открыть файл с таким названием.\n"
        "Внимательно проверьте название и/или содержимое файла и попробуйте еще раз.\n");
        return EXIT_FAILURE;
    }
    printf("\nДанные успешно введены в систему.\n");
    return EXIT_SUCCESS;
}

int read_lens(FILE *f, char **cities, int n, int road[n][n], int rail[n][n])
{
    int rc = EXIT_SUCCESS;
    char dst[MAX_WORD_LEN], src[MAX_WORD_LEN];
    int len, type;
    while (!rc)
    {
        if (!fgets(src, sizeof(src), f))
        {
            rc = EXIT_FAILURE;
            continue;
        }
        if (!fgets(dst, sizeof(dst), f))
        {
            rc = EXIT_FAILURE;
            continue;
        }
        if (src[strlen(src) - 1] == '\n')
            src[strlen(src) - 1] = '\0';
        if (dst[strlen(dst) - 1] == '\n')
            dst[strlen(dst) - 1] = '\0';
        if (fscanf(f, "%d", &len) != 1 || len < 0)
        {
            rc = EXIT_FAILURE;
            continue;
        }
        int pos_dst = get_pos(cities, n, dst);
        int pos_src = get_pos(cities, n, src);
        if (pos_dst < 0 || pos_src < 0)
        {
            rc = EXIT_FAILURE;
            continue;
        }
        if (fscanf(f, "%d", &type) != 1 || (type != 0 && type != 1) || fgetc(f) != '\n')
        {
            rc = EXIT_FAILURE;
            continue;
        }
        if (type == 0)
        {
            road[pos_dst][pos_src] = len;
            road[pos_src][pos_dst] = len;
        }
        else
        {
            rail[pos_dst][pos_src] = len;
            rail[pos_src][pos_dst] = len;
        }
    }
    if (!feof(f))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int get_pos(char **data, int n, char *item)
{
    for (int i = 0; i < n; i++)
        if (!strcmp(data[i], item))
            return i;
    return -1;
}

char **read_cities(FILE *f, int *n)
{
    rewind(f);
    if (fscanf(f, "%d", n) != 1 || *n < 0 || fgetc(f) != '\n')
        return NULL;
    char **cities = malloc(sizeof(char*) * *n);
    if (!cities)
        return NULL;
    for (int i = 0; i < *n; i++)
    {
        cities[i] = malloc(MAX_WORD_LEN * sizeof(char));
        if (!cities[i])
        {
            free_cities(cities, *n);
            return NULL;
        }
    }
    int i = 0;
    char buf[MAX_WORD_LEN];
    while (i < *n && fgets(buf, sizeof(buf), f))
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1 ] = '\0';
        if (!strlen(buf))
        {
            free_cities(cities, i);
            return NULL;
        }
        strcpy(cities[i], buf);
        i++;
    }
    if (i != *n)
    {
        free_cities(cities, i);
        return NULL;
    }
    return cities;
}

// int read_type(FILE *f, int n, int type[n])
// {
//     int i = 0;
//     while (i < n && fscanf(f, "%d", &type[i]) == 1)
//     {
//         if (type[i] != 0 && type[i] != 1)
//             return EXIT_FAILURE;
//         i++;
//     }
//     if (fgetc(f) != '\n')
//         return EXIT_FAILURE;
//     return EXIT_SUCCESS;
// }

void free_cities(char **cities, int len)
{
    for (int i = 0; i < len; ++i)
        free(cities[i]);
    free(cities);
}