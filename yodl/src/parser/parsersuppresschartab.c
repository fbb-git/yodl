#include "parser.ih"

void (*parser_suppress_chartab(register Parser *pp))
                                            (struct Parser *, char const *)
{
    register void (*ret)(struct Parser *, char const *) = pp->d_insert;

    if (pp->d_insert == p_insert_chartab_string)
        pp->d_insert = p_insert_no_chartab_string;
    else if (pp->d_insert == p_insert_chartab_ostream)
        pp->d_insert = p_insert_no_chartab_ostream;

    return ret;
}
