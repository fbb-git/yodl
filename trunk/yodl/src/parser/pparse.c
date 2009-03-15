#include "parser.ih"

void p_parse(register Parser *pp)
{
    while ((*pp->d_handler[lexer_lex(&pp->d_lexer)])(pp))
        ;
}
