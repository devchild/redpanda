//
// Created by VANHECKE Mario on 2019-04-18.
//
#include <stdlib.h>
#include <ast_binary_expression.h>
#include <ast_node_visitor.h>

void __ast_binary_expression__accept(ast_node* self, ast_node_visitor* visitor) {
    ast_node_visitor__visit_ast_binary_expression(visitor, self);
}

void ast_binary_expression_vtable__initialize(ast_binary_expression_vtable* vtable) {
    ast_node_vtable * base = (ast_node_vtable*)vtable;
    ast_node_vtable__initialize(base);
    base->accept = &__ast_binary_expression__accept;
}

ast_binary_expression* ast_binary_expression__new(const char* _operator, ast_node *lhs, ast_node *rhs) {
    static int vtable__initialized = 0;
    static ast_binary_expression_vtable vtable = {0};
    if (!vtable__initialized) {
        ast_binary_expression_vtable__initialize(&vtable);
        vtable__initialized = 1;
    }

    ast_binary_expression* self = (ast_binary_expression*) calloc(1, sizeof(ast_binary_expression));
    object* base = (object*)self;
    base->vtable = (object_vtable*)&vtable;

    self->_operator = _operator;
    self->lhs = lhs;
    self->rhs = rhs;

    return self;
}
