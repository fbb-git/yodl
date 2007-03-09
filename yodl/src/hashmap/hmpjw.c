#include "hashmap.ih"

/* returns hashvalue for the symboltable */

size_t hm_pjw(char const *key)
{
    register size_t h = 0;
    register size_t g;

    while (*key)
    {
        h <<= 4;
        h += *key;

                                          /* set most significant nibble */
        g = h & ~( (size_t)~0 >> 4 );
        if (g)
        {
            h ^= g >> 8;
            h ^= g;
        }
        key++;
    }
    return h;
}
