#include "parser.ih"

void p_insert_chartab_ostream(register Parser *pp, char const *txt)
{
    register String *sp = chartab_apply(txt);

    ostream_insert(pp->d_outs_ptr, string_str(sp));
    string_destructor(sp);
}
