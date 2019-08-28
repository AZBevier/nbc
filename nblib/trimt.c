/*~!trimt.c*/
/* Name:  trimt.c Part No.: _______-____r
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

#ident	"@(#)nbclib:trimt.c	1.1"

/*
	Trim trailing characters from a string.
	Returns pointer to last character in string not in tc.
*/

#include	<string.h>
#include	"libgen.h"

char *
trimt( string, tc )
char	*string;
char	*tc;	/* characters to trim */
{
	char	*p;

	p = string + strlen( string );
	while( p != string )
		if( !strchr( tc, *--p ) )
			return  ++p;
		
	return  p;
}
