/*~!ecvt.c*/
/* Name:  ecvt.c Part No.: _______-____r
 *
 * Copyright 1990 - J B Systems, Morrison, CO
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

#ident	"@(#)nbclib:ecvt.c	1.0"

/*
 *	ecvt converts to decimal
 *	the number of digits is specified by ndigit
 *	decpt is set to the position of the decimal point
 *	sign is set to 0 for positive, 1 for negative
 *
 */

#ifdef ieee	/* defined when -f flag to nbcc specified */
#define unix
#endif

#ifdef unix	/* unix is not defined in MPX UNIX */

#include <nan.h>
#include <values.h>
#define	NMAX	((DSIGNIF * 3 + 19)/10) /* restrict max precision */
#define	NDIG	80

extern char *cvt();

char *
ecvt(value, ndigit, decpt, sign)
double	value;
int	ndigit, *decpt, *sign;
{
	return (cvt(value, ndigit, decpt, sign, 0));
}

char *
fcvt(value, ndigit, decpt, sign)
double	value;
int	ndigit, *decpt, *sign;
{
	return (cvt(value, ndigit, decpt, sign, 1));
}

static char buf[NDIG];

static char *
cvt(value, ndigit, decpt, sign, f_flag)
double value;
int	ndigit, *sign, f_flag;
register int	*decpt;
{
	register char *p = &buf[0], *p_last = &buf[ndigit];

	KILLNaN(value); /* raise exception on Not-a-Number (3b only) */
	if (*sign = (value < 0.0))
		value = -value;
	buf[0] = '\0';
	*decpt = 0;
	if (value != 0.0) { /* rescale to range [1.0, 10.0) */
		/* in binary for speed and to minimize error build-up */
		/* even for the IEEE standard with its high exponents,
		   it's probably better for speed to just loop on them */
		static struct s { double p10; int n; } s[] = {
			1e32,	32,
			1e16,	16,
			1e8,	8,
			1e4,	4,
			1e2,	2,
			1e1,	1,
		};
		register struct s *sp = s;

		++*decpt;
		if (value >= 2.0 * MAXPOWTWO) /* can't be precisely integral */
			do {
				for ( ; value >= sp->p10; *decpt += sp->n)
					value /= sp->p10;
			} while (sp++->n > 1);
		else if (value >= 10.0) { /* convert integer part separately */
			register double pow10 = 10.0, powtemp;

			while ((powtemp = 10.0 * pow10) <= value)
				pow10 = powtemp;
			for ( ; ; pow10 /= 10.0) {
				register int digit = value/pow10;
				*p++ = digit + '0';
				value -= digit * pow10;
				++*decpt;
				if (pow10 <= 10.0)
					break;
			}
		} else if (value < 1.0)
			do {
				for ( ; value * sp->p10 < 10.0; *decpt -= sp->n)
					value *= sp->p10;
			} while (sp++->n > 1);
	}
	if (f_flag)
		p_last += *decpt;
	if (p_last >= buf) {
		if (p_last > &buf[NDIG - 2])
			p_last = &buf[NDIG - 2];
		for ( ; ; ++p) {
			if (value == 0 || p >= &buf[NMAX])
				*p = '0';
			else {
				register int intx; /* intx in [0, 9] */
				*p = (intx = (int)value) + '0';
				value = 10.0 * (value - (double)intx);
			}
			if (p >= p_last) {
				p = p_last;
				break;
			}
		}
		if (*p >= '5') /* check rounding in last place + 1 */
			do {
				if (p == buf) { /* rollover from 99999... */
					buf[0] = '1'; /* later digits are 0 */
					++*decpt;
					if (f_flag)
						++p_last;
					break;
				}
				*p = '0';
			} while (++*--p > '9'); /* propagate carries left */
		*p_last = '\0';
	}
	return (buf);
}

# else /* this is for mpx */

/*
 *	ecvt converts to decimal
 *	ndigits specifies the number of digits
 *	decpt is set to the position of the decimal point
 *	sign is set to 0 for positive, 1 for negative
 *
 *	for fcvt, ndigits is number of fraction digits
 *
 *	for both ecvt and fcvt, the leading digit in the result
 *	string is nonzero if arg is nonzero
 */

char	*cvt();

#define	NDIG	80

char* ecvt(arg, ndigits, decpt, sign)
double arg;
int ndigits, *decpt, *sign;
{
	return(cvt(arg, ndigits, decpt, sign, 1));
}

char* fcvt(arg, ndigits, decpt, sign)
double arg;
int ndigits, *decpt, *sign;
{
	return(cvt(arg, ndigits, decpt, sign, 0));
}

/* Gould S.E.L. machine-dependent version */
/* written 820617 by 3423                 */

