/* test program for float.c	*/
/* convert ascii to encore or ieee floating point */
 
#include <stdio.h>
#include "float.h"
int ieee  = 1;
int debug = 6;
int digits = 0;
#ifndef MOVEUP
FPN ifpn;	/* internal floating point number */
FPN *myatof();
#endif
 
#define FLODEB
 
short errcnt, warncnt, v;
quit(x) {
exit(x);
}
 
FPN	f1,f2;
 
main(){
	register i,j,k;
	int rnum[2];
	unsigned char num[100];
 
	for(;;){
again:		printf("enter number: ");
#ifdef OLDWAY
		getnum( &f1 );
#else
		i = 0;
		while ((j = getchar()) != '\n')
			num[i++] = j;
		num[i] = '\0';
		myatof(num);
		f1 = ifpn;
#endif
#ifdef FLODEB
	printf("exp = %d mant = ",f1.ne);sdump(f1.nf,NF);
#endif
		printf("results integer value: %lx\n", ftoi(&f1, 1));
		printf("result: ");
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
		flconv(6, f2.ne, &f2.nf, rnum, 0);
#ifdef linux
		printf("rnum = %08x%08x\n", rnum[1], rnum[0]);
#else
		printf("rnum = %08x%08x\n", rnum[0], rnum[1]);
#endif
	}
}
 
putman( f1 ) register FPN *f1; {
 
	register		k;
 
	k = divsk( f1->nf, NF, 10, 0 );
	if( isnzs( f1->nf, NF ) ) putman( f1 );
	if (digits++ < 15)
		putchar( k + '0' );
	else
		f1->ne++;
}
 
getnum( f ) register FPN *f; {
 
	register	i,tz;
	register	exp;
	register	sign;
 
	zerof( f );
	sign = exp = tz = 0;
 
	i = getchar();
 
	while( i == ' ' ) i = getchar();
	if( i == '-' ){ sign++; i = getchar(); }
	else if( i == '+' ) i = getchar();
	while( i == ' ' ) i = getchar();
	while( i >= '0' && i <= '9' ){
		tz = dodig( f, i-'0', tz );
		i = getchar();
	}
	if( i == '.' ){
		i = getchar();
		while( i >= '0' && i <= '9' ){
			tz = dodig( f, i-'0', tz );
			exp--;
			i = getchar();
		}
	}
	f->ne += tz + exp;
	while( i != '\n' ) i = getchar();
	if( sign ) negf( f );
}
 
#ifdef FLODEB
fdump( f ) register FPN *f; {
 
	printf("fdump: %5d  %2x %2x %2x %2x %2x %2x %2x %2x\n",
		f->ne,
		f->nf[7] & 0xff,
		f->nf[6] & 0xff,
		f->nf[5] & 0xff,
		f->nf[4] & 0xff,
		f->nf[3] & 0xff,
		f->nf[2] & 0xff,
		f->nf[1] & 0xff,
		f->nf[0] & 0xff );
}
#endif
 
#ifdef MYATOF
 
#include "float.h"
 
/* floating point service */
static short	fexp;			/* floating exponent		*/
static short	fr[NF];			/* floating fraction		*/
static long	fvhigh,fvlow;		/* floating final form		*/
static short	binexp;
 
/*	floating point  conversions	*/
 
#ifdef JUNK
flconv(typ, fe, f, rnum, ieee)
int typ;
short fe;
unsigned char *f;
int *rnum;
int ieee;
{
	register int i,j;
	printf("flconv: typ[%x] exp[%x] frac[",typ,fe);
	for(i=0; i<NF; i++) {
		printf("%x ",f[i]&0xff);
	}
	printf("]\n");
	xflconv(typ, fe, f, rnum, ieee);
	printf("flconv returns %lx %lx\n",rnum[0],rnum[1]);
}
 
xflconv(typ, fe, f, rnum, ieee)
#else
flconv(typ, fe, f, rnum, ieee)
#endif
int typ;
short fe;
unsigned char *f;
int *rnum;
int ieee;
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
	iftodbl(ieee);
	if (ieee) {
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
		fcvtf(rnum, ieee);
		return;
	}
#ifdef linux
	/* swap for linux */
	i = rnum[1];
	rnum[1] = rnum[0];
	rnum[0] = i;
#endif
}
 
