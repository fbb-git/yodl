#include "ostream.ih"

void o_max_replacements_exceeded(size_t max)
{
    message_show(MSG_CRIT);
    message(__FILE__ "Max number of macro/subst replacements (%u) exceeded\n", 
            (unsigned)max);
}

