cmake_minimum_required(VERSION 3.23)
project(myCompiler)

set(CMAKE_C_STANDARD 99)

add_executable(myCompiler main.c lexer.h lexer.c parser.h parser.c codegen.c codegen.h)
