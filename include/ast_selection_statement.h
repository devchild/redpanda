//
// Created by VANHECKE Mario on 2019-04-18.
//

#ifndef REDPANDA_AST_SELECTION_STATEMENT_H
#define REDPANDA_AST_SELECTION_STATEMENT_H

#include <ast_node.h>
#include <ast_binary_expression.h>
#include <ast_compound_statement.h>

typedef struct ast_selection_statement_vtable {
    ast_node_vtable base;
} ast_selection_statement_vtable;

typedef struct ast_selection_statement {
    ast_node base;

    /* if (condition) { then_body } else { else_body } */
    ast_binary_expression *condition;
    ast_compound_statement *then_body;
    ast_compound_statement *else_body;
} ast_selection_statement;

void ast_selection_statement_vtable__initialize(ast_selection_statement_vtable* self);
ast_selection_statement* ast_selection_statement__new(ast_binary_expression *condition,
                                                      ast_compound_statement *then_body,
                                                      ast_compound_statement *else_body);

#endif //REDPANDA_AST_SELECTION_STATEMENT_H
