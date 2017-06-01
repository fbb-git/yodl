
#include "parser.ih"

static char const extended[] = "/:.-_[](){}";

char *parser_name_parlist(register Parser *pp, bool skipws)
{
    char *name = parser_parlist(pp, COLLECT_SET);
    register char *cp;

    if (!*name)
        if (message_show(MSG_CRIT))
            message("%s: Illegal empty argument", parser_fun());

    for (cp = name; *cp; cp++)                      /* all chars must be    */
    {                                               /* alpha-numerica or in */
                                                    /* the extended         */
                                                    /* character set        */
        if ( !(isalnum(*cp) || strchr(extended, *cp)) )
            if (message_show(MSG_CRIT))
                message("%s: Illegal name-character(s) in `%s'",
                            parser_fun(), name);
    }

    if (skipws)
        parser_skipws(pp);

    return name;
}
