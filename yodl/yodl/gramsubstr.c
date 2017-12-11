#include "yodl.h"

/*
    SUBSTR(srctext)(offset)(length) inserts substr into the lexical scanner

    srctext may be the name of a symbol, offset and length may be counter
    names 
*/
    
void gram_SUBSTR()
{
    parser_push_fun("SUBSTR");                      // call SUBSTR

    char **parlist = new_memory(3, sizeof(char *));

    size_t idx = 0;
    while (true)
    {
        parlist[idx] = parser_parlist(&parser, COLLECT_SET);
        if (++idx == 3)
            break;
        parser_skipws(&parser);
    }

    if (message_show(MSG_NOTICE))
        message("%s `%s'", parser_fun(), string_short(parlist[0]));

                                                // get symbol or use literal
    char const *src = parser_strvalue(&parser, parlist[0]);  
    
    int offset;
    if (
        parlist[1] == 0 || 
        parser_value(&parser, &offset, parlist[1]) == FAILED
    )
        offset = 0;

    int length;
    if (
        parlist[2] == 0 || 
        parser_value(&parser, &length, parlist[2]) == FAILED
    )
        length = INT_MAX;
        
    String *str = string_new(src);

    char *subStr = string_substr(str, offset, length);
    lexer_push_str(&parser.d_lexer, subStr);

    free(subStr);

    string_destruct(str);

    for (idx = 0; idx < 3; ++idx)
        free(parlist[idx]);

    parser_pop_fun();
}
