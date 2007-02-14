#include "hashmap.ih"

static size_t primes[] =
{
    0,          /* not used, but immediately skipped by hm_expand()     */
#if 0
    97,         /* the initial primes are not used. Normally we'll use  */
    149,        /* several hundreds of identifiers                      */
    191,
    241,
#endif
    293,
    347,
    397,
    491,
    593,
    691,
    797,
    907,
    1009,
    1201,
    1409,
    1601,
    1801,
    2003,
    3001,
    4001,
    5003,
    6007,
    7001,
    8009,
    9001,
    10007,
    12007,
    14009,
    16001,
    18013,
    20011,
};


void hm_expand(register HashMap *symtab)
{
    if (++symtab->d_prime_idx == sizeof(primes) / sizeof(size_t))
        if (message_show(MSG_EMERG))
            message("hashmap_resize(): prime table exhausted\n");

    symtab->d_size = primes[symtab->d_prime_idx];
    hm_reshuffle(symtab);
}
