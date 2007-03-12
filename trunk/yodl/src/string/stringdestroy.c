#include "string.ih"

void string_destroy(register String *sp)
{
    free(sp->d_str);
}
