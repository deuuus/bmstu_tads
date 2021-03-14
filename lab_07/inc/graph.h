#ifndef GRAPH_H
#define GRAPH_H

#include <limits.h>
#include "../inc/io.h"

void search_min(char **cities, int n, int road[n][n], int rail[n][n], int begin_pos, int end_pos);
int all_visited(int n, int visited[]);
int nearest_pos(int n, int visited[], int used[], int road[n][n], int rail[n][n], int ind);
int first_not_visited(int n, int visited[]);
int not_connected(int n, int visited[], int marks[]);

#endif