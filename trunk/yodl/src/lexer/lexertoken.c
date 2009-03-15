#include "lexer.ih"

LEXER_TOKEN lexer_token(register Lexer *lp)
{
    return lp->d_token;
}
