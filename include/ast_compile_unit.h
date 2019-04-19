//
// Created by VANHECKE Mario on 2019-04-18.
//
#include <ast_node.h>
#include <ast_compile_unit_member_list.h>

#ifndef REDPANDA_AST_COMPILE_UNIT_H
#define REDPANDA_AST_COMPILE_UNIT_H

typedef struct ast_compile_unit_vtable {
    ast_node_vtable base;
} ast_compile_unit_vtable;

typedef struct ast_compile_unit {
    ast_node base;
    ast_compile_unit_member_list *compile_unit_member_list;
} ast_compile_unit;

void ast_compile_unit_vtable__initialize(ast_compile_unit_vtable* self);
ast_compile_unit* ast_compile_unit__new(ast_compile_unit_member_list *compile_unit_member_list);

#endif //REDPANDA_AST_COMPILE_UNIT_H
