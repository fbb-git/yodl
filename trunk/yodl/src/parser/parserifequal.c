#include "parser.ih"

bool parser_if_equal(register Parser *pp, register char **parlist)
{
    int v1;
    int v2;

    return
        p_valueOf(pp, &v1, parlist[0]) &&
        p_valueOf(pp, &v2, parlist[1]) &&
        v1 == v2;
}
