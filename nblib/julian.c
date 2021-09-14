/*~!julian.c*/
/* Name:  julian.c Part No.: _______-____r
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

#ident	"@(#)nbclib:julian.c	1.1"

/*
	julian is sent three arguments: yy or yyyy, mm, dd that comprise a
	gregorian date.  it returns the number of julian days: ddd
*/

#include <stdio.h>
#include "libgen.h"

#define	LEAP	((year % 4 == 0 && year % 100 != 0) || ( year % 400 \
 == 0 )) ? 1 : 0

int
julian( year, month, dayn )
int	year, month, dayn;
{
	register	mo_indx;
	int		julday = 0;
	register	leapyr;
	
	static	int	day_tab[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30,
					31, 30 };
	
	if ( year < 0 ) {
		fprintf( stderr, "julian: year must be greater than 0\n" );
		exit( 1 );
	}
	leapyr = LEAP;
	if ( month < 1  ||  month > 12 ) {
		fprintf( stderr, "julian: month must be between 1 and");
		fprintf( stderr, " 12\n" );
		exit( 1 );
	} else if ( dayn > day_tab[month]  || dayn < 1 ) {
		if ( month == 2  &&  dayn == 29  &&  leapyr )
			;
		else {
			fprintf( stderr, "julian: wrong number of" );
			fprintf( stderr, " days for month\n" );
			exit( 1 );
		}
	}
	for ( mo_indx = 1; mo_indx <= month; mo_indx++ )
		julday += day_tab[ mo_indx - 1 ];
	julday += dayn;
	if( leapyr  &&  month > 2 )
		julday++;
	return julday;
}
