#ifndef _INCLUDED_LINES_H_
#define _INCLUDED_LINES_H_

#include <stdarg.h>

typedef struct
{
    char **d_str;
    unsigned d_size;
    unsigned d_capacity;
}
Lines;

void        lines_add(Lines *lines, char const *line);  /* copies line      */
char const *lines_at(Lines *lines, unsigned idx);   /* 0: not existing      */
                                                    /* Not yet implemented  */
unsigned    lines_contains(Lines *lp, char const *target);
void        lines_construct(Lines *lines);
void        lines_destroy(Lines *lines);
                                                    /* FAILED or index      */
unsigned    lines_find(char const *target, char const **arr,
                       unsigned arrsize);
                                                    /* adds sprint-ed       */
void        lines_format(Lines *lines, char const *line, ...);
void        lines_grab(Lines *lines, char *line);       /* grabs line       */
unsigned    lines_size(Lines *lines);                   /* n lines stored   */

#endif
