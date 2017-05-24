#include "subst.ih"

SubstAction s_noSubst(register Subst *sp, int ch)
{
    if (ch != EOF)
        string_addchar(&sp->d_buffer, ch);

    return SUBST_GETCHAR;
}
