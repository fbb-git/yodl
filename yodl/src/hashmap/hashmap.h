#ifndef INCLUDED_HASHMAP_H_
#define INCLUDED_HASHMAP_H_

/* ======================================================================

    The hashtable contains a vector of pointers to hashitems.

    The hashItems are all freeable. HashItems know how to free themselves

    functions are called hashmap...()
*/

#include "../root/root.h"
#include "../hashitem/hashitem.h"

typedef struct
{
    size_t d_size;        /* physical size                        */
    size_t d_n;           /* actual n stored                      */
    size_t d_prime_idx;   /* currently used index in primetable   */
    HashItem **d_map;       /* actual hashmap                       */
}
HashMap;

void        hashmap_construct(HashMap *map);
                                /* initialize from ptr, until *ptr == 0     */
void        hashmap_constructText(HashMap *map, char const *(*ptr)[2]);

                                /* SUCCESS: Item is removed from the map */
Result       hashmap_erase(HashMap *map, char const *key, SymbolType type);

                                /* PFAILED if not found. */
HashItem    *hashmap_find(HashMap *map, char const *key, SymbolType type);

                                /* hashitem will be owned by map */
Result      hashmap_insert(HashMap *map, HashItem *hashitem);

void        hashmap_keys(HashMap *map);     /* display to stderr            */

                                /* FAILED: no name MACRO/BUILTIN, NULL:     */
                                /* newname already in use, otherwise: ok    */
HashItem   *hashmap_rename(HashMap *map, char const *name,
                                            char const *newname);

                                /* returns text (or "") of key, but the     */
                                /* hashitem's value must be a char *        */
char const *hashmap_textOf(HashMap *map, char const *key);

size_t    hashmap_value(HashMap *map, size_t idx);

                                /* type at map[idx]. idx must be valid */
static inline SymbolType hashmap_symboltype(register HashMap *map, size_t idx)
{
    return hashitem_type(map->d_map[idx]);
}

#endif




