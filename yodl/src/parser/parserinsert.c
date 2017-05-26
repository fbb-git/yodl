#include "parser.ih"

void parser_insert(register Parser *pp, char const *fmt, ...)
{
    va_list list;

    va_start (list, fmt);
    p_insert(pp, fmt, list);
    va_end (list);
}
