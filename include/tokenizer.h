#ifndef __TOKENIZER_H
#define __TOKENIZER_H

enum TokenType {
    END_OF_FILE,
    FUNCTION_START,
    FUNCTION_END,
    SYMBOL,
    INT,
    FLOAT,
    CHAR,
    STRING,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    GREATER_THAN,
    LESS_THAN,
    GREATER_THAN_OR_EQUAL_TO,
    LESS_THAN_OR_EQUAL_TO
};

typedef struct {
    enum TokenType token_type;
    char* value;
} Token;

static char* source;
static int token_counter;
char* peek_range(int);
Token* tokenize(char*);

#endif