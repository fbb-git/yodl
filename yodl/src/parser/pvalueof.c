#include "parser.ih"

bool  p_valueOf(register Parser *pp, int *value, char const *txt)
{
    if (!*txt)
        return false;                       /* empty text is no value   */

    if (sscanf(txt, "%d", value) > 0)       /* txt is a numerical value  */
        return true;                        /* return `value found'      */

    return counter_has_value(value,
                             hashmap_find(pp->d_symtab_ptr, txt, COUNTER));
}
