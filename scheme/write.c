#include <stdio.h>
#include <stdlib.h>
#include "write.h"
#include "object.h"

void Write(Scheme_Object* obj)
{
    switch (obj->type) {
        case FIXNUM:
            printf("%ld", obj->data.fixnum.value);
            break;
        case BOOLEAN:
            printf("#%c", Is_False(obj) ? 'f' : 't');
            break;
        default:
            fprintf(stderr, "cannot write unknown type.\n");
            exit(1);
    }
}