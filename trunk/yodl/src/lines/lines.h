#ifndef _INCLUDED_LINES_H_
#define _INCLUDED_LINES_H_

#include <stdarg.h>

#include "../root/root.h"

typedef struct
{
    char **d_str;
    size_t d_size;
    size_t d_capacity;
}
Lines;

void        lines_add(Lines *lines, char const *line);  /* copies line      */
char const *lines_at(Lines *lines, size_t idx);   /* 0: not existing      */
                                                    /* Not yet implemented  */
size_t      lines_contains(Lines *lp, char const *target);
void        lines_construct(Lines *lines);
void        lines_destroy(Lines *lines);
                                                    /* FAILED or index      */
size_t      lines_find(char const *target, char const **arr,
                       size_t arrsize);
                                                    /* adds sprint-ed       */
void        lines_format(Lines *lines, char const *line, ...)
            ATTRIBUTE_FORMAT_PRINTF(2, 3);
void        lines_grab(Lines *lines, char *line);       /* grabs line       */
size_t      lines_size(Lines *lines);                   /* n lines stored   */

#endif
