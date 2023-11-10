#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

BTree* createTree() {
    BTree* newTree = (BTree*)malloc(sizeof(BTree));
    if (newTree == NULL) {
        printf("ERRO: árvore não alocada na memória\n");
        return NULL;
    }
    newTree->root = NULL;
    newTree->sequence = MAX_KEYS;
    return newTree;
}

Knot* createKnot() {
    int i;
    Knot* new_ = (Knot*)malloc(sizeof(Knot));
    if (new_ == NULL) {
        printf("ERRO: árvore não alocada na memória\n");
        return NULL;
    }
    new_->total = 0;
    for (i = 0; i <= MAX_KEYS; i++) {
        new_->children[i] = NULL;
    }
    new_->father = NULL;
    return new_;
}

void split(BTree* tree, Knot* knot) {
    int i, j;
    Knot* father = knot->father;
    Knot* new_ = createKnot();
    int medianIndex = (MAX_KEYS) / 2;
    int median = knot->key[medianIndex];

    for (i = medianIndex + 1, j = 0; i < MAX_KEYS; i++, j++) {
        new_->key[j] = knot->key[i];
        new_->children[j] = knot->children[i];
        if (new_->children[j] != NULL) {
            new_->children[j]->father = new_;
        }
        knot->key[i] = 0;
        knot->children[i] = NULL;
    }
    new_->children[j] = knot->children[i];
    if (new_->children[j] != NULL) {
        new_->children[j]->father = new_;
    }
    knot->children[i] = NULL;

    knot->total = medianIndex;
    new_->total = j;

    if (father == NULL) {
        father = createKnot();
        tree->root = father;
        father->children[0] = knot;
        knot->father = father;
    }

    int location = 0;
    while (location < father->total && father->key[location] < median) {
        location++;
    }

    for (i = father->total; i > location; i--) {
        father->key[i] = father->key[i - 1];
        father->children[i + 1] = father->children[i];
    }

    father->key[location] = median;
    father->children[location + 1] = new_;
    father->total++;
    new_->father = father;

    for(i=0; i<=knot->total; i++) {
        if(knot->children[i]) {
            knot->children[i]->father=knot;
        }
    }
    
    for(i=0; i<=new_->total; i++) {
        if(new_->children[i]) {
            new_->children[i]->father=new_;
        }
    }
}

void output(BTree* tree, int key) {
    Knot* knot = tree->root;
    if (knot == NULL) {
        knot = createKnot();
        knot->key[0] = key;
        knot->total = 1;
        tree->root = knot;
    } else {
        Knot* leaf = knot;
        while (1) {
            if (leaf -> total < MAX_KEYS) {
                int location = leaf -> total - 1;
                while (location >= 0 && leaf -> key[location] > key) {
                    leaf -> key[location + 1] = leaf -> key[location];
                    location--;
                }
                leaf -> key[location + 1] = key;
                leaf -> total++;
                break;
            } else {
                split(tree, leaf);
                leaf=leaf -> father;

                if(leaf == NULL){
                    leaf=tree -> root;
                }

                int location=0;

                while(location < leaf -> total && leaf -> key[location]< key){
                    location++;
                }

                if(location == leaf -> total || leaf -> key[location]> key){
                    leaf=leaf -> children[location];
                }else{
                    leaf=leaf -> children[location + 1];
                }
            }
        }
    }
}

void merge(BTree* tree, Knot* knot, int index) {
    int i;
    Knot* left = knot->children[index];
    Knot* right = knot->children[index + 1];

    // Move a key father[index] do nó atual para o nó da left
    left->key[left->total] = knot->key[index];
    left->total++;

    // Copia as key e children da right para a left
    for (i = 0; i < right->total; i++) {
        left->key[left->total] = right->key[i];
        left->children[left->total] = right->children[i];
        left->total++;
    }

    // Atualiza os children da right no nó atual
    for (i = index; i < knot->total - 1; i++) {
        knot->key[i] = knot->key[i + 1];
        knot->children[i + 1] = knot->children[i + 2];
    }

    knot->total--;

    free(right);
}

void remove_key(Knot* knot, int key, int index) {
    int i;
    for (i = index; i < knot->total - 1; i++) {
        knot->key[i] = knot->key[i + 1];
    }
    knot->total--;
}

