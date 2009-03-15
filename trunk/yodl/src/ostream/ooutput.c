#include "ostream.ih"

/*
    When nothing is printed yet, the received info is stored in a buffer until
    the first non-blank or non-tab. If it's a \n, then the collected line is
    ignored. Otherwise it's printed, and d_empty is set to false

*/

void o_output(register Ostream *op, register char const *str)
{
    if (op->d_empty)                       /* nothing printed yet           */
    {
        while (true)
        {
            str += strspn(str, " \t");      /* skip all leading blank lines */
            if (*str != '\n')
                break;
            str++;
        }

        if (!*str)                          /* just WS at the beginning     */
            return;

        op->d_empty = false;
        op->d_inserted_blanks = false;
    }
    else if (op->d_inserted_blanks)         /* only blanks if no char       */
        op->d_inserted_blanks =             /* beyond the blanks            */
                    str[strspn(str, " \t\n")] == 0;

    if (fputs(str, op->d_stream) == EOF)
        o_write_failure();
}