iftodbl(ieee)		/* internal format to 64 bit floating point */
int ieee;
{
	register int	i;
	int	tmpexp;
 
	if (ieee) {
		for( i=0; i<9; i++ )pfrsh();
		incf();		/* round it up */
		pfrsh();	/* and truncate bit */
	} else {
#ifdef ENCORE
		for( i=0; i<5; i++ )pfrsh();
#else
#ifdef TEST_JIM
		for( i=0; i<6; i++ )pfrsh();
		while ((binexp+63) & 3)pfrsh(), binexp++;
		incf();		/* round it up */
		pfrsh();	/* and truncate bit */
		binexp++;
#else
#ifndef TRYING
	printf("flconv: frac[");
	for(i=NF-1; i>=0; i--) {
		printf("%x ",fr[i]&0xff);
	}
	printf("]\n");
#endif
		for( i=0; i<6; i++ )pfrsh();
		while ((binexp+63) & 3)pfrsh(), binexp++;
		incf();		/* round it up */
		pfrsh();	/* and truncate bit */
		binexp++;
#endif
#endif
	}
#ifndef TRYING
	printf("flconv: frac[");
	for(i=NF-1; i>=0; i--) {
		printf("%x ",fr[i]&0xff);
	}
	printf("]\n");
#endif
	for( i=3; i>=0; i-- ) fvlow = (fvlow << 8) | fr[i];
	for( i=7; i>=4; i-- ) fvhigh = (fvhigh << 8) | fr[i];
	if (ieee) {
		fvhigh &= 0x000fffffL;		/* clear out 12 bits */
		fvhigh |= (long)((binexp + 1085) & 0x7ff) << 20;
	} else {
		fvhigh &= 0x00ffffffL;		/* clear out 8 bits */
#ifdef ENCORE
		fvhigh |= (long)((binexp + 126) & 0x7f) << 24;
#else
		tmpexp = ((62 + binexp) >> 2) + 64;
#ifdef JUNK
		if (tmpexp > 77) {
			/* number too big, use max */
			fvhigh = 0x7fffffff;
			fvlow = 0xffffffff;
		} else if (tmpexp < -77) {
			/* number too small, use zero */
			fvhigh = 0;
			fvlow = 0;
		} else
#endif
 			fvhigh |= (tmpexp & 0x7f) << 24;
#endif
	}
}
 
pnorm(){
	while( fr[NF-1] <= 63 ){ pflsh(); binexp--; }
	while( fr[NF-1] > 127 ){ pfrsh(); binexp++; }
}
 
pflsh()
{
	register int	i,j;
 
	j = 0;
	for( i=0; i<NF; i++ ){
		j |= fr[i] << 1;
		fr[i] = j & 0xff;
		j >>= 8;
	}
}
 
pfrsh8()
{
	register int	i,j;
 
	j = 0;
	for( i=0; i<NF-1; i++ )
		fr[i] = fr[i+1];
	fr[NF-1] = 0;
}
 
pfrsh()
{
	register int	i,j;
 
	j = 0;
	for( i=NF-1; i>= 0; i-- ){
		j |= fr[i];
		fr[i] = j >> 1;
		j = (j & 1) << 8;
	}
}
 
mul10()
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
 
div10()
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
 
incf()
{		/* increment */
	register int	i;
 
	for( i=0; i<NF; i++ ){
		fr[i]++;
		if( (fr[i] &= 0xff) ) return;
	}
}
 
fcvtf(rnum, ieee)
int *rnum;
int ieee;
{			/* convert to single */
	register int	i;
	long	sign;
 
	if (ieee) {
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
		rnum[1] = 0;		/* simply truncate	*/
	}
}
 
#ifdef NOTNOW
fcvtd(rnum, ieee)
int *rnum;
int ieee;
{			/* convert to double */
	register int	i;
	long	sign;
 
	if (ieee) {
		sign = rnum[0] & 0x80000000L;
		i = rnum[0];
		i &= 7;
		rnum[1] = (long)i << 29;
		rnum[0] -= 0x40000000L;	/* remove exponent bias	*/
		rnum[0] <<= 1;		/* exponent sign to sign position */
		rnum[0] >>= 4;		/* extend it */
		rnum[0] &= 0x7fffffffL;	/* and clear sign bit */
		rnum[0] += 0x40000000L;	/* restore exponent bias*/
		rnum[0] |= sign;	/* restore sign */
	} else {
		rnum[1] = 0;		/* simply guarantee zero */
	}
}
 
cvitof( p )reg NODE *p;{		/* convert to float		*/
 
	reg int	i;
	reg int	signl;
	long	sign;
 
	sign = 0;
	if( p->nd_fval == 0 ){
		p->nd_fvl2 = 0;
		goto pret;
	}
	if( p->nd_fval < 0 ){
		sign++;
		p->nd_fval = -p->nd_fval;
	}
	for( i=0; i<4; i++ ){
		fr[i] = p->nd_fval & 0xff;
		p->nd_fval >>= 8;
	}
	for( ; i<8; i++ ) fr[i] = 0;
	fexp = binexp = 0;
	pnorm();
	iftodbl(ieee);
	p->nd_fval = fvhigh;
	p->nd_fvl2 = fvlow;
pret:	p->nd_type = TYREAL|(8<<5);
	if( sign ) p->nd_fval |= 0x80000000L;
}
 
