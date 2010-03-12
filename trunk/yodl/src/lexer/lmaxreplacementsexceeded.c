#include "lexer.ih"

void l_max_replacements_exceeded(size_t max)
{
    message_show(MSG_CRIT);
    message("Max number of macro/subst replacements (%u) exceeded\n", 
            (unsigned)max);
}

