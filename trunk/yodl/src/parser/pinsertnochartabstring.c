#include "parser.ih"

void p_insert_no_chartab_string(register Parser *pp, char const *txt)
{
    string_addstr(pp->d_string_ptr, txt);
}
