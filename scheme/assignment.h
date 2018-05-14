#ifndef SCHEME_C_ASSIGNMENT_H
#define SCHEME_C_ASSIGNMENT_H

#include "object.h"

extern SchemeObject* SetSymbol;

extern char IsAssignment(SchemeObject* exp);

extern SchemeObject* AssignmentVariable(SchemeObject* exp);

extern SchemeObject* AssignmentValue(SchemeObject* exp);

#endif //SCHEME_C_ASSIGNMENT_H
