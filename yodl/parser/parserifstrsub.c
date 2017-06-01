#include "parser.ih"

/*
    checks whether parlist[0] (hashtack) contains parlist[1] (needle)
*/

bool parser_if_strsub(register Parser *pp, register char **parlist)
{
    return strstr(parser_strvalue(pp, parlist[0]),
                  parser_strvalue(pp, parlist[1])) != NULL;
}
