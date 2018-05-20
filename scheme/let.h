#ifndef SCHEME_C_LET_H
#define SCHEME_C_LET_H

#include "object.h"

extern SchemeObject* LetSymbol;

extern char IsLet(SchemeObject* exp);

extern SchemeObject* LetToApplication(SchemeObject* exp);

#endif //SCHEME_C_LET_H
