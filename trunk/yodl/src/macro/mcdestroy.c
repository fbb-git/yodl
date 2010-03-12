#include "macro.ih"

void mc_destroy(void *macro)
{
    stack_destroy(&((Macro *)macro)->d_definition);
    stack_destroy(&((Macro *)macro)->d_arg);
}
