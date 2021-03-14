#ifndef IO_H
#define IO_H

#include "../inc/menu.h"
#include <string.h>

#define MAX_WORD_LEN 100

int read_name(FILE **f);
int read_city(char *name);
char **read_cities(FILE *f, int *n);
//int read_type(FILE *f, int n, int type[n]);
void free_cities(char **cities, int len);
int get_pos(char **data, int n, char *item);
int read_lens(FILE *f, char **cities, int n, int road[n][n], int rail[n][n]);

#endif