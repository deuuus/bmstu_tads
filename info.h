#ifndef INFO_H
#define INFO_H

#define PRINT  1
#define SORT   2
#define ADD    3
#define DEL    4
#define EXIT   5
#define HELP 6
#define H1   7
#define H2   8
#define H3   9
#define H4   10

#include <stdlib.h>
#include "read.h"

void show_info(void);
int choose_action(int *ans);
int choose_help(int *ans);

#endif