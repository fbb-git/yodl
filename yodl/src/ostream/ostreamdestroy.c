#include "ostream.ih"

void ostream_destroy(register Ostream *ostream)
{
    fclose(ostream->d_stream);
    if (strcmp(ostream->d_filename, "-"))
        unlink(ostream->d_filename);
}
