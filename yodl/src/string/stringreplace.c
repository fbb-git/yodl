#include "string.ih"

void string_replace(String *str,
                    char const *search, char const *replace)
{
    size_t searchlen = search ? strlen(search) : 0;
    register char *left = str->d_str;
    register char *right;
    String out;

    if (!searchlen)                     /* search should have some length */
        return;

    string_construct(&out, 0);

    while ((right = strstr(left, search)))
    {
        string_additerators(&out, left, right);
        string_addstr(&out, replace);
        left = right + searchlen;
    }
    string_addstr(&out, left);          /* append the final tail        */

    string_copy(str, &out);
    string_destroy(&out);
}
