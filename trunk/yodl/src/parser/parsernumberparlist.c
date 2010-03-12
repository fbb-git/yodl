#include "parser.ih"

/*
    The `list' argument may be
        - a numerical value
        - the name of a counter
    The returned value is the int-value of either the string (as a
    number) or the counter's value

    formerly: igram_isnumber()

*/
Result parser_number_parlist(register Parser *pp, int *valptr, bool skipws)
{
    register char *text = parser_parlist(pp, COLLECT_SET);
    Result res = parser_value(pp, valptr, text);        /* obtain the value */

    if (skipws)
        parser_skipws(pp);

    free(text);
    return res;
}
