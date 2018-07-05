#include <stdio.h>
#include <stdlib.h>
#include "write.h"
#include "object.h"

static void
WritePair(FILE* out, SchemeObject* pair)
{
    SchemeObject* car = Car(pair);
    SchemeObject* cdr = Cdr(pair);
    Writer(out, car);
    if (cdr->type == PAIR) {
        fprintf(out, " ");
        WritePair(out, cdr);
    } else if (cdr->type == THE_EMPTY_LIST) {
        return;
    } else {
        fprintf(out, " . ");
        Writer(out, cdr);
    }
}

extern void
Writer(FILE* out, SchemeObject* obj)
{
    char c;
    char* str;

    switch (obj->type) {
        case THE_EMPTY_LIST:
            fprintf(out, "()");
            break;
        case BOOLEAN:
            fprintf(out, "#%c", IsFalse(obj) ? 'f' : 't');
            break;
        case SYMBOL:
            fprintf(out, "%s", obj->data.symbol.value);
            break;
        case FIXNUM:
            fprintf(out, "%ld", obj->data.fixnum.value);
            break;
        case CHARACTER:
            c = obj->data.character.value;
            fprintf(out, "#\\");
            switch (c) {
                case '\n':
                    fprintf(out, "newline");
                    break;
                case ' ':
                    fprintf(out, "space");
                    break;
                default:
                    putc(c, out);
                    break;
            }
            break;
        case STRING:
            str = obj->data.string.value;
            putchar('"');
//            putc('"', out);
            while (*str != '\0') {
                switch (*str) {
                    case '\n':
                        fprintf(out, "\\n");
                        break;
                    case '\\':
                        fprintf(out, "\\\\");
                        break;
                    case '"':
                        fprintf(out, "\\\"");
                        break;
                    default:
                        putc(*str, out);
                }
                str++;
            }
//            putc('"', out);
            putchar('"');
            break;
        case PAIR:
            fprintf(out, "(");
            WritePair(out, obj);
            fprintf(out, ")");
            break;
        case PRIMITIVE_PROCEDURE:
            fprintf(out, "#<primitive-procedure>");
        case COMPOUND_PROCEDURE:
            fprintf(out, "#<compound-procedure>");
            break;
        case INPUT_PORT:
            fprintf(out, "#<input-port>");
            break;
        case OUT_PORT:
            fprintf(out, "#<output-port>");
            break;
        case EOF_OBJECT:
            fprintf(out, "#<eof>");
            break;
        default:
            fprintf(stderr, "cannot write unknown type.\n");
            exit(1);
    }
}
