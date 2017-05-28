#include "yodlpost.h"

/*
    toc entries are of the form:
        tocentry sectionname sectionnumber entrytext
    e.g.,
        24121 tocentry ssect 2.3.2: Compiling a C program by a C++ compiler

    First the section is determined. It's an error if omitted.

The toc is built as a description list. E.g.,

<dl>
    <dt><h2><a href="...">Chapter 1: Introduction</a></h2></dt>
    <dd><dl>
        <dt><h3><a href="...">1.1: From 1.xx to 2.00: what's new?</a></h3></dt>
        <dt><h3><a href="...">1.2: Why use Yodl?</a></h3></dt>
        <dt><h3><a href="...">1.3: Copying Yodl</a></h3></dt>
    </dl></dd>
    <dt><h2><a href="...">Chapter 2: Yodl User Guide</a></h2></dt>
    <dd><dl>
        ....
    </dl/dd>
</dl>
     
The generated toc is not indented, but lines end after </dt> and
(series of) </dl></dd> entries, which includes the final </dl>

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
                                            /* write <dd><dl> for deeper
                                               levels */
    for (; level > global.d_toclevel; ++global.d_toclevel)
        lines_add(&global.d_toc, "<dd><dl>");

                                            /* write </dl></dd> when returning
                                               to shallower levels */
    for (; level < global.d_toclevel; --global.d_toclevel)
        lines_add(&global.d_toc, "</dl></dd>");

                                            /* add a new entry              */
    lines_format(&global.d_toc,
                    "<dt>%s<a href=\"%s#l%u\">%s</a>%s</dt>",
                        toc_section[global.d_doctype][level][0],
                        string_str(&global.d_outName),
                        (unsigned)++s_lastLabelNr,
                        rest,
                        toc_section[global.d_doctype][level][1]);

    return hashitem_new_destructor(VOIDPTR, "", (void *)s_lastLabelNr, root_nop);
}
