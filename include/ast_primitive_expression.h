//
// Created by VANHECKE Mario on 2019-04-18.
//

#ifndef REDPANDA_AST_PRIMITIVE_EXPRESSION_H
#define REDPANDA_AST_PRIMITIVE_EXPRESSION_H

#include <ast_node.h>

typedef struct ast_primitive_expression_vtable {
    ast_node_vtable base;
} ast_primitive_expression_vtable;

typedef struct ast_primitive_expression {
    ast_node base;
    int type;

    int int_constant;
    float float_constant;
    const char *identifier;
} ast_primitive_expression;

void ast_primitive_expression_vtable__initialize(ast_primitive_expression_vtable* self);
ast_primitive_expression * ast_primitive_expression__new();
ast_primitive_expression * ast_primitive_expression__new_int(int value);

#endif //REDPANDA_AST_PRIMITIVE_EXPRESSION_H
