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

extern SchemeObject* IsEOFObjectProcedure(SchemeObject* arguments);

extern SchemeObject* OpenOutputPortProcedure(SchemeObject* arguments);

extern SchemeObject* CloseOutputPortProcedure(SchemeObject* arguments);

extern SchemeObject* IsOutputPortProcedure(SchemeObject* arguments);

extern SchemeObject* WriteCharProcedure(SchemeObject* arguments);

extern SchemeObject* WriteProcedure(SchemeObject* arguments);

extern SchemeObject* ErrorProcedure(SchemeObject* arguments);

#endif //SCHEME_C_IO_H
