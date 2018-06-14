#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtin.h"
#include "environment.h"
#include "predicate.h"

/* no GC */
extern SchemeObject*
AllocObject()
{
    SchemeObject* obj = malloc(sizeof(SchemeObject));
    if (obj == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }
    return obj;
}

extern SchemeObject*
MakeFixnum(long value)
{
    SchemeObject* obj = AllocObject();
    obj->type = FIXNUM;
    obj->data.fixnum.value = value;
    return obj;
}

extern char
IsFixnum(SchemeObject* obj)
{
    return obj->type == FIXNUM;
}

extern char
IsTheEmptyList(SchemeObject* obj)
{
    return obj == TheEmptyList;
}

extern char
IsBoolean(SchemeObject* obj)
{
    return obj->type == BOOLEAN;
}

extern char
IsFalse(SchemeObject* obj)
{
    return obj == False;
}

extern char
IsTrue(SchemeObject* obj)
{
    return !IsFalse(obj);
}

extern SchemeObject*
MakeCharacter(char value)
{
    SchemeObject* obj = AllocObject();
    obj->type = CHARACTER;
    obj->data.character.value = value;
    return obj;
}

extern char
IsCharacter(SchemeObject* obj)
{
    return obj->type == CHARACTER;
}

extern SchemeObject*
MakeString(char* value)
{
    SchemeObject* obj = AllocObject();
    obj->type = STRING;
    obj->data.string.value = value;
    return obj;
}

extern char
IsString(SchemeObject* obj)
{
    return obj->type == STRING;
}

extern SchemeObject*
Cons(SchemeObject* car, SchemeObject* cdr)
{
    SchemeObject* obj = AllocObject();
    obj->type = PAIR;
    obj->data.pair.car = car;
    obj->data.pair.cdr = cdr;
    return obj;
}

extern char
IsPair(SchemeObject* obj)
{
    return obj->type == PAIR;
}

extern SchemeObject*
Car(SchemeObject* pair)
{
    return pair->data.pair.car;
}

extern void
SetCar(SchemeObject* pair, SchemeObject* value)
{
    pair->data.pair.car = value;
}

extern SchemeObject*
Cdr(SchemeObject* pair)
{
    return pair->data.pair.cdr;
}

extern void
SetCdr(SchemeObject* pair, SchemeObject* value)
{
    pair->data.pair.cdr = value;
}

extern SchemeObject*
MakeSymbol(char* value)
{
    SchemeObject* obj;
    SchemeObject* element;

    /* search for they symbol in the symbol table */
    element = SymbolTable;
    while (!IsTheEmptyList(element)) {
        if (strcmp(Car(element)->data.symbol.value, value) == 0) {
            return Car(element);
        }
        element = Cdr(element);
    }

    /* create the symbol and it to the symbol table */
    obj = AllocObject();
    obj->type = SYMBOL;
    obj->data.symbol.value = malloc(strlen(value) + 1);
    if (obj->data.symbol.value == NULL) {
        fprintf(stderr, "Out of memory.\n");
        exit(1);
    }
    strcpy(obj->data.symbol.value, value);
    SymbolTable = Cons(obj, SymbolTable);
    return obj;
}

extern char
IsSymbol(SchemeObject* obj)
{
    return obj->type == SYMBOL;
}

extern char
IsQuote(SchemeObject* exp)
{
    return IsTaggedList(exp, QuoteSymbol);
}
