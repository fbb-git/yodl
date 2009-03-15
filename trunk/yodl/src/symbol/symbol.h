#ifndef INCLUDED_SYMBOL_H_
#define INCLUDED_SYMBOL_H_

#include "../root/root.h"
#include "../stack/stack.h"
#include "../hashmap/hashmap.h"

/*
    Symbols don't need special structs. They are just stacks, and their names
    are stored in `symtab'
*/

void        symbol_add(HashItem *item, char const *text_to_add);
Result      symbol_insert(HashMap *symtab, char const *name, char const *txt);
void        symbol_set(HashItem *item, char const *text);
char const *symbol_value(HashItem *sp);         /* NULL: no stacked value   */
char const *symbol_valueOf(HashItem *sp);       /* "" no or empty value     */

#endif
