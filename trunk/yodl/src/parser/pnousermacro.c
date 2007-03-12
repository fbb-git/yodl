#include "parser.ih"

void p_no_user_macro(register Parser *pp)
{
    register char *cp = new_str(p_matched(pp));

    if (lexer_lex(&pp->d_lexer) == TOKEN_OPENPAR)
    {
        if (hashmap_find(pp->d_symtab_ptr, cp, NOUSERMACRO) == PFAILED)
            warning("No macro: %s(...)", cp);

        lexer_push_str(&pp->d_lexer, "(");

        /*
            Omitting this will cause the parser to miss the TOKEN_OPENPAR
            as it's then consumed by the warning
            
            When it's a user macro, the consumption is ok, since we found a 
            macro by then, which needs to be expanded.
        */
    }
}




