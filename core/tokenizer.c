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

bool consume_int(){
    int j = 0;
    consumed_value = malloc(32);
    do {
        consumed_value[j] = source[i];
        j++;
    } while(is_digit(source[++i]));
    consumed_value[j] = '\0';
    if(is_alpha(source[--i])) return false;
    return true;
}

bool consume_symbol(){
    int j = 0;
    consumed_value = calloc(32, 4);
    do {
        consumed_value[j] = source[i];
        j++;
    } while(is_symbolic(source[++i]));
    consumed_value[j] = '\0';
    --i;
    if(debug) printf("\nidentifier: %s\n", consumed_value);
    return true;
}

bool consume_string(){
    int j = 0;
    consumed_value = calloc(32, 4);
    do {
        consumed_value[j] = source[i];
        j++;
    } while(is_stringable(source[++i]));
    consumed_value[j] = '\0';
    --i;
    if(debug) printf("\nidentifier: %s\n", consumed_value);
    return true;
}

void insert_token(enum TokenType token, char* name){
    tokens[token_counter].token_type = token;
    tokens[token_counter++].value = NULL;
    if(debug)   print_to_shell(name);
}

void insert_token_val(enum TokenType token, char* value, char* name){
    tokens[token_counter].token_type = token;
    tokens[token_counter++].value = value;
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
                if(consume_string()){
                    insert_token_val(STRING, consumed_value, "STRING");
                }
            default:
                if(is_digit(ch)){
                    consume_int();
                    if(ch == '.'){
                        if(consume_int()){
                            insert_token_val(FLOAT, consumed_value, "FLOAT");
                        }
                    } else {
                        insert_token_val(INT, consumed_value, "INT");
                    }
                } else if(is_symbolic(ch)){
                    consume_symbol();
                    insert_token_val(SYMBOL, consumed_value, "SYMBOL");
                }
                break;
        }
    } while(sourceCode[i++] != '\0');
    tokens[token_counter++].token_type = END_OF_FILE;
    if(debug) print_to_shell("END_OF_FILE");
    return tokens;
}