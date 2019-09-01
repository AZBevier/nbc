/*~!values.h*/
/* Name:  values.h Part No.: _______-____r
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

#ident	"@(#)nbinclude:values.h	1.0"

#ifndef VALUES_H
#define VALUES_H

/* These values work with any binary representation of integers
 * where the high-order bit contains the sign. */

/* a number used normally for size of a shift */
#define BITSPERBYTE	8
#define BITS(type)	(BITSPERBYTE * (int)sizeof(type))

/* short, regular and long ints with only the high-order bit turned on */
#define HIBITS	((unsigned short)(1 << BITS(short) - 1))
#define HIBITI	((unsigned int)1 << BITS(int) - 1)
#define HIBITL	((unsigned long)1L << BITS(long) - 1)

/* largest short, regular and long int */
#define MAXSHORT	((short)(~HIBITS))
#define MAXINT	(~HIBITI)
#define MAXLONG	(~HIBITL)

/* various values that describe the binary floating-point representation
 * _EXPBASE	- the exponent base
 * DMAXEXP 	- the maximum exponent of a double (as returned by frexp())
 * FMAXEXP 	- the maximum exponent of a float  (as returned by frexp())
 * DMINEXP 	- the minimum exponent of a double (as returned by frexp())
 * FMINEXP 	- the minimum exponent of a float  (as returned by frexp())
 * MAXDOUBLE	- the largest double
			((_EXPBASE ** DMAXEXP) * (1 - (_EXPBASE ** -DSIGNIF)))
 * MAXFLOAT	- the largest float
			((_EXPBASE ** FMAXEXP) * (1 - (_EXPBASE ** -FSIGNIF)))
 * MINDOUBLE	- the smallest double (_EXPBASE ** (DMINEXP - 1))
 * MINFLOAT	- the smallest float (_EXPBASE ** (FMINEXP - 1))
 * DSIGNIF	- the number of significant bits in a double
 * FSIGNIF	- the number of significant bits in a float
 * DMAXPOWTWO	- the largest power of two exactly representable as a double
 * FMAXPOWTWO	- the largest power of two exactly representable as a float
 * _IEEE	- 1 if IEEE standard representation is used
 * _DEXPLEN	- the number of bits for the exponent of a double
 * _FEXPLEN	- the number of bits for the exponent of a float
 * _HIDDENBIT	- 1 if high-significance bit of mantissa is implicit
 * LN_MAXDOUBLE	- the natural log of the largest double  -- log(MAXDOUBLE)
 * LN_MINDOUBLE	- the natural log of the smallest double -- log(MINDOUBLE)
 */
#if u3b || i386 || ieee

#if !defined( i386 ) 
#define MAXDOUBLE	1.79769313486231470e+308
#define MINDOUBLE	4.94065645841246544e-324
#else
/* 80287 specific code does a better job than generic */
#define MAXDOUBLE       1.79769313486231570e+308
#define MINDOUBLE       4.94065645841246544e-324
#endif

#ifndef MAXFLOAT
#define MAXFLOAT	((float)3.40282346638528860e+38)
#endif

#define MINFLOAT	((float)1.40129846432481707e-45)
#define	_IEEE		1
#define _DEXPLEN	11
#define _FEXPLEN	8
#define _HIDDENBIT	1

#define CUBRTHUGE	2.6196213420787355e102
#define INV_CUBRTHUGE	.38173571415718220434e-102

#define DMINEXP	(-(DMAXEXP + DSIGNIF - _HIDDENBIT - 3))
#define FMINEXP	(-(FMAXEXP + FSIGNIF - _HIDDENBIT - 3))
#define _LENBASE	1
#endif /* ieee or i386 */

#if defined(gould) && !defined(i386) && !defined(ieee)
#define MAXDOUBLE	0.7237005577332262e76
#ifndef MAXFLOAT
#define MAXFLOAT	((float)MAXDOUBLE)
#endif
/*#define MAXFLOAT	((float)0.7237005145e76)*/
#define MINDOUBLE	5.3976053469342702e-79
#define MINFLOAT	((float)MINDOUBLE)
#define	_IEEE		0
#define _DEXPLEN	8
#define _FEXPLEN	8
#define _HIDDENBIT	0

#define CUBRTHUGE	1.934281311383407e25
#define INV_CUBRTHUGE	5.169878828456423e-26

#define DMINEXP		(-(DMAXEXP+1))
#define FMINEXP		(-(FMAXEXP+1))
#define _LENBASE	4
#endif /* gould */

#define _EXPBASE	(1 << _LENBASE)
#define DSIGNIF	(BITS(double) - _DEXPLEN + _HIDDENBIT - 1)
#define FSIGNIF	(BITS(float)  - _FEXPLEN + _HIDDENBIT - 1)

#define DMAXPOWTWO	((double)(1L << BITS(long) - 2) * \
				(1L << DSIGNIF - BITS(long) + 1))

#define FMAXPOWTWO	((float)(1L << FSIGNIF - 1))
#define DMAXEXP	((1 << _DEXPLEN - 1) - 1 + _IEEE)
#define FMAXEXP	((1 << _FEXPLEN - 1) - 1 + _IEEE)
#define LN_MAXDOUBLE	(M_LN2 * DMAXEXP)
#define LN_MINDOUBLE	(M_LN2 * (DMINEXP - 1))
#define H_PREC	(DSIGNIF % 2 ? (1L << DSIGNIF/2) * M_SQRT2 : 1L << DSIGNIF/2)
#define X_EPS	(1.0/H_PREC)
#define X_PLOSS	((double)(long)(M_PI * H_PREC))
#define X_TLOSS	(M_PI * DMAXPOWTWO)
#define M_LN2	0.69314718055994530942
#define M_PI	3.14159265358979323846
#define M_SQRT2	1.41421356237309504880
#define MAXBEXP	DMAXEXP /* for backward compatibility */
#define MINBEXP	DMINEXP /* for backward compatibility */
#define MAXPOWTWO	DMAXPOWTWO /* for backward compatibility */

#endif /* VALUES_H */
