#include "subst.ih"

void s_maxReplacementsExceeded(size_t max)
{
    message_show(MSG_CRIT);
    message(
        __FILE__ "\nMax number of macro/subst replacements (%lu) exceeded\n", 
        max);
}

