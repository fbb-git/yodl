#include "lexer.ih"

void l_nextchar(register Lexer *lp)
{
    register int ch = l_get(lp);            // read from file or buffer

    // see below for a description
    while (ch == '\\')                      // a backslash
    {
        ch = l_get(lp);                     // get the next char

        if (ch == '/')
        {
            ch = l_get(lp);                 // inspect char beyond /

            if (ch == '/')                  // two // follow \: eoln comment
            {
                while ((ch = l_get(lp)) != '\n')    // find the newline
                    ;                               // and skip \n and 
            }                                       // blanks beyond
            else                            // one /, followed by whatever
            {
                l_unget(lp, ch);            // unget it
                l_unget(lp, '/');           // unget the /
                lp->d_lastchar = '\\';      // and return the backslash
                return;
            }
        }
        else if (ch != '\n')                // no newline beyond the backslash
        {
            l_unget(lp, ch);                /* unget that char              */
            lp->d_lastchar = '\\';          /* and return \                 */
            return;
        }
                                            // skip ' ', '\t' after EOLN
        while ((ch = l_get(lp)) == ' ' || ch == '\t')
            ;
    }

    if                                      /* not a backslash              */
    (
        ch == '\n'                          /* got newline,                 */
        &&                                  /* and:                         */
        !lp->d_keep_ws                      /* ignore ws at the end         */
    )
    {
        while (isspace(ch = l_get(lp)))
            ;                               /* skip until not a ws          */
    }

    lp->d_lastchar = ch;
    return;                                 /* done: return the char.       */
}

/*
    Nextchar determines the next character returned by the lexer.

    While the current char is a backslash:
        if the next two chars are //, then all characters on the current
            line are skipped, until the final newline has been reached.
            This effectively turns \// into an eoln comment.

        else, if only one / is encountered, then the / and subsequent char 
            are pushed back, and a backslash is returned.

        if the current char is not end-of-line then it's pushed back, and a
        backslash is returned.

        at this point an end-of-line char was seen, following \ or \//[^\n]*
        and all subsequent blank space chars (of the next line) are skipped.
        
        Now the loop continues at the top, maybe skipping another backslash
        or \//[^\n]* termineated line.

    When the loop ends, the next char (which may be a backslash) is returned.
*/

