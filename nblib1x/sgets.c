/*~!sgets.c*/
/* Name:  sgets.c Part No.: _______-____r
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

#ident	"@(#)nbclib:sgets.c	1.1"

/*
	Provide machine independent transfer of shorts, ala sgetl(3X).
*/

/*
 * The intent here is to provide a means to make the value of
 * bytes in an io-buffer correspond to the value of a short
 * in the memory while doing the io a `short' at a time.
 * Files written and read in this way are machine-independent.
 *
 */

#include <values.h>

short
sgets(buffer)
register char *buffer;
{
	register short w = 0;
	register int i = BITSPERBYTE * sizeof(short);

	while ((i -= BITSPERBYTE) >= 0)
		w |= (short) ((unsigned char) *buffer++) << i;
	return  w;
}
