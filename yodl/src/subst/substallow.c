#include "subst.ih"

void subst_allow(register Subst *sp, bool yesNo)
{
    sp->d_action = 
            yesNo == true ? 
                &s_subst
            :
                &s_noSubst;
}
