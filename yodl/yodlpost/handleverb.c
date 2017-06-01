#include "yodlpost.h"

/*
    d_keepws: at `verb on' it was set to 1 else 0.
*/

void handle_verb(long offset, HashItem *item)
{
    file_copy2offset(global.d_out, postqueue_istream(), offset);

    global.d_keep_ws = (bool)hashitem_value(item);
}
