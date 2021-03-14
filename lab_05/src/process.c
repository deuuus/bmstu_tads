#include "../inc/process.h"

void modeling_queue_with_list(void)
{
    list_queue_t list;
    init_list_queue(&list);

    double elapsed_time = 0.0;
    double waiting_time = 0.0;

    //время, оставшееся до выхода элемента очереди из ОА
    double time_to_out = 0.0; 
    //время, оставшееся до входа следующего элемента в очередь
    double time_to_in = rand_time(LEFT_LIM_PUSH, RIGHT_LIM_PUSH); 

    int passed_tasks = 0;

    int avg_len = 0;
    int avg[10] = {0}, temp[10] = {0};

    task_t temp_task;

    task_t task_in_work;
    task_in_work.num_of_passes = 0;

    //количество срабатываний аппарата
    int calls = 0;
    int tasks_in = 0;

    int work_mode = 0;
    int print_mode = 0;

    printf("\nВывести при этом на экран адреса элементов очереди при добавлении и удалении элементов?\n\n"
    "1) Да\n2) Нет\n\nВаш ответ: ");
    if (scanf("%d", &print_mode) != 1 || getchar() != '\n' || (print_mode != 1 && print_mode != 2))
        printf("\nОшибка: команда должна быть одним из чисел, предложенных в меню.\n");
    if (print_mode == 1)
        printf("\nПримечание: на экран выводится информация об использовании памяти для первых двух заявок "
        "в целях наглядности.\n");

    printf("\nЗапуск процесса моделирования.\n\n");


    while (passed_tasks < 1000)
    {
        if (work_mode == 0)
        {
            //если аппарат не работает
            //если в очереди есть элементы, то необходимо снять первый и запустить аппарат
            if (list.count != 0)
            {
                if (print_mode == 1 && passed_tasks < 2)
                    print_mem(list, 0);
                pop_list(&list, &task_in_work);
                time_to_out = rand_time(LEFT_LIM_WORK, RIGHT_LIM_WORK);
                work_mode = 1;
                calls++;
            }
            else
            {
                //если в очереди нет элементов, нужно подождать, пока новый элемент войдет в очередь
                elapsed_time += time_to_in;
                waiting_time += time_to_in;
                time_to_in = 0.0;
                task_in_work.num_of_passes = 0;
                push_list(&list, task_in_work);
                if (print_mode == 1 && passed_tasks < 2)
                    print_mem(list, 1);
                time_to_in = rand_time(LEFT_LIM_PUSH, RIGHT_LIM_PUSH);
                tasks_in++;
            }
        }
        else
        {
            //если аппарат работает
            if (cmp_double(time_to_in, time_to_out) > 0)
            {
                //если заявка не успеет войти в очередь до того, как аппарат закончит работу
                //то заканчиваем время работы аппарата
                time_to_in -= time_to_out;
                elapsed_time += time_to_out;
                time_to_out = 0.0;
                work_mode = 0;
                task_in_work.num_of_passes++;
                //если из аппарата вышла заявка, которая проходила очередь меньше 5 раз, добавляем ее обратно
                if (task_in_work.num_of_passes < 5)
                {
                    push_list(&list, task_in_work);
                    if (print_mode == 1 && passed_tasks < 2)
                        print_mem(list, 1);
                }
                else
                {
                    passed_tasks++;
                    if (passed_tasks % 100 == 0 && passed_tasks)
                    {
                        avg_len += list.count;
                        temp[passed_tasks / 100 - 1] = list.count;
                        avg[passed_tasks / 100 - 1] = avg_len / (passed_tasks / 100);
                    }
                }
                //иначе она закончила свой цикл и вышла из системы
                    
            }
            else
            {
                //если новая заявка успеет добавиться в очередь во время работы аппарата
                //вычитаем время захода из времени работы аппарата
                time_to_out -= time_to_in;
                elapsed_time += time_to_in;
                time_to_in = 0.0;
                //добавляем заявку в очередь
                temp_task.num_of_passes = 0;
                push_list(&list, temp_task);
                if (print_mode == 1 && passed_tasks < 2)
                    print_mem(list, 1);
                tasks_in++;
                //генерируем новое время ожидания добавления
                time_to_in = rand_time(LEFT_LIM_PUSH, RIGHT_LIM_PUSH);
            }
        }
    }
    printf("\n\nИнформация о длине очереди:\n\n");
    printf("┏━━━━━━━━━━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓\n");
    printf("┃  Кол-во вышедших ┃   100   ┃   200   ┃   300   ┃   400   ┃   500   ┃   600   ┃   700   ┃   800   ┃   900   ┃  1000   ┃\n");
    printf("┃     заявок       ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫\n");
    printf("┃   Текущая длина  ┃");
    for (int i = 0; i < 10; i++)
        printf("%9d┃", temp[i]);
    printf("\n┣━━━━━━━━━━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫\n");
    printf("┃   Средняя длина  ┃");
    for (int i = 0; i < 10; i++)
        printf("%9d┃", avg[i]);
    printf("\n┗━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛\n");
    printf("\nЗавершение процесса моделирования.\n\n");
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃      Общее время моделирования      ┃%14lf е.в. ┃\n", elapsed_time);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃  Кол-во вошедших в систему заявок   ┃%13d       ┃\n", tasks_in);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃  Кол-во вышедших из системы заявок  ┃%13d       ┃\n", passed_tasks);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃        Кол-во срабатываний ОА       ┃%13d       ┃\n", calls);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃         Время простоя аппарата      ┃%14lf е.в. ┃\n", waiting_time);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃            Длина очереди            ┃%12d        ┃\n", list.count);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┛\n");

    printf("\nРассчет погрешности:\n\n");
    printf("\nПогрешность по входу:\n"
        "(Теор.) %lf е.в. / 3 е.в. = %lf заявок, (Практич.) = %d заявок, |(%d - %lf)| / %lf * 100%% = %lf%%\n", 
        elapsed_time, elapsed_time / 3, tasks_in, tasks_in, elapsed_time / 3, elapsed_time / 3, 
        fabs(tasks_in - elapsed_time / 3) / (elapsed_time / 3) * 100);
    printf("\nПогрешность по выходу:\n"
        "(Теор.) t работы + t простоя = t моделир., (Практич.) %lf, |(%lf - %lf)| / %lf* 100%% = %lf%%\n",
        elapsed_time, calls / 2 + waiting_time, elapsed_time, calls / 2 + waiting_time,
        fabs(calls / 2 + waiting_time - elapsed_time) / (calls / 2 + waiting_time) * 100);
    printf("\nПогрешность по времени моделирования:\n" 
        "(Теор.) 3 * 1000 = 3000, (Практич.) %lf, |(%lf - 3000)| / 3000 * 100%% = %lf%%\n\n", 
        elapsed_time, elapsed_time, fabs(elapsed_time - 3000) / 3000 * 100);
    free_all(list.head);
}

