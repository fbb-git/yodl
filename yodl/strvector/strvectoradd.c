#include "strvector.ih"

enum
{
    EXTEND = 10
};

void strVector_add(StrVector *sv, char const *key, char const *value)
{
    if (sv->d_size == sv->d_capacity)
        new_size(&sv->d_pair, sv->d_capacity += EXTEND, 
                              sv->d_size,
                              sizeof(StrVectorPair *));

    sv->d_pair[sv->d_size++] = strVectorPair_new(key, value);
}
