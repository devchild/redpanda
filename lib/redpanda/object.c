//
// Created by VANHECKE Mario on 2019-04-18.
//

#include <object.h>
#include <stdlib.h>

void __object__dispose(object* self) {
    if (self) {
        self->vtable = NULL;
        free(self);
    }
}

char* __object__to_string(object* self) {
    return "object";
}

void object_vtable__initialize(object_vtable* self) {
    self->to_string = &__object__to_string;
    self->dispose = &__object__dispose;
}

object* object__new() {
    static int object_vtable__initialized = 0;
    static object_vtable vtable = {0};
    if (!object_vtable__initialized) {
        object_vtable__initialize(&vtable);
        object_vtable__initialized = 1;
    }

    object* self = (object*) malloc(sizeof(object));
    self->vtable = &vtable;
    return self;
}

void object__dispose(object* self) {
    self->vtable->dispose(self);
}

char* object__to_string(object* self) {
    return self->vtable->to_string(self);
}