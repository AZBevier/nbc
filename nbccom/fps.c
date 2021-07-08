/*~!fps.c*/
/* Name:  fps.c Part No.: _______-____r
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

#ident	"@(#)nbclib:fps.c	1.0"

/* These routines convert between integer/float/double.
 * longs are considered ints.  Fix if longs become 64 bits.
 * Unsigned ints are zero extended before conversion
 */

/* cvtfi - convert float to int */
int cvtfi (fpn)
register float fpn;
{
    register int ret = 0;
    register int neg = 0;

    if (fpn == 0)
    	return (ret);
    if (fpn < 0) {
    	neg = 1;
    	fpn = -fpn;
    }
    /* r7 has fpn to convert, return in r6 (ret) */
    asm (" slld r6,8");		/* get exp */
    asm (" sui  r6,64");	/* take off excess notation */
    asm (" ble  min");		/* br if very small */
    asm (" sui  r6,8");		/* see if in range */
    asm (" bgt  max");		/* br if too big */
    asm (" trn  r6,r6");	/* back to pos for shift count */
    asm (" sll  r6,2");		/* make shift count */
    asm (" ormh r6,srli");	/* or in srl instr */
    asm (" exrr r6");		/* do the shift */
    asm (" tbr  r6,0");		/* see if overflow to neg */
    asm (" bs   max");		/* br if yes */
    asm (" trr  r7,r6");	/* into correct reg */
    asm (" bu   fret");		/* return */
    asm ("min   zr   r6");	/* return min of zero */
    asm (" bu   fret");		/* return */
    asm ("max   li   r6,-1");	/* get all ones */
    asm (" zbr  r6,0");		/* max pos value now */
    asm (" bu   fret");		/* return */
    asm ("srli  srl  r7,0");	/* dummy shift instr */
    asm (" nop");		/* force nop out of xecuion path */
    asm ("fret  equ  $");	/* return merge */
    if (neg)
    	return (-ret);		/* return it */
    return (ret);		/* return it */
}

/* cvtfui - convert float to unsigned int */
unsigned int cvtfui (fpn)
float fpn;
{
    return((unsigned)cvtfi(fpn));
}

double dnum;

/* cvtdl - convert double to int */
int cvtdl (fpn)
double fpn;
{
    register int ret = 0;
    register int dummy;		/* so neg will be in reg 5 */
    register int neg = 0;

    if (dnum == 0)
    	return (ret);
    if (dnum < 0) {
    	neg = 1;
    	dnum = -dnum;
    }
    asm (" ld   r6,_dnum");	/* get number to convert */
    asm (" trr  r6,r4");	/* hi order part to r4 */
    /* convert double to long, args in r4, r6 & r7 */
    asm (" srl  r4,24");	/* get just exponent in r4 */
    asm (" slld r6,8");		/* pure fraction */
    asm (" sui  r4,64");	/* remove excess 64 notation */
    asm (" ble  dzero");	/* too small, return zero */
    asm (" sui  r4,16");	/* see if in range */
    asm (" bgt  dmax");		/* too big, return max */
    asm (" trn  r4,r4");	/* make positive shift count */
    asm (" sll  r4,2");		/* r2 = 4 * (16 - exp) */
    asm (" zbr  r4,26");	/* see if shift count is >= 32 */
    asm (" bns  nos32");	/* no, do double reg shift */
    asm (" trr  r6,r7");	/* yes, do trr to shift by 32 bits */
    asm (" zr   r6");		/* clear the shifted reg */
    asm ("nos32 ormh r4,srldi"); /* generate shift instruction */
    asm (" exrr r4");		/* shift r6, r7 */
    asm (" tbr  r6,0");		/* did we go negative, overflow */
    asm (" bs   dmax");		/* yes, set to max */
    asm (" bu   dret");		/* get out */
    asm ("dzero zr   r6");	/* return zeros */
    asm (" zr   r7");		/*  */
    asm (" bu   dret");		/* get out */
    asm ("dmax  li   r6,-1");	/* too big, return max */
    asm (" trr  r6,r7");	/* value of all 1's */
    asm (" zbr  r6,0");		/* less the sign bit */
    /* if long is a 64 bit number, delete next instruction */
    asm (" zbr  r7,0");		/* less the sign bit */
    asm (" bu   dret");		/* get out */
    asm ("srldi srld r6,0");	/*  */
    asm (" nop");		/*  */
    asm ("dret  equ $");	/* return merge point */
    if (neg)
    	return (-ret);		/* return it */
    return (ret);		/* return it */
}

/* cvtdul - convert double to unsigned int */
unsigned int cvtdul (fpn)
double fpn;
{
    return((unsigned)cvtdl(fpn));
}

