#include "macro.ih"

Result macro_pop(Macro *macro)
{
    if (!stack_size(&macro->d_definition))
        return FAILED;

    stack_pop(&macro->d_definition);
    stack_pop(&macro->d_arg);

    return SUCCESS;
}
