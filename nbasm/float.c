/*~!float.c*/
/* Name:  float.c Part No.: _______-____r
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

#ident	"@(#)nbcc:float.c	1.1"

/************************************************************************
*									*
*		float.c							*
*									*
*************************************************************************/

#include <stdio.h>
#include "float.h"			/* READ THIS FILE		*/

static int addsk();
static int mulsk();
static void mul10fk();
static int negs();
static int absf();	/* makes positive and returns sign		*/
static int mvb();
static int cmpss();
static int subss();
static int addss();
#ifdef JUNK
static void norm(F);
static void frsh(F);
#endif /* JUNK */

#define reg	register
#define uns	unsigned

extern int isnzs();
extern int dodig();
extern void itod();
extern void uitod();
extern void sdec();
extern void sdump();
extern void zerof();
extern void negf();
extern void divff();
extern void mulff();
extern void subff();
extern void addff();

/*		Local Variables						*/
/*	Predicates come first						*/
/*	isnegf(f)	is a macro in float.h				*/

int isnzf( f ) reg FPN *f; { /* return nz if *f is not identically zero	*/
	reg		int i;
	reg char	*p;
	reg char	*pe;

	p = (char *)f->nf;
	pe = p+NF;
	for( p = (char *)f->nf, pe = p+NF; p < pe; p++ ) if( *p ) return 1;
	return 0;
}

int isnzs( s, n ) reg char *s;
int n;
{
	reg char	*se;

	for( se = s+n; s < se; s++ ) if( *s ) return 1;
	return 0;
}

/*	basic subroutines follow					*/
/*	addsk adds a integer to a mantissa string.  The only restriction
	on k, is that it must not be greater than the maximum positive
	value of an integer less 255.	The carry out is returned.	*/

static int
addsk( s, n, k ) reg char *s; reg uns k;
int n;
{
	reg char	*se;

	for( se = s+n; s<se && k; s++ ){
		k += *s & 0xff;
		*s = k;
		k >>= 8;
	}
	return k;
}

static int
mulsk( s, n, radix, k ) reg char *s; reg uns k;
int n, radix;
{

	reg char	*se;

	for( se = s+n; s<se; s++ ){
		k += (*s & 0xff) * radix;
		*s = k;
		k >>= 8;
	}
	return k;
}

static int
divsk( s, n, radix, k ) reg char *s; reg uns k;
int n, radix;
{

	reg char	*se;

	for( se = s+n-1; se>=s; se-- ){
		k = (k << 8) | (*se & 0xff);
		*se = k / radix;
		k %= radix;
	}
	return k;
}

/*
mulfk(f,radix,k) is defined as a macro
divfk(r,radix,k) is defined as a macro
*/

/* mul10fk multiplies the mantissa by 10 if it does not overflow.
   If it would overflow, no multiply is done, and the exponent is
   incremented.
*/
static void
mul10fk(f,k) reg FPN *f; reg uns k;
{
	if( (f->nf[NF-1] & 0xff) > 12 ){	/* already overflowed */
		f->ne++;
		return;
	}
	k = mulsk( f->nf, NF, 10, k );
	if( k || isnegf(f) ){		/* overflow, divide back out	*/
		k = divsk( f->nf, NF, 10, k );
		f->ne++;
		if( k > 5 ) addsk( f->nf, NF, 1 );		/* round */
	}
}

int dodig( f, k, tz ) reg FPN *f;
int k, tz;
{
	if( f->ne ){
		f->ne++;
		return 0;
	}
	if( k == 0 ) return tz+1;
	while( --tz >= 0 ){
		if( f->ne ){			/* already overflowed	*/
			f->ne += tz;
			k = 0;
			break;
		}
		mul10fk( f, 0 );
	}
	if( f->ne ){				/* round on overflow	*/
		if( k >= 5 ) addsk( f->nf, NF, 1 );
		while( (k = divsk(f->nf,NF,10,0)) == 0 ) f->ne++;
		mulsk( f->nf,NF,10,k);
		return 0;
	}
	mul10fk( f, k );
	return 0;
}

