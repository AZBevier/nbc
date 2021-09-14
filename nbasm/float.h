/*~!float.h*/
/* Name:  float.h Part No.: _______-____r
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

#ident	"@(#)nbcc:float.h	1.1"

#ifndef FLOAT_H
#define FLOAT_H

/************************************************************************
*									*
*		float.h							*
*									*
*************************************************************************/

/* this module supplies a full set of routines to implement arithmetic
   on the compiler internal format for floating point numbers.  This
   form provides for a decimal exponent of two bytes (+-32768) and
   a mantissa of N bytes, which is in the form of an integer such that
   it is prime mod 10.  That is, trailing zeroes have been deleted.
   nf[0] is the least significant byte of the mantissa.

   Mathematically, if the exponent is ne and the fraction is nf. The
   value of the number is nf * 10**ne.

   There are two classes of routines:  those that operate on structures
   (denoted by the letter 'f') and those that work on arrays of characters
   (denoted by the letter 's').  Arguments to the latter are of the
   form ( (char *), int ), for the start and length respectively.

   There are a few routines that are hybrid, and utilize an immediate
   constant (denoted 'k'), hence:

	addff( f1,f2 )		adds the structure *f1 to *f2
	addfs( f1, sp, sl )	adds the byte string *sp to *f1
	addfk( f1, k )		adds k to *f1

   Predicates follow the same convention.
*/

#define NF	10		/* length of the fraction part	*/
#define FPN 	struct fstr

FPN	{			/* basic structure definition	*/
	short	ne;
	unsigned char	nf[NF];
};

#define isnegf(f)	((f)->nf[NF-1] & 0x80)
#define mulfk(f,rad,k)	mulsk( (f)->nf, NF, rad, k )
#define divfk(f,rad,k)	divsk( (f)->nf, NF, rad, k )

#endif /* FLOAT_H */
