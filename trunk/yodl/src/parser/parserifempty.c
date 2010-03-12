#include "parser.ih"

bool parser_if_empty(register Parser *pp, char **parlist)
{
    if (!*parlist[0])           /* true if nothing there                    */
        return true;

    parlist[0] = parser_eval(pp, parlist[0]);

    return !*parlist[0];        /* true if first element is empty string    */
}
