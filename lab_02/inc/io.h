#ifndef READ_H
#define READ_H

#define MAX_STR_LEN   15+2
#define MAX_COUNT   12000
#define READ_ERR      -1
#define VALUE_ERR     -2
#define DEL_ERR       -3
#define EMPTY_FILE_ERR -4

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int field;
    int index;
} key_t;

typedef struct {
	int year;
	int mileage;
	int repairs;
	int owners;
} used_car_t;

typedef struct {
	char brand[MAX_STR_LEN];
	char country[MAX_STR_LEN];
	int cost;
	char color[MAX_STR_LEN];
    int new;
	union {
		int warranty;
		used_car_t used;
	} condition;
} car_t;

int read_str(char str[]);
int read_uint(int *num);
int readf_str(char str[], FILE *f);
int readf_uint(int *num, FILE *f);
int read_file(car_t *cars, int *count, FILE *f);
int print();

#endif