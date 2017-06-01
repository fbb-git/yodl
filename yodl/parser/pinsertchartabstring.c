#include "parser.ih"

void p_insert_chartab_string(register Parser *pp, char const *txt)
{
    String *sp = chartab_apply(txt);
    string_add(pp->d_string_ptr, sp);
    string_delete(&sp);
}
