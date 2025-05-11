//
// Created by M.Ghelichkhani on 5/10/2025.
//

// parser.c

#include "parser.h"
#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern Token *token; // توکن فعلی (از lexer گرفته می‌شه)

// توابع کمکی
Node *new_node(NodeKind kind, Node *lhs, Node *rhs) {
    Node *node = calloc(1, sizeof(Node));
    node->kind = kind;
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

Node *new_node_num(int val) {
    Node *node = calloc(1, sizeof(Node));
    node->kind = ND_NUM;
    node->val = val;
    return node;
}

// بررسی و مصرف توکن خاص
int consume(char *op) {
    if (token->kind != TK_RESERVED || strlen(op) != token->len ||
        memcmp(token->str, op, token->len))
        return 0;
    token = token->next;
    return 1;
}

// بررسی و انتظار توکن خاص
void expect(char *op) {
    if (token->kind != TK_RESERVED || strlen(op) != token->len ||
        memcmp(token->str, op, token->len)) {
        fprintf(stderr, "expected \"%s\"\n", op);
        exit(1);
    }
    token = token->next;
}

// انتظار عدد
int expect_number() {
    if (token->kind != TK_NUM) {
        fprintf(stderr, "expected a number\n");
        exit(1);
    }
    int val = token->val;
    token = token->next;
    return val;
}

// forward declaration
Node *expr(void);
Node *mul(void);
Node *primary(void);

// expr = mul ("+" mul | "-" mul)*
Node *expr(void) {
    Node *node = mul();

    for (;;) {
        if (consume("+"))
            node = new_node(ND_ADD, node, mul());
        else if (consume("-"))
            node = new_node(ND_SUB, node, mul());
        else
            return node;
    }
}

// mul = primary ("*" primary | "/" primary)*
Node *mul(void) {
    Node *node = primary();

    for (;;) {
        if (consume("*"))
            node = new_node(ND_MUL, node, primary());
        else if (consume("/"))
            node = new_node(ND_DIV, node, primary());
        else
            return node;
    }
}

// primary = "(" expr ")" | num
Node *primary(void) {
    if (consume("(")) {
        Node *node = expr();
        expect(")");
        return node;
    }

    return new_node_num(expect_number());
}
