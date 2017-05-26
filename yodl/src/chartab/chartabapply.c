#include "chartab.ih"

String *chartab_apply(char const *txt)
{
    register String *sp = string_new(0);

    // d_active is an array od 256 characters whose values are the 
    // characters themselves 
    while (*txt)
        string_addstr(sp, 
                chartab.d_active[*(unsigned char const *)txt++]);

    return sp;
}
