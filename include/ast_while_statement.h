//
// Created by VANHECKE Mario on 2019-04-18.
//

#ifndef REDPANDA_AST_WHILE_STATEMENT_H
#define REDPANDA_AST_WHILE_STATEMENT_H

#include <ast_node.h>
#include <ast_binary_expression.h>
#include <ast_compound_statement.h>

typedef struct ast_while_statement_vtable {
    ast_node_vtable base;
} ast_while_statement_vtable;

typedef struct ast_while_statement {
    ast_node base;

    /* while (condition) { body } */
    ast_binary_expression *condition;
    ast_compound_statement *body;
} ast_while_statement;

void ast_while_statement_vtable__initialize(ast_while_statement_vtable* self);
ast_while_statement* ast_while_statement__new(ast_binary_expression *condition,
                                              ast_compound_statement *body);

#endif //REDPANDA_AST_WHILE_STATEMENT_H
