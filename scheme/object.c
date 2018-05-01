#include "object.h"
#include <stdio.h>
#include <stdlib.h>

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
