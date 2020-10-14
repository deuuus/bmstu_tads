#ifndef READ_H
#define READ_H

#define MAX_STR_LEN   30+2
#define MAX_COUNT   1000
#define READ_ERR      -1
#define VALUE_ERR     -2

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

int read(car_t *cars, int *count);
int read_str(char str[]);
int read_uint(int *num);

#endif