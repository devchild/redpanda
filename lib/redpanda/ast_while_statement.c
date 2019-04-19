//
// Created by VANHECKE Mario on 2019-04-18.
//
#include <stdlib.h>
#include <ast_while_statement.h>

void ast_while_statement_vtable__initialize(ast_while_statement_vtable* vtable) {
    ast_node_vtable * base = (ast_node_vtable*)vtable;
    ast_node_vtable__initialize(base);
}

ast_while_statement* ast_while_statement__new(ast_binary_expression *condition,
                                              ast_compound_statement *body) {
    static int vtable__initialized = 0;
    static ast_while_statement_vtable vtable = {0};
    if (!vtable__initialized) {
        ast_while_statement_vtable__initialize(&vtable);
        vtable__initialized = 1;
    }

    ast_while_statement* self = (ast_while_statement*) calloc(1, sizeof(ast_while_statement));
    object* base = (object*)self;

    base->vtable = (object_vtable*)&vtable;

    self->condition = condition;
    self->body = body;
    return self;
}
