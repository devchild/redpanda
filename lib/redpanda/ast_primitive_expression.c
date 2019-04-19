//
// Created by VANHECKE Mario on 2019-04-18.
//
#include <stdlib.h>
#include <ast_primitive_expression.h>
#include <ast_node_visitor.h>

void __ast_primitive_expression__accept(ast_node* self, ast_node_visitor* visitor) {
    ast_node_visitor__visit_ast_primitive_expression(visitor, self);
}

void ast_primitive_expression_vtable__initialize(ast_primitive_expression_vtable* vtable) {
    ast_node_vtable * base = (ast_node_vtable*)vtable;
    ast_node_vtable__initialize(base);
    base->accept = &__ast_primitive_expression__accept;
}

ast_primitive_expression* ast_primitive_expression__new() {
    static int vtable__initialized = 0;
    static ast_primitive_expression_vtable vtable = {0};
    if (!vtable__initialized) {
        ast_primitive_expression_vtable__initialize(&vtable);
        vtable__initialized = 1;
    }

    ast_primitive_expression* self = (ast_primitive_expression*) calloc(1, sizeof(ast_primitive_expression));
    object* base = (object*)self;
    base->vtable = (object_vtable*)&vtable;
    return self;
}

ast_primitive_expression * ast_primitive_expression__new_int(int value) {
    ast_primitive_expression *ret = ast_primitive_expression__new();
    ret->int_constant = value;
    return ret;
}
