#include "string.ih"

void string_erase(String *sp)
{
    string_assign(sp, 0);
}
