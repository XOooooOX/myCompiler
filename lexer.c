//
// Created by M.Ghelichkhani on 5/7/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include "lexer.h"

Token *token;

void error_at(char *loc,char *fmt,...){
    va_list ap;
    va_start(ap,fmt);

    int pos = loc - token->str;
    fprintf(stderr,"%s\n",token->str);
    fprintf(stderr, "%*s", pos, " ");
    fprintf(stderr, "^ ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

static Token *new_token(TokenKind kind,Token *cur,char *str,int len){
    Token *tok = calloc(1,sizeof(Token));
    tok->kind = kind;
    tok->str = str;
    tok->len = len;
    cur->next = tok;
    return tok;
}

static int startswith(char *p, char *q) {
    return strncmp(p, q, strlen(q)) == 0;
}

static bool isAlpha(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || (c == '_');
}

// توکن‌سازی
void tokenize(char *p) {
    Token head;
    head.next = NULL;
    Token *cur = &head;

    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }

        if (startswith(p, "==") || startswith(p, "!=") ||
            startswith(p, "<=") || startswith(p, ">=")) {
            cur = new_token(TK_RESERVED, cur, p, 2);
            p += 2;
            continue;
        }

        if (strchr("+-*/()<>", *p)) {
            cur = new_token(TK_RESERVED, cur, p++, 1);
            continue;
        }

        // بررسی شناسه‌ها (متغیرها و اسم‌ها)
        if (isAlpha(*p)) {
            char *start = p;
            while (isalnum(*p) || *p == '_') p++;
            cur = new_token(TK_IDENT, cur, start,p - start);
            continue;
        }

        if (isdigit(*p)) {
            char *q = p;
            int val = strtol(p, &p, 10);
            cur = new_token(TK_NUM, cur, q, p - q);
            cur->val = val;
            continue;
        }

        error_at(p, "توکن نامعتبر");
    }

    new_token(TK_EOF, cur, p, 0);
    token = head.next;
}