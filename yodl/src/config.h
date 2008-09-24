/* Yodl version */
#ifndef  TOPLEVEL_VERSION
#define  TOPLEVEL_VERSION "2.13.1"
#endif

#define YODL_YEARS "1996-2008"

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

/*
    The macro INCLUDEFILE(file) will search for `file' as-is, or in a
    system-wide library directory. What's your default system-wide directory
    for include files? This symbol should be set by the top-level Makefile.
    Edit that file (in this directory) before changing it here.
*/
#ifndef STD_INCLUDE
#define STD_INCLUDE     "/usr/share/yodl"
#endif

/*
    Standard conversions:
        Yodl's standard conversion types
*/
#define STD_CONVERSIONS "html latex man txt xml"


/*
    Location of the binaries: where will the binaries eventually be stored?
    Under Debian it will be /usr/bin
*/
#define YODL_BIN    "/usr/bin"
