#include <stdio.h>
#include <stdlib.h>
#include "tree.cpp"

int main() {
    BTree* tree = NULL;
    tree = createTree();

    printf("Insere(+): 1\n");
	output(tree, 1);
    print2D(tree);
    printf("\n------------------------------------\n");

    printf("Insere(+): 15\n");
	output(tree, 15);
    print2D(tree);
    printf("\n------------------------------------\n");

    printf("Insere(+): 9\n");
    output(tree, 9);
    print2D(tree);
    printf("\n------------------------------------\n");

    printf("Remove(-): 15\n");
    remove(tree, 15);
    print2D(tree);
    printf("\n------------------------------------\n");

    printf("Remove(-): 9\n");
    remove(tree, 9);
    print2D(tree);
    printf("\n------------------------------------\n");

    printf("Insere(+): 12\n");
    output(tree, 12);
    print2D(tree);
    printf("\n------------------------------------\n");

    printf("Insere(+): 24\n");
    output(tree, 24);
    print2D(tree);
    printf("\n------------------------------------\n");

    printf("Insere(+): 10\n");
    output(tree, 10);
    print2D(tree);
    printf("\n------------------------------------\n");

    printf("Insere(+): 18\n");
    output(tree, 18);
    print2D(tree);
    printf("\n------------------------------------\n");

    printf("Insere(+): 7\n");
    output(tree, 7);
    print2D(tree);
    printf("\n------------------------------------\n");

    printf("Remove(-): 7\n");
    remove(tree, 7);
    print2D(tree);
    printf("\n------------------------------------\n");

    printf("Insere(+): 14\n");
    output(tree, 14);
    print2D(tree);
    printf("\n------------------------------------\n");

    printf("Insere(+): 20\n");
    output(tree, 20);
    print2D(tree);
    printf("\n------------------------------------\n");

    printf("Insere(+): 28\n");
    output(tree, 28);
    print2D(tree);
    printf("\n------------------------------------\n");

    printf("Insere(+): 30\n");
    output(tree, 30);
    print2D(tree);
    printf("\n------------------------------------\n");

    printf("- REMOVE: 1\n");
    remove(tree, 1);
    print2D(tree);

    return 0;
}