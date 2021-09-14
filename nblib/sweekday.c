/*~!sweekday.c*/
/* Name:  sweekday.c Part No.: _______-____r
 *
 * Copyright 1992 - J B Systems, Morrison, CO
 *
 * The recipient of this product specifically agrees not to distribute,
 * disclose, or disseminate in any way, to any one, nor use for its own
 * benefit, or the benefit of others, any information contained  herein
 * without the expressed written consent of J B Systems.
 *
 *                     RESTRICTED RIGHTS LEGEND
 *
 * Use, duplication, or disclosure by the Government is  subject  to
 * restriction  as  set forth in paragraph (b) (3) (B) of the Rights
 * in Technical Data and Computer Software  Clause  in  DAR  7-104.9
 * (a).
 */

#ident	"@(#)nbclib:sweekday.c	1.1"

/* sweekday -- return string name of day of the week
**
** This routine returns the name of the day of the week that
** corresponds to an absolute date.  Day 1 is Saturday.  The
** static array therefore begins with Friday at [0].
*/

#include	"libgen.h"

/* Table of names of days.  Day 1 is a Saturday. */

static char * dayname[] = {
	"Friday", "Saturday", "Sunday", "Monday",
	"Tuesday", "Wednesday", "Thursday"
};

char *
sweekday(day)
long day;				/* absolute date */
{
    return( dayname[day%7] );
}
