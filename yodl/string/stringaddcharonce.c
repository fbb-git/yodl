#include "string.ih"

void string_addcharOnce(register String *sp, int c)
{
    if (string_last(sp) != c)
        string_addchar(sp, c);
}
