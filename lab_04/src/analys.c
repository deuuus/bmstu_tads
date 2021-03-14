#include "analys.h"

void print_cycle(int n, char *b, char mood);

void analys(void)
{
    printf("\nСравнительный анализ в количественном соотношении:\n\n");
    printf("┏━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃               ┃         Исключение        ┃         Добавление        ┃    Сортировка всех данных     ┃\n");
    printf("┃    Кол-во     ┣━━━━━━━━━━━━━┳━━━━━━━━━━━━━╋━━━━━━━━━━━━━┳━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━┫\n");
    printf("┃   элементов   ┃ Стек-массив ┃ Стек-список ┃ Стек-массив ┃ Стек-список ┃  Стек-массив  ┃  Стек-список  ┃\n");
    print_cycle(10, "10.txt", 'u');
    print_cycle(100, "100.txt", 'u');
    print_cycle(250, "250.txt", 'u');
    print_cycle(500, "500.txt", 'u');
    print_cycle(750, "750.txt", 'u');
    print_cycle(1000, "1000.txt", 'u');
    printf("┗━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┛\n");

    printf("\n\nСравнительный анализ в процентном соотношении:\n\n");
    printf("┏━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━┓\n");
    printf("┃               ┃   Исключение  ┃  Добавление   ┃  Сортировка   ┃\n");
    printf("┃    Кол-во     ┣━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┫\n");
    printf("┃   элементов   ┃ Стек-массив / ┃ Стек-массив / ┃ Стек-массив / ┃\n");
    printf("┃               ┃ Стек-список   ┃ Стек-список   ┃ Стек-список   ┃\n");
    print_cycle(10, "10.txt", 'p');
    print_cycle(100, "100.txt", 'p');
    print_cycle(250, "250.txt", 'p');
    print_cycle(500, "500.txt", 'p');
    print_cycle(750, "750.txt", 'p');
    print_cycle(1000, "1000.txt", 'p');
    printf("┗━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┛\n");
}

