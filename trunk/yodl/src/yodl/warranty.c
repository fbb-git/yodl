#include "../config.h"

#include "yodl.h"

/* see the note in usage.c */

void warranty()
{
    fprintf (stderr, "%s%s",
    "Yodl --  Your Own Document Language\n"
    "\n"
    "Copyright (c) " YEARS " by Frank B. Brokken (f.b.brokken@rug.nl)\n"
    "              1996-2004: also Karel Kubat; Jan Nieuwenhuizen\n"
    "\n"
    "    This program is free software; you can redistribute it and/or\n"
    "modify it under the terms of the GNU General Public License version 2\n"
    "as published by the Free Software Foundation.\n"
    "\n",

    "    This program is distributed in the hope that it will be useful,\n"
    "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU\n"
    "General Public License for more details.\n"
    "\n"
    "    You should have received a copy (refer to the file COPYING) of the\n"
    "GNU General Public License along with this program; if not, write to\n"
    "the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,\n"
    "USA.\n");
}