void modeling_queue_with_arr(void)
{
    arr_queue_t arr;
    init_arr_queue(&arr);

    double elapsed_time = 0.0;
    double waiting_time = 0.0;

    //время, оставшееся до выхода элемента очереди из ОА
    double time_to_out = 0.0; 
    //время, оставшееся до входа следующего элемента в очередь
    double time_to_in = rand_time(LEFT_LIM_PUSH, RIGHT_LIM_PUSH); 

    int passed_tasks = 0;

    int avg_len = 0;
    int avg[10] = {0};

    task_t temp_task;

    task_t task_in_work;
    task_in_work.num_of_passes = 0;

    //количество срабатываний аппарата
    int calls = 0;
    int tasks_in = 0;

    int work_mode = 0;

    printf("\nЗапуск процесса моделирования.\n\n");

    printf("┏━━━━━━━━━━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓\n");
    printf("┃  Кол-во вышедших ┃   100   ┃   200   ┃   300   ┃   400   ┃   500   ┃   600   ┃   700   ┃   800   ┃   900   ┃  1000   ┃\n");
    printf("┃     заявок       ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃         ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫\n");
    printf("┃   Текущая длина  ┃");

    while (passed_tasks < 1000)
    {
        if (work_mode == 0)
        {
            //если аппарат не работает
            //если в очереди есть элементы, то необходимо снять первый и запустить аппарат
            if (arr.count != 0)
            {
                pop_arr(&arr, &task_in_work);
                //printf("elem: %d\n", task_in_work.num_of_passes);
                time_to_out = rand_time(LEFT_LIM_WORK, RIGHT_LIM_WORK);
                work_mode = 1;
                calls++;
            }
            else
            {
                //если в очереди нет элементов, нужно подождать, пока новый элемент войдет в очередь
                elapsed_time += time_to_in;
                waiting_time += time_to_in;
                time_to_in = 0.0;
                task_in_work.num_of_passes = 0;
                push_arr(&arr, task_in_work);
                time_to_in = rand_time(LEFT_LIM_PUSH, RIGHT_LIM_PUSH);
                tasks_in++;
            }
        }
        else
        {
            //если аппарат работает
            if (cmp_double(time_to_in, time_to_out) > 0)
            {
                //если заявка не успеет войти в очередь до того, как аппарат закончит работу
                //то заканчиваем время работы аппарата
                time_to_in -= time_to_out;
                elapsed_time += time_to_out;
                time_to_out = 0.0;
                work_mode = 0;
                task_in_work.num_of_passes++;
                //если из аппарата вышла заявка, которая проходила очередь меньше 5 раз, добавляем ее обратно
                if (task_in_work.num_of_passes < 5)
                    push_arr(&arr, task_in_work);
                else
                    passed_tasks++;
                //иначе она закончила свой цикл и вышла из системы
                    
            }
            else
            {
                //если новая заявка успеет добавиться в очередь во время работы аппарата
                //вычитаем время захода из времени работы аппарата
                time_to_out -= time_to_in;
                elapsed_time += time_to_in;
                time_to_in = 0.0;
                //добавляем заявку в очередь
                temp_task.num_of_passes = 0;
                push_arr(&arr, temp_task);
                tasks_in++;
                //генерируем новое время ожидания добавления
                time_to_in = rand_time(LEFT_LIM_PUSH, RIGHT_LIM_PUSH);
            }
        }
    }
    printf("\n┣━━━━━━━━━━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫\n");
    printf("┃   Средняя длина  ┃");
    for (int i = 0; i < sizeof(avg) / sizeof(avg[0]); i++)
        printf("%9d┃", avg[i]);
    printf("\n┗━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛\n");
    printf("\nЗавершение процесса моделирования.\n\n");
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃      Общее время моделирования      ┃%14lf е.в. ┃\n", elapsed_time);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃  Кол-во вошедших в систему заявок   ┃%13d       ┃\n", tasks_in);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃  Кол-во вышедших из системы заявок  ┃%13d       ┃\n", passed_tasks);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃        Кол-во срабатываний ОА       ┃%13d       ┃\n", calls);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃         Время простоя аппарата      ┃%14lf е.в. ┃\n", waiting_time);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃            Длина очереди            ┃%12d        ┃\n", arr.count);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┛\n");

    printf("\nРассчет погрешности:\n\n");
    printf("\nПогрешность по входу:\n"
        "(Теор.) %lf е.в. / 3 е.в. = %lf заявок, (Практич.) = %d заявок, |(%d - %lf)| / %lf * 100%% = %lf%%\n", 
        elapsed_time, elapsed_time / 3, tasks_in, tasks_in, elapsed_time / 3, elapsed_time / 3, 
        fabs(tasks_in - elapsed_time / 3) / (elapsed_time / 3) * 100);
    printf("\nПогрешность по выходу:\n"
        "(Теор.) t работы + t простоя = t моделир., (Практич.) %lf, |(%lf - %lf)| / %lf* 100%% = %lf%%\n",
        elapsed_time, calls / 2 + waiting_time, elapsed_time, calls / 2 + waiting_time,
        fabs(calls / 2 + waiting_time - elapsed_time) / (calls / 2 + waiting_time) * 100);
    printf("\nПогрешность по времени моделирования:\n" 
        "(Теор.) 3 * 1000 = 3000, (Практич.) %lf, |(%lf - 3000)| / 3000 * 100%% = %lf%%\n\n", 
        elapsed_time, elapsed_time, fabs(elapsed_time - 3000) / 3000 * 100);
}

