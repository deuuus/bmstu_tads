#ifndef CARS_H
#define CARS_H

#include "io.h"
#include <time.h>

int sort(car_t cars[], int count, FILE *f);
void slow_sort(car_t a[], int n);
void key_quick_sort(key_t a[], int b, int e);
void match_key(key_t keys[], int key_n, car_t cars[], int cars_n);
void quick_sort(car_t a[], int b, int e);
void make_key_table(car_t cars[], key_t key[], int count, int *key_count, const char brand[], int min_cost, int max_cost);
void make_table(car_t cars[], car_t sorted[], int count, int *s_count, char brand[], int min_cost, int max_cost);
void match(car_t cars[], car_t sorted[], int count, int s_count, char brand[], int min_cost, int max_cost);
void swap(int *a, int *b);
int suit(car_t car, char brand[], int min_cost, int max_cost);
int add(car_t cars[], int *count, FILE *f);
int del(car_t cars[], int *count, FILE *f);
void key_slow_sort(key_t a[], int n);
void print_request(key_t a[], int n, const char brand[], int min_cost, int max_cost);

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