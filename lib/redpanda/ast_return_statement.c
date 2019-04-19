//
// Created by VANHECKE Mario on 2019-04-18.
//
#include <stdlib.h>
#include <ast_return_statement.h>
#include <ast_node_visitor.h>

void __ast_return_statement__accept(ast_node* self, ast_node_visitor* visitor) {
    ast_node_visitor__visit_ast_return_statement(visitor, self);
}

void ast_return_statement_vtable__initialize(ast_return_statement_vtable* vtable) {
    ast_node_vtable * base = (ast_node_vtable*)vtable;
    ast_node_vtable__initialize(base);
    base->accept = &__ast_return_statement__accept;
}

ast_return_statement* ast_return_statement__new(ast_node* expression) {
    static int vtable__initialized = 0;
    static ast_return_statement_vtable vtable = {0};
    if (!vtable__initialized) {
        ast_return_statement_vtable__initialize(&vtable);
        vtable__initialized = 1;
    }

    ast_return_statement* self = (ast_return_statement*) calloc(1, sizeof(ast_return_statement));
    object* base = (object*)self;
    base->vtable = (object_vtable*)&vtable;

    self->expression = expression;
    return self;
}
