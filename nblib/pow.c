/*~!pow.c*/
/* Name:  pow.c Part No.: _______-____r
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

#ident	"@(#)nbclib:pow.c	1.1"

/*
 *	pow(x, y) returns x ** y.
 *	Returns EDOM error and value 0 for 0 to a non-positive power
 *	or negative to a non-integral power;
 *	ERANGE error and value HUGE or -HUGE when the correct value
 *	would overflow, or 0 when the correct value would underflow.
 *	uses log and exp
 *	This version accepts negative x and integral y,
 *	apparently in violation of the ANSI FORTRAN standard for x ** y.
 *	There is a much more accurate but much more elaborate algorithm
 *	in Cody and Waite, which should be substituted for this.
 */

#include <math.h>
#include <values.h>
#include <errno.h>

double
pow(x, y)
register double x, y;
{
	register int neg;
	struct exception exc;

	if (y == 1) /* easy special case */
		return (x);
	exc.name = "pow";
	exc.arg1 = x;
	exc.arg2 = y;
	exc.retval = 0.0;
	if (!x) {
		if (y > 0)
			return (x); /* (0 ** pos) == 0 */
		goto domain;
	}
	neg = 0;
	if (x < 0) { /* test using integer arithmetic if possible */
		if (y >= -MAXLONG && y <= MAXLONG) {
			register long ly = (long)y;

			if ((double)ly != y)
				goto domain; /* y not integral */
			neg = ly % 2;
		} else {
			double fr, dum, modf();

			if (fr = modf(0.5 * y, &dum)) {
				if (fr != 0.5)
					goto domain; /* y not integral */
				neg++; /* y is odd */
			}
		}
		x = -x;
	}
	if (x != 1) { /* x isn't the final result */
		/* the following code protects against multiplying x and y
		 * until there is no chance of multiplicative overflow */
		if ((x = log(x)) < 0) { /* preserve sign of product */
			x = -x;
			y = -y;
		}
		if (y > LN_MAXDOUBLE/x) {
			exc.type = OVERFLOW;
			exc.retval = neg ? -HUGE : HUGE;
			if (!matherr(&exc))
				errno = ERANGE;
			return (exc.retval);
		}
		if (y < LN_MINDOUBLE/x) {
			exc.type = UNDERFLOW;
			if (!matherr(&exc))
				errno = ERANGE;
			return (exc.retval);
		}
		x = exp(x * y); /* finally; no mishap can occur */
	}
	return (neg ? -x : x);

domain:
	exc.type = DOMAIN;
	if (!matherr(&exc)) {
		(void) write(2, "pow: DOMAIN error\n", 18);
		errno = EDOM;
	}
	return (exc.retval);
}
