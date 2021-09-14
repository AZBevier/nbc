/*~!strecpy.c*/
/* Name:  strecpy.c Part No.: _______-____r
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

#ident	"@(#)nbclib:strecpy.c	1.1"

/*
	strecpy(output, input, except)
	strccpy copys the input string to the output string expanding
	any non-graphic character with the C escape sequence.
	Esacpe sequences produced are those defined in "The C Programming
	Language" pages 180-181.
	Characters in the except string will not be expanded.
*/

#include	<ctype.h>
#include	<string.h>
#include	"libgen.h"


char *
strecpy( pout, pin, except )
register char	*pout;
register char	*pin;
char	*except;
{
	register unsigned	c;
	register char		*output;

	output = pout;
	while( c = *pin++ ) {
		if( !isprint( c )  &&  ( !except  ||  !strchr( except, c ) ) ) {
			*pout++ = '\\';
			switch( c ) {
			case '\n':
				*pout++ = 'n';
				continue;
			case '\t':
				*pout++ = 't';
				continue;
			case '\b':
				*pout++ = 'b';
				continue;
			case '\r':
				*pout++ = 'r';
				continue;
			case '\f':
				*pout++ = 'f';
				continue;
			case '\v':
				*pout++ = 'v';
				continue;
			case '\\':
				continue;
			default:
				sprintf( pout, "%.3o", c );
				pout += 3;
				continue;
			}
		}
		if( c == '\\' )
			*pout++ = '\\';
		*pout++ = c;
	}
	*pout = '\0';
	return  output;
}