list_node_t *get_tail(list_queue_t list)
{
    if (!list.head)
        return NULL;
    list_node_t *cur = list.head;
    while (cur->next)
        cur = cur->next;
    return cur;
}

void init_list_queue(list_queue_t *list)
{
    list->head = NULL;
    list->count = 0;
}

void free_all(list_node_t *head)
{
    list_node_t *next;
    for (; head; head = next)
    {
        next = head->next;
        free(head);
    }
}

list_node_t *create(task_t task)
{
    list_node_t *new = malloc(sizeof(list_node_t));
    if (new)
    {
        new->task.num_of_passes = task.num_of_passes;
        new->next = NULL;
    }
    return new;
}

int push_list(list_queue_t *list, task_t task)
{
    if (!list->head)
        list->head = create(task);
    else
    {
        list_node_t *cur = list->head;
        while (cur->next)
            cur = cur->next;
        cur->next = create(task);
    }
    list->count++;
    return EXIT_SUCCESS;
}

int pop_list(list_queue_t *list, task_t *task)
{
    if (list->count == 0)
        return ERR_EMPTY_LIST;
    list_node_t *buf = list->head;
    list->head = list->head->next;
    task->num_of_passes = buf->task.num_of_passes;
    free(buf);
    list->count--;
    return EXIT_SUCCESS;
}

