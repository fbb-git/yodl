#include "lexer.ih"

LEXER_TOKEN l_handle_number(register Lexer *lp)
{
    do                                      /* at this point d_lastchar is  */
    {                                       /* a digit, so we may proceed   */
        string_addchar(&lp->d_text, lp->d_lastchar);
        l_nextchar(lp);
    }
    while (isdigit(lp->d_lastchar));

    l_unget(lp, lp->d_lastchar);
    return TOKEN_TEXT;
}
