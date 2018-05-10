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

static char IsInitial(int c)
{
    return isalpha(c) ||
           c == '*' ||
           c == '/' ||
           c == '>' ||
           c == '<' ||
           c == '=' ||
           c == '?' ||
           c == '!';
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
        default:
            break;
    }
    PeekExpectedDelimiter(in);
    return MakeCharacter((char) c);
}

static SchemeObject* ReadPair(FILE* in)
{
    int c;
    SchemeObject* car;
    SchemeObject* cdr;

    SkipWhitespace(in);

    c = getc(in);
    if (c == ')') { /* read the empty list */
        return The_Empty_List;
    }
    ungetc(c, in);

    car = Read(in);
    SkipWhitespace(in);

    c = getc(in);
    if (c == '.') { /* read improper list */
        c = Peek(in);
        if (!IsDelimiter(c)) {
            fprintf(stderr, "dot not followed by delimiter.\n");
            exit(1);
        }
        cdr = Read(in);
        SkipWhitespace(in);
        c = getc(in);
        if (c != ')') {
            fprintf(stderr, "where was the trailing right paren?\n");
            exit(1);
        }
        return Cons(car, cdr);
    } else { /* read list */
        ungetc(c, in);
        cdr = ReadPair(in);
        return Cons(car, cdr);
    }
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
    } else if (IsInitial(c) || ((c == '+') || (c == '-')) && IsDelimiter(Peek(in))) { /* read a symbol */
        int i = 0;
        while (IsInitial(c) || isdigit(c) || c == '+' || c == '-') { /* subtract 1 to save space for '\0' terminator */
            if (i < MAX_BUFFER - 1) {
                buffer[i++] = (char) c;
            } else {
                fprintf(stderr, "symbol too long. Maximum length is %d\n", MAX_BUFFER);
                exit(1);
            }
            c = getc(in);
        }
        if (IsDelimiter(c)) {
            buffer[i] = '\0';
            ungetc(c, in);
            return MakeSymbol(buffer);
        } else {
            fprintf(stderr, "symbol not followed by delimiter. Found '%c'\n", c);
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
    } else if (c == '(') { /* read the empty list or pair */
        return ReadPair(in);
    } else {
        fprintf(stderr, "bad input. Unexpected '%c'\n", c);
        exit(1);
    }
    fprintf(stderr, "read illegal state.\n");
    exit(1);
}
