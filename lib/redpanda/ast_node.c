//
// Created by VANHECKE Mario on 2019-04-17.
//
#include <stdlib.h>
#include <ast_node.h>
#include <object.h>
#include <ast_node_visitor.h>

char* __ast_node__to_string(object* self) {
    return "ast_node";
}

void __ast_node__accept(ast_node* self, ast_node_visitor* visitor) {
    ast_node_visitor__visit_ast_node(visitor, self);
}

void ast_node_vtable__initialize(ast_node_vtable* vtable) {
    object_vtable * base = (object_vtable*)vtable;
    object_vtable__initialize(base);
    base->to_string = &__ast_node__to_string;
    vtable->accept = &__ast_node__accept;
}

ast_node* ast_node__new() {
    static int vtable__initialized = 0;
    static ast_node_vtable vtable = {0};
    if (!vtable__initialized) {
        ast_node_vtable__initialize(&vtable);
        vtable__initialized = 1;
    }

    ast_node* self = (ast_node*) calloc(1, sizeof(ast_node));
    object* base = (object*)self;

    base->vtable = (object_vtable*)&vtable;
    return self;
}

void ast_node__accept(ast_node* self, ast_node_visitor* visitor) {
    ast_node_vtable* vtable = (ast_node_vtable*)self->base.vtable;
    vtable->accept(self, visitor);
}