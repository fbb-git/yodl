#include "subst.ih"

char *subst_get(register Subst *sp)
{
    register char *cp;
    sp->d_current_state_ptr = sp->d_start_state_ptr;
    cp = string_release(&sp->d_buffer);
    string_construct(&sp->d_buffer, 0);
    return cp;
}
