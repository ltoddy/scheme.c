#include "read.h"
#include <ctype.h>
#include <libio.h>
#include <stdio.h>
#include <stdlib.h>

static char IsDelimiter(int c)
{
    return isspace(c) ||
           c == EOF ||
           c == '(' ||
           c == ')' ||
           c == '"' ||
           c == ';';
}

static int Peek(FILE* in)
{
    int c = getc(in);
    ungetc(c, in);
    return c;
}

static void SkipWhitespace(FILE* in)
{
    int c;
    while ((c = getc(in)) != EOF) {
        if (isspace(c)) {
            continue;
        } else if (c == ';') { /* comments are whitespace also */
            while ((c = getc(in)) != EOF && (c != '\n'));
            continue;
        }
        ungetc(c, in);
        break;
    }
}

SchemeObject* Read(FILE* in)
{
    int c = 0;
    short sign = 1;
    long num = 0;
    SkipWhitespace(in);
    c = getc(in);
    if (c == '#') {
        c = getc(in);
        switch (c) {
            case 't':
                return True;
            case 'f':
                return False;
            default:
                fprintf(stderr, "unknown boolean literal\n");
                exit(1);
        }
    } else if (isdigit(c) || (c == '-' && isdigit(Peek(in)))) {
        /* read a fixnum */
        if (c == '-') {
            sign = -1;
        } else {
            ungetc(c, in);
        }
        while (isdigit(c = getc(in))) {
            num = (num * 10) + (c - '0');
        }
        num *= sign;
        if (IsDelimiter(c)) {
            ungetc(c, in);
            return MakeFixnum(num);
        } else {
            fprintf(stderr, "number not followed by delimiter.\n");
            exit(1);
        }
    } else {
        fprintf(stderr, "bad input. Unexpected '%c'\n", c);
        exit(1);
    }
    fprintf(stderr, "read illegal state.\n");
    exit(1);
}
