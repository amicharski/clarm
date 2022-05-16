#include "tokenizer_test.h"
#include "test.h"

void test_1(){
    assert_token_equals("(", "(1, (null))");
    assert_token_equals("()", "(1, (null))(2, (null))");
}

void test_2(){
}
// Issues:
// - Rebuild the consume_int() function
void test_3(){
    assert_token_equals("(+ 3 5)", "(1, (null))(8, (null))(4, 3)(4, 5)(2, (null))");
    assert_token_equals("(- 15 7)", "(1, (null))(9, (null))(4, 15)(4, 7)(2, (null))");
    assert_token_equals("(* 6 10)", "(1, (null))(10, (null))(4, 6)(4, 10)(2, (null))");
    assert_token_equals("(/ 27 3)", "(1, (null))(11, (null))(4, 27)(4, 3)(2, (null))");
    assert_token_equals("(* 5.5 2)", "(1, (null))(10, (null))(5, 5.5)(4, 2)(2, (null))");
}

void test_4(){

}

void test_5(){
}