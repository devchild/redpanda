//
// Created by VANHECKE Mario on 2019-04-18.
//
#include <stdlib.h>
#include <stdio.h>
#include <ast_printer.h>

void ast_printer__visit_ast_binary_expression(ast_node_visitor * self, ast_binary_expression* node) {

}
void ast_printer__visit_ast_compile_unit(ast_node_visitor * self, ast_compile_unit* node) {
    printf("COMPILE_UNIT - START\n");
    ast_node__accept(node->compile_unit_member_list, self);
    printf("COMPILE_UNIT - END\n");
}

void ast_printer__visit_ast_compile_unit_member_list(ast_node_visitor * self, ast_compile_unit_member_list* node) {
    printf("COMPILE_UNIT_MEMBER_LIST - START\n");
    for (int i= 0; i < node->base.count; i++)
        ast_node__accept(node->base.nodes[i], self);
    printf("COMPILE_UNIT_MEMBER_LIST - END\n");

}
void ast_printer__visit_ast_compound_statement(ast_node_visitor * self, ast_compound_statement* node) {

}
void ast_printer__visit_ast_declaration(ast_node_visitor * self, ast_declaration* node) {

}
void ast_printer__visit_ast_method(ast_node_visitor * self, ast_method* node) {
    printf("METHOD - START\n");
    ast_node__accept(node->statement_list, self);
    printf("METHOD - END\n");
}
void ast_printer__visit_ast_node_list(ast_node_visitor * self, ast_node_list* node) {
    printf("NODE_LIST - START\n");
    for (int i= 0; i < (node)->count; i++)
        ast_node__accept((node)->nodes[i], self);
    printf("NODE_LIST - END\n");
}
void ast_printer__visit_ast_node(ast_node_visitor * self, ast_node* node) {
    printf("NODE - START\n");
    printf("NODE - END\n");
}
void ast_printer__visit_ast_primitive_expression(ast_node_visitor * self, ast_primitive_expression* node) {
    printf("PRIMITIVE - START\n");
    printf("[%d]\n", node->int_constant);
    printf("PRIMITIVE - END\n");
}
void ast_printer__visit_ast_return_statement(ast_node_visitor * self, ast_return_statement* node) {
    printf("RETURN - START\n");
    ast_node__accept(node->expression, self);
    printf("RETURN - END\n");
}
void ast_printer__visit_ast_selection_statement(ast_node_visitor * self, ast_selection_statement* node) {

}
void ast_printer__visit_ast_statement_list(ast_node_visitor * self, ast_statement_list* node) {
    printf("STATEMENT_LIST - START\n");
    for (int i= 0; i < node->base.count; i++)
        ast_node__accept(node->base.nodes[i], self);
    printf("STATEMENT_LIST - END\n");
}
void ast_printer__visit_ast_while_statement(ast_node_visitor * self, ast_while_statement* node) {

}

void ast_printer_vtable__initialize(ast_printer_vtable* vtable) {
    ast_node_visitor_vtable * base = (ast_node_visitor_vtable*)vtable;
    ast_node_visitor_vtable__initialize(base);

    base->visit_ast_binary_expression = &ast_printer__visit_ast_binary_expression;
    base->visit_ast_compile_unit = &ast_printer__visit_ast_compile_unit;
    base->visit_ast_compile_unit_member_list = &ast_printer__visit_ast_compile_unit_member_list;
    base->visit_ast_compound_statement = &ast_printer__visit_ast_compound_statement;
    base->visit_ast_declaration = &ast_printer__visit_ast_declaration;
    base->visit_ast_method = &ast_printer__visit_ast_method;
    base->visit_ast_node_list = &ast_printer__visit_ast_node_list;
    base->visit_ast_node = &ast_printer__visit_ast_node;
    base->visit_ast_primitive_expression = &ast_printer__visit_ast_primitive_expression;
    base->visit_ast_return_statement = &ast_printer__visit_ast_return_statement;
    base->visit_ast_selection_statement = &ast_printer__visit_ast_selection_statement;
    base->visit_ast_statement_list = &ast_printer__visit_ast_statement_list;
    base->visit_ast_while_statement = &ast_printer__visit_ast_while_statement;
}

ast_printer* ast_printer__new() {
    static int vtable__initialized = 0;
    static ast_printer_vtable vtable = {0};
    if (!vtable__initialized) {
        ast_printer_vtable__initialize(&vtable);
        vtable__initialized = 1;
    }

    ast_printer* self = (ast_printer*) calloc(1, sizeof(ast_printer));
    object* base = (object*)self;
    base->vtable = (object_vtable*)&vtable;
    return self;
}
