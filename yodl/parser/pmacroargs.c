#include "parser.ih"

static char argPostfixChar[] =  "123456789"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "abcdefghijklmnopqrstuvwxyz";
static char argx[] = "ARG.";

void p_macro_args(register Parser *pp, String *definition, size_t argc)
{
    register size_t idx;

    for (idx = 0; idx < argc; idx++)        /* handle all arguments */
    {
        char *argument = parser_parlist(pp, COLLECT_SET);

        argx[3] = argPostfixChar[idx];
        string_replace(definition, argx, argument);
        free(argument);

        if (idx < argc - 1)                 /* skip blanks in between   */
            parser_skipws(pp);
    }
}
