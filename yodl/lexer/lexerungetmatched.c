#include "lexer.ih"

void lexer_unget_matched(register Lexer *lp)
{
    register char const *cp = lexer_text(lp);

    if (*cp)                            /* only push non-empty strings  */
    {
        if (message_show(MSG_DEBUG))
            message("pushing last matched `%s'", cp);
        lexer_push_str(lp, cp);
    }
}
