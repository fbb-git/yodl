#include "string.ih"

void string_construct(String *s, char const *str)
{
    s_init(s, str);
}
