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

static void SkipExpectedString(FILE* in, char* str)
{
    int c;
    while (*str != '\0') {
        c = getc(in);
        if (c != *str) {
            fprintf(stderr, "unexpected character '%c'\n", c);
            exit(1);
        }
        str++;
    }
}

static void PeekExpectedDelimiter(FILE* in)
{
    if (!IsDelimiter(Peek(in))) {
        fprintf(stderr, "character not followed by delimiter.");
        exit(1);
    }
}

static SchemeObject* ReadCharacter(FILE* in)
{
    int c = getc(in);
    switch (c) {
        case EOF:
            fprintf(stderr, "incomplete character literal.\n");
            exit(1);
        case 's':
            if (Peek(in) == 'p') {
                SkipExpectedString(in, "pace");
                PeekExpectedDelimiter(in);
                return MakeCharacter(' ');
            }
            break;
        case 'n':
            if (Peek(in) == 'e') {
                SkipExpectedString(in, "ewline");
                PeekExpectedDelimiter(in);
                return MakeCharacter('\n');
            }
            break;
    }
    PeekExpectedDelimiter(in);
    return MakeCharacter(c);
}

SchemeObject* Read(FILE* in)
{
    int c = 0;
    short sign = 1;
    long num = 0;

#define MAX_BUFFER 1024
    char buffer[MAX_BUFFER];

    SkipWhitespace(in);
    c = getc(in);
    if (c == '#') { /* read boolean or character */
        c = getc(in);
        switch (c) {
            case 't':
                return True;
            case 'f':
                return False;
            case '\\':
                return ReadCharacter(in);
            default:
                fprintf(stderr, "unknown boolean or characcter literal.\n");
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
    } else if (c == '"') { /* read a string */
        int i = 0;
        while ((c = getc(in)) != '"') {
            if (c == '\\') {
                c = getc(in);
                if (c == 'n') {
                    c = '\n';
                }
            }
            if (c == EOF) {
                fprintf(stderr, "non-terminated string literal.\n");
                exit(1);
            }
            if (i < MAX_BUFFER - 1) {
                buffer[i++] = (char) c;
            } else {
                fprintf(stderr, "string too long. Maximum length is %d\n", MAX_BUFFER);
                exit(1);
            }
        }
        buffer[i] = '\0';
        return MakeString(buffer);
    } else {
        fprintf(stderr, "bad input. Unexpected '%c'\n", c);
        exit(1);
    }
    fprintf(stderr, "read illegal state.\n");
    exit(1);
}
