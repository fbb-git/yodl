#include "lexer.ih"

/*
    We're not checking here anymore whether the perceived IDENT is a plain
    word, in which case it's a SYMBOL, or something special. This keeps the
    lexer simple, and leaves the more complex symtab handling to the parser,
    who should be the knowledgeable agent in semantic matters anyhow.

    An "xyz(" sequence is returned as "xyz", token SYMBOL (ungetting the
    ")"), a xyz. sequence is returned as a SYMBOL.

    "xyz(" may then be a BUILTIN or a MACRO or, after all, just
    plain TEXT.

*/

LEXER_TOKEN l_handle_ident(register Lexer *lp)
{
    register int c;

    do                                      /* at this point d_lastchar is  */
    {                                       /* an identchar, so we proceed  */
        string_addchar(&lp->d_text, lp->d_lastchar);
        l_nextchar(lp);
    }
    while (l_isIdentChar(lp));

    c = lp->d_lastchar;                 /* used below                       */
    l_unget(lp, c);                     /* unget the char beyond the ident  */

                                        /* the close parentheses comments   */
                                        /* are to keep my emacs             */
                                        /* paren-matcher happy              */
    return c == '(' ? TOKEN_SYMBOL : TOKEN_TEXT;                    /*  )   */
}
