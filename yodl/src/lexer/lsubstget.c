#include "lexer.ih"

/*
    Read the next character from the media and from the substitution Queue.

    Characters read from the media are matched against substitution
sequences. If a substutution sequence is found, it is pushed in front of the
substitution queue, and the input is read again. Eventually, no substitution
will have occurred, and the first character on the subst-Q is returned.

    Assume A is replaced by B, and the input media contain Ax. Then the
following will happen:

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

int l_subst_get(Lexer *lp)
{
    register Subst *sp = lp->d_subst_ptr;
    register Media *mp = lp->d_media_ptr;

    while (true)
    {
        register char *cp;
        int ch = media_get(mp);

        if (media_fgetc(mp))
            lp->d_nreplacements = 0;

        switch (subst_action(sp, ch))
        {
            case SUBST_CONTINUE:
            break;

            case SUBST_GETCHAR:
                if (*(cp = subst_get(sp)))
                    media_push_front(mp, cp + 1);
                ch = *cp ? *(unsigned char *)cp : EOF;
                free(cp);
            return ch;

            case SUBST_SUBSTITUTION:
                if 
                (
                    lp->d_maxreplacements 
                    && 
                    ++lp->d_nreplacements >= lp->d_maxreplacements
                )
                    l_max_replacements_exceeded(lp->d_maxreplacements);

                media_push_front(mp, cp = subst_get(sp));
                free(cp);
            continue;
        }
    }
}
