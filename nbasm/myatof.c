/*~!myatof.c*/
/* Name:  myatof.c Part No.: _______-____r
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

#ident	"@(#)nblib:myatof.c	1.0"

#ifdef MYATOF

#include <ctype.h>
#include "float.h"
#include <string.h>
#include <stdio.h>

/*  Note : this atof() generates an internal floating point representation
 *	   of a number.  If we are in IEEE mode, the number is translated
 *	   to IEEE format.  Otherwise it is translated to Encore format.
 */

FPN ifpn;	/* internal floating point number */

/*#define FLOATDEB*/

#ifdef FLOATDEB
extern int sdump();
#endif
extern void zerof();
extern void negf();
extern int dodig();

FPN * myatof(s)
register  unsigned char  *s;
{
	register int i;
	int	tz;
	int	exp;
	int	sign;
	int	esign;
/*
    unsigned char ss[200];
*/

#ifdef FLOATDEB
	printf("myatof entry: %s\n", s);
    fflush(stdout);
#endif
/*
	*ss='\0';
	strcpy((char *)ss, (char *)s);
	s = ss;
*/
	zerof( &ifpn );		/* clear destination number */
	esign = sign = exp = tz = 0;	/* and local variables */
	i = *s++;		/* get 1st char */

#ifdef FLOATDEB
	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i);
	printf("myatof start: exp %d man ", ifpn.ne);
	sdump(&ifpn.nf, NF);
    fflush(stdout);
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
    fflush(stdout);
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
    fflush(stdout);
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
    fflush(stdout);
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
    fflush(stdout);
#endif
	/* we are done with number */
	if (esign) tz = -tz;
	/* set the exponent */
	ifpn.ne += (tz + exp);
#ifdef FLOATDEB
	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i);
	printf("myatof 5: exp %d man ", ifpn.ne);
	sdump(&ifpn.nf, NF);
    fflush(stdout);
#endif
	/* if negative, negate the value */
	if( sign ) negf( &ifpn );
#ifdef FLOATDEB
	printf("tz = %x, exp = %x, next c = %x\n", tz, exp, i);
	printf("ret myatof: exp %d man ", ifpn.ne);
	sdump(&ifpn.nf, NF);
    fflush(stdout);
#endif
	return (&ifpn);
}

#endif /* MYATOF */
