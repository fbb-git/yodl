#include "yodlpost.h"

void handle_ignore_ws(long offset, HashItem *item)
{
    FILE *src = postqueue_istream();
    FILE *dest = global.d_out;

    if (global.d_keep_ws)
        file_copy2offset(src, dest, offset);
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
/*
    file_copy2offset(global.d_out, postqueue_istream(), offset);

    if (global.d_keep_ws)
        return;

    register int ch = fgetc(postqueue_istream());
    if (isspace(ch))
    {
        do
            ch = fgetc(postqueue_istream());
        while (isspace(ch));
        fputc('\n', global.d_out);
    }

    if (ch != EOF)
        fputc(ch, global.d_out);
*/
}
