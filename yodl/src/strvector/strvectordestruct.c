#include "strvector.ih"

void strVector_destruct(StrVector *sv)
{
    for (size_t idx = sv->d_size; idx--; )
        strVectorPair_delete(sv->d_pair[idx]);

    free(sv->d_pair);
}
