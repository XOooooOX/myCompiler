//
// Created by M.Ghelichkhani on 5/7/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "codegen.h"

#define SQUARE(x) ((x) * (x))

extern Token *token;


int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "usage: %s <expr>\n", argv[0]);
        exit(1);
    }

    tokenize(argv[1]);

    Node *node = expr();

    // چاپ کد اسمبلی استاندارد
    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");

    gen(node);

    // نتیجه نهایی توی stack هست، بیار تو rax و return کن
    printf("  pop rax\n");
    printf("  ret\n");

//    printf("You are in function: %s and line: %d\n", __func__,__LINE__);
//
//    int a = SQUARE(3);
//    printf("output of square macro:%d\n",a);
    return 0;
}
