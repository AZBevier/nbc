/*~!tconvs.c*/
/* Name:  tconvs.c Part No.: _______-____r
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

#ident	"@(#)nbclib:tconvs.c	1.1"

/* tconvs -- convert time string
**
** This routine converts a time string of the sort used by
** the date(1) command to UNIX internal time format,
** which is seconds since midnight, 1/1/1970.
** The time string is of the form
**	mmddhhmm[yy]
** which stands for month-day-hour-minute[-year]
** If the optional year is < 70, we assume it's after 2000.
** Returns -1 if the date/time string is bad.
*/

#include	"libgen.h"
#include	<time.h>

extern long	time();

/* convert two digit chars to number */
#define	cvt(d1,d2)	(((d1) - '0')*10+d2-'0')

long
tconvs(s)
char * s;				/* input string */
{
    char * cp = s;
    int len = 0;
    int year;
    long today = time((long *) 0);	/* get current time */
    struct tm * curtime = localtime(&today);
    long utime;

    /* check for all digits and a reasonable string length */

    while (*cp != '\0')
    {
	len++;
	if (*cp < '0' || *cp > '9')
	    return( -1L );		/* bad string */
	cp++;
    }
    if (len != 8 && len != 10)
	return( -1L );			/* bad length */

    /* tconv takes year, month, day, hour, minute, second */

    if (len == 10)
    {
	if ((year = cvt(s[8], s[9]) + 1900) < 1970)
	    year += 100;		/* make years < 1970 into next century */;
    }
    else
	year = 1900 + curtime->tm_year;

    utime =				/* set preliminary time */
	tconv(year, cvt(s[0], s[1]), cvt(s[2], s[3]),
		cvt(s[4], s[5]), cvt(s[6], s[7]), 0);

    return( utime );
}
