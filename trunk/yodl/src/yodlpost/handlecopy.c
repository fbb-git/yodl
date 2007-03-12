#include "yodlpost.h"

void handle_copy(long offset, HashItem *item)
{
    file_copy2offset(global.d_out, postqueue_istream(), offset);
}
