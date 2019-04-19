//
// Created by VANHECKE Mario on 2019-04-17.
//
#ifndef REDPANDA_AST_NODE_H
#define REDPANDA_AST_NODE_H

#include <object.h>

struct ast_node_visitor;

typedef struct ast_node {
    object base;
    int tag;
} ast_node;

typedef struct ast_node_vtable {
    object_vtable base;
    void (*accept)(ast_node* self, struct ast_node_visitor* visitor);
} ast_node_vtable;

void ast_node_vtable__initialize(ast_node_vtable* self);
ast_node* ast_node__new();
void ast_node__accept(ast_node* self, struct ast_node_visitor* visitor);

#endif //REDPANDA_AST_NODE_H
