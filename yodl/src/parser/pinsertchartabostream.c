#include "parser.ih"

void p_insert_chartab_ostream(register Parser *pp, char const *txt)
{
    /*
    warning("INSERT_CHARTAB_OSTREAM %p: `%s'", pp->d_string_ptr, txt);
    */

    register String *sp = chartab_apply(txt);

    ostream_insert(pp->d_outs_ptr, string_str(sp));
    string_destructor(sp);
}
