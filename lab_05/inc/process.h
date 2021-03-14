#ifndef PROCESS_H
#define PROCESS_H

#define ERR_FULL_ARR    1
#define ERR_EMPTY_ARR   2
#define ERR_EMPTY_LIST  3
#define ERR_MEM         4

#define MAX_ARR_SIZE  10000
#define EPS          1e-5

#define LEFT_LIM_PUSH   0
#define RIGHT_LIM_PUSH  6

#define LEFT_LIM_WORK   0
#define RIGHT_LIM_WORK  1

#include "../inc/menu.h"
#include <time.h>
#include <math.h>

typedef struct 
{
    int num_of_passes;
} task_t;

typedef struct
{
    task_t tasks[MAX_ARR_SIZE];
    task_t *head;
    task_t *tail;
    int count;
} arr_queue_t;


typedef struct list_node
{
    task_t task;
    struct list_node *next;
} list_node_t;


typedef struct
{
    int count;
    list_node_t *head;
} list_queue_t;


void modeling_queue_with_arr(void);
void modeling_queue_with_list(void);

double rand_time(const int left_lim, const int right_lim);

int cmp_double(double a, double b);

list_node_t *get_tail(list_queue_t list);
void print_mem(list_queue_t list, int mode);

int push_arr(arr_queue_t *arr, task_t task);
int push_list(list_queue_t *list, task_t task);
int pop_arr(arr_queue_t *arr, task_t *task);
int pop_list(list_queue_t *list, task_t *task);

void init_arr_queue(arr_queue_t *arr);
void init_list_queue(list_queue_t *list);
void init_task(task_t *task);

void free_all(list_node_t *head);
list_node_t *create(task_t task);

#endif