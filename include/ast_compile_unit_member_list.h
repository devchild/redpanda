//
// Created by VANHECKE Mario on 2019-04-18.
//
#include <ast_node_list.h>

#ifndef REDPANDA_AST_COMPILE_UNIT_MEMBER_LIST_H
#define REDPANDA_AST_COMPILE_UNIT_MEMBER_LIST_H

typedef struct ast_compile_unit_member_list_vtable {
    ast_node_list_vtable base;
} ast_compile_unit_member_list_vtable;

typedef struct ast_compile_unit_member_list {
    ast_node_list base;
} ast_compile_unit_member_list;

void ast_compile_unit_member_list_vtable__initialize(ast_compile_unit_member_list_vtable* self);
ast_compile_unit_member_list* ast_compile_unit_member_list__new();

#endif //REDPANDA_AST_COMPILE_UNIT_MEMBER_LIST_H