static int
negs( s, n ) reg char	*s;
int n;
{
	reg char	*se;

	for( se = s+n; s<se && *s==0; s++ );
	if( s < se ){
		*s = -*s;
		while( ++s < se ) *s ^= 0xff;
	}
}

void negf( f ) reg FPN *f; {
	negs( f->nf, NF );
}

static int
absf( f ) reg FPN *f; {	/* makes positive and returns sign		*/

	if( !isnegf(f) ) return 0;
	negs( f->nf, NF );
	return 1;
}

/*	too many compilers can't handle struct assigns, so we have
	this memcopy routine
*/

static int
mvb( tgt, src, n ) register char *tgt, *src;
int n;
{
	register char *bnd;

	for( bnd = tgt + n; tgt < bnd; )  *tgt++ = *src++;
}

/*		Major User Routines					*/
void addff( f1, f2 ) reg FPN *f1, *f2;
{
	reg		int k;
	FPN		f3;		/* f2 save cell			*/
	short		sgn1,		/* sign of f1			*/
			sgn2;		/* sign of f2			*/
	short		tz;

#ifdef BADCODE
	f3 = *f2;
#else
	mvb( &f3, f2, sizeof(FPN) );
#endif
	f2 = &f3;
	sgn1 = absf( f1 );
	sgn2 = absf( f2 );
	k = 0;
	while( f1->ne > f2->ne ){	/* align exponents, part 1	*/
		if( f1->nf[NF-1] < 13 ){
			mul10fk( f1, 0 );
			f1->ne--;
		} else {
			k = divfk( f2, 10, 0 );
			f2->ne++;
		}
	}
	while( f2->ne > f1->ne ){	/* align exponents, part 2	*/
		if( f2->nf[NF-1] < 13 ){
			mul10fk( f2, 0 );
			f2->ne--;
		} else {
			k = divfk( f1, 10, 0 );
			f1->ne++;
		}
	}
	tz = f1->ne;
	f1->ne = 0;
	if( sgn1 != sgn2 ) negs( f2->nf, NF );
	sgn2 = (f1->nf[NF-1] ^ f2->nf[NF-1]) & 0x80;
	if( k >= 5 ) k = 1;
	k = addss( f1->nf, NF, f2->nf, NF, k );
	if( !isnzf(f1) ) return;			/* result zero	*/
	if( sgn2 == 0 && (f1->nf[NF-1] ^ f2->nf[NF-1]) & 0x80 ){ /* overflow*/
		if( k ) negs( f1->nf, NF );
		divfk( f1, 10, 0);
		tz++;
		if( k ) negs( f1->nf, NF );
	}
	sgn1 ^= absf(f1);				/* now normalize */
	while( (k = divfk(f1,10,0)) == 0 ) tz++;
	mul10fk( f1, k );				/* restore	 */
	f1->ne += tz;
	if( sgn1 ) negs( f1->nf, NF );
}

void subff( f1, f2 ) reg FPN *f1, *f2; {
	FPN	f3;

#ifdef BADCODE
	f3 = *f2;
#else
	mvb( &f3, f2, sizeof(FPN) );
#endif
	negs( f3.nf, NF );
	addff( f1, &f3 );
}

