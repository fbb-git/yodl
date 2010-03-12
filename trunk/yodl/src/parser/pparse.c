#include "parser.ih"

void p_parse(register Parser *pp)
{
    #ifdef EBUG
        /* See psetuphandlerset.c for initialization of ps_handlerSet */

        LEXER_TOKEN token;
        do
        {
            token = lexer_lex(&pp->d_lexer);
            message("parser/p_parse(): handler_set: %s, token = %s `%s'", 
                    p_handler(pp),
                    lexer_tokenName(token), lexer_text(&pp->d_lexer));
        }
        while ((*pp->d_handler[token])(pp));
    #else
        while ((*pp->d_handler[lexer_lex(&pp->d_lexer)])(pp))
            ;
    #endif
}
