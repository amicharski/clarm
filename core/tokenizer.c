#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/tokenizer.h"
#include "../include/shell.h"

int i = 0;
char range_arr[40];
char* consumed_value;
Token* tokens;
bool debug = true;

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

bool is_digit(char ch){
    return ch >= '0' && ch <= '9';
}

bool is_alpha(char ch){
    return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
}

bool is_alphanumeric(char ch){
    return is_alpha(ch) || is_digit(ch);
}

bool is_symbolic(char ch){
    return is_alphanumeric(ch) || ch == '-' || ch == '+' || ch == '*' || ch == '!'
    || ch == '\'' || ch == '?' || ch == '<' || ch == '>' || ch == '=' || ch == '_';
}

bool is_stringable(char ch){
    return ch >= ' ' && ch <= '~' && ch != '\\' && ch != '"';
}

void insert_token(enum TokenType token, char* name){
    tokens[token_counter++].token_type = token;
    if(debug)   print_to_shell(name);
}

Token* tokenize(char* sourceCode){
    source = sourceCode;
    tokens = malloc(1024);
    do {
        char ch = sourceCode[i];
        if(debug)   printf("\nch: %c\n", ch);
        switch(ch){
            case '(':
                insert_token(FUNCTION_START, "FUNCTION START");
                break;
            case ')':
                insert_token(FUNCTION_END, "FUNCTION END");
                break;
            case '+':
                insert_token(ADD, "ADD");
                break;
            case '-':
                insert_token(SUBTRACT, "SUBTRACT");
                break;
            case '*':
                insert_token(MULTIPLY, "MULTIPLY");
                break;
            case '/':
                insert_token(DIVIDE, "DIVIDE");
                break;
            case '\\':
                insert_token(CHAR, "CHAR");
                ch += 2;
            case '>':
                if(peek_next() == '='){
                    insert_token(GREATER_THAN_OR_EQUAL_TO,
                                 "GREATER_THAN_OR_EQUAL_TO");
                    ch += 2;
                } else {
                    insert_token(GREATER_THAN, "GREATER_THAN");
                    ch++;
                }
            case '<':
                if(peek_next() == '='){
                    insert_token(LESS_THAN_OR_EQUAL_TO,
                                 "LESS_THAN_OR_EQUAL_TO");
                    ch += 2;
                } else {
                    insert_token(LESS_THAN, "LESS_THAN");
                    ch++;
                }
            case '"':
                while(is_stringable(ch))    ch++;
                if(peek_next() == '"'){
                    ch++;
                    insert_token(STRING, "STRING");
                }
            default:
                if(is_digit(ch)){
                    while(is_digit(ch++)){}
                    if(peek_next() == '.'){
                        if(is_digit(ch)){
                            while(is_digit(ch++)){}
                            insert_token(FLOAT, "FLOAT");
                        }
                    } else {
                        insert_token(INT, "INT");
                    }
                } else if(is_symbolic(ch)){
                    while(is_symbolic(ch++)){}
                    insert_token(SYMBOL, "SYMBOL");
                }
                break;
        }
    } while(sourceCode[i++] != '\0');
    tokens[token_counter++].token_type = END_OF_FILE;
    tokens[token_counter++].value = consumed_value;
    if(debug) print_to_shell("END_OF_FILE");
    return tokens;
}