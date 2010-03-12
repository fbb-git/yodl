#include "lexer.ih"

void lexer_set_keep_ws(register Lexer *lp, bool trueIsYes)
{
    lp->d_keep_ws = trueIsYes;
}