void mulff( f1, f2 ) FPN *f1, *f2; {
	reg		int i,j;
	reg 	int k;
	reg char	*s;
	reg char	*se;
	char		sb[NF+NF];	/* intermediate multiply buffer	*/
	short		sgn1,		/* sign of f1			*/
			sgn2,		/* sign of f2			*/
			l,
			e;
	FPN		f3;

	if( !isnzf(f1) || !isnzf(f2) ) goto rz;	/* one operand is zero	*/
#ifdef BADCODE
	f3 = *f2;
#else
	mvb( &f3, f2, sizeof(FPN) );
#endif
	f2 = &f3;
	sgn1 = absf( f1 );
	sgn2 = absf( f2 );
#ifdef FLODEB1
	dprt("mulff	");sdump(f1->nf,NF);dprt("	");sdump(f1->nf,NF);
#endif
	for( i=0; i<NF+NF; i++ ) sb[i] = 0;	/* clear buffer		*/

	/* now form the double length product				*/

	for( i=0; i<NF; i++ ){
		k = 0;
		s = sb+i;
		l = NF+NF-i;
		for( j=0; j<NF; j++ ){
			k += (f1->nf[i] & 0xff) * (f2->nf[j] & 0xff);
			addsk( s, l, k & 0xff );
			s++;
			l--;
			k = (k>>8) & 0xff;
		}
	}

	/* now reduce it to normal form					*/
#ifdef FLODEB1
	dprt("bef red: ");sdump(sb,NF+NF);
#endif
	e = 0;
	k = 0;
	while( isnzs( sb+NF,NF ) || sb[NF-1] & 0x80 ){	/* make high part 0 */
		e++;
		k = divsk( sb, NF+NF, 10, 0 );
	}
#ifdef FLODEB1
/*DEB*/dprt("red: k = %d ",k);sdump(sb,NF+NF);
#endif
	if( k >= 5 ) addsk( sb, NF, 1 );	/* rounding step	*/
	if( sb[NF-1] & 0x80 ){			/* still overflow	*/
		e++;
		divsk( sb, NF+NF, 10, 0 );
	}
	f1->ne += f2->ne + e;
	mvb( f1->nf,sb,NF);			/* copy in mantissa	*/
	if( !isnzf( f1 ) ) goto rz;		/* check for zero	*/
	while( (k = divsk( f1->nf, NF, 10, 0 )) == 0 ) f1->ne++;
	mulsk( f1->nf, NF, 10, k );
	if( sgn1 ^ sgn2 ) negs( f1->nf, NF );
	return;

rz:	zerof( f1 );
}

void zerof( f ) reg FPN *f; {
	reg char	*s, *se;

	f->ne = 0;
	for( s=(char *)f->nf, se = s+NF; s<se; s++ ) *s = 0;
}

#ifdef FUTURE
/* compare two numbers */
/* return -1 if f1 < f2
   return  0 if f1 = f2
   return +1 if f1 > f2
 */
int cmpff( f1, f2 ) FPN *f1, *f2; {
	FPN	f3;
	FPN	f4;
#ifdef BADCODE
	f3 = *f1;
	f4 = *f2;
#else
	mvb( &f3, f1, sizeof(FPN) );
	mvb( &f4, f2, sizeof(FPN) );
#endif
	/* check if negative */
	if( isnegf(f1) ) {
		/* f1 is neg number */
		if( isnegf(f2) ) {
			/* f1 and f2 are negative */
			subff(&f3, &f4);	/* f3 has result */
			/* if f3 is negative f1 < f2 */
			if (isnegf(&f3)) return(-1);
			/* if f3 is positive, f1 > f2 */
			if(isnzf(&f3)) return(1);
			/* f3 = f4 */
			return(0);
		} else {
			/* f1 is negative & f2 is positive number */
			return(-1);	/* f1 < f2 */
		}
	} else {
		/* f1 is positive number */
		if( isnegf(f2) ) {
			/* f1 is positive & f2 is negative */
			return(1);	/* f1 > f2 */
		} else {
			/* f1 and f2 are positive number */
			subff(&f3, &f4);	/* f3 has result */
			/* if f3 is negative f1 < f2 */
			if (isnegf(&f3)) return(-1);
			/* if f3 is positive, f1 > f2 */
			if(isnzf(&f3)) return(1);
			/* f3 = f4 */
			return(0);
		}
	}
}
#endif /* FUTURE */

