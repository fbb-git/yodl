#include "lexer.ih"

void l_push_level(register Lexer *lp, register char const *str)
{
    if (*str)
        l_push(lp, str, l_media_construct_memory);
}
