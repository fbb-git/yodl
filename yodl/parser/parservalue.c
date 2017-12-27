#include "parser.ih"

Result parser_value(register Parser *pp, int *value, char const *text)
{
    Term term = {text};             // set the text in term

    p_value(pp, &term);
    int accu = term.value;              // accumulate terms: 1st term

    while (1)                           // process all +/- operators
    {
        switch (term.binop)
        {
            case '+':
                p_value(pp, &term);
                accu += term.value;
            break;

            case '-':
                p_value(pp, &term);
                accu -= term.value;
            break;

            default:                    // end of sequence
                *value = accu;
            return term.result;
        }
    }
}
