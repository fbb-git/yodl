#include "chartab.ih"

char *ct_string(char const *str)
{
    String string;

    string_construct(&string, 0);

    while (*str)
    {
        string_addchar
        (
            &string,
            (*str == '\\') ? (int)ct_ascii(str++) : *str
        );
        str++;
    }
    return string_release(&string);
}
