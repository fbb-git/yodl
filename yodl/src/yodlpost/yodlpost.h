#ifndef INCLUDED_YODLPOST_H_
#define INCLUDED_YODLPOST_H_

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../postqueue/postqueue.h"
#include "../lines/lines.h"

typedef enum
{
    UNDETERMINED_SECTION = 0,
    CHAPTER,
    SECTION,
    SUBSECTION,
    SUBSUBSECTION,
    _SectionLevels_searchfield,
    sizeofSectionLevels
}
SectionLevels;

typedef enum
{
    BOOK                = (1 << 0),
    REPORT              = (1 << 1),
    ARTICLE             = (1 << 2),
    MANPAGE             = (1 << 3),
    LETTER              = (1 << 4),
    OTHER_DOCTYPE       = (1 << 5),
    sizeofDocType   = 6
}
DocType;
/*      Modify data.c:doctypes[] when this emum is altered              */

/*
    args_arg(2) has the name of Yodl's output file.
    d_noext is set to file_rmExtension(args_arg(2))
    d_outname is set the full filename of the current output file.
*/
typedef struct
{
    bool        d_keep_ws;              /* true if series of ws should  */
                                        /* be KEPT by ignore_ws         */
                                        /* initially false              */

    size_t    d_fileNr;               /* currently written file       */
    size_t    d_filecount;            /* counts filenumbers           */
    Lines       d_section;              /* stores section names         */
    DocType     d_doctype;

    char       *d_noext;                /* output file without ext.     */
    char       *d_ext;                  /* extension for the output     */
    String      d_outName;              /* name of current output file  */
    FILE       *d_out;                  /* currently written file       */


    Lines       d_toc;                  /* stores table of contents     */
    size_t    d_toclevel;             /* level of current toc entries */
                                        /* (chapter, section, etc.)     */

    HashMap     d_symbol;               /* configurable symbols         */
                                        /* (title, bodytagopt, etc.     */
}
Global;

typedef struct
{
    size_t d_filenr;
    size_t d_section;                  /* points to tos(d_section)    */
}
LabelInfo;

extern char const *default_symbols[][2];    /* initializes d_symbol     */
extern Global       global;
extern char const  *section_levels[];
extern HashMap      symtab;
extern Task         task[];
extern char const **toc_section[][sizeofSectionLevels];
extern char const  *doctypes[];


void html_chapterlinks(int current);    /* set links to next/prev chap  */
void xml_chapterlinks(int current);     /* set links to next/prev chap  */
char *xml_label_name(char const *lab);  /* change all nonalnum chars to .   */

HashItem *construct_deprecated(char const *key, char *rest);
HashItem *construct_label(char const *key, char *rest);
HashItem *construct_labvalue(char const *key, char *rest);
HashItem *construct_lastnumber(char const *key, char *rest);
HashItem *construct_newfile(char const *key, char *rest);
HashItem *construct_nop(char const *key, char *rest);
HashItem *construct_preset(char const *key, char *rest);
HashItem *construct_ref(char const *key, char *rest);
HashItem *construct_set(char const *key, char *rest);
HashItem *construct_toc(char const *key, char *rest);
HashItem *construct_tocentry(char const *key, char *rest);
HashItem *construct_txt_tocentry(char const *key, char *rest);
HashItem *construct_verb(char const *key, char *rest);
HashItem *construct_xml_done(char const *key, char *rest);
HashItem *construct_xml_tocentry(char const *key, char *rest);


void    handle_copy(long offset, HashItem *item);
void    handle_drain_ws(long offset, HashItem *item);

void    handle_html_done(long offset, HashItem *item);
void    handle_html_label(long offset, HashItem *item);
void    handle_html_tocentry(long offset, HashItem *item);
void    handle_html_newfile(long offset, HashItem *item);

void    handle_ignore_ws(long offset, HashItem *item);
void    handle_labvalue(long offset, HashItem *item);
void    handle_nop(long offset, HashItem *item);
void    handle_ref(long offset, HashItem *item);
void    handle_set(long offset, HashItem *item);
void    handle_solvelink(long offset, HashItem *item);
void    handle_txt_ref(long offset, HashItem *item);
void    handle_txt_toc(long offset, HashItem *item);
void    handle_txt_tocentry(long offset, HashItem *item);
void    handle_toc(long offset, HashItem *item);
void    handle_verb(long offset, HashItem *item);

