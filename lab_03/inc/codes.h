#ifndef CODES_H
#define CODES_H

#define ERR_POS -2
#define ERR_LINE -3
#define ERR_FOPEN -4
#define ERR_FGETS -5
#define ERR_TOO_MUCH_DATA -6
#define ERR_NO_DATA -7
#define ERR_FILE_DATA -8 
#define ERR_READ -9
#define ERR_VECT -10
#define ERR_COLS -11
#define ERR_PROD -12

#define MAX_STR_LEN 15

#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int n;
    int *a;
    int *ia;
} vector_t;


typedef struct {
    int n;
    int rows;
    int *a;
    int *ja;
    int *ia;
} matrix_t;

#endif