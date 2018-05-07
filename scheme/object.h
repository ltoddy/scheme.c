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
        struct {
            char value;
        } character;
        struct {
            char* value;
        } string;
    } data;
} SchemeObject;

extern SchemeObject* AllocObject();

extern SchemeObject* MakeFixnum(long value);

extern char IsFixnum(SchemeObject* obj);

extern void InitScheme();

extern SchemeObject* True;
extern SchemeObject* False;
extern SchemeObject* The_Empty_List;

extern char IsBoolean(SchemeObject* obj);

extern char IsFalse(SchemeObject* obj);

extern char IsTrue(SchemeObject* obj);

extern SchemeObject* MakeCharacter(char value);

extern char IsCharacter(SchemeObject* obj);

extern SchemeObject* MakeString(char* value);

extern char IsString(SchemeObject* obj);

#endif //SCHEME_C_OBJECT_H
