#include "lines.ih"

void lines_add(Lines *lines, char const *line)      /* copies line      */
{
    lines_grab(lines, new_str(line));
}
