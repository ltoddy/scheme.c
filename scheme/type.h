#ifndef SCHEME_C_TYPE_H
#define SCHEME_C_TYPE_H

typedef enum {
    BOOLEAN,
    FIXNUM,
    CHARACTER,
    STRING,
    THE_EMPTY_LIST,
    PAIR, SYMBOL,
    PRIMITIVE_PROCEDURE,
    COMPOUND_PROCEDURE
} SchemeObjectType;

#endif //SCHEME_C_TYPE_H
