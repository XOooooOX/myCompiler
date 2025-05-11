//
// Created by M.Ghelichkhani on 5/7/2025.
//

#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TK_RESERVED,
    TK_IDENT,
    TK_NUM,
    TK_EOF
} TokenKind;

typedef struct Token Token;

struct Token {
    TokenKind kind;
    Token *next;
    int val;
    char *str;
    int len;
};

extern Token *token;

void  tokenize(char *p);

void error_at(char *loc,char *fmt,...);

#endif //LEXER_H
