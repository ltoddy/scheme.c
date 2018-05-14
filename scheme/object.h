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
            char* value;
        } symbol;
        struct {
            long value;
        } fixnum;
        struct {
            char value;
        } character;
        struct {
            char* value;
        } string;
        struct {
            struct SchemeObject* car;
            struct SchemeObject* cdr;
        } pair;
    } data;
} SchemeObject;

extern SchemeObject* True;
extern SchemeObject* False;
extern SchemeObject* TheEmptyList;
extern SchemeObject* SymbolTable;
extern SchemeObject* QuoteSymbol;

extern SchemeObject* AllocObject();

extern SchemeObject* MakeFixnum(long value);

extern char IsFixnum(SchemeObject* obj);

extern char IsTheEmptyList(SchemeObject* obj);

extern char IsBoolean(SchemeObject* obj);

extern char IsFalse(SchemeObject* obj);

extern char IsTrue(SchemeObject* obj);

extern SchemeObject* MakeCharacter(char value);

extern char IsCharacter(SchemeObject* obj);

extern SchemeObject* MakeString(char* value);

extern char IsString(SchemeObject* obj);

extern SchemeObject* Cons(SchemeObject* car, SchemeObject* cdr);

extern char IsPair(SchemeObject* obj);

extern SchemeObject* Car(SchemeObject* pair);

extern void SetCar(SchemeObject* pair, SchemeObject* value);

extern SchemeObject* Cdr(SchemeObject* pair);

extern void SetCdr(SchemeObject* pair, SchemeObject* value);

extern SchemeObject* MakeSymbol(char* value);

extern char IsSymbol(SchemeObject* obj);

extern char IsQuote(SchemeObject* exp);

#endif //SCHEME_C_OBJECT_H
