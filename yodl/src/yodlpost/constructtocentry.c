#include "yodlpost.h"

/*
    toc entries are of the form:
        tocentry sectionname sectionnumber entrytext
    e.g.,
        24121 tocentry ssect 2.3.2: Compiling a C program by a C++ compiler

    First the section is determined. It's an error if omitted.

The toc is built as a description list.

Each level is surrounded by <dl> ... </dl> tags.
Each element in a level is enclosed by <dt>...</dt>, using a header
appropriate to the particular level.

When entering a sublevel, as many <dl>s are opened to reach the appropriate
level.
When leaving a sublevel, as many </dl>s are written to leave the current
level.

When staying inside a level, no <dl> or </dl> is written.

    Example tocentry:

        21862 tocentry ssect 2.3.1: History of the C++ Annotations

    The toc entry is appended to the toc-lines, the handler received offset
and internal label number.

*/

static size_t s_lastLabelNr;

HashItem *construct_tocentry(char const *key, char *rest)
{
    size_t level;
    char *section = string_firstword(&rest);

    if (!section)
    {
        message_error("incomplete tocentry");
        return 0;
    }
    string_strip(&rest);
                                                /* find the section's index */
    level = lines_find(section, section_levels, sizeofSectionLevels);

    if (level == UFAILED)                       /* no section given is err. */
    {
        message_error("unknown toc-section `%s'", section);
        free(section);
        return 0;
    }

    free(section);

    if (level > global.d_toclevel)          /* E.g., at chapter to ssect    */
    {                                       /* go to a nested section       */
        do                                  /* add levels until reaching    */
        {                                   /* the requested level          */
            lines_add(&global.d_toc, "<dl>");
        }
        while (++global.d_toclevel != level);
    }

    else if (level < global.d_toclevel)     /* E.g., at ssect to chapter    */
    {                                       /* go to outer level            */
        do                                  /* add levels until reaching    */
        {                                   /* the requested level          */
            lines_add(&global.d_toc, "</dl>");
        }
        while (level != --global.d_toclevel);
    }

                                            /* add a new entry              */
    lines_format(&global.d_toc,
                    "<dt>%s"
                    "<a href=\"%s#l%u\">%s</a>"
                    "%s</dt>",
                        toc_section[global.d_doctype][level][0],
                        string_str(&global.d_outName),
                        (unsigned)++s_lastLabelNr,
                        rest,
                        toc_section[global.d_doctype][level][1]);

    return hashitem_construct(VOIDPTR, "", (void *)s_lastLabelNr, root_nop);
}
