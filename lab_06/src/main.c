#include "../inc/menu.h"
#include "../inc/io.h"

int main(void)
{
    int act = EXIT_SUCCESS;
    int rc = EXIT_SUCCESS;
    tree_node_t *root = NULL, *node;
    node = create_node("slovo1");
    root = insert(root, node);
    node = create_node("slovo3");
    root = insert(root, node);
    node = create_node("slovo2");
    root = insert(root, node);
    while (act != EXIT)
    {
        if ((rc = choose_action(&act)))
            return rc;
        if (act == INPUT)
        {
            FILE *f = fopen("test.dot", "w");
            btree_export_to_dot(f, root);
            fclose(f);
        }
        if (act == INFO)
            show_info();
        if (act == EXIT)
            printf("\nЗавершение работы.\n");
    }
    return rc;
}