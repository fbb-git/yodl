#include "builtin.ih"

void builtin_call(Builtin *builtin)
{
    (*builtin->d_action)();
}
