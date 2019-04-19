//
// Created by VANHECKE Mario on 2019-04-18.
//
#ifndef REDPANDA_AST_NODE_VISITOR_H
#define REDPANDA_AST_NODE_VISITOR_H

#include <object.h>
#include <ast_binary_expression.h>
#include <ast_declaration.h>
#include <ast_compound_statement.h>
#include <ast_compile_unit_member_list.h>
#include <ast_compile_unit.h>
#include <ast_method.h>
#include <ast_return_statement.h>
#include <ast_selection_statement.h>
#include <ast_primitive_expression.h>
#include <ast_while_statement.h>

typedef struct ast_node_visitor {
    object base;
    int tag;
} ast_node_visitor;

typedef struct ast_node_visitor_vtable {
    object_vtable base;
    void (*visit_ast_binary_expression)(ast_node_visitor * self, ast_binary_expression* node);
    void (*visit_ast_compile_unit)(ast_node_visitor * self, ast_compile_unit* node);
    void (*visit_ast_compile_unit_member_list)(ast_node_visitor * self, ast_compile_unit_member_list* node);
    void (*visit_ast_compound_statement)(ast_node_visitor * self, ast_compound_statement* node);
    void (*visit_ast_declaration)(ast_node_visitor * self, ast_declaration* node);
    void (*visit_ast_method)(ast_node_visitor * self, ast_method* node);
    void (*visit_ast_node_list)(ast_node_visitor * self, ast_node_list* node);
    void (*visit_ast_node)(ast_node_visitor * self, ast_node* node);
    void (*visit_ast_primitive_expression)(ast_node_visitor * self, ast_primitive_expression* node);
    void (*visit_ast_return_statement)(ast_node_visitor * self, ast_return_statement* node);
    void (*visit_ast_selection_statement)(ast_node_visitor * self, ast_selection_statement* node);
    void (*visit_ast_statement_list)(ast_node_visitor * self, ast_statement_list* node);
    void (*visit_ast_while_statement)(ast_node_visitor * self, ast_while_statement* node);

} ast_node_visitor_vtable;

void ast_node_visitor_vtable__initialize(ast_node_visitor_vtable* self);
ast_node_visitor* ast_node_visitor__new();

void ast_node_visitor__visit_ast_binary_expression(ast_node_visitor * self, ast_binary_expression* node);
void ast_node_visitor__visit_ast_compile_unit(ast_node_visitor * self, ast_compile_unit* node);
void ast_node_visitor__visit_ast_compile_unit_member_list(ast_node_visitor * self, ast_compile_unit_member_list* node);
void ast_node_visitor__visit_ast_compound_statement(ast_node_visitor * self, ast_compound_statement* node);
void ast_node_visitor__visit_ast_declaration(ast_node_visitor * self, ast_declaration* node);
void ast_node_visitor__visit_ast_method(ast_node_visitor * self, ast_method* node);
void ast_node_visitor__visit_ast_node_list(ast_node_visitor * self, ast_node_list* node);
void ast_node_visitor__visit_ast_node(ast_node_visitor * self, ast_node* node);
void ast_node_visitor__visit_ast_primitive_expression(ast_node_visitor * self, ast_primitive_expression* node);
void ast_node_visitor__visit_ast_return_statement(ast_node_visitor * self, ast_return_statement* node);
void ast_node_visitor__visit_ast_selection_statement(ast_node_visitor * self, ast_selection_statement* node);
void ast_node_visitor__visit_ast_statement_list(ast_node_visitor * self, ast_statement_list* node);
void ast_node_visitor__visit_ast_while_statement(ast_node_visitor * self, ast_while_statement* node);

#endif //REDPANDA_AST_NODE_VISITOR_H
