#include "../inc/analys.h"

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

void analys(void)
{
    arr_queue_t arr;
    init_arr_queue(&arr);
    list_queue_t list;
    init_list_queue(&list);
    task_t task_todo;
    uint64_t time[4] = {0}, start, end;
    uint64_t mem[6];
    for (int i = 0; i < 1000; i++)
    {
        start = tick();
        push_arr(&arr, task_todo);
        end = tick();
        time[0] += end - start;
        start = tick();
        pop_arr(&arr, &task_todo);
        end = tick();
        time[1] += end - start;

        start = tick();
        push_list(&list, task_todo);
        end = tick();
        time[2] += end - start;
        start = tick();
        pop_list(&list, &task_todo);
        end = tick();
        time[3] += end - start;
    }
    for (int i = 0; i < 4; i++)
        time[i] /= 1000;
    printf("\n┏━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃     Операция     ┃ Статический массив ┃ Динамический список ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃    Добавление    ┃%9lld тиков     ┃%9lld тиков      ┃\n", time[0], time[2]);
    printf("┣━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃     Удаление     ┃%9lld тиков     ┃%9lld тиков      ┃\n", time[1], time[3]);
    printf("┗━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\n");
    mem[0] = sizeof(int) * 10 + 2 * sizeof(int*) + sizeof(int);
    mem[1] = sizeof(int) * 100 + 2 * sizeof(int*) + sizeof(int);
    mem[2] = sizeof(int) * 1000 + 2 * sizeof(int*) + sizeof(int);
    mem[3] = sizeof(int) + 10 * (sizeof(int) + sizeof(list_node_t*));
    mem[4] = sizeof(int) + 100 * (sizeof(int) + sizeof(list_node_t*));
    mem[5] = sizeof(int) + 1000 * (sizeof(int) + sizeof(list_node_t*));
    printf("┏━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃   Объем памяти   ┃ Статический массив ┃ Динамический список ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃    10 элементов  ┃%10lld байт     ┃%10lld байт      ┃\n", mem[0], mem[3]);
    printf("┣━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃   100 элементов  ┃%10lld байт     ┃%10lld байт      ┃\n", mem[1], mem[4]);
    printf("┣━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃  1000 элементов  ┃%10lld байт     ┃%10lld байт      ┃\n", mem[2], mem[5]);
    printf("┗━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━┛\n");
}