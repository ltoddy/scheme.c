#include <stdio.h>
#include <stdlib.h>
#include "write.h"
#include "object.h"

void Write(SchemeObject* obj)
{
    switch (obj->type) {
        case FIXNUM:
            printf("%ld", obj->data.fixnum.value);
            break;
        case BOOLEAN:
            printf("#%c", IsFalse(obj) ? 'f' : 't');
            break;
        default:
            fprintf(stderr, "cannot write unknown type.\n");
            exit(1);
    }
}
