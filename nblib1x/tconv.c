/*~!tconv.c*/
/* Name:  tconv.c Part No.: _______-____r
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

#ident	"@(#)nbclib:tconv.c	1.1"

/* tconv -- time convert
**
** This routine converts year, month, day, hour, minute, second
** to UNIX's internal time format.  If the input is bad,
** -1 is returned.
*/

#include	"libgen.h"
#include	<time.h>

extern long	time();

long
tconv(year, month, day, hour, minute, second)
int year, month, day;			/* date parameters */
int hour, minute, second;		/* time parameters */
{
    long utime = 0;			/* initial time */
    long date = to_day(month, day, year);
					/* get date (-1 if bad) */

    if (date < 0)
	return( -1L );			/* indicate bad input */

    /* the last time UNIX can handle is 1/18/2038; for simplicity,
    ** stop at 2038
    */
    if (year < 1970 || year > 2037)	/* UNIX can't handle these */
	return( -1L );

    utime = date - to_day(1, 1, 1970);	/* day zero is 1/1/1970 */
    if (0 <= hour && hour <= 23)
	utime = utime * 24 + hour;
    else
	return( -1L );			/* bad hour */

    if (0 <= minute && minute <= 59)
	utime = utime * 60 + minute;
    else
	return( -1L );			/* bad minute */

    if (second < 0 || second >= 60)
	return( -1L );			/* bad seconds */

    utime = utime * 60 + second;		/* include seconds */

    tzset();				/* set time zone information */
    utime += timezone;			/* adjust time for timezone */

    /* Correct for daylight savings time.  Since the number of timezone
    ** hours is one larger during DST, we must subtract an hour's worth
    ** of seconds to compensate (since the GMT was unchanged).
    */

    if (localtime(&utime)->tm_isdst != 0)
	utime -= 1*60*60;

    return( utime );
}
