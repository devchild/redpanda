//
// Created by VANHECKE Mario on 2019-04-18.
//

#ifndef REDPANDA_AST_STATEMENT_LIST_H
#define REDPANDA_AST_STATEMENT_LIST_H

#include <ast_node_list.h>

typedef struct ast_statement_list_vtable {
    ast_node_list_vtable base;
} ast_statement_list_vtable;

typedef struct ast_statement_list {
    ast_node_list base;
} ast_statement_list;

void ast_statement_list_vtable__initialize(ast_statement_list_vtable* self);
ast_statement_list* ast_statement_list__new();

#endif //REDPANDA_AST_STATEMENT_LIST_H
