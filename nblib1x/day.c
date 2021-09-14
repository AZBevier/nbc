/*~!day.c*/
/* Name:  day.c Part No.: _______-____r
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

#ident	"@(#)nbclib:day.c	1.1"

/*
	day - given julian date and year returns day of week
	based on the fact that January 1st, 1800, was a Wednesday.
*/

#include	<stdio.h>
#include	"libgen.h"

static char	*dayofwk[] = { "Tue", "Wed", "Thu", "Fri", "Sat", "Sun", "Mon" };

#define	leap(y)	( y%4 == 0  &&  y%100 != 0  ||  y%400 == 0 )

char *
day(date, y)
int		date;	/* Julian day of year, 1 through 366 */
register int	y;	/* year */
{
    register long	jdate;
    register int	year;

    if (date > 366 || date <= 0 || (date == 366 && ! leap(y)))
      return 0;
    if (y < 1800)
      return 0;
    jdate = date;
    for(year = 1800; year < y; year++) {
      jdate = jdate + (leap(year) ? 366 : 365);
    }
    return dayofwk [jdate % 7];
}
