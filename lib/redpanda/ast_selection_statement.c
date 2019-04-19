//
// Created by VANHECKE Mario on 2019-04-18.
//
#include <stdlib.h>
#include <ast_selection_statement.h>

void ast_selection_statement_vtable__initialize(ast_selection_statement_vtable* vtable) {
    ast_node_vtable * base = (ast_node_vtable*)vtable;
    ast_node_vtable__initialize(base);
}

ast_selection_statement* ast_selection_statement__new(ast_binary_expression *condition,
                                                      ast_compound_statement *then_body,
                                                      ast_compound_statement *else_body) {
    static int vtable__initialized = 0;
    static ast_selection_statement_vtable vtable = {0};
    if (!vtable__initialized) {
        ast_selection_statement_vtable__initialize(&vtable);
        vtable__initialized = 1;
    }

    ast_selection_statement* self = (ast_selection_statement*) calloc(1, sizeof(ast_selection_statement));
    object* base = (object*)self;
    base->vtable = (object_vtable*)&vtable;

    self->condition = condition;
    self->then_body = then_body;
    self->else_body = else_body;

    return self;
}
