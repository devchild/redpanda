//
// Created by VANHECKE Mario on 2019-04-18.
//

#ifndef REDPANDA_AST_COMPOUND_STATEMENT_H
#define REDPANDA_AST_COMPOUND_STATEMENT_H

#include <ast_node.h>
#include <ast_statement_list.h>

typedef struct ast_compound_statement_vtable {
    ast_node_vtable base;
} ast_compound_statement_vtable;

typedef struct ast_compound_statement {
    ast_node base;

    ast_statement_list *statement_list;
} ast_compound_statement;

void ast_compound_statement_vtable__initialize(ast_compound_statement_vtable* self);
ast_compound_statement* ast_compound_statement__new(ast_statement_list *statement_list);

#endif //REDPANDA_AST_COMPOUND_STATEMENT_H
