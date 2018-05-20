#ifndef SCHEME_C_APPLY_H
#define SCHEME_C_APPLY_H

#include "object.h"

extern SchemeObject* ApplyProc(SchemeObject* arguments);

extern SchemeObject* ApplyOperator(SchemeObject* arguments);

extern SchemeObject* ApplyOperands(SchemeObject* arguments);

#endif //SCHEME_C_APPLY_H
