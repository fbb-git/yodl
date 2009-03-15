#include "lines.ih"

void lines_destroy(register Lines *lp)
{
    register char **end = lp->d_str + lp->d_size;

    while (end-- != lp->d_str)
        free(*end);

    free(lp);
}
