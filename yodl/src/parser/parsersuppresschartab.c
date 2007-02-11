#include "parser.ih"

void *parser_suppress_chartab(register Parser *pp)
{
    Parser_Ufunvoid ret;

    ret.u_funp = pp->d_insert;

    if (pp->d_insert == p_insert_chartab_string)
        pp->d_insert = p_insert_no_chartab_string;
    else if (pp->d_insert == p_insert_chartab_ostream)
        pp->d_insert = p_insert_no_chartab_ostream;

    return ret.u_voidp;
}
