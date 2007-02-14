#include "parser.ih"

void parser_if_cond(register Parser *pp,
            bool (*comparator)(Parser *pp, char **parlist),
            char const *fun, size_t nparlists)
{
    register char **parlist;
    size_t idx = 0;

    parser_push_fun(fun);

    parlist = new_memory(nparlists, sizeof(char *));

    while (true)
    {
        parlist[idx] = parser_parlist(pp, COLLECT_SET);
        if (++idx == nparlists)
            break;
        parser_skipws(pp);
    }

    if (message_show(MSG_NOTICE))
        message("%s `%s'", parser_fun(), string_short(parlist[0]));

    lexer_push_str
    (
        &pp->d_lexer,
        (*comparator)(pp, parlist) ?
            parlist[nparlists - 2]              /* last but one: truelist   */
        :
            parlist[nparlists - 1]              /* last one: falselist      */
    );

    for (idx = 0; idx < nparlists; idx++)
        free(parlist[idx]);

    parser_pop_fun();
    free(parlist);
}
