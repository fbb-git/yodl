#include "lines.ih"

void lines_grab(register Lines *lp, char *line)      /* grabs line      */
{
    if (lp->d_size == lp->d_capacity)
        new_size(&lp->d_str, lp->d_capacity += LINES_BLOCK, lp->d_size,
                                                            sizeof(char *));

    lp->d_str[lp->d_size++] = line;
}
