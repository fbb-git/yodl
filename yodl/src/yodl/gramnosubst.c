#include "yodl.h"

/*
    NOTRANS():  macros are not expanded (except for CHAR())
                no CHARTABLE() is active.
*/

void gram_NOSUBST()
{
//    char *text;

    parser_push_fun("NOSUBST");

    parser_allow_subst(&parser, false);
    gram_NOTRANS();
    parser_allow_subst(&parser, true);

    parser_pop_fun();

//return;
//
//    parser_push_ws_level(&parser, 0);
//
//    text = parser_parlist(&parser, DEFAULT_SET);
//fprintf(stderr, "\ntext: `%s', length: %lu\n", text, strlen(text));
//    parser_allow_subst(&parser, true);
//
//    if (text)
//    {
//        text[strlen(text) - 1] = 0;
//        ostream_insert(&outs, text + 1);
//    }
//
//fprintf(stderr, "\ntext: `%s', length: %lu\n", text, strlen(text));
//
//    parser_pop_ws_level(&parser);
//
//    parser_pop_fun();
//    free(text);
}
