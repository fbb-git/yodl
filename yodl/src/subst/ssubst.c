#include "subst.ih"

/*
    if ch is not EOF and found in the current state transition, then add
    it to the buffer holding the matched characters (so far).

    If there isn't a match, but if there is a replacement, then put the
    replacement into the buffer.

    If there isn't a match, but there was a match earlier, then put the
    earlier replacement and all later characters into the buffer, and indicate
    a substitution as well
*/

SubstAction s_subst(register Subst *sp, int ch)
{
    size_t n_keep;
    register char const *text;

message("\n" __FILE__ " next: %c", ch);



                                        /* char found in the current    */
    if                                  /*                      state ? */
    (
        ch != EOF                       /* if not an EOF char           */
        &&                              /* and if state transition      */
        s_state_transition((State **)(void *)&sp->d_current_state_ptr, ch)
    )
    {                                   /* add char to `matched so far' */
message(__FILE__ ": POTENTIAL MATCH: continue after adding %c", ch);
        string_addchar(&sp->d_buffer, ch);  
        return SUBST_CONTINUE;
    }

message(__FILE__ ": collected so far: %s", string_str(&sp->d_buffer));

    n_keep = 0;                          /* replacement seen ?   */

    if ((text = s_state_replacement(sp->d_current_state_ptr, &n_keep)))
    {
        size_t length = string_length(&sp->d_buffer);
        char *buffer = string_release(&sp->d_buffer);

        string_assign(&sp->d_buffer, text);
        string_addstr(&sp->d_buffer, buffer + length - n_keep);
        free(buffer);

message(__FILE__ ": new collected text: %s", string_str(&sp->d_buffer));
    }
    else
message(__FILE__ ": no replacement yet for %s", string_str(&sp->d_buffer));

    if (ch != EOF)
{
message(__FILE__ ": add %c", ch);
        string_addchar(&sp->d_buffer, ch);
}
    else
        return SUBST_CONTINUE;

message(__FILE__ ": DO: %s", text == 0 ? "SUBST_GET" : "SUBST_SUBSTITUTE");

    return text == 0 ? SUBST_GETCHAR : SUBST_SUBSTITUTION;
}





