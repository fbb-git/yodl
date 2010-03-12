#include "lexer.ih"

bool l_isIdentChar(register Lexer *lp)
{
    return isalpha(lp->d_lastchar);     /* very simple... */
}
