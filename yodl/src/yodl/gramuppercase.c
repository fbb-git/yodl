#include "yodl.h"

void gram_UPPERCASE()
{
    char *text;
    size_t  maxlen;
    int len;

    parser_push_fun("UPPERCASE");

    text = parser_eval(&parser, parser_parlist(&parser, COLLECT_SET));
    parser_skipws(&parser);

    if (parser_number_parlist(&parser, &len, false) == SUCCESS)
    {
        maxlen = len;
        if (!maxlen || maxlen > strlen(text))
            maxlen = strlen(text);

        while (maxlen--)
            text[maxlen] = toupper(text[maxlen]);

        (*parser.d_insert)(&parser, text);
    }

    parser_pop_fun();
    free(text);
}
