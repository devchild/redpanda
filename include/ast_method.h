//
// Created by VANHECKE Mario on 2019-04-18.
//

#ifndef REDPANDA_AST_METHOD_H
#define REDPANDA_AST_METHOD_H

#include <ast_node.h>
#include <ast_statement_list.h>

typedef struct ast_method_vtable {
    ast_node_vtable base;
} ast_method_vtable;

typedef struct ast_method {
    ast_node base;

    const char *identifier;
    struct ast_statement_list *statement_list;
} ast_method;

void ast_method_vtable__initialize(ast_method_vtable* self);
ast_method* ast_method__new(const char* identifier, ast_statement_list *statement_list);

#endif //REDPANDA_AST_METHOD_H
