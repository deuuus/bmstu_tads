#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <stdio.h>

#define INPUT  1
#define SEARCH 2
#define INFO   3
#define EXIT   4

int choose_act(int *act);
void show_info(void);
void show_image_info(void);

#endif