//
// Created by VANHECKE Mario on 2019-04-18.
//

#ifndef REDPANDA_AST_NODE_LIST_H
#define REDPANDA_AST_NODE_LIST_H

#include <ast_node.h>

typedef struct ast_node_list_vtable {
    ast_node_vtable base;
} ast_node_list_vtable;

typedef struct ast_node_list {
    ast_node base;
    int count;
    ast_node **nodes;
} ast_node_list;

void ast_node_list_vtable__initialize(ast_node_list_vtable* self);
ast_node_list* ast_node_list__new();

ast_node_list *
ast_node_list__push(ast_node_list *self, ast_node *node);

#endif //REDPANDA_AST_NODE_LIST_H
