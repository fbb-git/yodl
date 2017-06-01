#include "ostream.ih"

void ostream_construct(register Ostream *out, bool trace, char const *name)
{
    if (!name || !*name)
    {
        if (message_show(MSG_INFO))
            message("output to stdout");
        out->d_filename = new_str("-");
        out->d_stream = stdout;
    }
    else
    {
        if (message_show(MSG_INFO))
            message("writing output file `%s'", name);
        out->d_filename = new_str(name);
        out->d_stream = file_open(name, "w");
    }

    out->d_trace = trace;
    out->d_empty = true;
    out->d_inserted_blanks = true;
}
