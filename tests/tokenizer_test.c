#include <stdio.h>
#include "tokenizer_test.h"
#include "test.h"
#include "../include/shell.h"

void test_1(){
    Token* tokens = tokenize("(");
    assert_equals(token_array_as_str(tokens), "(1, (null))");
}

// BUG: print_tokens in test_2 prints absolutely nothing
void test_2(){
    Token* tokens = tokenize("()");
    printf("hi\n");
    print_tokens(tokens);
    printf("bye\n");
    assert_equals(token_array_as_str(tokens), "(1, (null))(2, (null))");
}