#include "parser.ih"

bool p_handle_ignore_openpar(register Parser *pp)
{
    pp->d_paren++;
    return true;
}