static char* cvt(arg, ndigits, decpt, sign, eflag)
double arg;
int ndigits, *decpt, *sign, eflag;
{
 union {
        long l[2];
        double d ;
       } udl;
 int start, shift, radint, i, j, k, decndx, flag, rem, nldzrs, ldzrflg, nines;
 int raddig[14];      /* digits in radix 16**6 */
 static char decimal[NDIG+2];

 if (ndigits < 0) ndigits = 0;
 else if (ndigits > NDIG) ndigits = NDIG;
 *sign = 0;
 if (arg < 0) {arg = -arg; *sign = 1;}
 udl.d = arg;
#ifdef gould
 i = udl.l[0] ? ( ((unsigned) udl.l[0] >> 24) - 64) : 0;
#else not gould
 i = udl.l[0] ? ( (udl.l[0] >> 24) - 64) : 0;
#endif
 j = (66 - i) % 6;
 i = (i + j)/6;

/* arg is represented as (16**6)**i * 16**(-j) * f where :
 * -10 <= i <= 11 , 0 <=j <= 5 , 16**(-1) <= f < 1
 * raddig is an array of digits to radix 16**6, filled with bits appropriately
 *  aligned from f
 * radint is number of radix digits in integral part (0 <= radint <= 11)
 * shift is number of bits to right-shift f for alignment
 * start is index of first significant radix digit in raddig; if radint is zero,
 *  implied radix point is at left of raddig[0] 24 bit value
 * the 56 bits from f occupy either three or four raddig words
*/

 start = (-i) > 0 ? -i : 0;
 radint = i > 0 ? i : 0;
 shift = 4 * j;
#ifdef gould
 raddig[start] = (unsigned) (udl.l[0] & 0xffffff) >> shift;
 raddig[start + 1] = ((unsigned) udl.l[0] & (0xfffff >> 20-shift)) << 24 - shift
                    | (unsigned) udl.l[1] >> shift + 8;
 raddig[start + 2] = (((unsigned) udl.l[1] & (0xffffff0 >> 20-shift)) << 20-shift) >> 4;
 raddig[start + 3] = (((unsigned) udl.l[1] & (0xf >> 20-shift)) << 20 - shift) << 20;
#else not gould
 raddig[start] = (udl.l[0] & 0xffffff) >> shift;
 raddig[start + 1] = ((udl.l[0] & 0xfffff) >> 20-shift) << 24 - shift
                    | udl.l[1] >> shift + 8;
 raddig[start + 2] = ((udl.l[1] & 0xffffff0 >> 20-shift) << 20-shift) >> 4;
 raddig[start + 3] = ((udl.l[1] & 0xf >> 20 - shift) << 20 - shift) << 20;
#endif

/* fill any leading zeros of fraction */
 for (i = 0; i < start; i++) raddig[i] = 0;

/* fill any trailing zeros of integer part */
 for (i = start + 4; i < radint; i++) raddig[i] = 0;
 decndx = 0;
 nines = 0;	/* nines counts length of any trailing string of 9's */
 k = NDIG;	/* index to next-to-last char in decimal */
 decimal[NDIG+1] = '0';	/* initialize for possible rounding attempt */

/* convert any integer part to decimal digits */
 if (radint)
  { /* develop integer part from right to left */
    flag = 1;
    while (flag)
     { flag = 0;
       rem = 0;
       for (i = 0; i < radint; i++ )
        { j = raddig[i] + (rem << 24);
          rem = j % 10;
          flag |= (j = j / 10);
          raddig[i] = j;
        }
       decimal[k--] = rem + '0';
     }
    *decpt = NDIG - k;

    while ((ndigits | !eflag) && k < NDIG)
     { if (eflag) ndigits--;
       decimal[decndx++] = (j = decimal[++k]);
       nines = ((j == '9') ? ++nines : 0);
     }
  }

/* now put out any fraction*/
 nldzrs = 0;
 ldzrflg = !radint; if (!((udl.l[0] & 0x00ffffff) | udl.l[1])) ldzrflg = 0;
 if (!eflag && ndigits + decndx > NDIG) ndigits = NDIG - decndx;
 while (ndigits)
  { rem = 0;
    for (i = start+3; i >= radint; i-- )
     { j = raddig[i] * 10 + rem;
       raddig[i] = j & 0xffffff;
#ifdef gould
       rem = (unsigned) j >> 24;
#else not gould
       rem = j >> 24;
#endif
     }
    if (ldzrflg && !rem) { nldzrs++; if (!eflag) ndigits--;}
    else
     { ndigits--;
       ldzrflg = 0;
       decimal[decndx++] = (j = rem +'0');
       nines = ((j == '9') ? ++nines : 0);
     }
  }
 if (decndx == 0) {decimal[decndx++] = '0'; nldzrs--;}
 decimal[decndx] = '\0';
 if (!radint) *decpt = -nldzrs;

/* round */
 if (((flag = !(eflag && decndx < *decpt)) && raddig[radint] > 0x7fffff)
      || (!flag && decimal[k+1] >= '5'))
  { if (!nines) decimal[decndx-1] += 1;
    else      /* propagate rounding over trailing string of 9's */
     { for (i = 0; i < nines; i++)
        { if (i == decndx - 1)      /* may need to prepend a 1 */
           { decimal[0] = '1'; *decpt += 1;
             if (eflag) break;      /* ecvt allows no more */
             decimal[decndx] = '0'; decimal[decndx+1] = '\0'; break;
            }
           decimal[decndx-i-1] = '0';
        }
       if (decndx > nines) decimal[decndx-nines-1] += 1;
     }
  }
 return (decimal);
}

#endif /* unix */
