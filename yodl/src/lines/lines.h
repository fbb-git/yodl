#ifndef INCLUDED_LINES_H_
#define INCLUDED_LINES_H_

#include <stdarg.h>

#include "../root/root.h"

typedef struct
{
    char **d_str;
    size_t d_size;
    size_t d_capacity;
}
Lines;

                                                    /* Not yet implemented  */
size_t      lines_contains(Lines *lp, char const *target);

void        lines_destroy(Lines *lines);
                                                    /* FAILED or index      */
size_t      lines_find(char const *target, char const **arr,
                       size_t arrsize);
                                                    /* adds sprint-ed       */
void        lines_format(Lines *lines, char const *line, ...)
            ATTRIBUTE_FORMAT_PRINTF(2, 3);
void        lines_grab(Lines *lines, char *line);   /* grabs line       */


#include <string.h>

                                                    /* copies line      */
static inline void lines_add(Lines *lines, char const *line)
{
    lines_grab(lines, new_str(line));
}
                                                    /* 0: not existing      */
static inline char const *lines_at(register Lines *lines, size_t idx)
{
    return idx >= lines->d_size ? 0 : lines->d_str[idx];
}

static inline void lines_construct(Lines *lines)
{
    memset(lines, 0, sizeof(Lines));
}

static inline size_t lines_size(register Lines *lines)  /* n lines stored   */
{
    return lines->d_size;
}

#endif
