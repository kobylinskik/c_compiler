//#include "../structures.h"
//#include"../lexer/lexer.h"
#include "../parser/parser.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
    printf("%s\n", argv[1]);
    FILE * fp;
    fp = fopen(argv[1], "r");
    ast_t * tree = generate_tree(lex(fp));
    while (tree != NULL) {
        printf("Expr: %s\n", tree->expr);
        if (tree->children != NULL && strcmp(tree->children[0]->expr, "param_list") != 0){
            tree = tree->children[0];
        } else if (tree->children[1] != NULL) {
            tree = tree->children[1];
        }
    }
}