int pop_arr(arr_queue_t *arr, task_t *task)
{
    if (arr->count == 0)
        return ERR_EMPTY_ARR;
    task->num_of_passes = arr->head->num_of_passes;
    if (arr->head == (arr->tasks + MAX_ARR_SIZE))
        arr->head = arr->tasks;
    else
        arr->head++;
    arr->count--;
    return EXIT_SUCCESS;
}

int push_arr(arr_queue_t *arr, task_t task)
{
    if (arr->count == MAX_ARR_SIZE)
        return ERR_FULL_ARR;
    arr->tail->num_of_passes = task.num_of_passes;
    if (arr->tail == (arr->tasks + MAX_ARR_SIZE))
        arr->tail = arr->tasks;
    else
        arr->tail++;
    arr->count++;
    return EXIT_SUCCESS;
}

void init_task(task_t *task)
{
    task->num_of_passes = 0;
}

double rand_time(const int left_lim, const int right_lim)
{
    double p = (double)rand() / (double)RAND_MAX;
    return (right_lim - left_lim) * p + left_lim;
}

void init_arr_queue(arr_queue_t *arr)
{
    for (int i = 0; i < MAX_ARR_SIZE; i++)
        arr->tasks[i].num_of_passes = 0;
    arr->count = 0;
    arr->head = arr->tasks;
    arr->tail = arr->tasks;
}

int cmp_double(double a, double b)
{
    if (fabs(a - b) <= EPS)
        return 0;
    else if (a < (b - EPS))
        return -1;
    else
        return 1;
}

void print_mem(list_queue_t list, int mode)
{
    if (mode == 0)
    {
        printf("┏━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━┓\n");
        printf("┃ Освобождено  ┃%p┃\n", (void*)get_tail(list));
        printf("┗━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━┛\n");
    }
    else
    {
        printf("┏━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━┓\n");
        printf("┃   Выделено   ┃%p┃\n", (void*)get_tail(list));
        printf("┗━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━┛\n");
    }
    
}
