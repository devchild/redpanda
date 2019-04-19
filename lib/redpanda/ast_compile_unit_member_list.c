//
// Created by VANHECKE Mario on 2019-04-18.
//
#include <stdlib.h>
#include <ast_compile_unit_member_list.h>
#include <ast_node_visitor.h>

void __ast_compile_unit_member_list__accept(ast_node* self, ast_node_visitor* visitor) {
    ast_node_visitor__visit_ast_compile_unit_member_list(visitor, self);
}

void ast_compile_unit_member_list_vtable__initialize(ast_compile_unit_member_list_vtable* vtable) {
    ast_node_list_vtable * base = (ast_node_list_vtable*)vtable;
    ast_node_vtable * base_base = (ast_node_vtable*)vtable;
    ast_node_list_vtable__initialize(base);
    base_base->accept = &__ast_compile_unit_member_list__accept;
}

ast_compile_unit_member_list* ast_compile_unit_member_list__new() {
    static int vtable__initialized = 0;
    static ast_compile_unit_member_list_vtable vtable = {0};
    if (!vtable__initialized) {
        ast_compile_unit_member_list_vtable__initialize(&vtable);
        vtable__initialized = 1;
    }

    ast_compile_unit_member_list* self = (ast_compile_unit_member_list*) calloc(1, sizeof(ast_compile_unit_member_list));
    object* base = (object*)self;

    base->vtable = (object_vtable*)&vtable;
    return self;
}
