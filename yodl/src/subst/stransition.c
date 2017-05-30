#include "subst.ih"

bool s_transition(register Subst *sp, int ch)
{
    string_addchar(&sp->d_buffer, ch);  

                                        /* true if a transition is possible */
    return s_state_transition(&sp->d_current_state_ptr, ch);
}
