#include "parser.ih"

/*
    We've seen macroname, and know the next token is open-paren.

    Extract a parameterlist for each of the arguments.

    Each of the parameters is then replaced by its definition in the
    definition of the macro.

    Having done this, the full macro text is returned as the expansion

    If we can't find the macro's definition, that's an error
*/

void p_expand_macro(register Parser *pp, register HashItem *item)
{
    Macro *mp               = (Macro *)hashitem_value(item);
    char const *name        = hashitem_key(item);
    size_t argc             = macro_nArgs(mp);
    char const *def         = macro_definition(mp);
    String expansion;

    parser_push_fun(name);

    string_construct(&expansion, 0);

    if (def == PFAILED)
    {
        if (message_show(MSG_ERR))
            message("No stacked definition for macro `%s'", parser_fun());
    }
    else
    {
        if (message_show(MSG_NOTICE))
            message("Expanding macro`%s' to `%s'", parser_fun(),
                                                        string_short(def));
        string_addstr(&expansion, def);

        if (argc)                               /* macro with arguments     */
            p_macro_args(pp, &expansion, argc);
        else                                    /* no arguments:            */
        {                                       /* eat empty parameter list */
            char *argument = parser_parlist(pp, COLLECT_SET);
            if (*argument)
                if (message_show(MSG_WARNING))
                    message("macro `%s' called with non-zero parameter list",
                            parser_fun());
            free (argument);
        }
        lexer_push_str(&pp->d_lexer, string_str(&expansion));
    }
    string_destroy(&expansion);
    parser_pop_fun();
}
