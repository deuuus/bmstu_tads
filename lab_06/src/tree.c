#include "../inc/tree.h"

tree_node_t *read_bin(FILE *f)
{
    char str[MAX_WORD_LEN + 1];
    tree_node_t *root = NULL, *node;
    while (fgets(str, sizeof(str), f))
    {
        if (str[strlen(str) - 1] == '\n')
            str[strlen(str) - 1] = '\0';
        if (!strlen(str))
        {
            free_tree(root);
            return NULL;
        }
        node = create(str);
        root = insert(root, node);
    }
    if (!feof(f))
    {
        free_tree(root);
        return NULL;
    }
    else
        return root;
}

tree_node_t *make_bal_tree(FILE *f)
{
    char buf[MAX_WORD_LEN];
    tree_node_t *root = NULL, *node;
    while (fgets(buf, sizeof(buf), f))
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = '\0';
        node = create(buf);
        root = avl_insert(root, node);
    }
    return root;
}

tree_node_t *create(char *data)
{
    tree_node_t *new = malloc(sizeof(tree_node_t));
    if (new)
    {
        strcpy(new->data, data);
        new->left = NULL;
        new->right = NULL;
    }
    return new;
}

tree_node_t *find(tree_node_t *root, char *data)
{
    if (!root)
        return NULL;
    if (!strcmp(root->data, data))
        return root;
    if (strcmp(root->data, data) < 0)
        return find(root->right, data);
    else
        return find(root->left, data);
}

tree_node_t *avl_insert(tree_node_t *root, tree_node_t *to_insert)
{
    if (!root)
        return to_insert;
    if (strcmp(to_insert->data, root->data) <= 0)
        root->left = avl_insert(root->left, to_insert);
    else
        root->right = avl_insert(root->right, to_insert);
    return balance(root);
}

tree_node_t *insert(tree_node_t *root, tree_node_t *to_insert)
{
    if (!root)
        return to_insert;
    if (strcmp(to_insert->data, root->data) <= 0)
        root->left = insert(root->left, to_insert);
    else
        root->right = insert(root->right, to_insert);
    return root;
}

tree_node_t *avl_del(tree_node_t *root, char *data)
{
    if (!root)
        return NULL;
    if (strcmp(data, root->data) < 0)
        root->left = avl_del(root->left, data);
    else if (strcmp(data, root->data) > 0)
        root->right = avl_del(root->right, data);
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

tree_node_t *del(tree_node_t *root, char *data)
{
    if (!root)
        return NULL;
    if (strcmp(data, root->data) < 0)
        root->left = del(root->left, data);
    else if (strcmp(data, root->data) > 0)
        root->right = del(root->right, data);
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

tree_node_t *remove_avl_min(tree_node_t *root)
{
    if (!root->left)
        return root->right;
    root->left = remove_min(root->left);
    return balance(root);
}

tree_node_t *remove_min(tree_node_t *root)
{
    if (!root->left)
        return root->right;
    root->left = remove_min(root->left);
    return root;
}

tree_node_t *find_min(tree_node_t *root)
{
    if (root->left)
        return find_min(root->left);
    return root;
}

tree_node_t *balance(tree_node_t *node)
{
    if (balance_factor(node) == 2)
    {
        if (balance_factor(node->right) < 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    if (balance_factor(node) == -2)
    {
        if (balance_factor(node->left) > 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    return node;
}

int balance_factor(tree_node_t *node)
{
    if (!node)
        return 0;
    return height(node->right) - height(node->left);
}

int height(tree_node_t *root)
{
    if (!root)
        return 0;
    int left, right;
    left = height(root->left);
    right = height(root->right);
    if (left > right)
        return left + 1;
    else
        return right + 1;
}

// void update_height(tree_node_t *node)
// {
//     int hl = height(node->left), hr = height(node->right);
//     if (hl > hr)
//         node->height = hl;
//     else
//         node->height = hr;
// }

tree_node_t *rotate_right(tree_node_t *node)
{
    tree_node_t *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    return temp;
}

tree_node_t *rotate_left(tree_node_t *node)
{
    tree_node_t *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    return temp;
}

void node_to_dot(tree_node_t *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->data, tree->left->data);

    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->data, tree->right->data);
}

void tree_apply_pre(tree_node_t *root, void *arg)
{
    if (root == NULL)
        return;
    node_to_dot(root, arg);
    tree_apply_pre(root->left, arg);
    tree_apply_pre(root->right, arg);
}

void tree_export_to_dot(FILE *f, tree_node_t *tree)
{
    fprintf(f, "digraph G{\n");

    tree_apply_pre(tree, f);

    fprintf(f, "}");
}

int read_name(FILE **f)
{
    char name[MAX_WORD_LEN + 1];
    printf("\nВведите название файла, в котором содержится информация: ");
    if (!fgets(name, sizeof(name), stdin))
    {
        printf("\nОшибка: имя файла записано некорректно. Возможно, вы ввели пустую строку или\n"
        "превысили максимально допустимую длину названия файла(50 символов). Попробуйте еще раз.\n");
        return ERR_READ;
    }
    if (name[strlen(name) - 1] == '\n')
        name[strlen(name) - 1] = '\0';
    *f = fopen(name, "r");
    if (!(*f))
    {
        printf("\nОшибка: невозможно открыть файл с таким названием.\n"
        "Внимательно проверьте название файла и попробуйте еще раз.\n");
        return ERR_OPEN;
    }
    return EXIT_SUCCESS;
}

int read_int(int *n)
{
    if (scanf("%d", n) != 1 || *n <= 0)
    {
        printf("\nОшибка: должно быть введено целое положительное число.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int read_word(char *data)
{
    printf("\nВведите слово, которое необходимо удалить: ");
    if (scanf("%s", data) != 1 || getchar() != '\n')
    {
        printf("\nОшибка: слово записано некорректно. Возможно, вы ввели пустую строку или\n"
        "превысили максимально допустимую длину(50 символов). Попробуйте еще раз.\n");
        return ERR_READ;
    }
    if (data[strlen(data) - 1] == '\n')
        data[strlen(data) - 1] = '\0';
    return EXIT_SUCCESS;
}

void free_tree(tree_node_t *root)
{
    if (root == NULL)
    {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);

    free(root);
}