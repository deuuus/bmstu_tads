#include "../inc/analys.h"

tree_node_t *avl_del_cmp(tree_node_t *root, char *data, int *cmp);
tree_node_t *del_cmp(tree_node_t *root, char *data, int *cmp);
int find_table_cmp(list_t *words[], int hash_ind[], int n, char *data, int (*func)(char *, int), int *cmp);
void del_table_cmp(list_t *words[], int hash_ind[], int n, char *data, int (*func)(char *, int), int *cmp);
tree_node_t *avl_insert_cmp(tree_node_t *root, tree_node_t *to_insert, int *cmp);
tree_node_t *insert_cmp(tree_node_t *root, tree_node_t *to_insert, int *cmp);
tree_node_t *make_bal_tree_cmp(FILE *f, int*cmp);
tree_node_t *read_cmp(FILE *f, int *cmp);
tree_node_t *find_cmp(tree_node_t *root, char *data, int *cmp);
int find_file_cmp(FILE *f, char *data, int *cmp);
void del_file_cmp(FILE *f, char *data, int *cmp);

void analys(void)
{
    
    printf("\nСравнительный анализ структур данных:\n\n");
    printf("┏━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃  Кол-во элементов  ┃      Операция      ┃        ДДП         ┃   Сбалансир. ДДП   ┃      Хэш-таблица   ┃        Файл        ┃\n");
    FILE *f = fopen("data/test10.txt", "r");
    FILE *file = fopen("data/file10.txt", "r+w");
    int n = 10;
    analys_cycle(f, file, n);
    fclose(f);
    f = fopen("data/test100.txt", "r");
    file = fopen("data/file100.txt", "r+w");
    n = 100;
    analys_cycle(f, file, n);
    fclose(f);
    f = fopen("data/test1000.txt", "r");
    file = fopen("data/file1000.txt", "r+w");
    n = 1000;
    analys_cycle(f, file, n);
    printf("┗━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\n\nСравнительный анализ объема памяти:\n\n");
    mem_analys();
}

void mem_analys(void)
{
    uint64_t mem[4] = {0};
    mem[0] = 3 * sizeof(tree_node_t*) + MAX_WORD_LEN * sizeof(char);
    mem[1] = mem[0];
    mem[2] = sizeof(list_t*) + MAX_WORD_LEN + sizeof(int);
    mem[3] = sizeof(char*);
    printf("┏━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃  Кол-во элементов  ┃        ДДП         ┃   Сбалансир. ДДП   ┃      Хэш-таблица   ┃        Файл        ┃\n");
    for (int i = 2; i < 1025; i *= 2)
    {
        printf("┣━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n");
        printf("┃%13d       ┃%13lld       ┃%13lld       ┃%13lld       ┃%13lld       ┃\n", i, mem[0] * i, mem[1] * i, mem[2] * i, mem[3] * i);
    }
    printf("┗━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┛\n");
}

