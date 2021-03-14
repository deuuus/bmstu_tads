#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>

#define ERR_ACT        1

#define PROCESS_LIST   1
#define PROCESS_ARR    2
#define ANALYS         3
#define EXIT           4

int choose_action(int *act);
void show_info();

#endif