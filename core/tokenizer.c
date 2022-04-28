#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/tokenizer.h"
#include "../include/shell.h"

int i = 0;
char range_arr[40];
char* consumed_value;
Token* tokens;
bool debug = false;

char peek_next(){
    return source[i+1];
}

char* peek_range(int range){
    if(range > 40){
        printf("INTERNAL ERROR>>> RANGE CANNOT BE GREATER THAN 40");
        exit(2);
    }
    for(int j = 0; j < range; j++){
        range_arr[j] = source[i+j+1];
    }

    return (char *) range_arr;
}

Token* tokenize(char* sourceCode){
    source = sourceCode;
    tokens = malloc(1024);
    do {
        char ch = sourceCode[i];
        if(debug)   printf("\nch: %c\n", ch);
        switch(ch){
            case '(':
                tokens[token_counter++].token_type = LEFT_PAREN;
                if(debug) print_to_shell("LEFT PARENTHESIS");
                break;
            case ')':
                tokens[token_counter++].token_type = RIGHT_PAREN;
                if(debug) print_to_shell("RIGHT PARENTHESIS");
                break;
            case '[':
                tokens[token_counter++].token_type = LEFT_BRACKET;
                if(debug) print_to_shell("LEFT BRACKET");
                break;
            case ']':
                tokens[token_counter++].token_type = RIGHT_BRACKET;
                if(debug) print_to_shell("RIGHT BRACKET");
                break;
            case '{':
                tokens[token_counter++].token_type = LEFT_BRACE;
                if(debug) print_to_shell("LEFT BRACE");
                break;
            case '}':
                tokens[token_counter++].token_type = RIGHT_BRACE;
                if(debug) print_to_shell("RIGHT BRACE");
                break;
            case '^':
                tokens[token_counter++].token_type = CIRCUMFLEX;
                if(debug) print_to_shell("CIRCUMFLEX");
            case '@':
                tokens[token_counter++].token_type = COMMERCIAL_AT;
                if(debug) print_to_shell("COMMERCIAL AT");
            case '#':
                tokens[token_counter++].token_type = POUND;
                if(debug) print_to_shell("POUND");
            case '`':
                tokens[token_counter++].token_type = SYNTAX_QUOTE;
                if(debug) print_to_shell("SYNTAX QUOTE");
            case '~':
                if(peek_next() == '@'){
                    tokens[token_counter++].token_type = UNQUOTE_SPLICING;
                    if(debug) print_to_shell("UNQUOTE SPLICING");
                } else {
                    tokens[token_counter++].token_type = UNQUOTE;
                    if(debug) print_to_shell("UNQUOTE");
                }
        }
    } while(sourceCode[i++] != '\0');
    tokens[token_counter++].token_type = END_OF_FILE;
    tokens[token_counter++].value = consumed_value;
    if(debug) print_to_shell("EOF");
    return tokens;
}