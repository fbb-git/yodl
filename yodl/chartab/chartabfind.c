#include "chartab.ih"

Result chartab_find(char const **ctab)
{
    if (ctab == (char const **)chartab.d_active)
        return SUCCESS;

    return stack_contains(&chartab.d_chartab_st, ctab) ? SUCCESS : FAILED;
}
