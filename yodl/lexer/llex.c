#include "lexer.ih"

/*
    Return the next token    The matched text is in lp->d_text
    Once d_lastchar is EOF it remains EOF until reset by lexer_end_eval()

    lexer_push_file pushes a filename and sets a new cwd
    l_pop reverts back to the previous path at EOR or at a file switch
*/

LEXER_TOKEN l_lex(register Lexer *lp)
{
    l_nextchar(lp);                             /* determine the next char  */

    switch (lp->d_lastchar)
    {
        case EOF:
        return TOKEN_EOF;

        case EOR:
        return l_pop(lp) == SUCCESS ? TOKEN_EOR : TOKEN_EOF;

        case ' ':
        case '\t':
        return l_append(lp, TOKEN_SPACE);

        case '(':
        return l_append(lp, TOKEN_OPENPAR);

        case ')':
        return l_append(lp, TOKEN_CLOSEPAR);

        case '\n':
        return l_append(lp, TOKEN_NEWLINE);

        case '+':
        return l_append(lp, TOKEN_PLUS);

        default:
        return l_compound(lp);
    }
}
