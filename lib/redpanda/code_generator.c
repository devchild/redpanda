//
// Created by VANHECKE Mario on 2019-04-28.
//
#include <stdlib.h>
#include <stdio.h>
#include <code_generator.h>

void code_generator__visit_ast_binary_expression(ast_node_visitor * self, ast_binary_expression* node) {

}
void code_generator__visit_ast_compile_unit(ast_node_visitor * self, ast_compile_unit* node) {

    /*
     * ; Disassembly of file: simple1.o
; Sun Apr 21 20:31:04 2019
; Mode: 64 bits
; Syntax: YASM/NASM
; Instruction set: 8086, x64

default rel

global _main

_main:  ; Function begin
        push    rbp                                     ; 0000 _ 55
        mov     rbp, rsp                                ; 0001 _ 48: 89. E5
        xor     eax, eax                                ; 0004 _ 31. C0
        mov     dword [rbp-4H], 0                       ; 0006 _ C7. 45, FC, 00000000
        pop     rbp                                     ; 000D _ 5D
        ret                                             ; 000E _ C3
; _main End of function
     * */

    code_generator * me = (code_generator*)self;
    fprintf(me->_out_str, "; Assembled using redpanda compiler\n");
    fprintf(me->_out_str, "; Mode: 64 bits\n");
    fprintf(me->_out_str, "default rel\n");
    fprintf(me->_out_str, "global _main\n");
    ast_node__accept((ast_node*)node->compile_unit_member_list, self);
}

void code_generator__visit_ast_compile_unit_member_list(ast_node_visitor * self, ast_compile_unit_member_list* node) {
    code_generator * me = (code_generator*)self;
    for (int i= 0; i < node->base.count; i++)
        ast_node__accept(node->base.nodes[i], self);
}
void code_generator__visit_ast_compound_statement(ast_node_visitor * self, ast_compound_statement* node) {
    code_generator * me = (code_generator*)self;
}
void code_generator__visit_ast_declaration(ast_node_visitor * self, ast_declaration* node) {
    code_generator * me = (code_generator*)self;
}
void code_generator__visit_ast_method(ast_node_visitor * self, ast_method* node) {
    code_generator * me = (code_generator*)self;
    fprintf(me->_out_str, "_%s: ; function begin\n", node->identifier);
    fprintf(me->_out_str, "\tpush\trbp \n");
    fprintf(me->_out_str, "\tmov \trbp, \trsp \n");

    ast_node__accept((ast_node*)node->statement_list, self);

    fprintf(me->_out_str, "\tpop rbp\n");
    fprintf(me->_out_str, "\tret\n");
    fprintf(me->_out_str, "\t; _%s end of function\n", node->identifier);
}
void code_generator__visit_ast_node_list(ast_node_visitor * self, ast_node_list* node) {
    code_generator * me = (code_generator*)self;
    for (int i= 0; i < (node)->count; i++)
        ast_node__accept((node)->nodes[i], self);
}
void code_generator__visit_ast_node(ast_node_visitor * self, ast_node* node) {
    code_generator * me = (code_generator*)self;
}

void code_generator__visit_ast_primitive_expression(ast_node_visitor * self, ast_primitive_expression* node) {
    code_generator * me = (code_generator*)self;
    if (node->int_constant == 0) {
        fprintf(me->_out_str, "\txor \teax, \teax  \n");
    }
    else {
        fprintf(me->_out_str, "\tmov \teax,\t%X\n", node->int_constant);
    }
}

void code_generator__visit_ast_return_statement(ast_node_visitor * self, ast_return_statement* node) {
    code_generator * me = (code_generator*)self;
    ast_node__accept(node->expression, self);
}
void code_generator__visit_ast_selection_statement(ast_node_visitor * self, ast_selection_statement* node) {
    code_generator * me = (code_generator*)self;

}
void code_generator__visit_ast_statement_list(ast_node_visitor * self, ast_statement_list* node) {
    code_generator * me = (code_generator*)self;
    for (int i= 0; i < node->base.count; i++)
        ast_node__accept(node->base.nodes[i], self);
}
void code_generator__visit_ast_while_statement(ast_node_visitor * self, ast_while_statement* node) {
    code_generator * me = (code_generator*)self;

}

void code_generator_vtable__initialize(code_generator_vtable* vtable) {
    ast_node_visitor_vtable * base = (ast_node_visitor_vtable*)vtable;
    ast_node_visitor_vtable__initialize(base);

    base->visit_ast_binary_expression = &code_generator__visit_ast_binary_expression;
    base->visit_ast_compile_unit = &code_generator__visit_ast_compile_unit;
    base->visit_ast_compile_unit_member_list = &code_generator__visit_ast_compile_unit_member_list;
    base->visit_ast_compound_statement = &code_generator__visit_ast_compound_statement;
    base->visit_ast_declaration = &code_generator__visit_ast_declaration;
    base->visit_ast_method = &code_generator__visit_ast_method;
    base->visit_ast_node_list = &code_generator__visit_ast_node_list;
    base->visit_ast_node = &code_generator__visit_ast_node;
    base->visit_ast_primitive_expression = &code_generator__visit_ast_primitive_expression;
    base->visit_ast_return_statement = &code_generator__visit_ast_return_statement;
    base->visit_ast_selection_statement = &code_generator__visit_ast_selection_statement;
    base->visit_ast_statement_list = &code_generator__visit_ast_statement_list;
    base->visit_ast_while_statement = &code_generator__visit_ast_while_statement;
}

code_generator* code_generator__new(FILE *  _out_str) {
    static int vtable__initialized = 0;
    static code_generator_vtable vtable = {0};
    if (!vtable__initialized) {
        code_generator_vtable__initialize(&vtable);
        vtable__initialized = 1;
    }

    code_generator* self = (code_generator*) calloc(1, sizeof(code_generator));
    object* base = (object*)self;
    base->vtable = (object_vtable*)&vtable;
    self->_out_str = _out_str;
    return self;
}
