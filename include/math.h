/*~!math.h*/
/* Name:  math.h Part No.: _______-____r
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

#ident	"@(#)nbinclude:math.h	1.0"

#ifndef MATH_H
#define MATH_H

#ifndef _POLY9
extern int errno, signgam;

extern double atof(), frexp(), ldexp(), modf();
extern double j0(), j1(), jn(), y0(), y1(), yn();
extern double erf(), erfc();
extern double exp(), log(), log10(), pow(), sqrt();
extern double floor(), ceil(), fmod(), fabs();
extern double gamma();
extern double hypot();
extern int matherr();
extern double sinh(), cosh(), tanh();
extern double sin(), cos(), tan(), asin(), acos(), atan(), atan2();

/* some useful constants */
#define M_E	2.7182818284590452354
#define M_LOG2E	1.4426950408889634074
#define M_LOG10E	0.43429448190325182765
#define M_LN2	0.69314718055994530942
#define M_LN10	2.30258509299404568402
#define M_PI	3.14159265358979323846
#define M_PI_2	1.57079632679489661923
#define M_PI_4	0.78539816339744830962
#define M_1_PI	0.31830988618379067154
#define M_2_PI	0.63661977236758134308
#define M_2_SQRTPI	1.12837916709551257390
#define M_SQRT2	1.41421356237309504880
#define M_SQRT1_2	0.70710678118654752440

#if u3b || M32 || u3b15 || u3b5 || u3b2 || ieee
#define MAXFLOAT	((float)3.40282346638528860e+38)
#endif

#if pdp11 || vax
#define MAXFLOAT	((float)1.701411733192644299e+38)
#endif

#if gcos
#define MAXFLOAT	((float)1.7014118219281863150e+38)
#endif

#if defined(gould) && !defined(ieee)
#ifndef MAXFLOAT
#define MAXFLOAT	((float)0.7237005577332262e76)
#endif
#endif

#define HUGE	MAXFLOAT

#define _ABS(x)	((x) < 0 ? -(x) : (x))
#define _REDUCE(TYPE, X, XN, C1, C2)	{ \
	double x1 = (double)(TYPE)X, x2 = X - x1; \
	X = x1 - (XN) * (C1); X += x2; X -= (XN) * (C2); }
#define _POLY1(x, c)	((c)[0] * (x) + (c)[1])
#define _POLY2(x, c)	(_POLY1((x), (c)) * (x) + (c)[2])
#define _POLY3(x, c)	(_POLY2((x), (c)) * (x) + (c)[3])
#define _POLY4(x, c)	(_POLY3((x), (c)) * (x) + (c)[4])
#define _POLY5(x, c)	(_POLY4((x), (c)) * (x) + (c)[5])
#define _POLY6(x, c)	(_POLY5((x), (c)) * (x) + (c)[6])
#define _POLY7(x, c)	(_POLY6((x), (c)) * (x) + (c)[7])
#define _POLY8(x, c)	(_POLY7((x), (c)) * (x) + (c)[8])
#define _POLY9(x, c)	(_POLY8((x), (c)) * (x) + (c)[9])

struct exception {
	int type;
	char *name;
	double arg1;
	double arg2;
	double retval;
};

#define DOMAIN		1
#define	SING		2
#define	OVERFLOW	3
#define	UNDERFLOW	4
#define	TLOSS		5
#define	PLOSS		6
#endif
#endif

