#include "parser.ih"

bool p_handle_ignore_closepar(register Parser *pp)
{
    return --pp->d_paren;
}
