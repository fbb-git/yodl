#include "chartab.ih"

size_t ct_ascii(char const *ch, size_t *skip)
{
    size_t ret;

    if (*ch != '\\')
        return (unsigned char)*ch;

    ++*skip;

    switch (ch[1])
    {
        case 'a':
        return '\a';

        case 'b':
        return '\b';

        case 'f':
        return '\f';

        case 'n':
        return '\n';

        case 'r':
        return '\r';

        case 't':
        return '\t';

        case 'v':
        return '\v';

        case 'x':
        case 'X':
            if (isdigit(ch[3]) && isdigit(ch[4]))
            {
                sscanf(ch + 2, "%2x", &ret);
                *skip = 4;
                return ret;
            }
        return (unsigned char)ch[1];

        case '0':
        case '1':
            if (strchr("01234567", ch[2]) && strchr("01234567", ch[3]))
            {
                sscanf(ch + 1, "%3o", &ret);
                *skip = 4;
                return ret;
            }
        //FALLING THROUGH
        default:
        return (unsigned char)ch[1];
    }
}




