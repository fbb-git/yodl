#include "string.ih"

void string_additerators(register String *string,
                         char const *begin, char const *end)
{
    size_t oldLength;
    size_t newLength;
    int addLength = end - begin;

    if (addLength <= 0)
        return;

    oldLength = string->d_length;
    newLength = oldLength + addLength;

    s_size(string, newLength);

    memcpy(string->d_str + oldLength, begin, (size_t)addLength);
    string->d_str[newLength] = 0;
    string->d_length = newLength;
}
