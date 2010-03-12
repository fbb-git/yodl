#include "lexer.ih"

char const *lexer_text(register Lexer *lp)
{
    return string_str(&lp->d_text);
}
