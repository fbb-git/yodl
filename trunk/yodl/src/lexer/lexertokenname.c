#include "lexer.ih"

char const *lexer_tokenName(LEXER_TOKEN token)
{
    return l_token_name[token];
}