cvftoi( p ) reg NODE *p; {		/* float to int */
 
	reg int	i;
	reg int	sign;
 
	if( p->nd_fval == 0 ){
		p->nd_fvl2 = 0;
		p->nd_type = deflong;
		return;
	}
	if( p->nd_fval < 0 ) sign++;
#ifdef IEEE
	i = p->nd_fval >> 20;
	if( varlen( p->nd_type ) == 8 ){	/* from double */
		i &= 0x7ff;			/* exponent is 11 bits */
		i -= 1027;			/* remove bias */
		p->nd_fvl2 >>= 20;
		p->nd_fvl2 &= 0xfff;
		p->nd_fval = (p->nd_fval << 12) | p->nd_fvl2 | 0x80000000L;
		p->nd_fvl2 = 0;
	} else {
		i = (i >> 3) & 0xff;		/* exponent is 8 bits */
		i -= 127;			/* remove bias */
		p->nd_fval = (p->nd_fval << 23 ) | 0x80000000L;
	}
#else		/* use the UNIFORM format	*/
	if( sign ) fneg( p );
	i = p->nd_fval >> 24;
	i &= 0x7f;				/* get exponent	*/
	i -= 64;				/* remove bias	*/
	p->nd_fvl2 >>= 24;
	p->nd_fvl2 &= 0xff;
	p->nd_fval = (p->nd_fval << 8) | p->nd_fvl2;
	p->nd_fvl2 = 0;
#endif
	if( i < -1 ){				/* no significance at all */
		p->nd_fval = 0;
		i = 31;
	}
	while( i < 31 ){
		p->nd_fval >>= 1;
		p->nd_fval &= 0x7fffffffL;
		i++;
	}
	if( sign ) p->nd_fval = -p->nd_fval;
	p->nd_type = deflong;
}
 
fneg( p ) reg NODE *p; {
#ifdef IEEE
	p->nd_fval ^= 0x80000000L;
#else
	p->nd_fval = ~p->nd_fval;
	if( (p->nd_fvl2 = -p->nd_fvl2) == 0 ) p->nd_fval++;
#endif
}
#endif /* NOTNOW */
 
#ifdef JUNK
fdump(s)char *s;{
	register int	i;
	printf("fd(%s)fexp = %d binexp = %d ",s,fexp,binexp);
	printf(" %4x %4x [",fvhigh,fvlow);
	for( i=NF-1; i>= 0; i-- ) printf(" %2x",fr[i] );
	printf("]\n");
}
#endif
 
#endif /* MYATOF */
 
#ifdef MYATOF
 
#include <ctype.h>
#include "float.h"
 
/*  Note : this atof() generates an internal floating point representation
 *	   of a number.  If we are in IEEE mode, the number is translated
 *	   to IEEE format.  Otherwise it is translated to Encore format.
 */
 
#ifdef MOVEUP
FPN ifpn;	/* internal floating point number */
#endif
 
/* #define FLOATDEB */
 
#ifdef FLOATDEB
extern int sdump();
unsigned char ss[100];
#else
unsigned char ss[100];
#endif
 
FPN *
myatof(s)
register  unsigned char  *s;
{
	register int i;
	int	tz;
	int	exp;
	int	sign;
	int	esign;
 
#ifdef FLOATDEB
	printf("myatof entry: %s\n", s);
	strcpy(ss,s);
	s = ss;
#else
	*ss='\0';
	strcpy(ss,s);
	s = ss;
#endif
	zerof( &ifpn );		/* clear destination number */
	esign = sign = exp = tz = 0;	/* and local variables */
 
	i = *s++;		/* get 1st char */
 
#ifdef FLOATDEB
	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i);
	printf("myatof start: exp %d man ", ifpn.ne);
	sdump(&ifpn.nf, NF);
#endif
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
#ifdef FLOATDEB
	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i);
	printf("myatof 1: exp %d man ", ifpn.ne);
	sdump(&ifpn.nf, NF);
#endif
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
#ifdef FLOATDEB
	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i);
	printf("myatof 2: exp %d man ", ifpn.ne);
	sdump(&ifpn.nf, NF);
#endif
	/* now see if exponent */
	exp = (tz + exp);
	tz = 0;			/* zero trailing zeros count */
	/* skip any more white spaces */
	while( i == ' ' || i == '\t') i = *s++;
#ifdef FLOATDEB
	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i);
	printf("myatof 3: exp %d man ", ifpn.ne);
	sdump(&ifpn.nf, NF);
#endif
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
#ifdef FLOATDEB
	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i);
	printf("myatof 4: exp %d man ", ifpn.ne);
	sdump(&ifpn.nf, NF);
#endif
	/* we are done with number */
	if (esign) tz = -tz;
	/* set the exponent */
	ifpn.ne += (tz + exp);
#ifdef FLOATDEB
	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i);
	printf("myatof 5: exp %d man ", ifpn.ne);
	sdump(&ifpn.nf, NF);
#endif
	/* if negative, negate the value */
	if( sign ) negf( &ifpn );
#ifdef FLOATDEB
	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i);
	printf("ret myatof: exp %d man ", ifpn.ne);
	sdump(&ifpn.nf, NF);
#endif
	return (&ifpn);
}
 
#endif /* MYATOF */
