#include "subst.ih"

void subst_allow(register Subst *sp, bool yesNo)
{
    sp->d_allowSubst = yesNo;
}
