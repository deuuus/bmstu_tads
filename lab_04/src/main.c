#include "menu.h"
#include "io_arr.h"
#include "io_list.h"
#include "sort_arr.h"
#include "sort_list.h"
#include "analys.h"

int main()
{
    int act = EXIT_SUCCESS;
    int rc;
    arr_stack_t st_1;
    arr_stack_t st_2;
    arr_stack_t res;
    freed_t list;
    list.index = 0;
    init_arr(&st_1);
    init_arr(&st_2);
    init_arr(&res);
    int item;

    list_stack_t *top = malloc(sizeof(list_stack_t));
    top += MAX_SIZE * sizeof(list_stack_t);

    printf("top = %p\n", (void*)top);

    list_stack_t *ptr_1 = NULL;
    list_stack_t *ptr_2 = NULL;
    list_stack_t *ptr_res = NULL;
    char mood = 'a';
    while (act != EXIT)
    {
        if ((rc = choose_action(&act)))
            return rc;
        if (act == CREATE)
        {
            if ((rc = choose_stack_type(&act)))
                return rc;
            if (act == ARR_TYPE)
            {
                mood = 'a';
                printf("\nВведите элементы первого стека: ");
                if ((rc = read_arr(&st_1)))
                    return rc;
                printf("\nВведите элементы второго стека: ");
                if ((rc = read_arr(&st_2)))
                    return rc;
                init_arr(&res);
            }
            else
            {
                mood = 'l';
                printf("\nВведите элементы первого стека: ");
                if ((rc = read_list(&ptr_1)))
                    return rc;
                printf("\nВведите элементы второго стека: ");
                if ((rc = read_list(&ptr_2)))
                    return rc;
                ptr_res = NULL;
            }
        }
        if (act == PRINT)
        {
            if (mood == 'a')
            {
                printf("\nПервый стек: ");
                print_arr(&st_1);
                printf("\nВторой стек: ");
                print_arr(&st_2);
            }
            else
            {
                printf("\nПервый стек:\n");
                print_list(ptr_1);
                printf("\nВторой стек:\n");
                print_list(ptr_2);
                printf("\n\nСвободные области: ");
                if (list.index == 0)
                    printf("отсутвуют.\n\n");
                else
                {
                    printf("\n\n┏━━━━━━━━━━━━━━━━┓\n");
                    for (int i = 0; i < list.index; i++)
                    {
                        printf("┃%p┃\n", (void*)list.a[i]);
                        if (i != (list.index - 1))
                            printf("┣━━━━━━━━━━━━━━━━┫\n");
                    }
                    printf("┗━━━━━━━━━━━━━━━━┛\n");   
                }
            }
        }
        if (act == SORT)
        {
            printf("\nВнимание! После сортировки стеков отсортированные данные помещаются в новый\n"
                " общий стек, данные из двух введенных стеков при этом освобождаются.\n\n");
            if (mood == 'a')
            {
                if (res.ptr >= res.a)
                    print_arr(&res);
                else if (!sort_arr(&st_1, &st_2, &res))
                {
                    printf("Отсортированные введенные данные:\n");
                    print_arr(&res);
                }
            }
            else
            {
                if (ptr_res)
                    print_list(ptr_res);
                else if (!sort_list(&ptr_1, &ptr_2, &ptr_res))
                {
                    printf("Отсортированные введенные данные:\n");
                    print_list(ptr_res);
                }
            }
        }
        if (act == POP)
        {
            if (mood == 'a')
            {
                if ((rc = choose_stack(&act)))
                    return rc;
                if (act == FIRST_ST && (rc = pop_arr(&st_1, &item)))
                {
                    printf("Невозможно произвести удаление: стек пуст.");
                    return rc;
                }
                if (act == SECOND_ST && (rc = pop_arr(&st_2, &item)))
                {
                    printf("Невозможно произвести удаление: стек пуст.");
                    return rc;
                }
            }
            else
            {
                if ((rc = choose_stack(&act)))
                    return rc;
                if (act == FIRST_ST && (rc = pop_list_with_freed(&ptr_1, &item, &list)))
                {
                    printf("Невозможно произвести удаление: стек пуст.");
                    return rc;
                }
                if (act == SECOND_ST && (rc = pop_list_with_freed(&ptr_2, &item, &list)))
                {
                    printf("Невозможно произвести удаление: стек пуст.");
                    return rc;
                }
            }
            printf("\nПоследний элемент со значением %d успешно удален из стека.\n", item);
            if (mood == 'l')
            {
                printf("\n\nСвободные области: ");
                if (list.index == 0)
                    printf("отсутвуют.\n\n");
                else
                {
                    printf("\n\n┏━━━━━━━━━━━━━━━━┓\n");
                    for (int i = 0; i < list.index; i++)
                    {
                        printf("┃%p┃\n", (void*)list.a[i]);
                        if (i != (list.index - 1))
                            printf("┣━━━━━━━━━━━━━━━━┫\n");
                    }
                    printf("┗━━━━━━━━━━━━━━━━┛\n");   
                }
            }
        }
        if (act == PUSH)
        {
            printf("\nВведите элемент: ");
            if ((rc = get_item(&item)))
                return rc;
            if (mood == 'a')
            {
                if ((rc = choose_stack(&act)))
                    return rc;
                if (act == FIRST_ST)
                    push_arr(&st_1, item);
                else
                    push_arr(&st_2, item);
            }
            else
            {
                if ((rc = choose_stack(&act)))
                    return rc;
                if (act == FIRST_ST)
                    push_list_with_freed(&ptr_1, item, &list);
                else
                    push_list_with_freed(&ptr_2, item, &list);
            }
            printf("\nЭлемент со значением %d успешно добавлен в конец стека.\n", item);
        }
        if (act == ANALYS)
            analys();
        if (act == INFO)
            info();
    }
    printf("\nЗавершение работы.");
    return EXIT_SUCCESS;
}