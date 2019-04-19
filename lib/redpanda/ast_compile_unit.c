//
// Created by VANHECKE Mario on 2019-04-18.
//
#include <stdlib.h>
#include <ast_compile_unit.h>
#include <ast_node_visitor.h>

void __ast_compile_unit__accept(ast_node* self, ast_node_visitor* visitor) {
    ast_node_visitor__visit_ast_compile_unit(visitor, self);
}

void ast_compile_unit_vtable__initialize(ast_compile_unit_vtable* vtable) {
    ast_node_vtable * base = (ast_node_vtable*)vtable;
    ast_node_vtable__initialize(base);
    base->accept = &__ast_compile_unit__accept;
}

ast_compile_unit* ast_compile_unit__new(ast_compile_unit_member_list *compile_unit_member_list) {
    static int vtable__initialized = 0;
    static ast_compile_unit_vtable vtable = {0};
    if (!vtable__initialized) {
        ast_compile_unit_vtable__initialize(&vtable);
        vtable__initialized = 1;
    }

    ast_compile_unit* self = (ast_compile_unit*) calloc(1, sizeof(ast_compile_unit));
    object* base = (object*)self;
    base->vtable = (object_vtable*)&vtable;

    self->compile_unit_member_list = compile_unit_member_list;
    return self;
}
