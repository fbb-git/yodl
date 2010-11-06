#ifndef INCLUDED_OSTREAM_H_
#define INCLUDED_OSTREAM_H_

#include <stdio.h>
#include "../root/root.h"

typedef struct
{
    char const *d_filename;
    FILE       *d_stream;
    bool        d_trace;
    size_t    d_ws_only;
    bool        d_inserted_blanks;  /* True when only blanks were inserted  */
    bool        d_empty;
}
Ostream;

void        ostream_construct(Ostream *out, bool trace, char const *name);
void        ostream_destroy(Ostream *out);
void        ostream_insert(Ostream *outs, char const *str);

static inline void ostream_set_ws_level(register Ostream *out, size_t value)
{
    out->d_ws_only = value;
}

static inline bool ostream_empty(register Ostream *os)
{
    return os->d_empty;
}

static inline char const *ostream_filename(register Ostream *out)
{
    return out->d_filename;
}

static inline long ostream_offset(register Ostream *ostream)
{
    return ftell(ostream->d_stream);
}
                                            /* true: non-ws text was        */
                                            /* inserted                     */
static inline bool ostream_inserted_text(register Ostream *op)
{
    return !op->d_inserted_blanks;
}
                                            /* inserted only blanks         */
static inline void ostream_inserted_blanks(register Ostream *op)
{
    op->d_inserted_blanks = true;
}

#endif
