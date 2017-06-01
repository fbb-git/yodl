#include "string.ih"

void string_assign(register String *sp, register char const *txt)
{
    free(sp->d_str);

    s_init(sp, txt ? txt : s_stringEmpty);
}
