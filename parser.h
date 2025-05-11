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
    ND_NUM  // عدد
} NodeKind;

typedef struct Node Node;

struct Node {
    NodeKind kind;
    Node *lhs;
    Node *rhs;
    int val; // فقط برای ND_NUM
};

Node *expr(void);

#endif