void    handle_xml_done(long offset, HashItem *item);
void    handle_xml_label(long offset, HashItem *item);
void    handle_xml_newfile(long offset, HashItem *item);
void    handle_xml_solvelink(long offset, HashItem *item);
void    handle_xml_toc(long offset, HashItem *item);
void    handle_xml_tocentry(long offset, HashItem *item);
void    handle_xml_ref(long offset, HashItem *item);

void    usage(void);


/*
    When reading the index file, its keys are looked up in the Task array.
    Each key's construct_ function is called, and the returned HashItem *, is
    then processed according to its value/organization:

    construct_...() functions return:
                        0: disregard due to, e.g., error

                        HashItem *, processed depending on the existence of a
                        value for d_handler in the corresponding task-struct.

                        If non-zero:
                            the queue processor handles the HashItem in
                            sequence and calls its hashitem_destroy() function
                            and destroys the HashItem itself afterwards.

                        If zero:
                            the hashitem is stored by its key in the symbol
                            table.



construct/handler function pairs used by yodlpost:
========================================================

construct_deprecated():
    VALUE NOT FREED

    deprecated as the INTERNALINDEX(set key ...} should be used.

    returns HashItem(key, new_str(rest))

handle_set():
    stores value at element key in d_symbols.
    free() not required.

------------------------------------------------------------------------

construct_label():
    Stores the label in the symboltable:
    stores HashItem(labelname, new LabelInfo(sectionidx, filecount))

    returns HashItem(labelname, offset);

    0 is returned and an error is generated when no label is specified
      or if the label is doubly defined.

handle_label():
    cp2offset, then write the label anchor to the output file.

------------------------------------------------------------------------

construct_labvalue():
    returns HashItem(labelname, new long(offset));

    0 is returned and an error is generated when no label is specified.

handle_labvalue():
    Writes the label's section after copying the input file to the
    indicated offset

------------------------------------------------------------------------

construct_lastnumber():
    adds the section number to Lines d_section
    returns HashItem("", 0);

handle_lastnumber():
    No action required.

------------------------------------------------------------------------

construct_newfile():
    Marks the location of then next file to be processed.
    The file number is incremented at each construct_newfile() call, which
    is then used as the filenumber of subsequent labels. Later, when the queue
    is processed, the filecount is reset to 0. As the newfile handlers also
    increment the filecount the numbers are synchronized, and need not be kept
    inside the HashItem's value.

    returns HashItem("", 0)

handle_newfile():
    cp2offset,
    closes the current file (and writes chapterlinks), opens the next file
    (and writes chapterlinks)

------------------------------------------------------------------------

construct_ref():
    Marks the offset where the section of a label should be inserted.

    returns HashItem(labelname, new long(offset));

    returns 0 if no label was specified.

handle_ref():
    cp2offset,
    looks up the label, writes <a href=file#label>section nr.</a>

handle_solvelink():
    cp2offset,
    looks up the label, writes file#label

------------------------------------------------------------------------

construct_set():
    VALUE NOT FREED

    Extracts key and value beyond `set', to be stored later in the d_symbols
    map.

    returns HashItem(key, string_strip(rest))

    returns 0 if no key was specified. Empty `rest' is ok.

handle_set():
    stores value at element key in d_symbols.
    free() not required.

------------------------------------------------------------------------

construct_toc():
    returns HashItem(tocheader 0)

handle_toc():
    writes a <h1> tocheader </h1> followed by all lines of the toc to the
current output file.


------------------------------------------------------------------------

construct_tocentry():
    Enters a <a href "outfilename#labelnr">description</a> in the
    &global.d_toc

    returns HashItem(key, new TocInfo(offset, labelnr),

    which is converted into label l<labelnr> at `offset' by the queue
    processor.

    Error conditions are: missing or unknown section indicator.

handle_tocentry():
    cp2offset,
    prints <a name="lxxx"></a> to the output file.

------------------------------------------------------------------------

*/

#endif
