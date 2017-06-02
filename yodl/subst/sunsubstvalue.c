#include "subst.ih"

char *s_unsubstValue(StrVector const *sv, char *value)
{
    String str;
    string_construct(&str, 0);

    char *end = value;
    char *begin;
    while (true)
    {
        begin = strstr(end, "+XXSUBST(");               /* ) */

        if (begin == 0)
        {
            string_addstr(&str, end);            /* append the tail */
            break;
        }

        string_additerators(&str, begin, end);
        begin += strlen("+XXSUBST(");                  /* )    */
        int idx;
        end = begin + 1 + sscanf(begin, "%d", &idx);     /* get the index */

        string_addstr(&str, strVector_index(sv, idx)->d_value);
    }

    free(value);
    return string_release(&str);
}



