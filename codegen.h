//
// Created by M.Ghelichkhani on 5/11/2025.
//

#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"  // چون تابع gen از Node استفاده می‌کنه

// تولید کد اسمبلی برای AST
void gen(Node *node);

#endif // CODEGEN_H