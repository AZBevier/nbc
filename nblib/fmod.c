/*~!fmod.c*/
/* Name:  fmod.c Part No.: _______-____r
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

#ident	"@(#)nbclib:fmod.c	1.1"

/*
 *	fmod(x, y) returns the remainder of x on division by y,
 *	with the same sign as x,
 *	except that if |y| << |x|, it returns 0.
 */

#include <math.h>

double
fmod(x, y)
register double x, y;
{
	double d; /* can't be in register because of modf() below */

	/*
	 * The next lines determine if |y| is negligible compared to |x|,
	 * without dividing, and without adding values of the same sign.
	 */
	d = _ABS(x);
	if (d - _ABS(y) == d)
		return (x);
	(void) modf(x/y, &d); /* now it's safe to divide without overflow */
	return (x - d * y);
}
