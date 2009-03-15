#include "parser.ih"

void parser_apply_chartab(register Parser *pp)
{
    if (chartab_isActive())
    {
        if (pp->d_insert == p_insert_no_chartab_string)
            pp->d_insert = p_insert_chartab_string;

        else if (pp->d_insert == p_insert_no_chartab_ostream)
            pp->d_insert = p_insert_chartab_ostream;
    }
    else /* no chartab requested */
    {
        if (pp->d_insert == p_insert_chartab_string)
            pp->d_insert = p_insert_no_chartab_string;

        else if (pp->d_insert == p_insert_chartab_ostream)
            pp->d_insert = p_insert_no_chartab_ostream;
    }
}
