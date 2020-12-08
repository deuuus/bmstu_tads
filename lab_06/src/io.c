#include "../inc/io.h"

tree_node_t *create_node(char *data)
{
    tree_node_t *new_node = malloc(sizeof(tree_node_t));
    if (new_node)
    {
        strcpy(new_node->data, data);
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

tree_node_t *insert(tree_node_t *root, tree_node_t *to_insert)
{
    if (!root)
        return to_insert;
    if (strcmp(root->data, to_insert->data) <= 0)
        root->left = insert(root->left, to_insert);
    else
        root->right = insert(root->right, to_insert);
    return root;
}

void node_to_dot(tree_node_t *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->data, tree->left->data);

    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->data, tree->right->data);
}

void btree_apply_pre(tree_node_t *root, void *arg)
{
    if (root == NULL)
        return;
    node_to_dot(root, arg);
    btree_apply_pre(root->left, arg);
    btree_apply_pre(root->right, arg);
}

void btree_export_to_dot(FILE *f, tree_node_t *tree)
{
    fprintf(f, "digraph Graph {\n");

    btree_apply_pre(tree, f);

    fprintf(f, "}\n");
}