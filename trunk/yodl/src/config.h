#ifndef _INCLUDED_CONFIG_H_
#define _INCLUDED_CONFIG_H_

#include "../tmp/wip/config.h"

/*
    For the "INCLUDEFILE(filename)" macro and for filenames on the command
    line, yodl will supply a default extension (if needed).
*/

#define DEFAULT_EXT         ".yo"

/* 
    Parsing and re-parsing can lead to endless loops, e.g., if a macro or
    subst definition is eventually expanded to itself. The same may happen
    when a file includes itself.  To allow YODL to detect these situations,
    the following two configuration defines were defined:

    DEFAULT_MAX_NESTED_FILES defines the default maximum number of nested
    files that YODL will process, 

    DEFAULT_MAX_REPLACEMENTS defines the default maximum number of macro- or
    subst- expansions x 10,000 that are accepted between characters that were
    actually read from file. If either limit is exceeded, YODL aborts. Both
    defaults are run-time configurable using command-line flags. 

    No replacement limit is enforced when it is set to 0.
*/
#define DEFAULT_MAX_NESTED_FILES    20
#define DEFAULT_MAX_REPLACEMENTS    1

#endif