/* grit your teeth, here comes divide */
void divff( f1, f2 ) FPN *f1, *f2; {
	reg		int k;
	char		x1[ NF+1 ],		/* multiples of divisor	*/
			x2[ NF+1 ],
			x4[ NF+1 ],
			x8[ NF+1 ],
			di[ NF+1 ];		/* dividend hold cell	*/
	short		sgn1,
			sgn2;
	FPN		f3;

#ifdef FLODEB1
/*DEB*/dprt("f1: dividend ",k);sdump(f1->nf,NF);
/*DEB*/dprt("f2: divisor  ",k);sdump(f2->nf,NF);
#endif
	if( !isnzf( f1 ) ||			/* dividend is zero	*/
	    !isnzf( f2 ) ) return;		/* divisor is zero	*/
#ifdef BADCODE
	f3 = *f2;
#else
	mvb( &f3, f2, sizeof(FPN) );
#endif
	f2 = &f3;
	sgn1 = absf( f1 );
	sgn2 = absf( f2 );
	
	k = f1->ne - f2->ne;
	mvb( di, f1->nf, NF );
	di[NF] = 0;
	zerof( f1 );
	mvb( x1, f2->nf, NF );
	x1[NF] = 0;
	f1->ne = k+1;
	while( cmpss( di, NF+1, x1, NF+1 ) > 0 ){
		mulsk( x1, NF+1, 10, 0);
		f1->ne++;
	}
	mvb( x2, x1, NF+1 );
	addss( x2, NF+1, x1, NF+1, 0 );		/* form 2 * divisor	*/
	mvb( x4, x2, NF+1 );
	addss( x4, NF+1, x2, NF+1, 0 );		/* form 4 * divisor	*/
	mvb( x8, x4, NF+1 );
	addss( x8, NF+1, x4, NF+1, 0 );		/* form 8 * divisor	*/

	while( isnzs( di, NF+1 ) && f1->nf[NF-1] <= 12 ){
		k = 0;
		if( cmpss(di,NF+1,x8,NF+1) >= 0 ){
			k += 8;
#ifndef NOWORK
			subss(di,NF+1,x8,NF+1,0);
#else
			negs(x8,NF+1);
			addss(di,NF+1,x8,NF+1,0);
			negs(x8,NF+1);
#endif
		}
		if( cmpss(di,NF+1,x4,NF+1) >= 0 ){
			k += 4;
#ifndef NOWORK
			subss(di,NF+1,x4,NF+1,0);
#else
			negs(x4,NF+1);
			addss(di,NF+1,x4,NF+1,0);
			negs(x4,NF+1);
#endif
		}
		if( cmpss(di,NF+1,x2,NF+1) >= 0 ){
			k += 2;
#ifndef NOWORK
			subss(di,NF+1,x2,NF+1,0);
#else
			negs(x2,NF+1);
			addss(di,NF+1,x2,NF+1,0);
			negs(x2,NF+1);
#endif
		}
		if( cmpss(di,NF+1,x1,NF+1) >= 0 ){
			k += 1;
#ifndef NOWORK
			subss(di,NF+1,x1,NF+1,0);
#else
			negs(x1,NF+1);
			addss(di,NF+1,x1,NF+1,0);
			negs(x1,NF+1);
#endif
		}
		mul10fk( f1, k );
		f1->ne--;
		mulsk( di, NF+1, 10, 0 );
	}
	if( sgn1 ^ sgn2 ) negf( f1 );
}

static int
cmpss( s1, n1, s2, n2 ) reg char *s1, *s2;
int n1, n2;
{
	reg char	*se1, *se2;
	reg		int i;

	se1 = s1 + n1;
	se2 = s2 + n2;
	while( n1 > n2 ) if( n1--,*--se1 ) return 1;
	while( n2 > n1 ) if( n2--,*--se2 ) return -1;
	while( se1 > s1 )
		if( (i = (*--se1 & 0xff) - (*--se2 & 0xff)) != 0 ) return i;
	return 0;
}

static int
subss( s1, n1, s2, n2, k ) reg char *s1, *s2; reg /*uns*/ int k;
int n1, n2;
{
	reg char	*se1, *se2;

	if( n2 > n1 ) n2 = n1;
	se1 = s1 + n1;
	se2 = s2 + n2;
	while( s2 < se2 ){
		k += (*s1 & 0xff) - (*s2++ & 0xff);
		*s1++ = k;
		k >>= 8;
	}
	while( s1 < se1 ){
		if( k == 0 ) return 0;
		k += (*s1 & 0xff);
		*s1++ = k;
		k >>= 8;
	}
	return k;
}

