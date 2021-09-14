/*~!dirname.c*/
/* Name:  dirname.c Part No.: _______-____r
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

#ident	"@(#)nbclib:dirname.c	1.0"

/*
	Return pointer to the last element of a pathname.
*/

#include	<string.h>
#include	"libgen.h"


char *
dirname( s )
char	*s;
{
	register char	*p;

	if( !s  ||  !*s )			/* zero or empty argument */
		return  ".";

	p = s + strlen( s );
	while( p != s  &&  *--p == '/' )	/* trim trailing /s */
		;
	
	if (*p == ')')p++;		/* put back ptr to ) if there */
	while( p != s )
		if( *--p == '/' ) {	/* trim / for unix path */
			*p = '\0';
			return  s;
		}
		else
		if( *--p == ')' ) {	/* leave ) for mpx path */
			p[1] = '\0';
			return  s;
		}
	return  ".";
}
