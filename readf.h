#ifndef READF_H
#define READF_H

#include "read.h"

int read_file(car_t *cars, int *count, FILE *f);
int readf_str(char str[], FILE *f);
int readf_uint(int *num, FILE *f);
void print(car_t cars[], int count, FILE *f);

#endif