#include "string.ih"

unsigned string_find_first_not_of(register String *sp,
                                                    register int (*fun)(int))
{
    unsigned idx;

    for (idx = 0; idx < sp->d_length; idx++)
    {
        if (!(*fun)(sp->d_str[idx]))
            return idx;
    }
    return (unsigned)FAILED;
}
