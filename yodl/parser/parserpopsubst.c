#include "parser.ih"

void parser_popSubst(register Parser *pp)
{
    if ((pp->d_useSubstBits >>= 1) == 0)
        pp->d_useSubstBits = 1;

    lexer_useSubst(&pp->d_lexer, 
                   pp->d_useSubst = pp->d_useSubstBits & 1);
}

