#include "parser.ih"

void p_no_user_macro(register Parser *pp)
{
    register char *cp = new_str(p_matched(pp));

    if
    (
        lexer_lex(&pp->d_lexer) == TOKEN_OPENPAR
        &&
        hashmap_find(pp->d_symtab_ptr, cp, NOUSERMACRO) == PFAILED
    )
        warning("No macro: %s(...)", cp);
}
