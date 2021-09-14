/*~!leap.c*/
/* Name:  leap.c Part No.: _______-____r
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

#ident	"@(#)nbclib:leap.c	1.1"

/*
	given a year integer, leap returns a one if the year is
	a leap year and a zero otherwise
*/

#include "libgen.h"

int
leap( year )
int	year;
{
    return ((year % 4 == 0 && year % 100 != 0)  ||
      (year % 400 == 0)) ? 1 : 0;
}
