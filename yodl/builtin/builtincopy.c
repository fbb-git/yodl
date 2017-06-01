#include "builtin.ih"

Builtin *builtin_copy(Builtin const *builtin)
{
    Builtin *copy = new_memory(1, sizeof(Builtin));
    copy->d_name = builtin->d_name;
    copy->d_action = builtin->d_action;

    return copy;
}
