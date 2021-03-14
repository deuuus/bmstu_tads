#ifndef MENU_H
#define MENU_H

#define INPUT    1
#define BINARY   2
#define BALANCE  3 
#define DEL      4
#define HASH     5
#define DEL_HASH 6
#define ANALYS   7
#define INFO     8
#define EXIT     9

#define ERR_ACT 1

#include <stdio.h>
#include <stdlib.h>

int choose_action(int *act);
void show_info(void);
void show_image_info(void);
void show_bal_image_info(void);
void show_del_info(void);

#endif