#include "parser.ih"

unsigned parser_ws_level(register Parser *pp)
{
    return pp->d_ws_level;
}
