#include "strvector.ih"

int strVector_find(StrVector const *sv, char const *key)
{
    for (size_t idx = 0; idx != sv->d_size; ++idx)
    {
        if (strcmp(key, sv->d_pair[idx]->d_key) == 0)
            return idx;
    }

    return -1;
}
