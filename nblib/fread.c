/*~!fread.c*/
/* Name:  fread.c Part No.: _______-____r
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

#ident	"@(#)nbclib:fread.c	1.1"

/*
 * This version reads directly from the buffer rather than looping on getc.
 * Ptr args aren't checked for NULL because the program would be a
 * catastrophic mess anyway.  Better to abort than just to return NULL.
 */

#include <stdio.h>
#include "stdiom.h"
#include <sys/types.h>

#define MIN(x, y)	(x < y ? x : y)

extern int _filbuf();
extern _bufsync();
extern char *memcpy();

int
fread(ptr, size, count, iop)
char *ptr;
int count;
int size;
register FILE *iop;
{
	register long nleft;
	register int n;

	if (count <= 0) return 0;
	nleft = (long) count * size; /* may overflow */
	if (nleft < count || nleft < size)	/* overflow occured */
		return (0);

	/* Put characters in the buffer */
	/* note that the meaning of n when just starting this loop is
	   irrelevant.  It is defined in the loop */
	for ( ; ; ) {
		if (iop->_cnt <= 0) { /* empty buffer */
			if (_filbuf(iop) == EOF)
				return (count - (nleft + size - 1)/size);
			iop->_ptr--;
			iop->_cnt++;
		}
		n = MIN(nleft, iop->_cnt);
		ptr = memcpy(ptr, (char *) iop->_ptr, n) + n;
		iop->_cnt -= n;
		iop->_ptr += n;
		_BUFSYNC(iop);
		if ((nleft -= n) <= 0)
			return (count);
#ifdef mpx_1_line_reads
		return (count - (nleft + size - 1)/size);
#endif
	}
}
