#include "parser.ih"

void p_insert_no_chartab_ostream(register Parser *pp, char const *txt)
{
    /*
    warning("INSERT_NO_CHARTAB_OSTREAM %p: `%s'", pp->d_string_ptr, txt);
    */


    ostream_insert(pp->d_outs_ptr, txt);
}
