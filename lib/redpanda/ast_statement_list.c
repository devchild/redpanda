//
// Created by VANHECKE Mario on 2019-04-18.
//
#include <stdlib.h>
#include <ast_statement_list.h>

void ast_statement_list_vtable__initialize(ast_statement_list_vtable* vtable) {
    ast_node_list_vtable * base = (ast_node_list_vtable*)vtable;
    ast_node_list_vtable__initialize(base);
}

ast_statement_list* ast_statement_list__new() {
    static int vtable__initialized = 0;
    static ast_statement_list_vtable vtable = {0};
    if (!vtable__initialized) {
        ast_statement_list_vtable__initialize(&vtable);
        vtable__initialized = 1;
    }

    ast_statement_list* self = (ast_statement_list*) calloc(1, sizeof(ast_statement_list));
    object* base = (object*)self;

    base->vtable = (object_vtable*)&vtable;
    return self;
}
