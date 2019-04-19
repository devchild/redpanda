//
// Created by VANHECKE Mario on 2019-04-18.
//
#include <stdlib.h>
#include <ast_declaration.h>

void ast_declaration_vtable__initialize(ast_declaration_vtable* vtable) {
    ast_node_vtable * base = (ast_node_vtable*)vtable;
    ast_node_vtable__initialize(base);
}

ast_declaration* ast_declaration__new(int type_specifier, const char *identifier) {
    static int vtable__initialized = 0;
    static ast_declaration_vtable vtable = {0};
    if (!vtable__initialized) {
        ast_declaration_vtable__initialize(&vtable);
        vtable__initialized = 1;
    }

    ast_declaration* self = (ast_declaration*) calloc(1, sizeof(ast_declaration));
    object* base = (object*)self;
    base->vtable = (object_vtable*)&vtable;

    self->identifier = identifier;
    self->type_specifier = type_specifier;

    return self;
}
