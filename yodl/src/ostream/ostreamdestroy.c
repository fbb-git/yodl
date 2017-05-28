#include "ostream.ih"

void ostream_destruct(register Ostream *ostream)
{
    fclose(ostream->d_stream);
    if (strcmp(ostream->d_filename, "-"))
        unlink(ostream->d_filename);
}
