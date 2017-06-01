#include "lexer.ih"

/*
    This is the complement of l_push(). l_push() will push the active media on
the media stack, and initialize media.

    lpop() is called to pop the topmost element of the media stack, to
reactivate the then active media (if any), and to reassign d_media_ptr.

    This will succeed as long as the media stack size exceeds d_empty_size. We
can't pop if that's initially the case, and so that would represent an
internal failure. Yodl should not pop in those cases. If the stack is empty
following the pop, then popping fails. Otherwise, the previously pushed media
are reactivated.

    If there are any media available, d_media_ptr is set to the media stack's
tos.

*/

static bool lastFailed = false;

Result l_pop(register Lexer *lp)
{
    bool oldFile = false;

    if (stack_size(&lp->d_media_st) == lp->d_empty_size)
        if (message_show(MSG_EMERG))
            message("Attempt to pop empty media stack beyond element %u",
                (unsigned)lp->d_empty_size);

    if (media_isFile(lp->d_media_ptr))    /* remove stacked file          */
    {
        oldFile = true;
        lp->d_filedepth--;
    }

    stack_pop(&lp->d_media_st);             /* remove the current media     */
                                            /* empty stack: no more media   */
    if (stack_size(&lp->d_media_st) == lp->d_empty_size)
    {
        lp->d_media_ptr = NULL;
        lastFailed = true;
        return FAILED;
    }
                                            /* reset lp->d_media_ptr to tos */
    lp->d_media_ptr = stack_tos(&lp->d_media_st)->u_voidp;

    if (media_isFile(lp->d_media_ptr))
    {
        if (oldFile || lastFailed)
            (*lp->d_chdirFun)(lp, media_filename(lp->d_media_ptr));
        lastFailed = false;
    }
    else
        lastFailed = oldFile && !lastFailed;

    media_restore_state(lp->d_media_ptr); /* generates MSG_INFO           */

    return SUCCESS;
}









