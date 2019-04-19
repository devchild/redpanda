//
// Created by VANHECKE Mario on 2019-04-18.
//
#include <stdlib.h>
#include <ast_compound_statement.h>
#include <ast_node_visitor.h>

void __ast_compound__accept(ast_node* self, ast_node_visitor* visitor) {
    ast_node_visitor__visit_ast_compound_statement(visitor, self);
}

void ast_compound_statement_vtable__initialize(ast_compound_statement_vtable* vtable) {
    ast_node_vtable * base = (ast_node_vtable*)vtable;
    ast_node_vtable__initialize(base);
    base->accept = &__ast_compound__accept;
}

ast_compound_statement* ast_compound_statement__new(ast_statement_list *statement_list) {
    static int vtable__initialized = 0;
    static ast_compound_statement_vtable vtable = {0};
    if (!vtable__initialized) {
        ast_compound_statement_vtable__initialize(&vtable);
        vtable__initialized = 1;
    }

    ast_compound_statement* self = (ast_compound_statement*) calloc(1, sizeof(ast_compound_statement));
    object* base = (object*)self;
    base->vtable = (object_vtable*)&vtable;

    self->statement_list = statement_list;
    return self;
}
