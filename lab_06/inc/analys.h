#ifndef ANALYS_H
#define ANALYS_H

#include "../inc/tree.h"
#include "../inc/hash.h"
#include "inttypes.h"
#include <assert.h>
#include "../inc/file.h"

void analys(void);
void analys_cycle(FILE *fdata, FILE *file, int size);
void mem_analys(void);
void analys_del(tree_node_t *root, tree_node_t *broot, char *data);
uint64_t tick(void);

#endif