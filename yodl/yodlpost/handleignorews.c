#include "yodlpost.h"

void handle_ignore_ws(long offset, HashItem *item)
{
    FILE *src = postqueue_istream();
    FILE *dest = global.d_out;

    if (global.d_keep_ws)
        file_copy2offset(dest, src, offset);
    else
    {
        bool skipws = false;

        while (ftell(src) < offset)
        {
            int ch;

            switch (ch = fgetc(src))
            {
                case EOF:
                return;
            
                case '\n':
                    if (skipws)
                        continue;
                    skipws = true;
                break;

                case ' ':
                case '\t':
                    if (skipws)
                        continue;
                break;

                default:
                    skipws = false;
                break;
            }
            fputc(ch, dest);
        }
    }
}
