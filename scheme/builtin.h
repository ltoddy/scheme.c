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

extern SchemeObject* True;
extern SchemeObject* False;
extern SchemeObject* TheEmptyList;
extern SchemeObject* SymbolTable;
extern SchemeObject* QuoteSymbol;
extern SchemeObject* TheEmptyEnvironment;
extern SchemeObject* TheGlobalEnvironment;
extern SchemeObject* DefineSymbol;
extern SchemeObject* SetSymbol;
extern SchemeObject* OkSymbol;
extern SchemeObject* IfSymbol;

extern void InitScheme();

#endif //SCHEME_C_BUILTIN_H
