#include "subst.ih"

char const *s_state_insert(register State *sp, char const *key,
                                               char const *subst)
{
    while (*key)
    {
        register char const *cp;
                                        /* if key is in the set, switch to  */
        if ((cp = strchr(sp->d_str, *key)) != 0)         /*  that state  */
            sp = sp->d_next[cp - sp->d_str];
        else
        {                               /* if not, add a new state to the   */
            size_t last = string_length(&sp->d_set);      /*          set */

            string_addchar(&sp->d_set, (char)*key); /* add key's 1st char */
            sp->d_str = string_str(&sp->d_set); /* and set the state's ptr  */

                                                /* add a new state          */
            new_size(&sp->d_next, last + 1, last, sizeof(State *));
            sp = sp->d_next[last] = s_state_new();
        }
        key++;                          /* inspect the next key char        */
    }

                                        /* all key chars exhausted: insert  */
                                        /* replacement text                 */

    if (sp->d_replacement)              /* oops, it's already there         */
        return sp->d_replacement;       /* return the one found             */

    sp->d_replacement = new_str(subst);
    return 0;                           /* here 0 indicates SUCCESS         */
}
