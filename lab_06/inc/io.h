#ifndef IO_H
#define IO_H

#include "../inc/menu.h"
#include <string.h>

#define MAX_WORD_LEN 50

typedef struct tree_node
{
    char data[MAX_WORD_LEN];
    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

tree_node_t *create_node(char *data);
tree_node_t *insert(tree_node_t *root, tree_node_t *to_insert);
void node_to_dot(tree_node_t *tree, void *param);
void btree_apply_pre(tree_node_t *root, void *arg);
void btree_export_to_dot(FILE *f, tree_node_t *tree);

#endif