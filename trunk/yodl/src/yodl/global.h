#ifndef INCLUDED_GLOBAL_H_
#define INCLUDED_GLOBAL_H_

#include "../hashmap/hashmap.h"
#include "../builtin/builtin.h"
#include "../chartab/chartab.h"
#include "../ostream/ostream.h"
#include "../parser/parser.h"

extern Builtin  builtin_array[];
extern Ostream  outs;
extern HashMap  symtab;
extern Parser   parser;

#endif
