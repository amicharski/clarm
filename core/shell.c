#include <stdio.h>
#include <stdlib.h>
#include "../include/shell.h"

static int line_number = 1;

void print_to_shell(char* text){
    printf("CLARM>>> %s\n", text);
}

void print_error(char* msg){
    printf("CLARMERROR (ERROR AT LINE %d)>>> %s", line_number, msg);
    exit(1);
}