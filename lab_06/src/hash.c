#include "../inc/hash.h"

void read_table(FILE *f, list_t *words[], int hash_ind[], int n, int *col, int (*func)(char *, int))
{
    rewind(f);
    *col = 0;
    char buf[MAX_WORD_LEN];
    for (int i = 0; i < n; i++)
        hash_ind[i] = 0;
    while (fgets(buf, sizeof(buf), f))
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = '\0';
        insert_table(words, hash_ind, n, buf, col, func);
    }
}

void insert_table(list_t *words[], int hash_ind[], int n, char *data, int *col, int (*func)(char *, int))
{
    int x = func(data, n);
    if (hash_ind[x] != 0)
    {
        *col += 1;
        words[x] = push_back(words[x], create_list(data));
    }
    else
    {
        words[x] = create_list(data);
        hash_ind[x]++;
    }
}

void free_words(list_t *words[], int n)
{
    for (int i = 0; i < n; i++)
    {
        list_t *next;
        for (; words[i]; words[i] = next)
        {
            next = words[i]->next;
            free(words[i]);
        }
    }
}

int find_table(list_t *words[], int hash_ind[], int n, char *data, int (*func)(char *, int))
{
    int x = func(data, n);
    if (hash_ind[x] == 0)
        return -1;
    list_t *cur = words[x];
    while (strcmp(cur->data, data))
        cur = cur->next;
    return func(cur->data, n);
}

void del_table(list_t *words[], int hash_ind[], int n, char *data, int (*func)(char *, int))
{
    int pos = find_table(words, hash_ind, n, data, func);
    list_t *cur = words[pos], *prev = NULL;
    while (strcmp(cur->data, data))
    {
        prev = cur;
        cur = cur->next;
    }
    if (!prev)
    {
        words[pos] = words[pos]->next;
        if (!words[pos])
            hash_ind[pos] = 0;
    }   
    else
        prev->next = cur->next;
}

void print_table(list_t *words[], int hash_ind[], int n)
{
    printf("\n┏━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃  Значение хэш-функции  ┃              Данные              ┃\n");
    for (int i = 0; i < n; i++)
        if (hash_ind[i] != 0)
        {
            int k = 10;
            printf("┣━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n"
            "┃%12d            ┃%10s", i, words[i]->data);
            list_t *cur = words[i];
            while(cur->next)
            {
                cur = cur->next;
                printf("->%s", cur->data);
                k += strlen(cur->data) + 2;
            }
            while (k < 34)
            {
                k++;
                printf(" ");
            }
            printf("┃\n");
        }
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

list_t *create_list(char *data)
{
    list_t *new = malloc(sizeof(list_t));
    if (new)
    {
        strcpy(new->data, data);
        new->next = NULL;
    }
    return new;
}

list_t *push_back(list_t *head, list_t *to_push)
{
    if (!head)
        return to_push;
    list_t *cur = head;
    while (cur->next)
        cur = cur->next;
    cur->next = to_push;
    return head;
}

int hash_func_mod_salt(char *str, int n)
{
    int sum = strlen(str);
    while (*str)
    {
        sum += (int)(*str);
        str++;
    }
    return sum % n;
}

int hash_func_prod_salt(char *str, int n)
{
    double a = 0.656565;
    int sum = strlen(str);
    while (*str)
    {
        sum += (int)(*str);
        str++;
    }
    a *= sum;
    a -= (int)a;
    return a * n;
}