#ifndef MENU_H
#define MENU_H

#define INFO             1
#define PRINT            2
#define SORT             3
#define ADD              4
#define DEL              5
#define ANALYS            6
#define EXIT             7
#define S_KEY_US_TABLE   8
#define S_TABLE          9
#define S_KEY_S_TABLE   10
#define MEASURES        11

#include <stdlib.h>
#include "io.h"

void show_info(void);
int choose_action(int *ans);
int choose_analys(int *ans);

#endif