#ifndef MENU_H
#define MENU_H

#include "codes.h"

#define INPUT  1
#define PRINT  2
#define PROD   3
#define INFO   4
#define ANALYS 5
#define EXIT   6

#define ERR_MENU -1

int choose_action(int *act);
void show_info(void);

#endif