#include "subst.ih"

bool s_state_transition(State **state_pp, int ch)
{
    register char const *cp;
    register State *sp = *state_pp;             /* sp: current state        */

    if ((cp = strchr(sp->d_str, ch)) == 0)      /* ch not in this state     */
        return false;

    *state_pp = sp->d_next[cp - sp->d_str];     /* change to state          */
                                                /* corresponding to the     */
                                                /* matched character        */

    (*state_pp)->d_parent = sp;                 /* set the parent state     */
                                                /* in the next state        */
    return true;
}
