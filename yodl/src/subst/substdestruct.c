#include "subst.ih"

void subst_destruct(register Subst *sp)
{
    strVector_destruct(&sp->d_strVector);
    string_destruct(&sp->d_buffer);
}
