#include "parser.ih"

bool parser_if_strequal(register Parser *pp, register char **parlist)
{
    return !strcmp(parser_strvalue(pp, parlist[0]), parser_strvalue(pp, parlist[1]));
}
