#include "lexer.ih"

/*
    Beginning a new evaluation proceeded as follows:
        1. d_empty_size was pushed
        2. d_empty_size was set to the current d_media_st size
        3. the string to evaluate was pushed.

    Ending an evaluation occurs in the reverse order:
        3. the d_media_st is popped, and d_media is set to its top or NULL.
        2. d_empty_size is set to the tos of d_empty_st, or to 0 if the stack
            is empty
        1. d_empty_st is popped if it has any size

    However, since the popping is done by l_pop(), d_empty_size must be
reduced first, as l_pop() won't pop to size d_empty_size. So, we will first
reduce d_empty_size, and then call l_pop().

    At this point the EOF state is left, by setting d_lastchar to 0.

*/

void lexer_end_nested(register Lexer *lp)
{
    size_t oldempty = lp->d_empty_size;       /* store the old bottom to  */
                                                /* be used below            */

    if (!stack_size(&lp->d_empty_st))           /* end-nested NEEDS a stack */
        if (message_show(MSG_EMERG))
            message("Lexer's evaluation stack exhausted");

                                                /* reset to previous size   */
    lp->d_empty_size = stack_tos(&lp->d_empty_st)->u_size_t;
    stack_pop(&lp->d_empty_st);                 /* pop the previous size    */

    if (message_show(MSG_INFO))
        message("Reducing nested media stack bottom from %u to %u",
                (unsigned)oldempty, (unsigned)lp->d_empty_size);

    if (oldempty == 0 && lp->d_empty_size == 0) /* no size change at the    */
        return;                                 /* bottom. We're done       */

    /*
        No lpop(), since that's already done earlier by the lexer,
        producing the EOF condition for the nested evaluation
    */
                                        /* reset lp->d_media_ptr to tos     */
    lp->d_media_ptr = stack_tos(&lp->d_media_st)->u_voidp;

    if (lp->d_media_ptr != PFAILED)
        media_restore_state(lp->d_media_ptr);     /* generates MSG_INFO   */

}
