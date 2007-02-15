#include "parser.ih"

void p_insert_no_chartab_ostream(register Parser *pp, char const *txt)
{
    ostream_insert(pp->d_outs_ptr, txt);
}