void analys_cycle(FILE *fdata, FILE *file, int size)
{
    uint64_t time[4] = {0}, cmp[4] = {0}, start, end;
    tree_node_t *root = NULL, *bal_root = NULL;
    list_t *words[N];
    int hash_ind[N];
    int n = 3000, col = n;
    int (*func)(char *, int) = hash_func_mod_salt;
    printf("┣━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃                    ┃");
    root = read_bin(fdata);
    bal_root = make_bal_tree(fdata);
    read_table(fdata, words, hash_ind, n, &col, func);
    root = insert(root, create("3"));
    bal_root = avl_insert(bal_root, create("3"));
    insert_table(words, hash_ind, n, "3", &col, func);
    char **file_words = read_file(fdata);
    for (int i = 0; i < 100000; i++)
    {
        start = tick();
        root = del(root, "3");
        end = tick();
        root = insert(root, create("3"));
        time[0] += end - start;

        start = tick();
        bal_root = avl_del(bal_root, "3");
        end = tick();
        bal_root = avl_insert(bal_root, create("3"));
        time[1] += end - start;

        start = tick();
        del_table(words, hash_ind, n, "3", func);
        end = tick();
        insert_table(words, hash_ind, n, "3", &col, func);
        time[2] += end - start;
    }
    insert_file(file, "5678");
    for (int i = 0; i < 200; i++)
    {
        start = tick();
        del_file(file, "5678");
        end = tick();
        insert_file(file, "5678");
        time[3] += end - start;
    }
    del_file(file, "5678");
    time[0] /= 100000;
    time[1] /= 100000;
    time[2] /= 100000;
    time[3] /= 200;
    int x = 0;
    del_cmp(root, "3", &x);
    cmp[0] = x;
    x = 0;
    avl_del_cmp(root, "3", &x);
    cmp[1] = x;
    x = 0;
    del_table_cmp(words, hash_ind, n, "3", func, &x);
    cmp[2] = x;
    x = 0;
    del_file_cmp(file, "5678", &x);
    cmp[3] = x;
    printf("                    ┃%10lld тиков    ┃%10lld тиков    ┃%10lld тиков    ┃%10lld тиков    ┃\n", time[0], time[1], time[2], time[3]);
    printf("┃                    ┃      Удаление      ┃");
    printf("  ---------------   ┃  ---------------   ┃  ---------------   ┃  ---------------   ┃\n");
    printf("┃                    ┃                    ┃%8lld сравнений  ┃%8lld сравнений  ┃%8lld сравнений  ┃%8lld сравнений  ┃\n", cmp[0], cmp[1], cmp[2], cmp[3]);
    printf("┃                    ┣━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃                    ┃");
    time[0] = 0;
    time[1] = 0;
    time[3] = 0;
    for (int i = 0; i < 100000; i++)
    {
        start = tick();
        root = insert(root, create("b"));
        end = tick();
        root = del(root, "b");
        time[0] += end - start;
        
        start = tick();
        bal_root = avl_insert(bal_root, create("b"));
        end = tick();
        bal_root = avl_del(bal_root, "b");
        time[1] += end - start;

        start = tick();
        insert_table(words, hash_ind, n, "b", &col, func);
        end = tick();
        del_table(words, hash_ind, n, "b", func);
        time[2] += end - start;
    }
    for (int i = 0; i < 100; i++)
    {
        start = tick();
        insert_file(file, "5678");
        end = tick();
        del_file(file, "5678");
        time[3] += end - start;
    }
    time[0] /= 100000;
    time[1] /= 100000;
    time[2] /= 100000;
    time[3] /= 100;
    x = 0;
    insert_cmp(root, create("a"), &x);
    cmp[0] = x;
    x = 0;
    avl_insert_cmp(root, create("a"), &x);
    cmp[1] = x;
    cmp[2] = 0;
    cmp[3] = 0;
    printf("                    ┃%10lld тиков    ┃%10lld тиков    ┃%10lld тиков    ┃%10lld тиков    ┃\n", time[0], time[1], time[2], time[3]);
    printf("┃                    ┃      Вставка       ┃");
    printf("  ---------------   ┃  ---------------   ┃  ---------------   ┃  ---------------   ┃\n");
    printf("┃                    ┃                    ┃%8lld сравнений  ┃%8lld сравнений  ┃%8lld сравнений  ┃%8lld сравнений  ┃\n", cmp[0], cmp[1], cmp[2], cmp[3]);
    printf("┃%11d         ┣━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n", size);
    printf("┃                    ┃");
    time[0] = 0;
    time[1] = 0;
    time[3] = 0;
    free_tree(root);
    free_tree(bal_root);
    for (int i = 0; i < 1000; i++)
    {
        start = tick();
        root = read_bin(fdata);
        end = tick();
        rewind(fdata);
        free_tree(root);
        time[0] += end - start;

        start = tick();
        bal_root = make_bal_tree(fdata);
        end = tick();
        free_tree(bal_root);
        rewind(fdata);
        time[1] += end - start;

        for (int i = 0; i < n; i++)
            hash_ind[i] = 0;
        free_words(words, n);
        start = tick();
        read_table(fdata, words, hash_ind, n, &col, func);
        end = tick();
        rewind(fdata);
        time[2] += end - start;
    }
    for (int i = 0; i < 100; i++)
    {
        start = tick();
        char **words_file = read_file(file);
        end = tick();
        free_file(words_file, file_len(file));
        time[3] += end - start;
    }
    time[0] /= 1000;
    time[1] /= 1000;
    time[2] /= 1000;
    time[3] /= 100;
    x = 0;
    root = read_cmp(fdata, &x);
    rewind(fdata);
    cmp[0] = x;
    x = 0;
    bal_root = make_bal_tree_cmp(fdata, &x);
    rewind(fdata);
    cmp[1] = x;
    read_table(fdata, words, hash_ind, n, &col, func);
    rewind(fdata);
    cmp[2] = col;
    cmp[3] = 0;
    printf("                    ┃%10lld тиков    ┃%10lld тиков    ┃%10lld тиков    ┃%10lld тиков    ┃\n", time[0], time[1], time[2], time[3]);
    printf("┃                    ┃      Создание      ┃");
    printf("  ---------------   ┃  ---------------   ┃  ---------------   ┃  ---------------   ┃\n");
    printf("┃                    ┃                    ┃%8lld сравнений  ┃%8lld сравнений  ┃%8lld сравнений  ┃%8lld сравнений  ┃\n", cmp[0], cmp[1], cmp[2], cmp[3]);
    printf("┃                    ┣━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃                    ┃");
    time[0] = 0;
    time[1] = 0;
    time[3] = 0;
    for (int i = 0; i < 1000; i++)
    {
        start = tick();
        find(root, "3");
        end = tick();
        time[0] += end - start;

        start = tick();
        find(bal_root, "3");
        end = tick();
        time[1] += end - start;

        start = tick();
        find_table(words, hash_ind, n, "3", func);
        end = tick();
        time[2] += end - start;

        start = tick();
        find_file(fdata, "3");
        end = tick();
        time[3] += end - start;
    }
    time[0] /= 1000;
    time[1] /= 1000;
    time[2] /= 1000;
    time[3] /= 1000;
    x = 0;
    find_cmp(root, "3", &x);
    cmp[0] = x;
    x = 0;
    find_cmp(bal_root, "3", &x);
    cmp[1] = x;
    x = 0;
    find_table_cmp(words, hash_ind, n, "3", func, &x);
    cmp[2] = x;
    free_file(file_words, file_len(fdata));
    x = 0;
    find_file_cmp(file, "849", &x);
    cmp[3] = x;
    printf("                    ┃%10lld тиков    ┃%10lld тиков    ┃%10lld тиков    ┃%10lld тиков    ┃\n", time[0], time[1], time[2], time[3]);
    printf("┃                    ┃       Поиск        ┃");
    printf("  ---------------   ┃  ---------------   ┃  ---------------   ┃  ---------------   ┃\n");
    printf("┃                    ┃                    ┃%8lld сравнений  ┃%8lld сравнений  ┃%8lld сравнений  ┃%8lld сравнений  ┃\n", cmp[0], cmp[1], cmp[2], cmp[3]);
} 

