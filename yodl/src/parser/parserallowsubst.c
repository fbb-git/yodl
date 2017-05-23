#include "parser.ih"

void parser_allow_subst(register Parser *pp, bool onOff)
{
    subst_allow(&pp->d_subst, onOff);
}
