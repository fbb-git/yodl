#include "builtin.ih"

void (*builtin_setAction(Builtin *builtin, void (*action)()))()
{
    void (*old_action)() = builtin->d_action;
    builtin->d_action = action;
    return old_action;
}
