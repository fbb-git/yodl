#include "subst.ih"

void subst_construct(register Subst *sp)
{
    string_construct(&sp->d_buffer, 0);
    sp->d_start_state_ptr = sp->d_current_state_ptr = s_state_new();
}
