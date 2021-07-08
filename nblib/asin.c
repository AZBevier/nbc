/*~!asin.c*/
/* Name:  asin.c Part No.: _______-____r
 *
 * Copyright 1991 - J B Systems, Morrison, CO
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

#ident	"@(#)nbclib:asin.c	1.1"

/*
 *	C program for double-precision asin/acos.
 *	Returns EDOM error and value 0 if |argument| > 1.
 *	Algorithm and coefficients from Cody and Waite (1980).
 *	Calls sqrt if |argument| > 0.5.
 */

#include <math.h>
#include <values.h>
#include <errno.h>

double
asin(x)
double x;
{
	extern double asin_acos();

	return (asin_acos(x, 0));
}

static double
asin_acos(x, acosflag)
register double x;
int acosflag;
{
	register double y;
	register int neg = 0, large = 0;
	struct exception exc;
	
	exc.arg1 = x;
	if (x < 0) {
		x = -x;
		neg++;
	}
	if (x > 1) {
		exc.type = DOMAIN;
		exc.name = acosflag ? "acos" : "asin";
		exc.retval = 0.0;
		if (!matherr(&exc)) {
			(void) write(2, exc.name, 4);
			(void) write(2, ": DOMAIN error\n", 15);
			errno = EDOM;
		}
		return (exc.retval);
	}
    /* skip for efficiency and to prevent underflow */
	if (x > X_EPS) {
/*??    if (x < (X_EPS)) { */
		static double p[] = {
			-0.69674573447350646411e0,
			 0.10152522233806463645e2,
			-0.39688862997504877339e2,
			 0.57208227877891731407e2,
			-0.27368494524164255994e2,
		}, q[] = {
			 1.0,
			-0.23823859153670238830e2,
			 0.15095270841030604719e3,
			-0.38186303361750149284e3,
			 0.41714430248260412556e3,
			-0.16421096714498560795e3,
		};

		if (x <= 0.5)
			y = x * x;
		else {
			large++;
			y = 0.5 - 0.5 * x;
			x = -sqrt(y);
			x += x;
		}
		x += x * y * _POLY4(y, p)/_POLY5(y, q);
	}
	if (acosflag) {
		if (!neg)
			x = -x;
		return (!large ? M_PI_2 + x : neg ? M_PI + x : x);
	}
	if (large)
		x += M_PI_2;
	return (neg ? -x : x);
}

double
acos(x)
double x;
{
	return (asin_acos(x, 1));
}
