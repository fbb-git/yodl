#include "lines.h"

char const *lines_at(register Lines *lines, unsigned idx)
{
    return idx >= lines->d_size ? 0 : lines->d_str[idx];
}
