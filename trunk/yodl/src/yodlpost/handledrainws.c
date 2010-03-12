#include "yodlpost.h"

void handle_drain_ws(long offset, HashItem *item)
{
    FILE *src = postqueue_istream();
    FILE *dest = global.d_out;

    while (ftell(src) < offset)
    {
        register int ch;

        switch (ch = fgetc(src))
        {
            case EOF:
            return;
        
            case ' ':
            case '\t':
            continue;
        }
        fputc(ch, dest);
    }
}

