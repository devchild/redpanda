//
// Created by VANHECKE Mario on 2019-04-18.
//

#ifndef REDPANDA_OBJECT_H
#define REDPANDA_OBJECT_H

struct object;
struct object_vtable;

typedef struct object_vtable {
    void (*dispose)(struct object*);
    char* (*to_string)(struct object*);
} object_vtable;

typedef struct object {
    object_vtable* vtable;
} object;

void object_vtable__initialize(object_vtable* self);
object* object__new();
void object__dispose(object* self);
char* object__to_string(object* self);

#endif //REDPANDA_OBJECT_H
