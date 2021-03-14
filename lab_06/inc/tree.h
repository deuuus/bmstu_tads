#ifndef TREE_H
#define TREE_H

#include "../inc/menu.h"
#include <string.h>

#define MAX_WORD_LEN 50

#define ERR_READ 1
#define ERR_OPEN 2
#define ERR_DATA 3

typedef struct tree_node
{
    char data[MAX_WORD_LEN];
    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

//Функции сбалансированного ДДП
tree_node_t *make_bal_tree(FILE *f);
tree_node_t *balance(tree_node_t *node);
tree_node_t *avl_insert(tree_node_t *root, tree_node_t *to_insert);
tree_node_t *avl_del(tree_node_t *root, char *data);
tree_node_t *remove_avl_min(tree_node_t *root);
int balance_factor(tree_node_t *node);
int height(tree_node_t *root);
//void update_height(tree_node_t *node);
tree_node_t *rotate_right(tree_node_t *node);
tree_node_t *rotate_left(tree_node_t *node);

//Функции обычного ДДП
tree_node_t *read_bin(FILE *f);
tree_node_t *insert(tree_node_t *root, tree_node_t *to_insert);
tree_node_t *del(tree_node_t *root, char *data);
tree_node_t *remove_min(tree_node_t *root);

//Общие функции
tree_node_t *create(char *data);
tree_node_t *find(tree_node_t *root, char *data);
tree_node_t *find_min(tree_node_t *root);
void free_tree(tree_node_t *root);
int read_name(FILE **f);
int read_word(char *data);
int read_int(int *n);

void node_to_dot(tree_node_t *tree, void *param);
void tree_apply_pre(tree_node_t *root, void *arg);
void tree_export_to_dot(FILE *f, tree_node_t *tree);

#endif