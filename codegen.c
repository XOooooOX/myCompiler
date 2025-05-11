//
// Created by M.Ghelichkhani on 5/11/2025.
//
// codegen.c

#include <stdio.h>
#include "parser.h"

// تولید کد برای نود
void gen(Node *node) {
    if (node->kind == ND_NUM) {
        printf("  push %d\n", node->val);
        return;
    }

    gen(node->lhs);
    gen(node->rhs);

    printf("  pop rdi\n");  // rhs
    printf("  pop rax\n");  // lhs

    switch (node->kind) {
        case ND_ADD:
            printf("  add rax, rdi\n");
            break;
        case ND_SUB:
            printf("  sub rax, rdi\n");
            break;
        case ND_MUL:
            printf("  imul rax, rdi\n");
            break;
        case ND_DIV:
            printf("  cqo\n");         // گسترش rax به rdx:rax برای idiv
            printf("  idiv rdi\n");    // تقسیم rax بر rdi
            break;
    }

    printf("  push rax\n");
}
