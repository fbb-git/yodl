#include "macro.ih"

Result macro_push(Macro *macro, char const *definition, unsigned nargs)
{
    stack_push(&macro->d_definition, new_str(definition));
    stack_push(&macro->d_arg, (void *)nargs);

    return SUCCESS;
}
