#include "../inc/file.h"

char **read_file(FILE *f)
{
    int n = file_len(f), i = 0;
    char buf[MAX_WORD_LEN];
    char **words = malloc(sizeof(char*) * n);
    for (int i = 0; i < n; i++)
        words[i] = malloc(sizeof(char*) * MAX_WORD_LEN);
    while (fgets(buf, sizeof(buf), f))
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = '\0';
        strcpy(words[i], buf);
        i++;
    }
    rewind(f);
    return words;
}

int find_file(FILE *f, char *data)
{
    rewind(f);
    int i = 0;
    char buf[MAX_WORD_LEN];
    while (fgets(buf, sizeof(buf), f))
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = '\0';
        if (!strcmp(buf, data))
        {
            rewind(f);
            return i;
        }
        i++;
    }
    rewind(f);
    return -1;
}

void insert_file(FILE *f, char *data)
{
    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", data);
    rewind(f);
}

void del_file(FILE *f, char *data)
{
    rewind(f);
    char **words = read_file(f);
    int i, n = file_len(f), len = 0;
    for (i = 0; i < n; i++)
        if (!strcmp(words[i], data))
            break;
    if (i < n)
    {
        for (int j = i; j < n - 1; j++)
            strcpy(words[j], words[j + 1]);
        rewind(f);
        for (int j = 0; j < n - 1; j++)
        {
            len += strlen(words[j]) + 1;
            fprintf(f, "%s", words[j]);
            if (j < n - 2)
                fprintf(f, "\n");
        }
        ftruncate(fileno(f), len);
        rewind(f);
    }
}

void free_file(char **words, int len)
{
    for (int i = 0; i < len; ++i)
        free(words[i]);
    free(words);
}

int file_len(FILE *f)
{
    rewind(f);
    char buf[MAX_WORD_LEN];
    int k = 0;
    while (fgets(buf, sizeof(buf), f))
        k++;
    rewind(f);
    return k;
}