#include "string.ih"

char string_popfront(register String *sp)
{
    char front = *sp->d_str;

    if (sp->d_length)
        memmove(sp->d_str, sp->d_str + 1, sp->d_length--);

    return front;
}
