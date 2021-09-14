/*~!weekday.c*/
/* Name:  weekday.c Part No.: _______-____r
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

#ident	"@(#)nbclib:weekday.c	1.1"

/* weekday -- return numeric day of the week
**
** This routine returns the numeric day of the week that corresponds
** to an absolute date.  Output day 0 is a Sunday.  Input day 1 is a
** Saturday.
*/

#include	"libgen.h"

int
weekday(dayn)
long dayn;				/* absolute date */
{
    return ((int)((dayn+5) % 7));	/* day 1 is a Saturday */
}
