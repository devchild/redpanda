//
// Created by VANHECKE Mario on 2019-04-18.
//

#ifndef REDPANDA_AST_PRINTER_H
#define REDPANDA_AST_PRINTER_H

#include <ast_node_visitor.h>

typedef struct ast_printer_vtable {
    ast_node_visitor_vtable base;
} ast_printer_vtable;

typedef struct ast_printer {
    ast_node_visitor base;

} ast_printer;

void ast_printer_vtable__initialize(ast_printer_vtable* self);
ast_printer* ast_printer__new();

#endif //REDPANDA_AST_PRINTER_H
