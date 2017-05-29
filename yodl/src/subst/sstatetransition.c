#include "subst.ih"

bool s_state_transition(State **state_pp, int ch)
{
    register char const *cp;
    register State *sp = *state_pp;             /* sp: current state        */

message(__FILE__ " %p: looking for %c in %s", sp, ch, sp->d_str);

    if ((cp = strchr(sp->d_str, ch)) == 0)      /* ch not in this state     */
        return false;

    *state_pp = sp->d_next[cp - sp->d_str];     /* change to state          */
                                                /* corresponding to the     */
                                                /* matched character        */

message(__FILE__ " %p: next state continues with %s", *state_pp, 
(*state_pp)->d_str);


    (*state_pp)->d_parent = sp;                 /* set the parent state     */
                                                /* in the next state        */
    return true;
}
