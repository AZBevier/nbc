/*~!atofn.c*/
/* Name:  atofn.c Part No.: _______-____r
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
 
#ident	"@(#)nbcc:atofn.c	1.0"
 
/* #define LOOK */
 
/* convert ascii to encore or ieee floating point */
/* for now, just do encore */
 
#include <stdio.h>
#include "float.h"
static int ieee = 0;		/* generate encore FPN */
FPN ifpn;	/* internal floating point number */
FPN *atofi();
static int pnorm();
static int pflsh();
static int pfrsh8();
static int pfrsh();
static int mul10();
static int div10();
static int incf();
 
union {
	double	d;
	int	n[2];
} d;
 
#ifdef LOOK
static FPN f1, f2;
static int digits = 0;
 
static putman( fx ) register FPN *fx; {
	register	k;
 
	k = divsk( fx->nf, NF, 10, 0 );
	if( isnzs( fx->nf, NF ) ) putman( fx );
	if (digits++ < 15)
		putchar( k + '0' );
	else
		fx->ne++;
}
#endif
 
/* enter with a null terminated string */
/* return a double value */
 
double atofn(num)
unsigned char *num;
{
	atofi(num);
#ifdef LOOK
	f1 = ifpn;
	f2 = f1;
	if( isnegf( &f1 ) ){
		putchar( '-' );
		negf( &f1 );
	}
	digits = 0;
	putman( &f1 );
	putchar( '.' );
	putchar( 'e' );
	if( f1.ne >= 0 ) putchar( '+' );
	printf("%d\n",f1.ne);
#endif
	flconv(6, ifpn.ne, ifpn.nf, d.n, ieee);
#ifdef LOOK
#ifdef linux
	printf("rnum = %08x%08x\n", d.n[1], d.n[0]);
#else
	printf("rnum = %08x%08x\n", d.n[0], d.n[1]);
#endif
#endif
	return (d.d);
}
 
/* floating point service */
static short	fexp;			/* floating exponent */
static short	fr[NF];			/* floating fraction */
static long	fvhigh,fvlow;		/* floating final form */
static short	binexp;			/* binary exponent */
 
/* floating point conversions */
 
flconv(typ, fe, f, rnum, Ieee)
int typ;
short fe;
unsigned char *f;
int *rnum;
int Ieee;
{
	/* pack up a floating point number */
	register int	i,j;
	register int	sign;
 
	binexp = 0;
 
	for( i=0; i<NF; i++ ) fr[i] = f[i] & 0xff;
	fexp = fe;
	rnum[0] = rnum[1] = 0;
	fvhigh = fvlow = 0;
	sign = 0;
	if( fr[NF-1] & 0x80 ){
		sign = j = 1;
		for( i=0; i<NF; i++ ){
			j += ~fr[i] & 0xff;
			fr[i] = j & 0xff;
			j >>= 8;
		}
	}
	for( i=0; i<NF; i++ ) if( fr[i] ) break;
	if( i == NF ) return;			/* true zero */
	pnorm();
	j = 0;
	while( fexp < 0 ) {
		 j = div10();
		 fexp++;
		 pnorm();
	}			 /* reduce dec exp */
	if( j >= 5 ) {
		 incf();
		 pnorm();
	}
	while( fexp > 0 ) {
		j = mul10();
		fexp--;
		if ( j ) pfrsh8(), fr[NF-1] = j, binexp += 8;
		pnorm();
	}
	iftodbl(Ieee);
	if (Ieee) {
		if( sign ) fvhigh |= 0x80000000L;
	} else {
		if( sign ){
			fvhigh = ~fvhigh;
			fvlow = -fvlow;
			if( fvlow == 0 ) fvhigh++;
		}
	}
	rnum[0] = fvhigh;
	rnum[1] = fvlow;
	if (typ == 5) {			/* if float, truncate */
		fcvtf(rnum, Ieee);
		return;
	}
#ifdef linux
	/* swap for linux */
	i = rnum[1];
	rnum[1] = rnum[0];
	rnum[0] = i;
#endif
}
 
iftodbl(IEee)		/* internal format to 64 bit floating point */
int IEee;
{
	register int	i;
	int	tmpexp;
 
	if (IEee) {
		for( i=0; i<9; i++ )pfrsh();
		incf();		/* round it up */
		pfrsh();	/* and truncate bit */
	} else {
		for( i=0; i<6; i++ )pfrsh();
		while ((binexp+63) & 3)pfrsh(), binexp++;
		incf();		/* round it up */
		pfrsh();	/* and truncate bit */
		binexp++;
	}
	for( i=3; i>=0; i-- ) fvlow = (fvlow << 8) | fr[i];
	for( i=7; i>=4; i-- ) fvhigh = (fvhigh << 8) | fr[i];
	if (IEee) {
		fvhigh &= 0x000fffffL;		/* clear out 12 bits */
		fvhigh |= (long)((binexp + 1085) & 0x7ff) << 20;
	} else {
		fvhigh &= 0x00ffffffL;		/* clear out 8 bits */
		tmpexp = ((62 + binexp) >> 2) + 64;
 		fvhigh |= (tmpexp & 0x7f) << 24;
	}
}
 
