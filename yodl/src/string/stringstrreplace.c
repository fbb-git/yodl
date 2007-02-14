#include "string.ih"

char *string_str_replace(char const *left,
                    char const *search, char const *replace)
{
    size_t searchlen = search ? strlen(search) : 0;
    register char const *right;
    String out;

    if (!searchlen)                     /* search should have some length */
        return new_str(left);

    {
        string_construct(&out, 0);

        while ((right = strstr(left, search)))
        {
            string_additerators(&out, left, right);
            string_addstr(&out, replace);
            left = right + searchlen;
        }
        string_addstr(&out, left);          /* append the final tail        */

        return string_release(&out);
    }
}
