#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/shell.h"

static int line_number = 1;

void print_to_shell(char* text){
    printf("CLARM>>> %s\n", text);
}

void print_error(char* msg){
    printf("CLARMERROR (ERROR AT LINE %d)>>> %s", line_number, msg);
    exit(1);
}

void print_tokens(Token* tokens){
    int i = 0;
    while(tokens[i].token_type != END_OF_FILE){
        printf("(%d, %s)\n", tokens[i].token_type, tokens[i].value);
        i++;
    }
}

char* token_as_str(Token* token){
    char* str = malloc(sizeof(char) * 20);
    strcpy(str, "(");
    char* type = malloc(sizeof(char) * 2);
    snprintf(type, 2, "%u", token->token_type);
    strcat(str, type);
    strcat(str, ", ");
    char* value = malloc(sizeof(char) * 20);
    snprintf(value, 20, "%s", token->value);
    strcat(str, value);
    strcat(str, ")\0");
    return str;
}

char* token_array_as_str(Token* tokens){
    char *token_str = malloc(sizeof(&tokens) * sizeof(char));
    token_str[0] = '\0';
    int i = 0;
    while(tokens[i].token_type != END_OF_FILE){
        token_str = strcat(token_str, token_as_str(&tokens[i]));
        i++;
    }
    return token_str;
}