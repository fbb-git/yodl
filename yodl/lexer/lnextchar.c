#include "lexer.ih"

/*
    Nextchar determines the next character to return.
    It is:

        - reading a \-character:
            - \ if it is not followed by a \n
            - the next non-(space or tab) character if \ was followed by a \n
                (so use backslash + 2 newlines to return one newline)
        - reading a \n -char:
            if blanks at the end of the line can be skipped:




*/

void l_nextchar(register Lexer *lp)
{
    register int ch = l_get(lp);            /* read from file or buffer     */

    while (ch == '\\')                      /* a backslash: handled         */
    {                                       /* traditionally                */
        ch = l_get(lp);                     /* read the next one            */

        if (ch != '\n')                     /* not a \EOLN                  */
        {
            l_unget(lp, ch);                /* unget that char              */
            lp->d_lastchar = '\\';          /* and return \                 */
            return;
        }
                                            /* skip ' ', '\t' after \EOLN   */
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
