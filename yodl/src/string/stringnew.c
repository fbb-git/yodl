#include "string.ih"

String *string_new(char const *str)
{
    register String *sp = new_memory(1, sizeof(String));

    string_construct(sp, str);
    return sp;
}
