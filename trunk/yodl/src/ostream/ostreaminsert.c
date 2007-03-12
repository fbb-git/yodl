#include "ostream.ih"

static size_t s_last_line;
static bool   s_errors;

void ostream_insert(register Ostream *ostream, char const *str)
{
    if (s_errors)                           /* return on errors             */
        return;

    if (message_errors())                   /* repeatedly done on errors    */
    {                                       /* but that's ok                */
        s_errors = true;
        return;
    }

    if (!*str)                              /* no string, nogo */
    {
        if (message_show(MSG_DEBUG))
            message("INSERT: <nothing>");
        return;
    }

    if (message_show(MSG_DEBUG))
        message("INSERT \"%s\"", str);

    if (ostream->d_trace)
        fprintf(stderr, "%s", str);

    if (ostream->d_ws_only)
    {
        String out;
        bool non_ws;

        string_construct(&out, str);

                                    /* Ugly semantics, but it means:        */
                                    /* true if there are any non-white      */
                                    /* white-space in `out'                 */
                                /* we did not fail to find the first non-ws */
        non_ws = string_find_first_not_of(&out, isspace) != UFAILED;

        if (non_ws)                 /* If we did find NON-ws chars here */
        {
            if (s_last_line != message_lineno())
            {
                s_last_line = message_lineno();
                warning("IGNORED unexpected non-whitespace text `%s'",
                                                string_str(&out));
            }
            string_destroy(&out);
            return;                 /* ignore the cargo if it contains  */
                                    /* non-ws                           */
        }
        string_destroy(&out);
    }
    o_output(ostream, str);
}
