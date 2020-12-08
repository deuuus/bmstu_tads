#ifndef MENU_H
#define MENU_H

#define INPUT 1
#define INFO  2
#define EXIT  3

#define ERR_ACT 1

#include <stdio.h>
#include <stdlib.h>

int choose_action(int *act);
void show_info(void);

#endif