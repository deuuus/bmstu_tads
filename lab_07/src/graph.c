#include "../inc/graph.h"

void search_min(char **cities, int n, int road[n][n], int rail[n][n], int begin_pos, int end_pos)
{
    int marks[n];
    for (int i = 0; i < n; i++)
        marks[i] = -1;
    marks[begin_pos] = 0;
    int visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    int cur = begin_pos, near, len;
    int used[n];
    for (int i = 0; i < n; i++)
        used[i] = 0;
    while (all_visited(n, visited) && !not_connected(n, visited, marks) && cur != -1)
    {
        //printf("\nТекущая вершина: %s\n", cities[cur]);
        while ((near = nearest_pos(n, visited, used, road, rail, cur)) != -1)
        {
            //printf("Ближайшая вершина: %s\n", cities[near]);
            len = road[cur][near];
            //printf("Длина до этой вершины от %s: %d\n", cities[cur], len);
            if (len && ((len + marks[cur]) < marks[near] || marks[near] == -1))
            {
                //printf("Смена: %d -> %d\n", marks[near], len + marks[cur]);
                marks[near] = len + marks[cur]; 
            }
            len = rail[cur][near];
           // printf("Длина до этой вершины от %s: %d\n", cities[cur], len);
            if (len && ((len + marks[cur]) < marks[near] || marks[near] == -1))
            {
                //printf("Смена: %d -> %d\n", marks[near], len + marks[cur]);
                marks[near] = len + marks[cur]; 
            }
            used[near] = 1;
        }
        visited[cur] = 1;
        for (int i = 0; i < n; i++)
            used[i] = 0;
        cur = nearest_pos(n, visited, used, road, rail, cur);
    }
    if (marks[end_pos] == -1)
    {
        printf("\nПути между этими городами не существует.");
        return;
    }
    printf("\nМинимальная длина пути из города %s в город %s: %d\n", cities[begin_pos], cities[end_pos], marks[end_pos]);
    printf("\nОптимальный путь:\n");
    cur = end_pos;
    int path[n];
    int type[n], k = 0;
    while (cur != begin_pos)
    {
        for (int i = 0; i < n; i++)
            if (marks[cur] - road[cur][i] == marks[i])
            {
                path[k] = i;
                type[path[k++]] = 0;
                cur = i;
                continue;
            }
            else if (marks[cur] - rail[cur][i] == marks[i])
            {
                path[k] = i;
                type[path[k++]] = 1;
                cur = i;
                continue;
            }
    }
    for (int i = k - 1; i >= 0; i--)
        printf("%s -> ", cities[path[i]]);
    printf(cities[end_pos]);
    int count = 0;
    printf("\nПересадки с одного типа транспорта на другой в пунктах:\n");
    for (int i = k - 1; i > 0; i--)
        if (type[path[i]] != type[path[i - 1]])
        {
            count++;
            printf("%s", cities[path[i - 1]]);
            if (type[path[i - 1]] == 0)
                printf("(Ж/Д->Шоссе)\n");
            else
                printf("(Шоссе->Ж/Д)\n");
        }
    if (!count)
        printf("\nОтсутствуют.\n");
    FILE *f = fopen("data.gv", "w");
    fprintf(f, "digraph G{\n");
    for (int i = k - 1; i >= 0; i--)
    {
        fprintf(f, "%s [color=red]\n", cities[path[i]]);
    }
    fprintf(f, "%s [color=red]\n", cities[end_pos]);
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
        {
            if (road[i][j] != 0)
                fprintf(f, "%s->%s[label=%d, color=blue];\n", cities[i], cities[j], road[i][j]);
            if (rail[i][j] != 0)
                fprintf(f, "%s->%s[label=%d, color=green];\n", cities[i], cities[j], rail[i][j]);
        }
    fprintf(f, "}");
    fclose(f);
}

int all_visited(int n, int visited[])
{
    for (int i = 0; i < n; i++)
        if (!visited[i])
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int nearest_pos(int n, int visited[], int used[], int road[n][n], int rail[n][n], int ind)
{
    int min_pos = LONG_MAX - 10, pos = -1;
    for (int i = 0; i < n; i++)
    {
        if (road[ind][i] != 0 && visited[i] == 0 && used[i] == 0 && road[ind][i] < min_pos)
        {
            min_pos = road[ind][i];
            pos = i;
        }
        if (rail[ind][i] != 0 && visited[i] == 0 && used[i] == 0 && rail[ind][i] < min_pos)
        {
            min_pos = rail[ind][i];
            pos = i;
        }
    }  
    return pos;
}

int first_not_visited(int n, int visited[])
{
    for (int i = 0; i < n; i++)
        if (!visited[i])
            return i;
    return -1;
}

int not_connected(int n, int visited[], int marks[])
{
    int k = 0, all = 0;
    for (int i = 0; i < n; i++)
        if (visited[i] == 0)
        {
            if (marks[i] == -1)
                k++;
            all++;
        }
    return all == k;
}