static int pnorm(){
	while( fr[NF-1] <= 63 ){ pflsh(); binexp--; }
	while( fr[NF-1] > 127 ){ pfrsh(); binexp++; }
}
 
static int pflsh()
{
	register int	i,j;
 
	j = 0;
	for( i=0; i<NF; i++ ){
		j |= fr[i] << 1;
		fr[i] = j & 0xff;
		j >>= 8;
	}
}
 
static int pfrsh8()
{
	register int	i,j;
 
	j = 0;
	for( i=0; i<NF-1; i++ )
		fr[i] = fr[i+1];
	fr[NF-1] = 0;
}
 
static int pfrsh()
{
	register int	i,j;
 
	j = 0;
	for( i=NF-1; i>= 0; i-- ){
		j |= fr[i];
		fr[i] = j >> 1;
		j = (j & 1) << 8;
	}
}
 
static int mul10()
{
	register int	i,j;
 
	j = 0;
	for( i=0; i<NF; i++ ){
		j += fr[i] * 10; 
		fr[i] = j & 0xff;
		j >>= 8;
	}
	return (j);
}
 
static int div10()
{
	register int	i,j;
 
	j = 0;
	for( i=NF-1; i>=0; i-- ){
		j <<= 8;
		j |= fr[i];
		fr[i] = j/10;
		j %= 10;
	}
	return j;
}
 
static int incf()
{		/* increment */
	register int	i;
 
	for( i=0; i<NF; i++ ){
		fr[i]++;
		if( (fr[i] &= 0xff) ) return;
	}
}
 
fcvtf(rnum, IEEE)
int *rnum;
int IEEE;
{			/* convert to single */
	register int	i;
	long	sign;
 
	if (IEEE) {
		sign = rnum[0] & 0x80000000L;	/* save sign */
		i = (unsigned int)rnum[1] >> 29;	/* get three bits */
		i &= 7;
		rnum[0] -= 0x40000000L;	/* remove exponent bias	*/
		rnum[0] <<= 3;		/* make room for three bits */
		rnum[0] += i;		/* put in bottom three bits */
		rnum[1] = 0;
		rnum[0] += 0x40000000L;	/* restore exponent bias */
		rnum[0] &= 0x7fffffffL;	/* turn off sign	 */
		rnum[0] |= sign;	/* restore sign */
	} else {
		rnum[0] &= 0xffffff00;	/* simply truncate	*/
		rnum[1] = 0;		/* simply truncate	*/
	}
}
 
/*  Note : this atof() generates an internal floating point representation
 *         of a floating point number.
 */
 
FPN * atofi(s)
register  unsigned char  *s;
{
	register int i;
	int	tz;
	int	exp;
	int	sign;
	int	esign;
 
	zerof( &ifpn );		/* clear destination number */
	esign = sign = exp = tz = 0;	/* and local variables */
 
	i = *s++;		/* get 1st char */
 
	/* skip any leading white spaces */
	while( i == ' ' || i == '\t') i = *s++;
	/* see if a sign given */
	if( i == '-' ) {
		sign++;
		i = *s++;
	} else if( i == '+' )
		i = *s++;
	/* skip any more white spaces */
	while( i == ' ' || i == '\t') i = *s++;
	/* skip any leading zero's */
	while( i == '0') i = *s++;
	/* now process any number digits */
	while( i >= '0' && i <= '9' ){
		tz = dodig( &ifpn, i-'0', tz );
		i = *s++;
	}
	/* now process a fraction, if present */
	if( i == '.' ){
		/* do the fraction */
		i = *s++;
		while( i >= '0' && i <= '9' ){
			tz = dodig( &ifpn, i-'0', tz );
			exp--;
			i = *s++;
		}
	}
	/* now see if exponent */
	exp = (tz + exp);
	tz = 0;			/* zero trailing zeros count */
	/* skip any more white spaces */
	while( i == ' ' || i == '\t') i = *s++;
	/* now process an exponent, if present */
	if( i == 'e' || i == 'E' ){
		/* do the exponent */
		i = *s++;
		/* see if a sign given */
		if( i == '-' ) {
			esign++;
			i = *s++;
		} else if( i == '+' )
			i = *s++;
		/* skip any leading zero's */
		while( i == '0') i = *s++;
		while( i >= '0' && i <= '9' ){
			tz = tz * 10 + i-'0';
			i = *s++;
		}
	}
	/* we are done with number */
	if (esign) tz = -tz;
	/* set the exponent */
	ifpn.ne += (tz + exp);
	/* if negative, negate the value */
	if( sign ) negf( &ifpn );
	return (&ifpn);
}
 
