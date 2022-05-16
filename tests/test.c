#include <stdio.h>
#include <string.h>
#include "test.h"

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