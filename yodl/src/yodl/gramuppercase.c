#include "yodl.h"

void gram_UPPERCASE()
{
    char *text;
    unsigned  maxlen;

    parser_push_fun("UPPERCASE");

    text = parser_eval(&parser, parser_parlist(&parser, COLLECT_SET));
    parser_skipws(&parser);

    if (parser_number_parlist(&parser, (int *)&maxlen, false) == SUCCESS)
    {
        if (!maxlen || maxlen > strlen(text))
            maxlen = strlen(text);

        while (maxlen--)
            text[maxlen] = toupper(text[maxlen]);

        (*parser.d_insert)(&parser, text);
    }

    parser_pop_fun();
    free(text);
}
