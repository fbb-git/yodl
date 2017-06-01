#include "parser.ih"

void parser_useSubst(register Parser *pp, bool useSubst)
{
    pp->d_useSubst = useSubst;
    lexer_useSubst(&pp->d_lexer, useSubst);
}