/* cvtif - convert int to float */
float cvtif (in)
register int in;
{
    register float sfpn = 0.0;
    register int neg = 0;

    if (in == 0)
    	return (sfpn);
    if (in < 0) {
    	neg = 1;
    	in = -in;
    }
    /* int in r7, float value in r6 on completion */
    asm (" trr  r7,r6");	/* parameter to correct reg */
    asm (" scz  r6,r2");	/* count leading zeros */
    asm (" srl  r6,1");		/* backup by 1 bit */
    asm (" sbr  r6,0");		/* set sign bit */
    asm (" tbr  r2,30");	/* was count mod 2? */
    asm (" bns  test1");	/* br if not */
    asm (" srl  r6,2");		/* yes, two more zeros */
    asm ("test1 tbr r2,31");	/* was count odd? */
    asm (" bns  test2");	/* br if not */
    asm (" srl  r6,1");		/* yes, one more bit */
    asm ("test2 srl r2,2");	/* normalize radix */
    asm (" sui  r2,72");	/* excess 64 notation */
    asm (" trn  r2,r2");	/* make positive */
    asm (" src  r2,8");		/* position in first byte */
    asm (" srl  r6,8");		/* make room for FP number */
    asm (" orr  r2,r6");	/* put exp & fraction together */
    if (neg)
    	return (-sfpn);		/* return it */
    return (sfpn);		/* return it */
}

/* cvtuif - convert unsigned int to float */
float cvtuif (in)
unsigned int in;
{
    return(cvtif((int)in));
}

/* cvtld - convert int to double */
/* this code will have to change for longs of 64 bits */
double cvtld (in)
register int in;
{
    register int dummy;		/* so neg will be in reg 5 */
    register int neg = 0;

    dnum = 0.0;
    if (in == 0)
    	return (dnum);
    if (in < 0) {
    	neg = 1;
    	in = -in;
    }
    asm (" zr   r6");		/* high order is zero */
    asm (" trr  r6,r4");	/* hi order part to r4 */
    /* int in r6 & r7, double value in r6 & r7 on completion */
    asm (" zr   r0");		/* for exponent */
    asm (" anmw r4,=x'ff000000'"); /* just get exponent */
    asm (" beq  lda");		/* br if space for exp */
    asm (" srld r6,8");		/* very large, make room for exp */
    asm (" li   r0,-2");	/* set initial exponent */
    asm ("lda   trr  r6,r4");	/* copy hi order part */
    asm (" anmw r4,=x'00f00000'"); /* see if already normalized */
    asm (" bne  ldd");		/* br if normalized */
    asm (" slld r6,4");		/* not yet, shift in next nibble */
    asm (" abr  r0,31");	/* add 1 more power of 16 to exp */
    asm (" bu   lda");		/* keep going until normalized */
    asm ("ldd   trn  r0,r0");	/* prep for excess 64 notation */
    asm (" adi  r0,x'4e'");	/* make excess 64 exponent */
    asm (" src  r0,8");		/* put in hi order byte */
    asm (" orr  r0,r6");	/* merge with fraction */
    asm (" std  r6,_dnum");	/* save return number */
    if (neg)
    	return (-dnum);		/* return it */
    return (dnum);		/* return it */
}

/* cvtuld - convert unsigned int to double */
/* this code will have to change for longs of 64 bits */
double cvtuld (in)
unsigned int in;
{
    register int dummy;		/* so neg will be in reg 5 */

    dnum = 0.0;
    if (in == 0)
    	return (dnum);
    asm (" zr   r6");		/* high order is zero */
    asm (" trr  r6,r4");	/* hi order part to r4 */
    /* int in r6 & r7, double value in r6 & r7 on completion */
    asm (" zr   r0");		/* for exponent */
    asm (" anmw r4,=x'ff000000'"); /* just get exponent */
    asm (" beq  lda1");		/* br if space for exp */
    asm (" srld r6,8");		/* very large, make room for exp */
    asm (" li   r0,-2");	/* set initial exponent */
    asm ("lda1   trr  r6,r4");	/* copy hi order part */
    asm (" anmw r4,=x'00f00000'"); /* see if already normalized */
    asm (" bne  ldd1");		/* br if normalized */
    asm (" slld r6,4");		/* not yet, shift in next nibble */
    asm (" abr  r0,31");	/* add 1 more power of 16 to exp */
    asm (" bu   lda");		/* keep going until normalized */
    asm ("ldd1   trn  r0,r0");	/* prep for excess 64 notation */
    asm (" adi  r0,x'4e'");	/* make excess 64 exponent */
    asm (" src  r0,8");		/* put in hi order byte */
    asm (" orr  r0,r6");	/* merge with fraction */
    asm (" std  r6,_dnum");	/* save return number */
    return (dnum);		/* return it */
}

