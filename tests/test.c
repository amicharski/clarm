#include <stdio.h>
#include <string.h>
#include "test.h"
#include "../include/shell.h"

bool assert_equals(char* string1, char* string2){
    printf("String 1: %s\n", string1);
    printf("String 2: %s\n", string2);
    if(strcmp(string1, string2) == 0){
        printf("TRUE\n");
        return true;
    } else {
        printf("FALSE\n");
        return false;
    }
}

bool assert_token_equals(char* test_token, char* expected_token){
    return assert_equals(token_array_as_str(tokenize(test_token)), expected_token);
}