#ifndef SCHEME_C_OBJECT_H
#define SCHEME_C_OBJECT_H

#include <stddef.h>
#include "type.h"

typedef struct Scheme_Object {
    Scheme_Object_Type type;
    union {
        struct {
            char value;
        } boolean;
        struct {
            long value;
        } fixnum;
    } data;
} Scheme_Object;

extern Scheme_Object* Alloc_Object();

extern Scheme_Object* Make_Fixnum(long value);

extern char Is_Fixnum(Scheme_Object* obj);

extern void Init_Scheme();

extern Scheme_Object* True;
extern Scheme_Object* False;

extern char Is_Boolean(Scheme_Object* obj);

extern char Is_False(Scheme_Object* obj);

extern char Is_True(Scheme_Object* obj);

#endif //SCHEME_C_OBJECT_H
