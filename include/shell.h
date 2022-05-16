#ifndef __SHELL_H
#define __SHELL_H

#include "tokenizer.h"

static int line_number;

void print_to_shell(char*);
void print_error(char*);
void print_tokens(Token*);

char* token_as_str(Token*);
char* token_array_as_str(Token*);

#endif