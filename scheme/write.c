#include <stdio.h>
#include <stdlib.h>
#include "write.h"
#include "object.h"

void Write(SchemeObject* obj)
{
    char c;
    char* str;

    switch (obj->type) {
        case FIXNUM:
            printf("%ld", obj->data.fixnum.value);
            break;
        case BOOLEAN:
            printf("#%c", IsFalse(obj) ? 'f' : 't');
            break;
        case CHARACTER:
            c = obj->data.character.value;
            printf("#\\");
            switch (c) {
                case '\n':
                    printf("newline");
                    break;
                case ' ':
                    printf("space");
                    break;
                default:
                    putchar(c);
                    break;
            }
            break;
        case STRING:
            str = obj->data.string.value;
            putchar('"');
            while (*str != '\0') {
                switch (*str) {
                    case '\n':
                        printf("\\n");
                        break;
                    case '\\':
                        printf("\\\\");
                        break;
                    case '"':
                        printf("\\\"");
                        break;
                    default:
                        putchar(*str);
                }
                str++;
            }
            putchar('"');
            break;
        default:
            fprintf(stderr, "cannot write unknown type.\n");
            exit(1);
    }
}
