#include "lexer.ih"

unsigned  lexer_lineno(register Lexer *lp)
{
    register Media *mp;

    return (mp = lp->d_media_ptr) ? l_media_lineno(mp) : 0;
}
