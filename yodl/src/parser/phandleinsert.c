#include "parser.ih"

bool p_handle_insert(register Parser *pp)
{
    (*pp->d_insert)(pp, lexer_text(&pp->d_lexer));

    return true;
}

/*  Possibilities:
        p_insert_chartab_string;        -> chartab_apply
        p_insert_chartab_ostream;       -> chartab_apply
        p_insert_no_chartab_string;
        p_insert_no_chartab_ostream;
        p_insert_nothing

    chartab_apply visits all characters of a string and converts them to the
    converted value. The converted string is returns. The characters to
    convert are obtained from the text matching the last TOKEN returned by the 
    lexer 
*/
