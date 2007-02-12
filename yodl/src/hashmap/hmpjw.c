#include "hashmap.ih"

/* returns hashvalue for the symboltable */

unsigned hm_pjw(char const *key)
{
    register unsigned h = 0;
    register unsigned g;

    while (*key)
    {
        h <<= 4;
        h += *key;

                                          /* set most significant nibble */
        g = h & (unsigned)(0xf << 4 * ((sizeof(unsigned) * 2) - 1));
        if (g)
        {
            h ^= g >> 8;
            h ^= g;
        }
        key++;
    }

    return h;
}
