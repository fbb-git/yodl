#ifndef _INCLUDED_YODL_H_
#define _INCLUDED_YODL_H_

#include <errno.h>
#include <libgen.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

#include "../config.h"

#include "global.h"             /* The global Parser parser struct is used  */
                                /* by the gram_XXX functions to perform     */
                                /* their tasks                              */

#include "../new/new.h"
#include "../args/args.h"
#include "../message/message.h"
#include "../lexer/lexer.h"
#include "../macro/macro.h"
#include "../process/process.h"
#include "../chartab/chartab.h"
#include "../counter/counter.h"
#include "../file/file.h"
#include "../symbol/symbol.h"


#include "gram.h"               /* defines all `void gram_...() functions */

void    add_user_macros();
void    add_user_symbols();
bool    check_live_data(char const *cmd);
void    insert_XXincludePath();
void    preamble(int argc, char **argv);    /* global initializations */
void    set_message_level();
void    usage();
bool    userconfirm(char const *cmd);
void    warranty();


#endif
