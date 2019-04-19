//
// Created by VANHECKE Mario on 2019-04-18.
//
#include <stdlib.h>
#include <ast_node_list.h>
#include <stdio.h>
#include <ast_node_visitor.h>

void __ast_node_list__accept(ast_node* self, ast_node_visitor* visitor) {
    ast_node_visitor__visit_ast_node_list(visitor, self);
}

void ast_node_list_vtable__initialize(ast_node_list_vtable* vtable) {

    ast_node_vtable * base = (ast_node_vtable*)vtable;
    ast_node_vtable__initialize(base);
    base->accept = &__ast_node_list__accept;
}

ast_node_list* ast_node_list__new() {
    static int vtable__initialized = 0;
    static ast_node_list_vtable vtable = {0};
    if (!vtable__initialized) {
        ast_node_list_vtable__initialize(&vtable);
        vtable__initialized = 1;
    }

    ast_node_list* self = (ast_node_list*) calloc(1, sizeof(ast_node_list));
    object* base = (object*)self;

    base->vtable = (object_vtable*)&vtable;
    return self;
}


ast_node_list *
ast_node_list__push(ast_node_list *self, ast_node *node)
{
    int nstmts;
    size_t size;

    nstmts = self->count + 1;
    size = nstmts * sizeof(ast_node*);

    self->nodes = realloc(self->nodes, size);
    if (self->nodes == NULL) {
        fprintf(stderr, "Memory reallocation request failed.\n");
        exit(EXIT_FAILURE);
    }

    self->nodes[nstmts - 1] = node;
    self->count++;

    return self;
}