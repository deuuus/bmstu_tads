#include "sort_list.h"

int sort_list(list_stack_t **ptr_a, list_stack_t **ptr_b, list_stack_t **ptr_res)
{
    (*ptr_res) = NULL;
    list_stack_t *buf = NULL;
    int item, buf_item;
    int rc;
    while ((*ptr_a))
    {
        pop_list(ptr_a, &item);
        while (*ptr_res)
        {
            pop_list(ptr_res, &buf_item);
            if ((rc = push_list(&buf, buf_item)))
                return rc;
            if (buf_item < item)
            {
                pop_list(&buf, &buf_item);
                if ((rc = push_list(ptr_res, buf_item)))
                    return rc;
                break;
            }
        }
        if ((rc = push_list(ptr_res, item)))
            return rc;
        while (buf)
        {
            pop_list(&buf, &buf_item);
            if ((rc = push_list(ptr_res, buf_item)))
                return rc;
        }
    }
    while ((*ptr_b))
    {
        pop_list(ptr_b, &item);
        while (*ptr_res)
        {
            pop_list(ptr_res, &buf_item);
            if ((rc = push_list(&buf, buf_item)))
                return rc;
            if (buf_item < item)
            {
                pop_list(&buf, &buf_item);
                if ((rc = push_list(ptr_res, buf_item)))
                    return rc;
                break;
            }
        }
        if ((rc = push_list(ptr_res, item)))
            return rc;
        while (buf)
        {
            pop_list(&buf, &buf_item);
            if ((rc = push_list(ptr_res, buf_item)))
                return rc;
        }
    }
    return EXIT_SUCCESS;
}