#ifndef SCHEME_C_OBJECT_H
#define SCHEME_C_OBJECT_H

#include "type.h"

typedef struct Scheme_Object {
    Scheme_Object_Type type;
    union {
        struct {
            long value;
        } fixnum;
    } data;
} Scheme_Object;

extern Scheme_Object* Alloc_Object();

extern Scheme_Object* Make_Fixnum(long value);

extern char Is_Fixnum(Scheme_Object* obj);

#endif //SCHEME_C_OBJECT_H
