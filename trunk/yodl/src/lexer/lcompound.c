#include "lexer.ih"

LEXER_TOKEN l_compound(register Lexer *lp)
{
    if (l_isIdentChar(lp))
        return l_handle_ident(lp);

    if (isdigit(lp->d_lastchar))
        return l_handle_number(lp);

    return l_append(lp, TOKEN_PLAINCHAR);  /* formerly: `any'  */
}
