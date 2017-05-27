#include "ostream.ih"

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

size_t d_nreplacements = 0;
size_t d_maxreplacements = 10000;

int o_subst_get(Ostream *op)
{
    register Subst *sp = op->d_subst_ptr;
    register Queue *qp = &op->d_queue;

    d_nreplacements = 0;

    while (true)
    {
        register char *cp;
        int ch = queue_get(qp);

        switch (subst_action(sp, ch))
        {
            case SUBST_CONTINUE:
            break;

            case SUBST_GETCHAR:
                if (*(cp = subst_get(sp)))
                    queue_push(qp, strlen(cp + 1), cp + 1);

                ch = *cp ? *(unsigned char *)cp : EOF;
                free(cp);
            return ch;

            case SUBST_SUBSTITUTION:
                if 
                (
                    d_maxreplacements 
                    && 
                    ++d_nreplacements >= d_maxreplacements
                )
                    o_max_replacements_exceeded(d_maxreplacements);

                cp = subst_get(sp);
                queue_push(qp, strlen(cp), cp);
                free(cp);
            continue;
        }
    }
}










