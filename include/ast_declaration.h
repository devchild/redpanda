//
// Created by VANHECKE Mario on 2019-04-18.
//

#ifndef REDPANDA_AST_DECLARATION_H
#define REDPANDA_AST_DECLARATION_H

#include <ast_node.h>

typedef struct ast_declaration_vtable {
    ast_node_vtable base;
} ast_declaration_vtable;

typedef struct ast_declaration {
    ast_node base;

    int type_specifier;
    const char *identifier;
} ast_declaration;

void ast_declaration_vtable__initialize(ast_declaration_vtable* self);
ast_declaration* ast_declaration__new(int type_specifier, const char *identifier);

#endif //REDPANDA_AST_DECLARATION_H
