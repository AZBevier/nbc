/*~!atof.c*/
/* Name:  atof.c Part No.: _______-____r
 *
 * Copyright 1995 - J B Systems, Morrison, CO
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

#ident	"@(#)nbclib:atof.c	1.1"

#if defined(gould) && !defined(ieee)

#include <ctype.h>
#include <values.h>
#include <math.h>
#include <errno.h>

#ifndef STRTOD
#define	STRTOD 0
#endif

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

/*
 *  	  We use this version instead of System V's portable version
 *	  so that the BSD compiler and the SYSV compiler will agree
 *	  on floating point conversion precision.
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

#if STRTOD

#define STORE_PTR (*ptr = s)
#define	GOT_DIGIT (got_digit++)
#define	RET_ZERO(val) if (!got_digit) return(0.0)
double
strtod(s, ptr)
register char *s;
char **ptr;
{

#else

#define	STORE_PTR
#define	GOT_DIGIT
#define	RET_ZERO(val) if (val == 0.0) return(0.0)
double
atof(s)
register  unsigned char  *s;
{
#endif

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

#if STRTOD
    int got_digit = 0;
    char *dummy;
    if (ptr == (char **)0)
	ptr = &dummy;
    STORE_PTR;
#endif

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
	    GOT_DIGIT;
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
			    if (isdigit(ch = *(s+1)) && ch > '4') {
				++n;
				GOT_DIGIT;
			    }
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

    RET_ZERO(d.d);
    STORE_PTR;
    if ((*s & 0xde) == 'D') {	/* ascii 'd', 'e', 'D', or 'E' */
	switch (*++s) {
	    case '-':
		flag.bit.esgn = 1;
	    case '+':
		s++;
		break;
	}

	for (; isdigit(ch = *s); s++) {
	    if (exp < DMAXEXP)
		exp = exp * 10 + (ch - '0');
	    else {
		errno = ERANGE;
		if (flag.bit.esgn)
			return(0.0);
		return(flag.bit.sgn ? -HUGE : HUGE);
	    }
	}
	STORE_PTR;
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

#else /* !gould || ieee */

/* #ident	"@(#)libc-port:gen/atof.c	2.16" */
/*LINTLIBRARY*/
/*
 *	C library - ascii to floating (atof) and string to double (strtod)
 *
 *	This version compiles both atof and strtod depending on the value
 *	of STRTOD, which is set in the file and may be overridden on the
 *	"cc" command line.  The only difference is the storage of a pointer
 *	to the character which terminated the conversion.
 *	Long-integer accumulation is used, except on the PDP11, where
 *	"long" arithmetic is simulated, so floating-point is much faster.
 */
#ifndef STRTOD
#define STRTOD	0
#endif

#include <ctype.h>
#include <values.h>

extern double ldexp();

#if u3b || M32 || i386 || defined(ieee)
#	define POW1_25LEN	9
#else
#if defined(gould) && !defined(i386)
#	define POW1_25LEN	7
#else
#	define POW1_25LEN	6
#endif
#endif

static double pow1_25[POW1_25LEN] = { 0.0 };

#if STRTOD
#define STORE_PTR	(*ptr = p)
#define DEC_PTR		(*ptr = p - 1)
#define GOT_DIGIT	(got_digit++)
#define RET_ZERO(val)	if (!got_digit) return (0.0)

double
strtod(p, ptr)
register char *p;
char **ptr;
#else
#define STORE_PTR
#define DEC_PTR
#define GOT_DIGIT
#define RET_ZERO(val)	if (!val) return (0.0)

double
atof(p)
register char *p;
#endif
{
	register int c;
	int exp = 0, neg_val = 0;
	double fl_val;
#if STRTOD
	int got_digit = 0;
	char *dummy;
	if (ptr == (char **)0)
		ptr = &dummy; /* harmless dumping place */
	STORE_PTR;
#endif
	while (isspace(c = *p)) /* eat leading white space */
		p++;
	switch (c) { /* process sign */
	case '-':
		neg_val++;
	case '+': /* fall-through */
		p++;
	}
	{	/* accumulate value */
		register long high = 0, low = 0, scale = 1;
		register int decpt = 0, nzeroes = 0;

		while (isdigit(c = *p++) || c == '.' && !decpt++) {
			if (c == '.')
				continue;
			GOT_DIGIT;
			if (decpt) { /* handle trailing zeroes specially */
				if (c == '0') { /* ignore zero for now */
					nzeroes++;
					continue;
				}
				while (nzeroes > 0) { /* put zeroes back in */
					exp--;
					if (high < MAXLONG/10) {
						high *= 10;
					} else if (scale < MAXLONG/10) {
						scale *= 10;
						low *= 10;
					} else
						exp++;
					nzeroes--;
				}
				exp--; /* decr exponent if decimal pt. seen */
			}
			if (high < MAXLONG/10) {
				high *= 10;
				high += c - '0';
			} else if (scale < MAXLONG/10) {
				scale *= 10;
				low *= 10;
				low += c - '0';
			} else
				exp++;
		}
		RET_ZERO(high);
		fl_val = (double)high;
		if (scale > 1)
			fl_val = (double)scale * fl_val + (double)low;
	}
	DEC_PTR; /* in case there is no legitimate exponent */
	if (c == 'E' || c == 'e') { /* accumulate exponent */
		register int e_exp = 0, neg_exp = 0;
		STORE_PTR;

		switch (*p) { /* process sign */
		case '-':
			neg_exp++;
		case '+': /* fall-through */
		case ' ': /* many FORTRAN environments generate this! */
			p++;
		}
		if (isdigit(c = *p)) { /* found a legitimate exponent */
			do {
				/* limit outrageously large exponents */
				if (e_exp < DMAXEXP)
					e_exp = 10 * e_exp + c - '0';
			} while (isdigit(c = *++p));
			if (neg_exp)
				exp -= e_exp;
			else
				exp += e_exp;
			STORE_PTR;
		}
	}
#if STRTOD
	if (!fl_val) /* atof will already have returned, but strtod had */
		return (fl_val); /* to find the end of the exponent first */
#endif
	/*
	 * The following computation is done in two stages,
	 * first accumulating powers of (10/8), then jamming powers of 8,
	 * to avoid underflow in situations like the following (for
	 * the DEC representation): 1.2345678901234567890e-37,
	 * where exp would be about (-37 + -18) = -55, and the
	 * value 10^(-55) can't be represented, but 1.25^(-55) can
	 * be represented, and then 8^(-55) jammed via ldexp().
	 */
	if (exp != 0) { /* apply exponent */
		register double *powptr = pow1_25, fl_exp = fl_val;

		if (*powptr == 0.0) { /* need to initialize table */
			*powptr = 1.25;
			for (; powptr < &pow1_25[POW1_25LEN - 1]; powptr++)
				powptr[1] = *powptr * *powptr;
			powptr = pow1_25;
		}
		if ((c = exp) < 0) {
			c = -c;
			fl_exp = 1.0;
		}
		if (c >= DMAXEXP/2) /* outrageously large exponents */
			c = DMAXEXP/2 - 1; /* will be handled by ldexp */
		for ( ; ; powptr++) {
			/* binary representation of ints assumed; otherwise
			 * replace (& 01) by (% 2) and (>>= 1) by (/= 2) */
			if (c & 01)
				fl_exp *= *powptr;
			if ((c >>= 1) == 0)
				break;
		}
		fl_val = ldexp(exp < 0 ? fl_val/fl_exp : fl_exp, 3 * exp);
	}
	return (neg_val ? -fl_val : fl_val); /* apply sign */
}
#endif /* gould ieee */
