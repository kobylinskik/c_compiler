#include<stdlib.h>
#include<string.h>
typedef struct ast {
    char * expr;
    struct ast ** children;
    int children_count;
} ast_t;

ast_t * create_node (char * expr, ast_t ** node_array, int children_count) {
    ast_t * node = malloc(sizeof(ast_t));
    node->expr = malloc(sizeof(char *));
    strcpy(node->expr, expr);
    if(children_count != 0) {
        node->children = malloc(children_count*sizeof(ast_t));
        for (int i=0; i<children_count; i++) {
            node->children[i] = node_array[i];
        }
        node->children_count = children_count;
    }    
    return node;
}

typedef struct stack {
    ast_t * value;
    struct stack * next;
} stack_t;

ast_t * pop (stack_t ** stack) {
    ast_t * ret_val = (*stack)->value;
    stack_t * temp = (*stack)->next;
    free(*stack);
    *stack = temp;
    return ret_val;
}

void push_node (stack_t ** top, ast_t * val) {
    stack_t * temp;
    temp = malloc(sizeof(stack_t));
    temp->value = val;
    temp->next = *top;
    *top = temp;
}

void push_string (stack_t ** top, char * val) {
    ast_t * node = create_node(val, NULL, 0);
    push_node(top, node); 
}

void push_char (stack_t ** top, char val) {
    char * str = malloc(sizeof(char *));
    str[0] = val;
    str[1] = '\0';
    push_string(top, str);
}