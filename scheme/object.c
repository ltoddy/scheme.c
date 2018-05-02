#include "object.h"
#include <stdio.h>
#include <stdlib.h>

/* no GC */
Scheme_Object* Alloc_Object()
{
    Scheme_Object* obj = malloc(sizeof(Scheme_Object));
    if (obj == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }
    return obj;
}

Scheme_Object* Make_Fixnum(long value)
{
    Scheme_Object* obj = Alloc_Object();
    obj->type = FIXNUM;
    obj->data.fixnum.value = value;
    return obj;
}

char Is_Fixnum(Scheme_Object* obj)
{
    return obj->type == FIXNUM;
}

Scheme_Object* True = NULL;
Scheme_Object* False = NULL;

void Init_Scheme()
{
    True = Alloc_Object();
    True->type = BOOLEAN;
    True->data.boolean.value = 1;

    False = Alloc_Object();
    False->type = BOOLEAN;
    False->data.boolean.value = 0;
}

char Is_Boolean(Scheme_Object* obj)
{
    return obj->type == BOOLEAN;
}

char Is_False(Scheme_Object* obj)
{
    return obj == False;
}

char Is_True(Scheme_Object* obj)
{
    return !Is_False(obj);
}
