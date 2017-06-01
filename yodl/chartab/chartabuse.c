#include "chartab.ih"

/*
    Method: push active (if requested),
            reset active

    Then at popping:
            reset active to tos()
            pop stack
*/

Result chartab_use(HashMap *symtab, char const *name, bool push)
{
    register StackValue stValue;

    if (push)
    {
        stValue.u_charpp = chartab.d_active;
        stack_push(&chartab.d_chartab_st, stValue);
    }

    if (!*name)
        chartab.d_active = NULL;
    else
    {
        HashItem *item = hashmap_find(symtab, name, CHARTABLE);
        if (item == PFAILED)
            return FAILED;

        chartab.d_active = (char **)hashitem_value(item);
    }

    return SUCCESS;
}
