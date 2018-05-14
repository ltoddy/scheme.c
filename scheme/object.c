#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtin.h"
#include "environment.h"
#include "predicate.h"

/* no GC */
SchemeObject* AllocObject()
{
    SchemeObject* obj = malloc(sizeof(SchemeObject));
    if (obj == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }
    return obj;
}

SchemeObject* MakeFixnum(long value)
{
    SchemeObject* obj = AllocObject();
    obj->type = FIXNUM;
    obj->data.fixnum.value = value;
    return obj;
}

char IsFixnum(SchemeObject* obj)
{
    return obj->type == FIXNUM;
}

char IsTheEmptyList(SchemeObject* obj)
{
    return obj == TheEmptyList;
}

char IsBoolean(SchemeObject* obj)
{
    return obj->type == BOOLEAN;
}

char IsFalse(SchemeObject* obj)
{
    return obj == False;
}

char IsTrue(SchemeObject* obj)
{
    return !IsFalse(obj);
}

SchemeObject* MakeCharacter(char value)
{
    SchemeObject* obj = AllocObject();
    obj->type = CHARACTER;
    obj->data.character.value = value;
    return obj;
}

char IsCharacter(SchemeObject* obj)
{
    return obj->type == CHARACTER;
}

SchemeObject* MakeString(char* value)
{
    SchemeObject* obj = AllocObject();
    obj->type = STRING;
    obj->data.string.value = value;
    return obj;
}

char IsString(SchemeObject* obj)
{
    return obj->type == STRING;
}

SchemeObject* Cons(SchemeObject* car, SchemeObject* cdr)
{
    SchemeObject* obj = AllocObject();
    obj->type = PAIR;
    obj->data.pair.car = car;
    obj->data.pair.cdr = cdr;
    return obj;
}

char IsPair(SchemeObject* obj)
{
    return obj->type == PAIR;
}

SchemeObject* Car(SchemeObject* pair)
{
    return pair->data.pair.car;
}

void SetCar(SchemeObject* pair, SchemeObject* value)
{
    pair->data.pair.car = value;
}

SchemeObject* Cdr(SchemeObject* pair)
{
    return pair->data.pair.cdr;
}

void SetCdr(SchemeObject* pair, SchemeObject* value)
{
    pair->data.pair.cdr = value;
}

SchemeObject* MakeSymbol(char* value)
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

char IsSymbol(SchemeObject* obj)
{
    return obj->type == SYMBOL;
}

char IsQuote(SchemeObject* exp)
{
    return IsTaggedList(exp, QuoteSymbol);
}
