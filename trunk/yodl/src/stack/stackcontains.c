#include "stack.ih"

bool stack_contains(Stack *sp, char const **ctab)
{
    register StackValue *vp = sp->d_value;
    register size_t idx;

    for (idx = sp->d_n; idx--; vp++)
    {
        if (ctab == vp->u_charCpp)
            return true;
    }

    return false;
}
