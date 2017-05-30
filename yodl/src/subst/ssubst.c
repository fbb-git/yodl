#include "subst.ih"

SubstAction s_subst(register Subst *sp, int ch)
{
    return                               /* char found in the current    */
        s_transition(sp, ch) ?           /*                      state ? */
            SUBST_TRANSITION
        :
            s_tryReplace(sp);           /* try to replace a SUBST key   */
                                        /* by a SUBST value. If not,    */
                                        /* the caller obtains the next  */
                                        /* char from the queue          */
}



/*
    if ch is not EOF and found in the current state transition, then add
    it to the buffer holding the matched characters (so far).

    If there isn't a match, but if there is a replacement, then put the
    replacement into the buffer.

    If there isn't a match, but there was a match earlier, then put the
    earlier replacement and all later characters into the buffer, and indicate
    a substitution as well
*/



