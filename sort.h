#ifndef SORT_H
#define SORT_H

#include "read.h"
#include "readf.h"
#include <time.h>

int sort(car_t cars[], int count, FILE *f);
void slow_sort(car_t a[], int n);
void key_quick_sort(key_t a[], int b, int e);
void match(key_t key[], int key_n, car_t cars[], int cars_n);
void quick_sort(car_t a[], int b, int e);
void prt(car_t cars[], int count);
int show_h4(void);
void make_table(car_t cars[], key_t key[], int count, int *key_count, char brand[], int min_cost, int max_cost);
void swap(int *a, int *b);
int add(car_t cars[], int *count, FILE *f);
int del(car_t cars[], int *count, FILE *f);
void key_slow_sort(key_t a[], int n);
void print_request(key_t a[], int n, const char brand[], int min_cost, int max_cost);

int show_h1(car_t cars[], int *count, FILE *f);
int show_h2(car_t cars[], int *count, FILE *f);
int show_h3(car_t cars[], int *count, FILE *f);

void del_owners(car_t cars[], int *count, int owners);
void del_repairs(car_t cars[], int *count, int repairs);
void del_mileage(car_t cars[], int *count, int mileage);
void del_year(car_t cars[], int *count, int year);
void del_warranty(car_t cars[], int *count, int war);
void del_new(car_t cars[], int *count, int new);
void del_cost(car_t cars[], int *count, int cost);
void del_color(car_t cars[], int *count, char color[]);
void del_country(car_t cars[], int *count, char country[]);
void del_brand(car_t cars[], int *count, char brand[]);

#endif