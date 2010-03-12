#include "lexer.ih"

/*
    Read the next character from the media.

    If there are no media, then EOF is returned anyway.

    Otherwise, a character is requested from the media.

    The obtained character, including EOF, is given to d_subst,
which gets a chance to use it for a substitution.

        If substitute consumes the character, another char is requested from
the media.
            While consuming characters,
            * d_subst may detect a substitution match, in which case the
                substitution + terminating character is pushed on to the media
                stack. So, following a successful match, the media will start
                to retrieve the substitution.
            * s_subst may consider the next character to be part of an
                ongoing substitution key-match, in which case it stores the
                char in an internal buffer, indicating that it has consumed
                the char.
            * s_subst may not consider the next character part of a known
                subsitution. In that case the character is added to its
                internal buffer, the first char. of the buffer is returned,
                and the remaining chars are pushed on to the media stack. If
                there is no buffer, and the received character was EOF, EOF is
                returned.

    If d_subst returns an EOF char, l_pop() is called to reactivate any
previously pushed media. If that succeeds, the loop continues at the request
for another character from the media. If that fails, EOF is returned.

*/

int l_get(register Lexer *lp)
{
    register int ch;

    if (!lp->d_media_ptr)                           /* no more media        */
        return EOF;

    if ((ch = l_subst_get(lp)) == EOF)              /* at the and of a      */
        ch = EOR;                                   /* buffer: return EOR   */

    if (message_mask() & MSG_DEBUG)
        l_getchar_message(lp, "Getting", ch);       /* maybe debug msg      */

    return ch;
}