void remove_recursive(BTree* tree, Knot* knot, int key) {
    int index = 0;
    int i;
    while (index < knot->total && knot->key[index] < key) {
        index++;
    }

    if (index < knot->total && knot->key[index] == key) {
        // A key está presente knot nó atual
        if (knot->children[index] != NULL) {
            // Se o nó tem children à left, substitua a key pela maior key no son à left
            Knot* pred = knot->children[index];
            while (pred->children[pred->total] != NULL) {
                pred = pred->children[pred->total];
            }
            int predecessor = pred->key[pred->total - 1];
            knot->key[index] = predecessor;
            remove_recursive(tree, pred, predecessor);
        } else {
            // Se o nó não tem children, simplesmente remova a key
            remove_key(knot, key, index);
        }
    } else {
        // A key não está no nó atual, então desça para o son apropriado
        Knot* son = knot->children[index];
        if (son == NULL) {
            // A key não está na árvore, saia
            return;
        }
        if (son->total == MAX_KEYS) {
            // Se o son tiver o número mínimo de key, tente equilibrá-lo
            if (index > 0 && knot->children[index - 1]->total > MAX_KEYS) {
                // Se o son à left tiver key extras, empreste uma key do father
                for (i = son->total; i > 0; i--) {
                    son->key[i] = son->key[i - 1];
                }
                son->key[0] = knot->key[index - 1];
                if (son->children[0] != NULL) {
                    for (i = son->total + 1; i > 0; i--) {
                        son->children[i] = son->children[i - 1];
                    }
                    son->children[0] = knot->children[index - 1]->children[knot->children[index - 1]->total];
                }
                knot->key[index - 1] = knot->children[index - 1]->key[knot->children[index - 1]->total - 1];
                knot->children[index - 1]->total--;
                son->total++;
            } else if (index < knot->total && knot->children[index + 1]->total > MAX_KEYS) {
                // Se o son à right tiver key extras, empreste uma key do father
                son->key[son->total] = knot->key[index];
                if (son->children[0] != NULL) {
                    son->children[son->total + 1] = knot->children[index + 1]->children[0];
                }
                knot->key[index] = knot->children[index + 1]->key[0];
                for (i = 0; i < knot->children[index + 1]->total - 1; i++) {
                    knot->children[index + 1]->key[i] = knot->children[index + 1]->key[i + 1];
                }
                if (knot->children[index + 1]->children[0] != NULL) {
                    for (i = 0; i < knot->children[index + 1]->total; i++) {
                        knot->children[index + 1]->children[i] = knot->children[index + 1]->children[i + 1];
                    }
                }
                knot->children[index + 1]->total--;
                son->total++;
            } else {
                // Nenhum dos children tem key extras, então funda-os
                if (index > 0) {
                    merge(tree, knot, index - 1);
                    index--;
                } else {
                    merge(tree, knot, index);
                }
                remove_recursive(tree, knot->children[index], key);
            }
        } else {
            // O son tem espaço suficiente, continue a remoção recursiva
            remove_recursive(tree, son, key);
        }
    }
}

void remove_key_tree(BTree* tree, int key) {
    Knot* root = tree->root;

    // Caso especial: se a root for a única key e for igual à key que estamos tentando remove
    if (root->total == 1 && root->key[0] == key) {
        tree->root = root->children[0];
        free(root);
    } else {
        remove_recursive(tree, root, key);
    }
}

void remove(BTree* tree, int key) {
    if (tree == NULL || tree->root == NULL) {
        return;
    }
    remove_key_tree(tree, key);

    // Se a root não tiver key, torne o son restante a nova root
    if (tree->root->total == 0) {
        Knot* new__root = tree->root->children[0];
        free(tree->root);
        tree->root = new__root;
    }
}

void print2D_functional(Knot *knot, int space, int parent_key) {
    int i;
    if (knot == NULL)
        return;
    space += 10;
    print2D_functional(knot->children[knot->total], space, knot->key[0]);
    printf("\n");
    for (i = 10; i < space; i++)
        printf(" ");
    if (space > 10) // Não imprime a key do father para a root
        printf("(father: %d) ", parent_key);
    printf("[");
    for(i = 0; i < knot->total; i++) {
        printf("%d", knot->key[i]);
        if (i < knot->total - 1)
            printf(", ");
    }
    printf("]\n");
    for(i = 0; i < knot->total; i++)
        print2D_functional(knot->children[i], space, knot->key[i]);
}

void print2D(BTree *tree) {
   print2D_functional(tree->root, 0, -1);
}