void analys_del(tree_node_t *root, tree_node_t *broot, char *data)
{
    root = insert(root, create(data));
    broot = avl_insert(broot, create(data));
    uint64_t time[2] = {0}, start, end;
    uint64_t mem[2];
    for (int i = 0; i < 1000; i++)
    {
        start = tick();
        root = del(root, data);
        end = tick();
        time[0] += end - start;
        root = insert(root, create(data));

        start = tick();
        broot = avl_del(broot, data);
        end = tick();
        time[1] += end - start;
        broot = avl_insert(broot, create(data));
    }
    time[0] /= 1000;
    time[1] /= 1000;
    mem[0] = 2 * sizeof(tree_node_t*) + sizeof(root->data);
    mem[1] = mem[0];
    printf("\nСравнительный анализ:\n");
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃                        ┃     Исходное дерево     ┃ Сбалансированное дерево ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃ Время удаления (такты) ┃%13lld            ┃%13lld            ┃\n", time[0], time[1]);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃  Объем памяти (байты)  ┃%13lld            ┃%13lld            ┃\n", mem[0], mem[1]);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

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

tree_node_t *avl_del_cmp(tree_node_t *root, char *data, int *cmp)
{
    if (!root)
        return NULL;
    (*cmp) += 1;
    if (strcmp(data, root->data) < 0)
        root->left = avl_del_cmp(root->left, data, cmp);
    else if (strcmp(data, root->data) > 0)
        root->right = avl_del_cmp(root->right, data, cmp);
    else
    {
        tree_node_t *left = root->left, *right = root->right;
        if (!right)
            return left;
        tree_node_t *min = find_min(right);
        min->right = remove_min(right);
        min->left = left;
        free(root);
        return balance(min); 
    }
    return balance(root);
}

