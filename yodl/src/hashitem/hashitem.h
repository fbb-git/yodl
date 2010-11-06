#ifndef INCLUDED_HASHITEM_H_
#define INCLUDED_HASHITEM_H_

#include "../root/root.h"

/* =========================================================================
    `private' functions are called hi_...() and are declared in hashitem.ih.

    A corresponding approach is followed for other structs, mentioned below.

    public functions are called hashitem...()

*/
typedef struct
{
    SymbolType  d_type;                     /* type of symbol       */
    char        *d_key;                     /* ascii-z              */

    void        *d_value;                   /* points to the value  */
    void        (*d_destructor)(void *);    /* knows how to destroy d_value */
}
HashItem;

void        hashitem_changekey(HashItem *hashitem, char const *key);
HashItem   *hashitem_construct(SymbolType type, char const *key, void *value,
                                         void (*destructor)(void *));
void        hashitem_erase(HashItem *hashitem);
HashItem   *hashitem_new(char const *key, SymbolType type);
Result      hashitem_pop(HashItem *item);
void        hashitem_set(HashItem *item, void *value,
                                         void (*destructor)(void *));

/* 
    Internal HashItem use only. Not used outside of this directory, needed here
    to allow proper compilation of the static inline functions below
*/

#include <string.h>

/*  public interface continues from here */


static inline char const *hashitem_key(HashItem const *item)
{
    return item->d_key;
}

static inline void hashitem_setType(register HashItem *item, SymbolType type)
{
    item->d_type = type;
}
                                                /* caller may not free      */
                                                /* the returned info        */
                                                /* modifying its contents   */
                                                /* is ok                    */
static inline void *hashitem_value(register HashItem *item)
{
    return item != PFAILED ? item->d_value : PFAILED;
}

static inline SymbolType hashitem_fullType(register HashItem *item)
{
    return item == PFAILED ? UNDEFINED_SYMBOL : item->d_type;
}

static inline bool hashitem_iskeytype(HashItem const *hashitem,
                                       char const *key, SymbolType type)
{
    return (hashitem->d_type & type) && !strcmp(hashitem->d_key, key);
}

static inline SymbolType hashitem_type(register HashItem *item)
{
    return item == PFAILED ? UNDEFINED_SYMBOL : (item->d_type & ANY);
}

#endif
