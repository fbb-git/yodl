#include "chartab.ih"

String *chartab_apply(char const *txt)
{
    register String *sp = string_new(0);

    while (*txt)
        string_addstr(sp, 
                chartab.d_active[*(unsigned char const *)txt++]);

    return sp;
}
