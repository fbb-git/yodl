#include "yodl.h"

void gram_SUBSTKEY()
{
    parser_push_fun("SUBSTKEY");

    int value;
    if (parser_number_parlist(&parser, &value, false) == SUCCESS)
    {
        StrVectorPair const *ptr = strVector_index(parser_strVector(&parser),
                                                   value);

        lexer_push_str(&parser.d_lexer, ptr->d_value);
    }

    parser_pop_fun();
}
