#include"../structures.h"
#include"../lexer/lexer.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

_Bool is_type_declaration(token_t * token) {
    return token->type == type_declaration;
}

_Bool is_identifier(token_t * token) {
    return token->type == identifier;
}

_Bool is_open_parenthesis(token_t * token) {
    return token->type == open_parenthesis;
}

_Bool is_close_parenthesis(token_t * token) {
    return token->type == close_parenthesis;
}

_Bool is_open_brace(token_t * token) {
    return token->type == open_brace;
}

_Bool is_close_brace(token_t * token) {
    return token->type == close_brace;
}

_Bool is_return_keyword(token_t * token) {
    return token->type == return_keyword;
}

_Bool is_literal(token_t * token) {
    return token->type == literal;
}

_Bool is_semicolon(token_t * token) {
    return token->type == semicolon;
}

ast_t * parse_param(token_t ** token_arr, int * index) {
    if (!is_type_declaration(token_arr[*index])) {
        printf("Expected type declaration, got: %s at %d\n", token_arr[*index]->value, *index);
        exit(1);
    }
    char * type = malloc(sizeof(char *));
    strcpy(type, token_arr[*index]->value);
    (*index)++;
    if (!is_identifier(token_arr[*index])) {
        printf("Expected identifier, got: %s at %d\n", token_arr[*index]->value, *index);
        exit(1);
    }
    char * id = malloc(sizeof(char *));
    strcpy(id, token_arr[*index]->value);
    (*index)++;
    ast_t * id_node = create_node(id, NULL, 0);
    return create_node(type, &id_node, 1);
}

ast_t * parse_params_list(token_t ** token_arr, int * index) {
    int param_count = 0;
    ast_t ** params = malloc(10 * sizeof(ast_t *));
    (*index)++;
    while (!is_close_parenthesis(token_arr[*index])) {    
        params[param_count] = parse_param(token_arr, index);
        param_count++;
    }
    (*index)++;
    return create_node("param_list", params, param_count);
}

ast_t * parse_statement(token_t ** token_arr, int * index) {
    if (!is_return_keyword(token_arr[*index])) {
        printf("Expected return keyword, got: %s at %d\n", token_arr[*index]->value, *index);
        exit(1);
    }
    char * ret_key = malloc(sizeof(char *));
    strcpy(ret_key, token_arr[*index]->value);
    (*index)++;
    if (!is_identifier(token_arr[*index])) {
        printf("Expected a literal, got: %s", token_arr[*index]->value);
        exit(1);
    }
    char * ret_val = malloc(sizeof(char *));
    strcpy(ret_val, token_arr[*index]->value);
    (*index)++;
    if (!is_semicolon(token_arr[*index])) {
        printf("Expected a semicolon, got: %s", token_arr[*index]->value);
        exit(1);
    }
    (*index)++;
    ast_t * ret_val_ast = create_node(ret_val, NULL, 0);
    ast_t * ret_children[1] = {ret_val_ast};
    return create_node(ret_key, ret_children, 1);
}

ast_t * parse_statements_list(token_t ** token_arr, int * index) {
    int statement_count = 0;
    ast_t ** statements = malloc(10 * sizeof(ast_t *));
    (*index)++;
    while (!is_close_brace(token_arr[*index])) {    
        statements[statement_count] = parse_statement(token_arr, index);
        statement_count++;
    }
    (*index)++;
    return create_node("stmt_list", statements, statement_count);
}

ast_t * parse_function(token_t ** token_arr, int * index) {
    printf("Parse function; token_arr[%d] = %s\n", *index, token_arr[*index]->value);
    if (!is_type_declaration(token_arr[*index])) {
        printf("Expected type declaration, got: %s at %d\n", token_arr[*index]->value, *index);
        exit(1);
    }
    char * type = token_arr[*index]->value;
    (*index)++;    
    if (!is_identifier(token_arr[*index])) {
        printf("Expected identifier, got: %s at %d\n", token_arr[*index]->value, *index);
        exit(1);
    }
    char * id = token_arr[*index]->value;
    (*index)++;
    if (!is_open_parenthesis(token_arr[*index])) {
        printf("Expected open parenthesis, got: %s at %d\n", token_arr[*index]->value, *index);
        exit(1);
    }
    ast_t * param_list = parse_params_list(token_arr, index);
    if (!is_open_brace(token_arr[*index])) {
        printf("Expected open brace, got: %s at %d\n", token_arr[*index]->value, *index);
        exit(1);
    }  
    ast_t * statement_list = parse_statements_list(token_arr, index);
    ast_t * func_children[2] = {param_list, statement_list};
    ast_t * id_tree = create_node(id, func_children, 2);
    return create_node(type, &id_tree, 1);
}

ast_t * generate_tree(token_t ** tokens) {
    int index = 0;
    ast_t * tree = parse_function(tokens, &index);
}
/*
int main() {
    FILE * fp;
    fp = fopen("./text", "r+");
    token_t ** result = lex(fp);
    for (int i = 0; result[i] != NULL; i++) {
        printf("Result[%d]: %s\n", i, result[i]->value);
        if(is_type_declaration(result[i])) {
            printf("I've found a type declaration!\n");

        }
    }
    printf("Loop over!\n");
    int index = 0;
    ast_t * tree = parse_function(result, &index);
    while (tree != NULL) {
        printf("Expr: %s\n", tree->expr);
        if (tree->children != NULL && strcmp(tree->children[0]->expr, "param_list") != 0){
            tree = tree->children[0];
        } else if (tree->children[1] != NULL) {
            tree = tree->children[1];
        }
    }    
    //printf("Statements list: %s, return: %s, return child: %s\n", tree->expr, tree->children[0]->expr, tree->children[0]->children[0]->expr);
    return 0;
}*/