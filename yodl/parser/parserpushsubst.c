#include "parser.ih"

void parser_pushSubst(register Parser *pp, bool useSubst)
{
    pp->d_useSubstBits <<= 1;
    
    lexer_useSubst(&pp->d_lexer, 
                   pp->d_useSubst = (pp->d_useSubstBits |= useSubst) & 1);
}

