#include "macro.ih"

void mc_destroy(void *macro)
{
    stack_destruct(&((Macro *)macro)->d_definition);
    stack_destruct(&((Macro *)macro)->d_arg);

    free(macro);
}
