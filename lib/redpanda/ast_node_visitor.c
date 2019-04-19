//
// Created by VANHECKE Mario on 2019-04-18.
//
#include <stdlib.h>
#include <ast_node_visitor.h>

void __ast_node_visitor__visit_ast_binary_expression(ast_node_visitor * self, ast_binary_expression* node) {}
void __ast_node_visitor__visit_ast_compile_unit(ast_node_visitor * self, ast_compile_unit* node) {}
void __ast_node_visitor__visit_ast_compile_unit_member_list(ast_node_visitor * self, ast_compile_unit_member_list* node) {}
void __ast_node_visitor__visit_ast_compound_statement(ast_node_visitor * self, ast_compound_statement* node) {}
void __ast_node_visitor__visit_ast_declaration(ast_node_visitor * self, ast_declaration* node) {}
void __ast_node_visitor__visit_ast_method(ast_node_visitor * self, ast_method* node) {}
void __ast_node_visitor__visit_ast_node_list(ast_node_visitor * self, ast_node_list* node) {}
void __ast_node_visitor__visit_ast_node(ast_node_visitor * self, ast_node* node) {}
void __ast_node_visitor__visit_ast_primitive_expression(ast_node_visitor * self, ast_primitive_expression* node) {}
void __ast_node_visitor__visit_ast_return_statement(ast_node_visitor * self, ast_return_statement* node) {}
void __ast_node_visitor__visit_ast_selection_statement(ast_node_visitor * self, ast_selection_statement* node) {}
void __ast_node_visitor__visit_ast_statement_list(ast_node_visitor * self, ast_statement_list* node) {}
void __ast_node_visitor__visit_ast_while_statement(ast_node_visitor * self, ast_while_statement* node) {}

void ast_node_visitor_vtable__initialize(ast_node_visitor_vtable* vtable) {
    object_vtable * base = (object_vtable*)vtable;
    object_vtable__initialize(base);

    vtable->visit_ast_binary_expression = &__ast_node_visitor__visit_ast_binary_expression;
    vtable->visit_ast_compile_unit = &__ast_node_visitor__visit_ast_compile_unit;
    vtable->visit_ast_compile_unit_member_list = &__ast_node_visitor__visit_ast_compile_unit_member_list;
    vtable->visit_ast_compound_statement = &__ast_node_visitor__visit_ast_compound_statement;
    vtable->visit_ast_declaration = &__ast_node_visitor__visit_ast_declaration;
    vtable->visit_ast_method = &__ast_node_visitor__visit_ast_method;
    vtable->visit_ast_node_list = &__ast_node_visitor__visit_ast_node_list;
    vtable->visit_ast_node = &__ast_node_visitor__visit_ast_node;
    vtable->visit_ast_primitive_expression = &__ast_node_visitor__visit_ast_primitive_expression;
    vtable->visit_ast_return_statement = &__ast_node_visitor__visit_ast_return_statement;
    vtable->visit_ast_selection_statement = &__ast_node_visitor__visit_ast_selection_statement;
    vtable->visit_ast_statement_list = &__ast_node_visitor__visit_ast_statement_list;
    vtable->visit_ast_while_statement = &__ast_node_visitor__visit_ast_while_statement;
}

ast_node_visitor* ast_node_visitor__new() {
    static int vtable__initialized = 0;
    static ast_node_visitor_vtable vtable = {0};
    if (!vtable__initialized) {
        ast_node_visitor_vtable__initialize(&vtable);
        vtable__initialized = 1;
    }

    ast_node_visitor* self = (ast_node_visitor*) calloc(1, sizeof(ast_node_visitor));
    object* base = (object*)self;

    base->vtable = (object_vtable*)&vtable;
    return self;
}

void ast_node_visitor__visit_ast_binary_expression(ast_node_visitor * self, ast_binary_expression* node) {
    ((ast_node_visitor_vtable*)((object*)self)->vtable)->visit_ast_binary_expression(self, node);
}
void ast_node_visitor__visit_ast_compile_unit(ast_node_visitor * self, ast_compile_unit* node) {
    ((ast_node_visitor_vtable*)((object*)self)->vtable)->visit_ast_compile_unit(self, node);
}
void ast_node_visitor__visit_ast_compile_unit_member_list(ast_node_visitor * self, ast_compile_unit_member_list* node) {
    ((ast_node_visitor_vtable*)((object*)self)->vtable)->visit_ast_compile_unit_member_list(self, node);
}
void ast_node_visitor__visit_ast_compound_statement(ast_node_visitor * self, ast_compound_statement* node) {
    ((ast_node_visitor_vtable*)((object*)self)->vtable)->visit_ast_compound_statement(self, node);
}
void ast_node_visitor__visit_ast_declaration(ast_node_visitor * self, ast_declaration* node) {
    ((ast_node_visitor_vtable*)((object*)self)->vtable)->visit_ast_declaration(self, node);
}
void ast_node_visitor__visit_ast_method(ast_node_visitor * self, ast_method* node) {
    ((ast_node_visitor_vtable*)((object*)self)->vtable)->visit_ast_method(self, node);
}
void ast_node_visitor__visit_ast_node_list(ast_node_visitor * self, ast_node_list* node) {
    ((ast_node_visitor_vtable*)((object*)self)->vtable)->visit_ast_node_list(self, node);
}
void ast_node_visitor__visit_ast_node(ast_node_visitor * self, ast_node* node) {
    ((ast_node_visitor_vtable*)((object*)self)->vtable)->visit_ast_node(self, node);
}
void ast_node_visitor__visit_ast_primitive_expression(ast_node_visitor * self, ast_primitive_expression* node) {
    ((ast_node_visitor_vtable*)((object*)self)->vtable)->visit_ast_primitive_expression(self, node);
}
void ast_node_visitor__visit_ast_return_statement(ast_node_visitor * self, ast_return_statement* node) {
    ((ast_node_visitor_vtable*)((object*)self)->vtable)->visit_ast_return_statement(self, node);
}
void ast_node_visitor__visit_ast_selection_statement(ast_node_visitor * self, ast_selection_statement* node) {
    ((ast_node_visitor_vtable*)((object*)self)->vtable)->visit_ast_selection_statement(self, node);
}
void ast_node_visitor__visit_ast_statement_list(ast_node_visitor * self, ast_statement_list* node) {
    ((ast_node_visitor_vtable*)((object*)self)->vtable)->visit_ast_statement_list(self, node);
}
void ast_node_visitor__visit_ast_while_statement(ast_node_visitor * self, ast_while_statement* node) {
    ((ast_node_visitor_vtable*)((object*)self)->vtable)->visit_ast_while_statement(self, node);
}