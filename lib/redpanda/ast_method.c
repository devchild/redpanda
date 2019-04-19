//
// Created by VANHECKE Mario on 2019-04-18.
//
#include <stdlib.h>
#include <ast_method.h>
#include <ast_node_visitor.h>


void __ast_method__accept(ast_node* self, ast_node_visitor* visitor) {
    ast_node_visitor__visit_ast_method(visitor, self);
}

void ast_method_vtable__initialize(ast_method_vtable* vtable) {
    ast_node_vtable * base = (ast_node_vtable*)vtable;
    ast_node_vtable__initialize(base);
    base->accept = &__ast_method__accept;
}

ast_method* ast_method__new(const char* identifier, ast_statement_list *statement_list) {
    static int vtable__initialized = 0;
    static ast_method_vtable vtable = {0};
    if (!vtable__initialized) {
        ast_method_vtable__initialize(&vtable);
        vtable__initialized = 1;
    }

    ast_method* self = (ast_method*) calloc(1, sizeof(ast_method));
    object* base = (object*)self;
    base->vtable = (object_vtable*)&vtable;

    self->identifier = identifier;
    self->statement_list = statement_list;
    return self;
}
