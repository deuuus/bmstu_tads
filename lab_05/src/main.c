#include "../inc/menu.h"
#include "../inc/process.h"
#include "../inc/analys.h"

int main()
{
    int act = EXIT_SUCCESS;
    int rc;
    while (act != EXIT)
    {
        if ((rc = choose_action(&act)))
            return rc;
        if (act == PROCESS_LIST)
            modeling_queue_with_list();
        if (act == PROCESS_ARR)
            modeling_queue_with_arr();
        if (act == ANALYS)
            analys();
        if (act == EXIT)
            printf("\nЗавершение работы.");
    }
    return EXIT_SUCCESS;
}