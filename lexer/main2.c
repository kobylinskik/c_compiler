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
    char * buf = malloc(10 * sizeof(char *));
    //char * buf2 = malloc(sizeof(char *));
    char ** result = malloc(sizeof(char **));
    char file_char;
    int a;
    for (a = 0; file_char != EOF; a++) {
        file_char = fgetc(fp);
        buf[a] = file_char;
        //printf("%d\n", i);
    }
    buf[a] = '\0';

    //const char * buf = buf1;
    printf("%s\n", buf);
    int j = 0;
    int k = 0;

    result[j] = malloc(sizeof(char *));

    for (int i=0; i <= a; i++) {
        //printf("%d\n", i);
        if(is_whitespace(buf[i])) {
            if(result[j][0] != '\0') {
                result[j][k] = '\0';
                j++;
                k = 0;
                result[j] = malloc(sizeof(char *));
            }            
        } else if(is_special_char(buf[i])) {
            if(result[j][0] != '\0') {
                result[j][k] = '\0';
                j++;
                k = 0;
                result[j] = malloc(sizeof(char *));
            }           
            result[j][0] = buf[i];
            result[j][1] = '\0';
            j++;
            k = 0;
            result[j] = malloc(sizeof(char *));
        } else {
            result[j][k] = buf[i];
            k++;
        }
    }

    printf("%s\n", buf);
/*
    for (int i = 0; buf1[i] != EOF; i++) {
        printf("Processing character: %c\n", buf1[i]);
        if(is_whitespace(buf1[i])) {
            buf2[j] = '\0';
            printf("Encountered a space character. Buffer: %s\n", buf2);            
            if(buf2[0]!='\0'){
                result[k] = malloc(sizeof(char *));
                strcpy(result[k], buf2);
                buf2[0] = '\0';
                j = 0;
                k++;
            }           
        } else if (is_special_char(buf1[i])){
            buf2[j] = '\0';    
            printf("Encountered a special character. Buffer: %s\n", buf2);                    
            if(buf2[0]!='\0'){
                result[k] = malloc(sizeof(char *));
                strcpy(result[k], buf2);
                buf2[0] = '\0';
                j = 0;
                k++;
            } else {
                printf("Empty buffer\n");
            }
            buf2[0] = buf1[i];
            buf2[1] = '\0';
            result[k] = malloc(sizeof(char*));
            strcpy(result[k], buf2);
            buf2[0] = '\0';
            j = 0;
            k++;
        } else {            
            buf2[j] = buf1[i];
            j++;
        }
    }
*/
    printf("k: %d\n", j);
    for (int l = 0; l < j; l++) {
        printf("Result[%d]: %s\n", l, result[l]);
    }
    return 0;
}