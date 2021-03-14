#include "io_list.h"

int read_list(list_stack_t **ptr)
{
    free_list(ptr);
    *ptr = NULL;
    char ch = 'i';
    int item, rc;
    while (ch != '\n')
    {
        if ((rc = get_item(&item)))
            return rc;
        if ((rc = push_list(ptr, item)))
        {
            printf("\nНевозможно добавить элемент в стек: ошибка выделения памяти.\n\n");
            return rc;
        }
        ch = getchar();
    }
    printf("\nЭлементы успешно введены.\n");
    return EXIT_SUCCESS;
}

void free_list(list_stack_t **ptr)
{
    while (*ptr)
    {
        list_stack_t *buf = *ptr;
        *ptr = (*ptr)->prev;
        free(buf);
    }
}

int push_list(list_stack_t **ptr, int item)
{
    list_stack_t *new = malloc(sizeof(list_stack_t));
    if (!new)
        return ERR_MALLOC;
    new->prev = *ptr;
    new->data = item;
    *ptr = new;
    return EXIT_SUCCESS;
}

int pop_list(list_stack_t **ptr, int *item)
{
    if (!(*ptr))
        return ERR_EMPTY_STACK;
    *item = (*ptr)->data;
    list_stack_t *buf = *ptr;
    *ptr = (*ptr)->prev;
    free(buf);
    return EXIT_SUCCESS;
}

void init_list(list_stack_t **ptr)
{
    *ptr = NULL;
}

int pop_list_with_freed(list_stack_t **ptr, int *item, freed_t *list)
{
    if (!(*ptr))
        return ERR_EMPTY_STACK;
    *item = (*ptr)->data;
    list_stack_t *buf = *ptr;
    *ptr = (*ptr)->prev;
    free(buf);
    list->a[list->index++] = buf;
    return EXIT_SUCCESS;
}

int push_list_with_freed(list_stack_t **ptr, int item, freed_t *list)
{
    list_stack_t *new = malloc(sizeof(list_stack_t));
    if (!new)
        return ERR_MALLOC;
    new->prev = *ptr;
    new->data = item;
    *ptr = new;
    int i = 0;
    while (i < list->index && (void*)new != (void*)list->a[i])
        i++;
    if (i != list->index)
    {
        for (int j = list->index - 1; j > i; j--)
            list->a[j - 1] = list->a[j];
        list->index--;
    }
    return EXIT_SUCCESS;
}

void print_list(list_stack_t *ptr)
{
    int item;
    list_stack_t *buf = NULL;
    if (!ptr)
        printf("\nСтек пуст.\n");
    else
    {   
        printf("\n┏━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━┓\n");
        printf("┃%21s┃%22s┃\n", "Адрес", "Значение");
        while (ptr)
        {
            printf("┣━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━┫\n");
            printf("┃%p", (void*)ptr);
            pop_list(&ptr, &item);
            printf("┃%14d┃\n", item);
            push_list(&buf, item);
        }
        printf("┗━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━┛\n");
        while (buf)
        {
            pop_list(&buf, &item);
            push_list(&ptr, item);
        }
    }
}