#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

int main(int argc, char **argv){
    FILE *fp;
    fp = fopen("./text", "r+");
    //char * buf = malloc(10 * sizeof(char *));
    //char * buf2 = malloc(sizeof(char *));
    char ** result = malloc(20 * sizeof(char **));
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
    result[j][k] = '\0';

    for (int l = 0; l < j; l++) {
        printf("Result[%d]: %s\n", l, result[l]);
    }
    return 0;
}