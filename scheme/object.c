#include "object.h"
#include <stdio.h>
#include <stdlib.h>

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

SchemeObject* True = NULL;
SchemeObject* False = NULL;
SchemeObject* The_Empty_List = NULL;

void InitScheme()
{
    True = AllocObject();
    True->type = BOOLEAN;
    True->data.boolean.value = 1;

    False = AllocObject();
    False->type = BOOLEAN;
    False->data.boolean.value = 0;

    The_Empty_List = AllocObject();
    The_Empty_List->type = THE_EMPTY_LIST;
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
