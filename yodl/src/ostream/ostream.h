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
void        ostream_set_ws_level(Ostream *outs, size_t value);
bool        ostream_empty(Ostream *outs);
char const *ostream_filename(Ostream *out);
long        ostream_offset(Ostream *out);
                                            /* true: non-ws text was        */
                                            /* inserted                     */
bool        ostream_inserted_text(Ostream *op);
                                            /* inserted only blanks         */
void        ostream_inserted_blanks(register Ostream *op);

#endif
