#ifndef __TOKENIZER_H
#define __TOKENIZER_H

enum TokenType {
    END_OF_FILE = 0,
    FUNCTION_START = 1,
    FUNCTION_END = 2,
    SYMBOL = 3,
    INT = 4,
    FLOAT = 5,
    CHAR = 6,
    STRING = 7,
    ADD = 8,
    SUBTRACT = 9,
    MULTIPLY = 10,
    DIVIDE = 11,
    GREATER_THAN = 12,
    LESS_THAN = 13,
    GREATER_THAN_OR_EQUAL_TO = 14,
    LESS_THAN_OR_EQUAL_TO = 15
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