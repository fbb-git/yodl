#include "lexer.ih"

/*
    As this function CLEARS the semantic buffer, make sure that it is only
    called by the parser. Otherwise, matched text will be overwritten while
    being constructed.

    lexer_lex() is the public interface to the lexer, returning the next
available token. Once lexer_lex() returns EOF, it keeps doing so, unless it is
reset by, e.g., lexer_end_eval().
*/

LEXER_TOKEN lexer_lex(register Lexer *lp)
{
    string_erase(&lp->d_text);                  /* use fresh semantic value */

    lp->d_token = l_lex(lp);                    /* get the next token       */
    if (message_show(MSG_INFO))
        message("lexer_lex() returns %s (= `%s')",
                                l_token_name[lp->d_token], lexer_text(lp));

    return lp->d_token;
}