static int
addss( s1, n1, s2, n2, k ) reg char *s1, *s2; reg /*uns*/ int k;
int n1, n2;
{
	reg char	*se1, *se2;

	if( n2 > n1 ) n2 = n1;
	se1 = s1 + n1;
	se2 = s2 + n2;
	while( s2 < se2 ){
		k += (*s1 & 0xff) + (*s2++ & 0xff);
		*s1++ = k;
		k >>= 8;
	}
	while( s1 < se1 ){
		if( k == 0 ) return 0;
		k += (*s1 & 0xff);
		*s1++ = k;
		k >>= 8;
	}
	return k;
}

/*	now a couple of conversions	*/
long
ftoi(f,rnd) reg FPN *f;
int rnd;
{
	FPN	f1;
	reg	int i;
	reg	int j;
	short	sign;
	long	v;

	mvb( &f1, f, sizeof(FPN) );
	sign = absf( &f1 );
	i = 0;
	j = f1.ne;
	while( j > 0 ) mulsk( f1.nf, NF, 10, 0 ), j--;
	while( j < 0 ) i = divsk( f1.nf, NF, 10, 0 ), j++;
	if( rnd && i >= 5 ) addsk( f1.nf, NF, 1 );
	for( i=3; i>=0; i-- ) v <<= 8, v |= f1.nf[i] & 0xff;
	if( sign ) v = -v;
	return v;
}

#ifndef FLODEB
/*DEB*/
static char psb[32];

void sdump(s,n) reg char *s; reg int n;
{
	mvb( psb, s, n );
	sdec( psb,n );
	putchar( '\n' );
}

void sdec( s, n )
int s, n;
{
	reg int i;

	i = divsk( s, n, 10, 0 );
	if( isnzs( s, n ) ) sdec( s, n );
	putchar( i+'0' );
}
#endif

#ifdef JUNK
static void
norm( F )
FPN *F;
{
	register int	i;
	register uns int j=0;

	if (!isnzf (F)) return;		/* zero, return */
	while( F->nf[NF-1] == 0 ){
		for( i=(NF-2); i>=0; i-- ) F->nf[i+1] = F->nf[i];
		F->nf[0] = 0;
		F->ne -= 8;
	}
	while( F->nf[NF-1] <= 63 ){
		for( i=0; i<NF; i++ )
		   j |= F->nf[i] << 1, F->nf[i] = j & 0xff, j >>= 8;
		F->ne--;
	}
	while( (unsigned char)F->nf[NF-1] > 127 ) frsh( F ), F->ne++;
}

static void
frsh( F )
FPN *F;
{
	register int	i;
	register uns int j=0;

	for( i=NF-1; i>= 0; i-- )
	    j |= F->nf[i], F->nf[i] = j >> 1, j = (j << 8) & 0x100;
}
#endif /* JUNK */

void itod( num, F )		/* convert int to double */
int num;
FPN *F;
{
	register int	i;
	int	sign;

	zerof( F );
	sign = 0;

	if(num == 0) return;
	if( num < 0 ) sign++, num = -num;
	for( i=0; i<4; i++ ) F->nf[i] = num & 0xff, num >>= 8;
	for( ; i<NF; i++ ) F->nf[i] = 0;
#ifdef JUNK
	norm( F );
#endif
	if( sign ) negf( F );
}

void uitod( num, F )		/* convert unsigned int to double */
unsigned int num;
FPN *F;
{
	register int	i;

	zerof( F );

	if(num == 0) return;
	for( i=0; i<4; i++ ) F->nf[i] = num & 0xff, num >>= 8;
	for( ; i<NF; i++ ) F->nf[i] = 0;
#ifdef JUNK
	norm( F );
#endif
}
