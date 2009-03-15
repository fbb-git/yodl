#ifndef INCLUDED_COUNTER_H_
#define INCLUDED_COUNTER_H_

#include "../root/root.h"
#include "../hashmap/hashmap.h"

void        counter_add(HashItem *item, int add);   /* err  if no counter   */
bool        counter_has_value(int *valuePtr, HashItem *item);
Result      counter_insert(HashMap *symtab, char const *key, int value);
void        counter_set(HashItem *item, int value); /* err  if no counter   */
char const *counter_text(HashItem *item);       /* returns static buffer    */
int         counter_value(HashItem *item);      /* err  if no stack/item    */

#endif
