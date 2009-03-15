#include "yodlpost.h"

/*
    toc entries are of the form:
        tocentry sectionname sectionnumber entrytext
    e.g.,
        24121 tocentry ssect 2.3.2: Compiling a C program by a C++ compiler

    First the section is determined. It's an error if omitted.

The toc is built as a description list.

Each level is a nested table

When entering a sublevel, as many <table>s are opened to reach the appropriate
level.
When leaving a sublevel, as many </table>s are written to leave the current
level.

When staying inside a level, no <table> or </table> is written.

    Example tocentry:

        21862 tocentry ssect 2.3.1: History of the C++ Annotations

    The toc entry is appended to the toc-lines, the handler received offset
and internal label number.

*/

static size_t s_lastLabelNr;

HashItem *construct_xml_tocentry(char const *key, char *rest)
{
    size_t level;
    char *section = string_firstword(&rest);

    if (!section)
    {
        message_error("incomplete tocentry");
        return 0;
    }
                                                /* find the section's index */
    level = lines_find(section, section_levels, sizeofSectionLevels);
    free(section);


    if (level == UFAILED)                       /* no section given is err. */
    {
        message_error("unknown toc-section `%s'", section);
        return 0;
    }

                                            /* add a new entry              */

    if (global.d_filecount)
        lines_format(&global.d_toc,
                    "%d %s%02u %u %s",
                        global.d_toclevel - level,
                        global.d_noext,
                        (unsigned)global.d_filecount,
                        (unsigned)++s_lastLabelNr,
                        rest);
    else
        lines_format(&global.d_toc,
                    "%d %s %u %s",
                        global.d_toclevel - level,
                        global.d_noext,
                        (unsigned)++s_lastLabelNr,
                        rest);


    global.d_toclevel = level;

    return hashitem_construct(VOIDPTR, "", (void *)s_lastLabelNr, root_nop);
}
