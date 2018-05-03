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

void InitScheme()
{
    True = AllocObject();
    True->type = BOOLEAN;
    True->data.boolean.value = 1;

    False = AllocObject();
    False->type = BOOLEAN;
    False->data.boolean.value = 0;
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
