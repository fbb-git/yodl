#include "parser.ih"

void p_insert_chartab_string(register Parser *pp, char const *txt)
{
    /*
    warning("INSERT_CHARTAB_STRING %p: `%s'", pp->d_string_ptr, txt);
    */

    register String *sp = chartab_apply(txt);
    string_add(pp->d_string_ptr, sp);
    string_destructor(sp);
}
