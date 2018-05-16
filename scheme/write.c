#include <stdio.h>
#include <stdlib.h>
#include "write.h"
#include "object.h"

static void WritePair(SchemeObject* pair)
{
    SchemeObject* car = Car(pair);
    SchemeObject* cdr = Cdr(pair);
    Write(car);
    if (cdr->type == PAIR) {
        printf(" ");
        WritePair(cdr);
    } else if (cdr->type == THE_EMPTY_LIST) {
        return;
    } else {
        printf(" . ");
        Write(cdr);
    }
}

void Write(SchemeObject* obj)
{
    char c;
    char* str;

    switch (obj->type) {
        case SYMBOL:
            printf("%s", obj->data.symbol.value);
            break;
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
        case PAIR:
            printf("(");
            WritePair(obj);
            printf(")");
            break;
        case THE_EMPTY_LIST:
            printf("()");
            break;
        case PRIMITIVE_PROCEDURE:
        case COMPOUND_PROCEDURE:
            printf("#<procedure>");
            break;
        default:
            fprintf(stderr, "cannot write unknown type.\n");
            exit(1);
    }
}
