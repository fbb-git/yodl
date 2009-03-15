#include "lexer.ih"

/*
    When ungetting, EOF doesn't have to be pushed back, since its EOF, and it
can't be pushed back as a single character.

    Then, lexer_push_str() will end the EOF condition, if present.

*/

void l_unget(register Lexer *lp, int ch)
{
    if (ch >= 0)                                    /* do not unget EOR/EOF */
    {
        if (message_mask() & MSG_DEBUG)
            l_getchar_message(lp, "Ungetting ", ch);

        media_unget_memory(lp->d_media_ptr, ch);
    }
}
