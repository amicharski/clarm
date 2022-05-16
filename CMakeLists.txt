cmake_minimum_required(VERSION 3.21)
project(clarm C)

set(CMAKE_C_STANDARD 23)

add_executable(clarm core/main.c core/tokenizer.c core/shell.c tests/tokenizer_test.c tests/test.c)
