#include "gc.h"

void
collect(SchemeObject* environment)
{
    // TODO
}

static void
collect_linked_list(SchemeObject* environment)
{
    /**
     * TODO
     * ((var-1, val-1) -> (var-2, val-2) -> (var-3, val-3) ...)
     * 回收这样链表形式
     */
}