tree_node_t *del_cmp(tree_node_t *root, char *data, int *cmp)
{
    if (!root)
        return NULL;
    (*cmp) += 1;
    if (strcmp(data, root->data) < 0)
        root->left = del_cmp(root->left, data, cmp);
    else if (strcmp(data, root->data) > 0)
        root->right = del_cmp(root->right, data, cmp);
    else
    {
        tree_node_t *left = root->left, *right = root->right;
        if (!right)
            return left;
        tree_node_t *min = find_min(right);
        min->right = remove_min(right);
        min->left = left;
        free(root);
        return min; 
    }
    return root;
}

int find_table_cmp(list_t *words[], int hash_ind[], int n, char *data, int (*func)(char *, int), int *cmp)
{
    int x = func(data, n);
    if (hash_ind[x] == 0)
        return -1;
    list_t *cur = words[x];
    while (strcmp(cur->data, data))
    {
        (*cmp) += 1;
        cur = cur->next;
    }
    return func(cur->data, n);
}

void del_table_cmp(list_t *words[], int hash_ind[], int n, char *data, int (*func)(char *, int), int *cmp)
{
    int pos = find_table(words, hash_ind, n, data, func);
    list_t *cur = words[pos], *prev = NULL;
    while (strcmp(cur->data, data))
    {
        (*cmp) += 1;
        prev = cur;
        cur = cur->next;
    }
    if (!prev)
    {
        words[pos] = words[pos]->next;
        if (!words[pos])
            hash_ind[pos] = 0;
    }   
    else
        prev->next = cur->next;
}

tree_node_t *avl_insert_cmp(tree_node_t *root, tree_node_t *to_insert, int *cmp)
{
    if (!root)
        return to_insert;
    (*cmp) += 1;
    if (strcmp(to_insert->data, root->data) <= 0)
        root->left = avl_insert_cmp(root->left, to_insert, cmp);
    else
        root->right = avl_insert_cmp(root->right, to_insert, cmp);
    return balance(root);
}

tree_node_t *insert_cmp(tree_node_t *root, tree_node_t *to_insert, int *cmp)
{
    if (!root)
        return to_insert;
    (*cmp) += 1;
    if (strcmp(to_insert->data, root->data) <= 0)
        root->left = insert_cmp(root->left, to_insert, cmp);
    else
        root->right = insert_cmp(root->right, to_insert, cmp);
    return root;
}

tree_node_t *read_cmp(FILE *f, int *cmp)
{
    char str[MAX_WORD_LEN + 1];
    tree_node_t *root = NULL, *node;
    while (fgets(str, sizeof(str), f))
    {
        if (str[strlen(str) - 1] == '\n')
            str[strlen(str) - 1] = '\0';
        node = create(str);
        if (!node)
            return NULL;
        root = insert_cmp(root, node, cmp);
    }
    if (!feof(f))
    {
        free_tree(root);
        return NULL;
    }
    else
        return root;
}

tree_node_t *make_bal_tree_cmp(FILE *f, int*cmp)
{
    char buf[MAX_WORD_LEN];
    tree_node_t *root = NULL, *node;
    while (fgets(buf, sizeof(buf), f))
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = '\0';
        node = create(buf);
        root = avl_insert_cmp(root, node, cmp);
    }
    return root;
}

tree_node_t *find_cmp(tree_node_t *root, char *data, int *cmp)
{
    if (!root)
        return NULL;
    (*cmp) += 1;
    if (!strcmp(root->data, data))
        return root;
    if (strcmp(root->data, data) < 0)
        return find_cmp(root->right, data, cmp);
    else
        return find_cmp(root->left, data, cmp);
}

int find_file_cmp(FILE *f, char *data, int *cmp)
{
    rewind(f);
    int i = 0;
    char buf[MAX_WORD_LEN];
    while (fgets(buf, sizeof(buf), f))
    {
        (*cmp) += 1;
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = '\0';
        if (!strcmp(buf, data))
        {
            rewind(f);
            return i;
        }
        i++;
    }
    rewind(f);
    return -1;
}

void del_file_cmp(FILE *f, char *data, int *cmp)
{
    rewind(f);
    char **words = read_file(f);
    int i, n = file_len(f);
    for (i = 0; i < n; i++)
    {
        (*cmp) += 1;
        if (!strcmp(words[i], data))
            break;
    }
    if (i < n)
    {
        for (int j = i; j < n - 1; j++)
            strcpy(words[j], words[j + 1]);
        rewind(f);
        for (int j = 0; j < n - 1; j++)
            fprintf(f, "%s\n", words[j]);
        rewind(f);
    }
}