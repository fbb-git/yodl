#include "macro.ih"

Result macro_push(Macro *macro, char const *definition, size_t nargs)
{
    register StackValue stValue;

    stValue.u_voidp = new_str(definition);
    stack_push(&macro->d_definition, stValue);

    stValue.u_size_t = nargs;
    stack_push(&macro->d_arg, stValue);

    return SUCCESS;
}
