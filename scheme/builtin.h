#ifndef SCHEME_C_BUILTIN_H
#define SCHEME_C_BUILTIN_H

#include "object.h"

#define CAAR(obj)   Car(Car(obj))
#define CADR(obj)   Car(Cdr(obj))
#define CDAR(obj)   Cdr(Car(obj))
#define CDDR(obj)   Cdr(Cdr(obj))
#define CAAAR(obj)  Car(Car(Car(obj)))
#define CAADR(obj)  Car(Car(Cdr(obj)))
#define CADAR(obj)  Car(Cdr(Car(obj)))
#define CADDR(obj)  Car(Cdr(Cdr(obj)))
#define CDAAR(obj)  Cdr(Car(Car(obj)))
#define CDADR(obj)  Cdr(Car(Cdr(obj)))
#define CDDAR(obj)  Cdr(Cdr(Car(obj)))
#define CDDDR(obj)  Cdr(Cdr(Cdr(obj)))
#define CAAAAR(obj) Car(Car(Car(Car(obj))))
#define CAAADR(obj) Car(Car(Car(Cdr(obj))))
#define CAADAR(obj) Car(Car(Cdr(Car(obj))))
#define CAADDR(obj) Car(Car(Cdr(Cdr(obj))))
#define CADAAR(obj) Car(Cdr(Car(Car(obj))))
#define CADADR(obj) Car(Cdr(Car(Cdr(obj))))
#define CADDAR(obj) Car(Cdr(Cdr(Car(obj))))
#define CADDDR(obj) Car(Cdr(Cdr(Cdr(obj))))
#define CDAAAR(obj) Cdr(Car(Car(Car(obj))))
#define CDAADR(obj) Cdr(Car(Car(Cdr(obj))))
#define CDADAR(obj) Cdr(Car(Cdr(Car(obj))))
#define CDADDR(obj) Cdr(Car(Cdr(Cdr(obj))))
#define CDDAAR(obj) Cdr(Cdr(Car(Car(obj))))
#define CDDADR(obj) Cdr(Cdr(Car(Cdr(obj))))
#define CDDDAR(obj) Cdr(Cdr(Cdr(Car(obj))))
#define CDDDDR(obj) Cdr(Cdr(Cdr(Cdr(obj))))

extern SchemeObject* OkSymbol;

extern void InitScheme();

// primitive procedure
extern SchemeObject* AddProcedure(SchemeObject* arguments); /* + */

extern SchemeObject* SubProcedure(SchemeObject* arguments); /* - */

extern SchemeObject* MulProcedure(SchemeObject* arguments); /* * */

extern SchemeObject* QuotientProcedure(SchemeObject* arguments); /* quotient */

extern SchemeObject* RemainderProcedure(SchemeObject* arguments); /* remainder */

extern SchemeObject* IsNumberEqualProcedure(SchemeObject* arguments); /* = */

extern SchemeObject* IsLessThanProcedure(SchemeObject* arguments); /* < */

extern SchemeObject* IsGreaterThanProcedure(SchemeObject* arguments); /* > */

extern SchemeObject* ConsProcedure(SchemeObject* arguments); /* (cons ...) */

extern SchemeObject* CarProcedure(SchemeObject* arguments); /* (car ...) */

extern SchemeObject* CdrProcedure(SchemeObject* arguments); /* (cdr ...) */

extern SchemeObject* SetCarProcedure(SchemeObject* arguments); /* (set-car! ...) */

extern SchemeObject* SetCdrProcedure(SchemeObject* arguments); /* (set-cdr! ...) */

extern SchemeObject* ListProcedure(SchemeObject* arguments); /* (list ...) */

extern SchemeObject* IsEqProcedure(SchemeObject* arguments); /* (eq? ...) */

extern SchemeObject* IsNullProcedure(SchemeObject* arguments); /* (null? ...) */

extern SchemeObject* IsBooleanProcedure(SchemeObject* arguments); /* (boolean? ...) */

extern SchemeObject* IsSymbolProcedure(SchemeObject* arguments); /* (symbol? ...) */

extern SchemeObject* IsIntegerProcedure(SchemeObject* arguments); /* (integer? ...) */

extern SchemeObject* IsCharProcedure(SchemeObject* arguments); /* (char? ...) */

extern SchemeObject* IsStringProcedure(SchemeObject* arguments); /* (string? ...) */

extern SchemeObject* IsPairProcedure(SchemeObject* arguments); /* (pair? ...) */

extern SchemeObject* IsProcedureProcedure(SchemeObject* arguments); /* (procedure? ...) */

extern SchemeObject* NumberToStringProcedure(SchemeObject* arguments); /* (number->string ...) */

extern SchemeObject* StringToNumberProcedure(SchemeObject* arguments); /* (string->number ...) */

extern SchemeObject* SymbolToStringProcedure(SchemeObject* arguments); /* (symbol->string ...) */

extern SchemeObject* StringToSymbolProcedure(SchemeObject* arguments); /* (string->symbol ...) */

extern SchemeObject* CharToIntegerProcedure(SchemeObject* arguments); /* (char->integer ...) */

extern SchemeObject* IntegerToCharProcedure(SchemeObject* arguments); /* (integer->char ...) */

// end primitive procedure

#endif //SCHEME_C_BUILTIN_H
