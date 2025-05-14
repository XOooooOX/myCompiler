//
// Created by M.Ghelichkhani on 5/10/2025.
//

// parser.h

#ifndef PARSER_H
#define PARSER_H

typedef enum {
    ND_ADD, // +
    ND_SUB, // -
    ND_MUL, // *
    ND_DIV, // /
    ND_NUM,  // عدد
    ND_LVAR, // متغیر محلی
    ND_ASSIGN // انتساب
} NodeKind;

typedef struct Node Node;

struct Node {
    NodeKind kind;
    Node *lhs;
    Node *rhs;
    int val; // فقط برای ND_NUM
    int offset; // offset az rbp baraye nd_lvar
};

Node *expr(void);

#endif
