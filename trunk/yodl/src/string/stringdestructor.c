#include "string.ih"

void string_destructor(register void *sp)
{
    string_destroy((String *)sp);
    free(sp);
}