void print_cycle(int n, char *b, char mood)
{
    struct timeval t_start, t_end;
    size_t time_arr[3] = { 0 }, time_list[3] = { 0 };
    size_t mem_arr[3] = { 0 }, mem_list[3] = { 0 };
    int item;
    arr_stack_t st_1;
    arr_stack_t st_2;
    arr_stack_t temp_st_1;
    arr_stack_t temp_st_2;
    arr_stack_t res;
    init_arr(&st_1);
    init_arr(&st_2);
    init_arr(&temp_st_1);
    init_arr(&temp_st_2);
    init_arr(&res);
    list_stack_t *ptr_1 = NULL;
    list_stack_t *ptr_2 = NULL;
    list_stack_t *temp_ptr_1 = NULL;
    list_stack_t *temp_ptr_2 = NULL;
    list_stack_t *ptr_res = NULL;
    FILE *f;
    int reps = 10000;
    char name[30] = "shared/test_";
    strcat(name, b);
    f = fopen(name, "r");
    int a[MAX_SIZE];
    int k = 0;
    while (fscanf(f, "%d", &item) == 1)
    {
        push_arr(&st_1, item);
        push_list(&ptr_1, item);
        a[k++] = item;
        if (fgetc(f) == '\n')
            break;
    }
    while (fscanf(f, "%d", &item) == 1)
    {
        push_arr(&st_2, item);
        push_list(&ptr_2, item);
    }

    for (int i = 0; i < reps; i++)
    {
        copy_arr(&st_1, &temp_st_1);
        gettimeofday(&t_start, NULL);
        while (temp_st_1.ptr >= temp_st_1.a)
            pop_arr(&temp_st_1, &item);
        gettimeofday(&t_end, NULL);
        time_arr[0] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    mem_arr[0] = sizeof(int) * n + sizeof(int*);
    time_arr[0] /= reps;

    for (int i = 0; i < reps; i++)
    {
        temp_ptr_1 = copy_list(&ptr_1);
        gettimeofday(&t_start, NULL);
        while (temp_ptr_1)
            pop_list(&temp_ptr_1, &item);
        gettimeofday(&t_end, NULL);
        time_list[0] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    time_list[0] /= reps;
    mem_list[0] = sizeof(list_stack_t) * n;

    for (int i = 0; i < reps; i++)
    {
        init_arr(&temp_st_1);
        gettimeofday(&t_start, NULL);
        k = 0;
        while (k < n)
            push_arr(&temp_st_1, a[k++]);
        gettimeofday(&t_end, NULL);
        time_arr[1] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    time_arr[1] /= reps;
    mem_arr[1] = sizeof(int) * n + sizeof(int*);

    for (int i = 0; i < reps; i++)
    {
        temp_ptr_1 = NULL;
        gettimeofday(&t_start, NULL);
        k = 0;
        while (k < n)
            push_list(&temp_ptr_1, a[k++]);
        gettimeofday(&t_end, NULL);
        time_list[1] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    time_list[1] /= reps;
    mem_list[1] = sizeof(list_stack_t) * n;


    reps = 300;
    for (int i = 0; i < reps; i++)
    {
        copy_arr(&st_1, &temp_st_1);
        copy_arr(&st_2, &temp_st_2);
        gettimeofday(&t_start, NULL);
        init_arr(&res);
        sort_arr(&temp_st_1, &temp_st_2, &res);
        gettimeofday(&t_end, NULL);
        time_arr[2] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    time_arr[2] /= reps;
    mem_arr[2] = 4 * (sizeof(int) * n + sizeof(int*)) + sizeof(int) * 2;

    for (int i = 0; i < reps; i++)
    {
        temp_ptr_1 = copy_list(&ptr_1);
        temp_ptr_2 = copy_list(&ptr_2);
        gettimeofday(&t_start, NULL);
        sort_list(&temp_ptr_1, &temp_ptr_2, &ptr_res);
        gettimeofday(&t_end, NULL);
        time_list[2] += (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    }
    time_list[2] /= reps;
    mem_list[2] = 4 * sizeof(list_stack_t) * n;

    if (mood == 'u')
    {
        printf("┣━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┫\n");
        printf("┃               ┃%10lld ms┃%10lld ms┃%10lld ms┃%10lld ms┃%12lld ms┃%12lld ms┃\n",
            time_arr[0], time_list[0], time_arr[1], time_list[1], time_arr[2], time_list[2]);
        printf("┃%9d      ┃ ----------- ┃ ----------- ┃ ----------- ┃ ----------- ┃"
            " ------------- ┃ ------------- ┃\n", n);
        printf("┃               ┃%11lld b┃%11lld b┃%11lld b┃%11lld b┃%13lld b┃%13lld b┃\n",
            mem_arr[0], mem_list[0], mem_arr[1], mem_list[1], mem_arr[2], mem_list[2]);
    }
    else if (mood == 'p')
    {
        int res[6] = { 0 };
        for (int i = 0; i < 3; i++)
        {
            if (time_list[i] != 0)
                res[i] = (int)((double)time_arr[i] / (double)time_list[i] * 100);
            if (mem_list[i] != 0)
                res[i + 3] = (int)((double)mem_arr[i] / (double)mem_list[i] * 100);
        }
        printf("┣━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┫\n");
        printf("┃               ┃Время: %6d %%┃Время: %6d %%┃Время: %6d %%┃\n", res[0], res[1], res[2]);
        printf("┃%9d      ┃ ------------- ┃ ------------- ┃ ------------- ┃\n", n);
        printf("┃               ┃Память: %5d %%┃Память: %5d %%┃Память: %5d %%┃\n", res[3], res[4], res[5]);
    }
}

list_stack_t* copy_list(list_stack_t **src)
{
    list_stack_t *buf = NULL;
    list_stack_t *cp = NULL;
    int item;
    while (*src)
    {
        pop_list(src, &item);
        push_list(&buf, item);
    }
    while (buf)
    {
        pop_list(&buf, &item);
        push_list(src, item);
        push_list(&cp, item);
    }
    return cp;
}

void copy_arr(arr_stack_t *src, arr_stack_t *dst)
{
    arr_stack_t buf;
    init_arr(&buf);
    init_arr(dst);
    int item;
    while (src->ptr >= src->a)
    {
        pop_arr(src, &item);
        push_arr(&buf, item);
    }
    while (buf.ptr >= buf.a)
    {
        pop_arr(&buf, &item);
        push_arr(src, item);
        push_arr(dst, item);
    }
}