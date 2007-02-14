#include "parser.ih"

/*
    Handles series of + characters. If the next token signifies a symbol the +
chars but one are inserted, and the symbol is handled by the symbol
pointer. This function is either p_default_symbol or p_parlist_symbol.

    p_default_symbol will handle the symbols: builtins are called, user
defined macros are expanded and inserted into the input media, other symbols
are inserted into the output media.

    p_parlist_symbol is probably obsolete, thus obsoleting the function
pointer here.

*/


bool p_plus_series(register Parser *pp,
                    void (*symbol)(Parser *, bool, SymbolType),
                    SymbolType mask)
{
    register Lexer *lp = &pp->d_lexer;
    size_t pluscount = 1;                     /* saw a +              */
    String plus;

    string_construct(&plus, 0);

    while (lexer_lex(lp) == TOKEN_PLUS)
        pluscount++;                            /* count 'em all        */

    if (pluscount > 1)                          /* got a + series       */
        string_fill(&plus, pluscount - 1, '+');   /* insert all but 1     */

    if (lexer_token(lp) == TOKEN_SYMBOL)        /* handle +MACRO, +BUILTIN  */
    {                                           /* or +xxx as +xxx          */
        (*pp->d_insert)(pp, string_str(&plus));
        (*symbol)(pp, true, mask);
    }
    else
    {
        lexer_unget_matched(lp);                 /* unget the last token */
        string_addchar(&plus, '+');
        (*pp->d_insert)(pp, string_str(&plus));
    }
    string_destroy(&plus);

    return true;
}
