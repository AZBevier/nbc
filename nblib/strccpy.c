/*~!strccpy.c*/
/* Name:  strccpy.c Part No.: _______-____r
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

#ident	"@(#)nbclib:strccpy.c	1.1"

/*
	strccpy(output, input)
	strccpy copys the input string to the output string compressing
	any C-like escape sequences to the real character.
	Esacpe sequences recognized are those defined in "The C Programming
	Language" pages 180-181.
*/
#include	"libgen.h"

char *
strccpy(pout, pin)
register char *pout;
register char *pin;
{
	register char c;
	register char *output;
	int count;
	int wd;

	output = pout;
	while (c = *pin++) {
		if (c == '\\')
			switch (c = *pin++) {
			case 'n':
				*pout++ = '\n';
				continue;
			case 't':
				*pout++ = '\t';
				continue;
			case 'b':
				*pout++ = '\b';
				continue;
			case 'r':
				*pout++ = '\r';
				continue;
			case 'f':
				*pout++ = '\f';
				continue;
			case 'v':
				*pout++ = '\v';
				continue;
			case '\\':
				*pout++ = '\\';
				continue;
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
				wd = c - '0';
				count = 0;
				while ((c = *pin++) >= '0' && c <= '7') {
					wd <<= 3;
					wd |= (c - '0');
					if (++count > 1) {   /* 3 digits max */
						pin++;
						break;
					}
				}
				*pout++ = wd;
				--pin;
				continue;
			default:
				*pout++ = c;
				continue;
		}
		*pout++ = c;
	}
	*pout = '\0';
	return (output);
}
