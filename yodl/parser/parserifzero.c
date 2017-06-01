#include "parser.ih"

bool parser_if_zero(register Parser *pp, register char **parlist)
{
    int value;

    return  p_valueOf(pp, &value, parlist[0]) &&
            value == 0;
}
