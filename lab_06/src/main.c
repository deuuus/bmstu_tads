#include "../inc/menu.h"
#include "../inc/tree.h"
#include "../inc/hash.h"
#include "../inc/analys.h"

int main(void)
{
    int act = EXIT_SUCCESS;
    int rc = EXIT_SUCCESS;
    tree_node_t *root = NULL;
    tree_node_t *bal_root = NULL;
    FILE *f_data = NULL, *f_graph;
    list_t *words[N];
    int hash_ind[N];
    int n = 0, col, max_col;
    int (*func)(char *, int) = hash_func_mod_salt;
    while (act != EXIT)
    {
        if ((rc = choose_action(&act)))
            return rc;
        if (act == INPUT)
        {
            if ((rc = read_name(&f_data)))
                continue;
            root = read_bin(f_data);
            if (!root)
            {
                printf("\nОшибка: файл содержит некорректные данные.\n");
                continue;
            }   
            printf("\nДанные успешно считаны.\n");
        }
        if (act == BINARY)
        {
            if (!f_data)
            {
                printf("\nДанные не введены в систему. Воспользуйтесь пунктом 1 из меню.\n");
                continue;
            }
            rewind(f_data);
            root = read_bin(f_data);
            f_graph = fopen("utils/bst.gv", "w");
            tree_export_to_dot(f_graph, root);
            fclose(f_graph);
            rewind(f_data);
            show_image_info();
        }
        if (act == BALANCE)
        {
            if (!root)
            {
                printf("\nДанные не введены в систему. Воспользуйтесь пунктом 1 из меню.\n");
                continue;
            }
            bal_root = make_bal_tree(f_data);
            f_graph = fopen("utils/bbst.gv", "w");
            tree_export_to_dot(f_graph, bal_root);
            fclose(f_graph);
            show_bal_image_info();
        }
        if (act == DEL)
        {
            if (!root)
            {
                printf("\nДДП еще не сформировано. Воспользуйтесь пунктом 2 из меню.\n");
                continue;
            }
            if (!bal_root)
            {
                printf("\nСбалансированное дерево еще не сформировано. Воспользуйтесь пунктом 3 из меню.\n");
                continue;
            }
            char data[MAX_WORD_LEN];
            if ((rc = read_word(data)))
                continue;
            if (!find(root, data))
                printf("\nУзел с таким значением не найден в деревьях.\n");
            else
            {
                bal_root = avl_del(bal_root, data);
                root = del(root, data);
                f_graph = fopen("utils/bbst.gv", "w");
                tree_export_to_dot(f_graph, bal_root);
                fclose(f_graph);
                f_graph = fopen("utils/bst.gv", "w");
                tree_export_to_dot(f_graph, root);
                fclose(f_graph);
                show_del_info();
                analys_del(root, bal_root, data);
            }
        }
        if (act == HASH)
        {
            if (!root)
            {
                printf("\nДанные еще не введены в систему. Воспользуйтесь пунктом 1 из меню.\n");
                continue;
            }
            printf("\nВведите размерность таблицы: ");
            if ((rc = read_int(&n)))
                continue;
            printf("\nВведите максимально допустимое количество коллизий: ");
            if ((rc = read_int(&max_col)))
                continue;
            read_table(f_data, words, hash_ind, n, &col, func);
            print_table(words, hash_ind, n);
            if (col > max_col)
            {
                printf("\nПревышено максимально допустимое количество коллизий.\n\n"
                "Применение другой хэщ-функции:\n");
                func = hash_func_prod_salt;
                read_table(f_data, words, hash_ind, n, &col, func);
                print_table(words, hash_ind, n);
                if (col > max_col)
                    printf("\nПревышено максимально допустимое количество коллизий.\n\n"
                    "Использованы все имеющиеся хэш-функции. Попробуйте увеличить размерность таблицы.\n");
            }
        }
        if (act == DEL_HASH)
        {
            if (!n)
            {
                printf("\nХэш-атблица не создана. Воспользуйтесь пунктом 5 из меню.\n");
                continue;
            }
            char data[MAX_WORD_LEN];
            if ((rc = read_word(data)))
                continue;
            if (find_table(words, hash_ind, n, data, func) < 0)
                printf("\nВведенное слово не найдено в хэш-таблице.\n");
            else
            {
                del_table(words, hash_ind, n, data, func);
                print_table(words, hash_ind, n);
            }
        }
        if (act == ANALYS)
            analys();
        if (act == INFO)
            show_info();
        if (act == EXIT)
            printf("\nЗавершение работы.\n");
    }
    return rc;
}