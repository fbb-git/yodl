#include "parser.ih"

void p_insert_no_chartab_string(register Parser *pp, char const *txt)
{
    /*
    warning("INSERT_NO_CHARTAB_STRING %p: `%s'", pp->d_string_ptr, txt);
    */

    string_addstr(pp->d_string_ptr, txt);
}
