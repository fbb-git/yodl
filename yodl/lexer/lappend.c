#include "lexer.ih"

/*
    Simply append lp->d_lastchar to the semantic buffer, and return the
indicated token

*/

LEXER_TOKEN l_append(register Lexer *lp, LEXER_TOKEN token)
{
    string_addchar(&lp->d_text, lp->d_lastchar);    /* push back last one */
    return token;
}
