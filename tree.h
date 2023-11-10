#ifndef BTREE_H
#define BTREE_H
#define MAX_KEYS 4
// tree DE sequence DO 4

typedef struct knot {
    int total;
    int key[MAX_KEYS];
    struct knot* children[MAX_KEYS + 1];
    struct knot* father;
} Knot;

typedef struct b_tree {
    Knot* root;
    int sequence;
} BTree;

BTree* createTree();

Knot* createKnot();

void split(BTree* tree, Knot* knot);

void output(BTree* tree, int key);

void merge(BTree* tree, Knot* knot, int index);

void remove_key(Knot* knot, int key, int index);

void remove_recursive(BTree* tree, Knot* knot, int key);

void remove_key_tree(BTree* tree, int key);

void remove(BTree* tree, int key);

void print2D_functional(Knot *knot, int space, int parent_key);

void print2D(BTree *tree);

#endif