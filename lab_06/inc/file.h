#ifndef FILE_H
#define FILE_H

#include "../inc/tree.h"
#include <unistd.h>

char **read_file(FILE *f);
int find_file(FILE *f, char *data);
void free_file(char **words, int len);
int file_len(FILE *f);
void insert_file(FILE *f, char *data);
void del_file(FILE *f, char *data);

#endif