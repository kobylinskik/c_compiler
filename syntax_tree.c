#include<stdlib.h>
#include<stdio.h>
typedef struct ast {
    char * expr;
    struct ast ** children;
    int children_count;
} ast_t;

ast_t * create_node (char * expr, ast_t ** node_array, int children_count) {
    ast_t * node = malloc(sizeof(ast_t));
    node->expr = expr;
    if(children_count != 0) {
        node->children = malloc(children_count*sizeof(ast_t));
        for (int i=0; i<children_count; i++) {
            node->children[i] = node_array[i];
        }
        node->children_count = children_count;
    }    
    return node;
}

int main(){ 
    char * expr1 = "abcde";
    ast_t * node1 = create_node(expr1, NULL, 0);
    char * expr2 = "qwe";
    ast_t * node2 = create_node(expr2, NULL, 0);    
    char * expr3 = "zxc";
    ast_t * children[2] = {node1, node2};
    ast_t * node3 = create_node(expr3, children, 2);
    printf("%s\n", node3->children[0]->expr);
    printf("%s\n", node3->children[1]->expr);
    return 0;
}