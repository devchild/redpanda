//
// Created by VANHECKE Mario on 2019-04-18.
//
#ifndef REDPANDA_AST_BINARY_EXPRESSION_H
#define REDPANDA_AST_BINARY_EXPRESSION_H

#include <ast_node.h>

typedef struct ast_binary_expression_vtable {
    ast_node_vtable base;
} ast_binary_expression_vtable;

typedef struct ast_binary_expression {
    ast_node base;

    const char* _operator;
    ast_node *lhs;
    ast_node *rhs;
} ast_binary_expression;

void ast_binary_expression_vtable__initialize(ast_binary_expression_vtable* self);
ast_binary_expression* ast_binary_expression__new(const char* _operator, ast_node *lhs, ast_node *rhs);

#endif //REDPANDA_AST_BINARY_EXPRESSION_H
