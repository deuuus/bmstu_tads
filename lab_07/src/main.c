#include "../inc/menu.h"
#include "../inc/io.h"
#include "../inc/graph.h"

int main(void)
{
    int rc = EXIT_SUCCESS;
    int act = EXIT_SUCCESS;
    FILE *f = NULL;
    char **cities = NULL;
    int n;
    char src[MAX_WORD_LEN], dst[MAX_WORD_LEN];
    int begin_pos, end_pos;
    while (act != EXIT && !rc)
    {
        if ((rc = choose_act(&act)))
            continue;
        if (act == INPUT)
        {
            if ((rc = read_name(&f)))
            {
                f = NULL;
                continue;
            }
        }
        if (act == SEARCH)
        {
            if (!f)
            {
                printf("\nДанные еще не введены в систему. Воспользуйтесь пунктом 1 из меню.\n");
                continue;
            }
            cities = read_cities(f, &n);
            if (!cities)
            {
                printf("\nПроизошла ошибка во время считывания информации о городах.\n");
                continue;
            }
            // int type[n];
            // if ((rc = read_type(f, n, type)))
            // {
            //     printf("\nПроизошла ошибка во время считывания информации о типах путей.\n");
            //     continue;
            // }
            int road[n][n], rail[n][n];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                {
                    road[i][j] = 0;
                    rail[i][j] = 0;
                }

            if ((rc = read_lens(f, cities, n, road, rail)))
            {
                printf("\nПроизошла ошибка во время считывания информации о путях.\n");
                continue;
            }
            printf("\nВведите город отправки: ");
            if ((rc = read_city(src)))
                continue;
            if ((begin_pos = get_pos(cities, n, src)) == -1)
            {
                printf("\nГород с таким названием не найден в системе.\n");
                continue;
            }
            printf("\nВведите город назначения: ");
            if ((rc = read_city(dst)))
                continue;
            if ((end_pos = get_pos(cities, n, dst)) == -1)
            {
                printf("\nГород с таким названием не найден в системе.\n");
                continue;
            }
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                    printf("%d ", road[i][j]);
                printf("\n");
            }
            printf("\n");
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                    printf("%d ", rail[i][j]);
                printf("\n");
            }
            search_min(cities, n, road, rail, begin_pos, end_pos);
            show_image_info();
        }
        if (act == INFO)
            show_info();
    }
    free_cities(cities, n);
    return EXIT_SUCCESS;
}