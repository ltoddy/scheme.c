#ifndef SCHEME_C_IO_H
#define SCHEME_C_IO_H

#include "object.h"

/* I/O primitive procedure */
extern SchemeObject* EOF_OBJ;

extern SchemeObject* LoadProcedure(SchemeObject* arguments);

extern SchemeObject* OpenInputPortProcedure(SchemeObject* arguments);

extern SchemeObject* CloseInputPortProcedure(SchemeObject* arguments);

extern SchemeObject* IsInputPortProcedure(SchemeObject* arguments);

extern SchemeObject* ReadProcedure(SchemeObject* arguments);

extern SchemeObject* ReadCharProcedure(SchemeObject* arguments);

#endif //SCHEME_C_IO_H
