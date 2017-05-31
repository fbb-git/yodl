#include "strvector.ih"

StrVectorPair *strVectorPair_new(char const *key, char const *value)
{
    StrVectorPair *ret = new_memory(1, sizeof(StrVectorPair));
    ret->d_key = new_str(key);
    ret->d_value = new_str(value);

    return ret;
}
