#include "lines.h"

char const *lines_at(register Lines *lines, size_t idx)
{
    return idx >= lines->d_size ? 0 : lines->d_str[idx];
}
