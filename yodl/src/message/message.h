#ifndef INCLUDED_MESSAGE_H_
#define INCLUDED_MESSAGE_H_

#include "../root/root.h"

/*
    Enum MESSAGE_SEVERITY follows the syslog classification.  message() may
use the | operator to combine a message for several severity levels Also
message_setseverity() may use this, as well as MSG_NONE to suppress all
messages and MSG_ALL to show all messages (except for MSG_EMERG messages and
builtin WARNING() calls)

    MSG_DEBUG:  Probably too much info, like getting a (and which) character
                from the lexer's media stack.
    MSG_INFO:   Not as detailed as characters, but still very much info, like
                a media switch and return to a former media.
    MSG_NOTICE: All predefined function calls fall in this category
    MSG_WARNING:Something you should know about, but probably not affecting
                Yodl's proper functioning.
    MSG_ERR:    An error (like doubly defined symbols), parsing continues (up
                to a maximum number of errors) with fingers crossed,
                but no output is generated. With MSG_ERR functions may
                terminate without properly freeing allocated memory. The
                maximum error limit should be reached before memory
                exhaustion occurs. If not: too bad. The alternative is too
                cumbersome in C, lacking proper exception handling mechanisms.
    MSG_CRIT:   Below here yodl terminates. The message itself can be
                suppressed, but exiting can't. A critical condition is, e.g.,
                not an open parenthesis at a location where a parameter list
                is expected, or a non-existing file in an INCLUDEFILE
                specification (as thisfile should be parsed. A non-existing
                file with a NOEXPANDINCLUDE specification is a mere MSG_ERR)
    MSG_ALERT:  Yodl requests something of the system (like a get_cwd(),
                but the system fails.
    MSG_EMERG:  Shouldn't happen, like a failing regex_comp() with a fixed
                pattern: it used to work up to now, so it's unclear as to
                why it now fails. Also, an underflow of the lexer's media
                stack falls into this category. EMERG messages cannot be
                suppressed.
*/

typedef enum
{
    MSG_DEBUG   = 1 << 0,           /*  debug-level message                 */
    MSG_INFO    = 1 << 1,           /*  informational message               */
    MSG_NOTICE  = 1 << 2,           /*  normal, but significant, condition  */
    MSG_WARNING = 1 << 3,           /*  warning conditions                  */
    MSG_ERR     = 1 << 4,           /*  error conditions                    */
    MSG_CRIT    = 1 << 5,           /*  critical conditions                 */
    MSG_ALERT   = 1 << 6,           /*  action must be taken immediately    */
    MSG_EMERG   = 1 << 7,           /*  system is unusable                  */

    MSG_NONE    = 0,                /*  No messages                         */
    MSG_ALL     = ~0                /*  All messages                        */
}
MESSAGE_SEVERITY;

typedef struct
{
    size_t              d_max_errors;
    size_t              d_errors;
    char                *d_program_name;
    char                *d_filename;
    size_t              d_lineno;
    MESSAGE_SEVERITY    d_severity;
    MESSAGE_SEVERITY    d_last_show;
    bool                d_warn;

    char                *d_short_filename;          /* not allocated    */
}
Message;

extern int message_data;

void    message(char const* format, ...) ATTRIBUTE_FORMAT_PRINTF(1, 2);
void    message_construct(char const *argv0);
void    message_error(char const *fmt,...) ATTRIBUTE_FORMAT_PRINTF(1, 2);
void    message_optarg(char const *opt);
bool    message_show(MESSAGE_SEVERITY level);
void    message_setfilename(char const *newname);
void    message_setlineno(size_t   lineno);
void    message_setmaxerrors(size_t   max);
void    message_setmask(size_t   mask);
void    message_setseverity(MESSAGE_SEVERITY level);
void    message_setverbosity(int mode, char *arg);  /* arg may be modified  */
void    message_setwarn(bool trueIsOn);
void    message_incseverity(void);
void    warning(char const* format, ...) ATTRIBUTE_FORMAT_PRINTF(1, 2);
                                                    /* not suppressable     */


bool                message_errors(void);
char const         *message_filename(void);
size_t              message_lineno(void);
char const         *message_programname(void);
char const         *message_verbosity(void);       /* returns (hex) mask   */
char const         *message_version(void);
MESSAGE_SEVERITY    message_mask(void);

#endif
