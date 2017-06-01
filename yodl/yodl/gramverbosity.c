#include "yodl.h"

/*
    parlist 1: empty: MSG is set to indicated level in parlist 2
                +     MSG in parlist 2 are shown too
                -     MSG in parlist 2 are suppressed
               other: error

    a decimal value: the corresponding MSG flags are set as the new
    verbosity level.

    one or more MSG_ values: these flags are set. Also, MSG_NONE and MSG_ALL
    may be used
*/

void gram_VERBOSITY()
{
    register char *request;
    register char *mod;

    parser_push_fun("VERBOSITY");

    mod = parser_parlist(&parser, COLLECT_SET);
    parser_skipws(&parser);
    request = parser_parlist(&parser, COLLECT_SET);

    if (!*request)
    {
        if (message_show(MSG_ERR))
            message("VERBOSITY()(): 2nd arg (verbosity setting) missing");
    }
    else
        message_setverbosity(*mod, request);

    parser_pop_fun();
    free(mod);
    free(request);
}
