#include "ostream.ih"

int o_subst_get(Ostream *op)
{
    register Subst *sp = op->d_subst_ptr;
    register Queue *qp = &op->d_queue;


    while (true)
    {
        register char *cp;
        int ch = queue_get(qp);             /* next char from the queue     */

        if (ch == EOF)                      /* no more characters           */
            return EOF;

        switch (subst_process(sp, ch))      /* process this Q's character   */
        {
            case SUBST_TRANSITION:          /* a transition was possible    */
            break;                          /* get the next char fm the Q   */

            case SUBST_GETCHAR:
                if (*(cp = subst_get(sp)) == 0)
                    ch = EOF;
                else
                {
                    queue_push(qp, strlen(cp + 1), cp + 1);
                    ch = *cp;
                    free(cp);
                }
            return ch;

            case SUBST_REPLACED:            /* SUBST key was replaced       */
                cp = subst_get(sp);         /* the new Q contents           */
                queue_push(qp, strlen(cp), cp); /* put it in the Q          */
                free(cp);
            continue;
        }
    }
}


/*
    Read the next character from the media and from the substitution Queue.

    Characters read from the media are matched against substitution
sequences. If a substutution sequence is found, it is pushed in front of the
substitution queue, and the input is read again. Eventually, no substitution
has occurred, and the first character on the subst-Q is returned.

    Assume A is replaced by B, and the input media contain Ax. Then the
following happens:

    --------------------------------------------------------------------
                                            Subst
                                        -------------
                    result      Media   Buffer  Queue       comment
    --------------------------------------------------------------------
    get media:      A           x
    subst.more()    true        x       A                   buffer potential
                                                            subst-sequence
    get media:      x           EOF     A
    subst.more()    true                        Bx          A replaced by B

    get media:      B           EOF             x
    subst.more():   false       EOF             Bx

    subst.get():    B           EOF             x           returns B

Next call:

    get media:      x           EOF             EOF
    subst.more()    false       EOF             x

    subst.get():    x           EOF             EOF         returns x

Next call:

    get media:      EOF         EOF             EOF
    subst.more()    false       EOF             EOF

    subst.get():    x           EOF             EOF         returns EOF

    --------------------------------------------------------------------
*/

