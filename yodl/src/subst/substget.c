#include "subst.ih"

char *subst_get(register Subst *sp)
{
    sp->d_current_state_ptr = sp->d_start_state_ptr;
    register char *cp = string_release(&sp->d_buffer);
    string_construct(&sp->d_buffer, 0);
    return cp;
}
