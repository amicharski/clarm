#include <stdio.h>
#include "tokenizer_test.h"
#include "test.h"
#include "../include/shell.h"

void test_1(){
    Token* tokens = tokenize("(");
    assert_equals(token_array_as_str(tokens), "(1, (null))");
}

void test_2(){
    Token* tokens = tokenize("()");
    assert_equals(token_array_as_str(tokens), "(1, (null))(2, (null))");
}

void test_3(){
    Token* tokens = tokenize("(+ 3 5)");
    assert_equals(token_array_as_str(tokens), "(1, (null))(8, (null))(4, 3)(4, 5)(2, (null))");
}