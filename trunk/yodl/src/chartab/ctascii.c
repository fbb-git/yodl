#include "chartab.ih"

size_t ct_ascii(char const *ch)
{
    if (*ch != '\\')
        return (unsigned char)*ch;

    switch (ch[1])
    {
        case 'a':
            return ('\a');
        case 'b':
            return ('\b');
        case 'f':
            return ('\f');
        case 'n':
            return ('\n');
        case 'r':
            return ('\r');
        case 't':
            return ('\t');
        case 'v':
            return ('\v');
        default:
            return ((unsigned char)ch[1]);
    }
}
