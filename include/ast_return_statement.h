//
// Created by VANHECKE Mario on 2019-04-18.
//

#ifndef REDPANDA_AST_RETURN_STATEMENT_H
#define REDPANDA_AST_RETURN_STATEMENT_H

#include <ast_node.h>

typedef struct ast_return_statement_vtable {
    ast_node_vtable base;
} ast_return_statement_vtable;

typedef struct ast_return_statement {
    ast_node base;

    ast_node *expression;
} ast_return_statement;

void ast_return_statement_vtable__initialize(ast_return_statement_vtable* self);
ast_return_statement* ast_return_statement__new(ast_node* expression);

#endif //REDPANDA_AST_RETURN_STATEMENT_H
