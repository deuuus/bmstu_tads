#ifndef HASH_H
#define HASH_H

#include "../inc/tree.h"
#include <time.h>

#define N 10000

typedef struct list
{
    char data[MAX_WORD_LEN];
    struct list *next;
} list_t;

void read_table(FILE *f, list_t *words[], int hash_ind[], int n, int *col, int (*func)(char *, int));
void insert_table(list_t *words[], int hash_ind[], int n, char *data, int *col, int (*func)(char *, int));
void print_table(list_t *words[], int hash_ind[], int n);
int find_table(list_t *words[], int hash_ind[], int n, char *data, int (*func)(char *, int));
void del_table(list_t *words[], int hash_ind[], int n, char *data, int (*func)(char *, int));
void free_words(list_t *words[], int n);

int hash_func_mod_salt(char *str, int n);
int hash_func_prod_salt(char *str, int n);
list_t *create_list(char *data);
list_t *push_back(list_t *head, list_t *to_push);

#endif