#ifndef SCHEME_C_OBJECT_H
#define SCHEME_C_OBJECT_H

#include <stddef.h>
#include "type.h"

typedef struct SchemeObject {
    SchemeObjectType type;
    union {
        struct {
            char value;
        } boolean;
        struct {
            long value;
        } fixnum;
    } data;
} SchemeObject;

extern SchemeObject* AllocObject();

extern SchemeObject* MakeFixnum(long value);

extern char IsFixnum(SchemeObject* obj);

extern void InitScheme();

extern SchemeObject* True;
extern SchemeObject* False;

extern char IsBoolean(SchemeObject* obj);

extern char IsFalse(SchemeObject* obj);

extern char IsTrue(SchemeObject* obj);

#endif //SCHEME_C_OBJECT_H
