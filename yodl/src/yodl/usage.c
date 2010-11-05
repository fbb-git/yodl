#include "yodl.h"

/* 
    The usage-text splitting is to prevent the 

        string length 'xxx' is greater than the length '509' ISO C89 compilers
        are required to support

    warning message
*/

void usage()
{
    fprintf (stderr, "%s%s%s%s%s%d%s%d%s",
    message_version(),
"\n"
"Your Own Document Language\n"
"\n"
"Usage: yodl [OPTION]... [FILE]...\n"
"Convert to various documentation formats from FILE or <stdin>.\n"
"\n"
"Options:\n"
"  -D, --define=NAME[=VALUE]\n"
"                       define NAME as a symbol, same as "
                                                    "DEFINESYMBOL(NAME)()\n"
"                       If `=VALUE' is added, NAME receives VALUE as its\n"
"                       initial value, same as DEFINESYMBOL(NAME)(VALUE)\n"
"  -d, --definemacro=NAME=EXPANSION\n"
"                       define NAME as macro expanding to EXPANSION\n",

"  -h, --help           this message\n"
"  -i, --index[=file]   `file' is the name of the index file. By default\n"
"                       <outputbase>.idx is used. No default for stdout.\n"
"  -I, --include=DIR    use directory DIR for system-wide includes files\n"
"                         [.:" STD_INCLUDE "]\n"
"  -k, --keep-ws        When WSLEVEL is non-zero, keep ws at line-heads\n"
"                       unless lines are terminated by \\\n"
"  -l, --live-data=HOW  set \"live data\" policy to HOW [none]:\n",

"                         execute SYSTEM and PIPETHROUGH commands:\n"
"                           `none' or `0':    never (the default)\n"
"                           `confirm' or `1': only when confirmed\n"
"                           `report' or `2':  issuing warning\n"
"                           `ok' or `3':      always\n",

"  -L, --legacy-include do NOT change working directory when including a\n"
"                       Yodl file located in another directory\n"

"  -m, --messages=SET   set message level to a combination of SET acdeinw:\n"
"                          a: alert,    c: crit,    d: debug,\n"
"                          e: error,    i: info,    n: notice,\n"
"                          w: warning\n"
"  -n, --max-nested-files=NR set the maximum number of nested files that\n"
"                       can be parsed to NR [",
    DEFAULT_MAX_NESTED_FILES,
"]\n"
"  -o, --output=FILE    send output to FILE instead of <stdout>\n"
"  -p, --preload=CMD    preload CMD\n"
"  -r, --max-replacements=NR set the maximum number of macros or substs\n"
"                       per character read from file to NR x 10,000 [",
    DEFAULT_MAX_REPLACEMENTS,
"]\n"
"                       (--max-replacements=0 implies no maximum)\n"
"  -t, --trace          trace generated output to <stderr> for each parsing "
                                                                    "pass\n"
"  -V, --version        show Yodl's version\n"
"  -v, --verbose        increase verbosity (-vv...)\n"
"  -W, --warranty       show warranty and copyright\n"
"  -w, --warn           warn about no-macro calls\n"
"\n");


    exit (1);
}









