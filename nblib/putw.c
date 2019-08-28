/*~!putw.c*/
/* Name:  putw.c Part No.: _______-____r
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

#ident	"@(#)nbclib:putw.c	1.1"

/*
 * The intent here is to provide a means to make the order of
 * bytes in an io-stream correspond to the order of the bytes
 * in the memory while doing the io a `word' at a time.
 */

#include <stdio.h>

int
putw(w, stream)
int w;
register FILE *stream;
{
	register char *s = (char *)&w;
	register int i = sizeof(int);

	while (--i >= 0)
		(void) putc(*s++, stream);
	return (ferror(stream));
}
