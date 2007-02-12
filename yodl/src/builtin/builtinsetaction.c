#include "builtin.ih"

void (*builtin_setAction(Builtin *builtin, void (*action)(void)))(void)
{
    void (*old_action)(void) = builtin->d_action;
    builtin->d_action = action;
    return old_action;
}
