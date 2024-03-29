/*~!numd.c*/
/* Name:  numd.c Part No.: _______-____r
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

#ident	"@(#)nbclib:numd.c	1.1"

/*	
	true if string is numeric, with or without decimal point
*/

#include	<ctype.h>
#include	"libgen.h"


int
numd( string )
register char *string;
{
	register int	seen_a_digit = 0;

	if( !string  ||  !*string )
		return  0;	/* null pointer or null string */
	while( *string  &&  *string != '.' )
		if( isdigit( *(string++) ) )
			seen_a_digit = 1;
		else
			return  0;
	if( *string == '.' ) {	/* have found decimal */
		string++;	/* go to char. after decimal */
		while( *string )
			if( isdigit( *(string++) ) )
				seen_a_digit = 1;
			else
				return  0;
	}
	return  seen_a_digit;
}
