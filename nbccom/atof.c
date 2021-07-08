/*
 *	(c) Copyright 1985 Gould Inc.
 *	    All Rights Reserved.
 *
 */

#if	defined(RCSID) && !defined(lint)
static char *rcsid = "@(#) (Gould) $Header: /bulk2/simhv/nbc-master/nbccom/RCS/atof.c,v 1.1 1995/01/27 21:56:20 jbev Exp $";
/*  @(#) UTX/32   atof.c; ver 1.3 */
#endif

#include <ctype.h>

/*  Note : atof() has been modified to treat trailing zeros which occur before
 *         a decimal point as a power-of-ten multiplier; trailing zeros after a
 *         decimal point are effectively ignored. Thus, for example, 1.00e-2
 *         and .01e0 now convert to the same value.
 *         Note also that division by powers of ten yields a more accurate
 *         result than does multiplication by (approximations to) inverse
 *         powers of ten.
 */

/*
 *  GOULD:  Add table of GOULD hardware floating-point representations
 *	  of powers of ten to get a more accurate exponent conversion.
 */
static double   alignmentdummy = 0;
static int  powers[] =
    {
	0x41a00000, 0x0,
	0x42640000, 0x0,
	0x44271000, 0x0,
	0x475f5e10, 0x0,
	0x4e2386f2, 0x6fc10000,
	0x5b4ee2d6, 0xd415b85b,
	0x76184f03, 0xe93ff9f5
    };
static int limit[] =
    {
	0x4dffffff, 0xffffffff
    };

double
atof(s)
register  unsigned char  *s;
{
    union {
	double d;
	int i[2];
	unsigned char c[8];		/* in order to access exponent */
					/* and last nibble of d */
    } d;
    double	*adjpt, *limp = (double *) limit;
    int         ch, scale = 0, nzro = 0, exp = 0;
    union	{
	int all;
	struct {
	    unsigned nil:27, dp:1, sgn:1, esgn:1, ovlim:1, atlim:1;
	} bit;
    } flag;

    flag.all = 0;

    for (;; s++) {
	switch (*s) {
	    case ' ': 
	    case '\t': 
		continue;
	    case '-': 
		flag.bit.sgn = 1;
	    case '+': 
		s++;
		break;
	}
	break;
    }

    for (d.d = 0.0;; s++) {
	if (isdigit(ch = *s)) {
	    if (flag.bit.dp)
		--scale;
	    if (ch == '0')
		++nzro;
	    else {
		++nzro;
		while (nzro) {
		    register int n = 0;

		    if (flag.bit.ovlim)
			++scale;
		    else {
			if (nzro == 1)
			    n = ch - '0';
			if (flag.bit.atlim) {
			    flag.bit.ovlim = 1;
			    if (isdigit(ch = *(s+1)) && ch > '4')
				++n;
			    n += (d.c[7] * 10) & 0xf;	/* fix lost nibble */
			}
			d.d = d.d * 10.0 + (double) n;
			if (d.d > *limp)
			    flag.bit.atlim = 1;
		    }
		    --nzro;
		}
	    }
	    continue;
	}
	else if (ch == '.' && !flag.bit.dp) {
	    flag.bit.dp = 1;
	    continue;
	}
	else
	/* 
	 * have seen two decimal points
	 * or a character other than a digit or period
	 */
	    break;
    }

    if ((*s & 0xde) == 'D') {	/* ascii 'd', 'e', 'D', or 'E' */
	switch (*++s) {
	    case '-': 
		flag.bit.esgn = 1;
	    case '+': 
		s++;
		break;
	}

	for (; isdigit(ch = *s); s++) {
	    exp = exp * 10 + (ch - '0');
	}
	if (flag.bit.esgn) {
	    exp = -exp;
	    flag.bit.esgn = 0;
	}
    }

    exp += scale + nzro;
/* limit exp to reasonable values - out-of-range will overflow or underflow */
    scale = (int) ((float) 1.20412 * (float) (d.c[0] - 64));
    if (exp > 80 - scale)
	exp = 80 - scale;
    else if (exp < -80 - scale)
	exp = -80 - scale;

    adjpt = (double *) powers;

    if (exp < 0) {
	exp = -exp;
	flag.bit.esgn = 1;
    }
    else if ((exp & 1) == 1 && (d.c[1] & 0xf0) == 0x10
	&& (d.i[0] & 0x00ffffff) <= 0x00199999
	&& ((unsigned) d.i[1] >> 1) < 0x4ccccccd) {
	register int n = d.c[7] * 10;

	    d.d *= 10.0;
	    d.c[7] |= n;	/* fix lost nibble */
	    exp &= ~1;
    }

    for (; exp; exp >>= 1) {
	if (exp & 1) {
	    if (!flag.bit.esgn)
		d.d *= (*adjpt);
	    else
		d.d /= (*adjpt);
	}
	++adjpt;
    }

    return(flag.bit.sgn ? -d.d : d.d);
}

/*
 *	(c) Copyright 1985 Gould Inc.
 *	    All Rights Reserved.
 */
