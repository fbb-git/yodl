#include "lexer.ih"

void l_nextchar(register Lexer *lp)
{
    register int ch = l_get(lp);            // read from file or buffer

    while (ch == '\\')                      // a backslash
    {
        ch = l_get(lp);                     // get the next char
        if (ch == '\\')                     // another backslash: skip all
        {                                   // chars until newline
            while ((ch = l_get(lp)) != '\n')
                ;
        }

        if (ch != '\n')                     // not EOLN
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
    Nextchar determines the next character to return.
    The next char is:

        - when reading a \-character:
            - the next non-(space or tab) character if \ is the last character
                on a line (so backslash + 2 newlines to return one newline)
            - if immediately followed by another \ all subsequent chars on
                that line are skipped, as are all space- and tab characters on
                the next line (this allows end-of-line comment to be added to
                e.g., macro definitions). To 
            - \ if not the last character on the line or not followed by a
                second \ character. To write a single \ at the end of a line
                use, e.g., CHAR(\) at the end of a line. To skip all ws
                characters thereafter use, e.g., CHAR(\)\.
        - when reaching the end of the line, 
            if blanks at the end of the line can be skipped: the first
            non-blank character on the next line.
        - otherwise the next character is returned.
*/

