#include "chartab.ih"

char *ct_string(char const *str)
{
    String string;

    string_construct(&string, 0);

    while (*str)
    {
        size_t increment = 1;
        string_addchar
        (
            &string,
            (*str == '\\') ? (int)ct_ascii(str, &increment) : *str
        );
        str += increment;
    }

    return string_release(&string);
}
