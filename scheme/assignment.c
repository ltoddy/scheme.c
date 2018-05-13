#include "assignment.h"
#include "environment.h"

void DefineVariable(SchemeObject* var, SchemeObject* val, SchemeObject* environ)
{
    SchemeObject* frame = FirstFrame(environ);
    SchemeObject* vars = FrameVariables(frame);
    SchemeObject* vals = FrameValues(frame);

    while (!IsTheEmptyList(vals)) {
        if (var == Car(vars)) {
            SetCar(vals, val);
            return;
        }
        vars = Cdr(vars);
        vals = Cdr(vals);
    }
    AddBindingToFrame(var, val, frame);
}
