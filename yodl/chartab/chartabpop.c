#include "chartab.ih"

/*
    Pushing method: push active
            reset active

    Then here, at popping:
            reset active to tos()
            pop stack
*/

Result chartab_pop()
{
    if (!stack_size(&chartab.d_chartab_st))
        return FAILED;

    chartab.d_active = stack_tos(&chartab.d_chartab_st)->u_charpp;
    stack_pop(&chartab.d_chartab_st);

    return SUCCESS;
}
