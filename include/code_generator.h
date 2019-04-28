//
// Created by VANHECKE Mario on 2019-04-28.
//
#ifndef REDPANDA_CODE_GENERATOR_H
#define REDPANDA_CODE_GENERATOR_H

#include <ast_node_visitor.h>
#include <stdio.h>

typedef struct code_generator_vtable {
    ast_node_visitor_vtable base;
} code_generator_vtable;

typedef struct code_generator {
    ast_node_visitor base;
    FILE *  _out_str;
} code_generator;

void code_generator_vtable__initialize(code_generator_vtable* self);
code_generator* code_generator__new(FILE *  _out_str);

#endif //REDPANDA_CODE_GENERATOR_H
