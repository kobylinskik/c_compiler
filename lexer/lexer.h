#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum token_type {type_declaration, return_keyword, identifier, semicolon, literal, open_brace, close_brace, open_parenthesis, close_parenthesis};

enum token_type get_token_type (char * str) {
    if (strcmp(str, "int") == 0) {
        return type_declaration;
    } else if (strcmp(str, "return") == 0){
        return return_keyword;
    } else if (strcmp(str, "(") == 0) {
        return open_parenthesis;
    } else if (strcmp(str, ")") == 0) {
        return close_parenthesis;
    } else if (strcmp(str, "{") == 0) {
        return open_brace;
    } else if (strcmp(str, "}") == 0) {
        return close_brace;
    } else if (strcmp(str, ";") == 0) {
        return semicolon;
    } else {
        return identifier;
    }
}

typedef struct token {
    enum token_type type;
    char * value;
} token_t;

token_t * create_token (char * str) {
    token_t * token = malloc(sizeof(token));
    token->value = str;
    token->type = get_token_type(str);
    return token;
}

_Bool is_whitespace(char c) {
    return c == ' ' 
        || c == '\n'
        || c == '\t'
        || c == '\v'
        || c == '\r'
        || c == EOF;
}

_Bool is_special_char(char c) {
    return c == '{' 
        || c == '}'
        || c == '('
        || c == ')'
        || c == ';';
}

token_t ** lex(FILE *fp) {
    char ** result = malloc(30 * sizeof(char **));
    char file_char;

    int j = 0;
    int k = 0;

    result[j] = malloc(sizeof(char *));

    do {
        file_char = fgetc(fp);
        if(is_whitespace(file_char)) {
            if(result[j][0] != '\0') {
                result[j][k] = '\0';
                j++;
                k = 0;
                result[j] = malloc(sizeof(char *));
            }
        } else if(is_special_char(file_char)) {
            if(result[j][0] != '\0') {
                result[j][k] = '\0';
                j++;
                k = 0;
                result[j] = malloc(sizeof(char *));
            }
            result[j][0] = file_char;
            result[j][1] = '\0';
            j++;
            k = 0;
            result[j] = malloc(sizeof(char *));
        } else {
            result[j][k] = file_char;
            k++;
        }
    } while (file_char != EOF);

    

    //result[j][k] = '\0';
    result[j] = EOF;
    for(int i=0; result[i]!=EOF; i++){
        printf("Result[%d]: %s\n", i, result[i]);
    }
    token_t ** tokens = malloc(10 * sizeof(token_t *));
    for(int i=0; result[i]!=EOF; i++) {
        tokens[i] = create_token(result[i]);
    } 
    return tokens;
}