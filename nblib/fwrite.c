/*~!fwrite.c*/
/* Name:  fwrite.c Part No.: _______-____r
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

#ident	"@(#)nbclib:fwrite.c	1.1"

/*
 * This version writes directly to the buffer rather than looping on putc.
 * Ptr args aren't checked for NULL because the program would be a
 * catastrophic mess anyway.  Better to abort than just to return NULL.
 *
 * This version does buffered writes larger than BUFSIZ directly, when
 * the buffer is empty.
 */

#include <stdio.h>
#include "stdiom.h"
#include <sys/types.h>

#define MIN(x, y)       (x < y ? x : y)

extern char *memcpy();

int
fwrite(ptr, size, count, iop)
char *ptr;
int count;
int size;
register FILE *iop;
{
	register long nleft;
	register int n;
	register unsigned char *cptr, *bufend;
	int bufsiz = BUFSIZ;

	if (count <= 0 || _WRTCHK(iop))
	        return (0);

	bufend = _bufend(iop);
	nleft = (long) count * size;	/* may overflow */
	if (nleft < count || nleft < size)	/* overflow occured */
		return (0);


	/* if the file is unbuffered, or if the iop->ptr = iop->base, and there
	   is > BUFSZ chars to write, we can do a direct write */
	if (iop->_base >= iop->_ptr)  {	/*this covers the unbuffered case, too*/
		if (((iop->_flag & _IONBF) != 0) || (nleft >= bufsiz))  {
			if ((n=write(fileno(iop),ptr,nleft)) != nleft)
			    {
				iop->_flag |= _IOERR;
				n = (n >= 0) ? n : 0;
			}
			return n/size;
		}
	}
	/* Put characters in the buffer */
	/* note that the meaning of n when just starting this loop is
	   irrelevant.  It is defined in the loop */
	for (; ; ptr += n) {
	        while ((n = bufend - (cptr = iop->_ptr)) <= 0)  /* full buf */
	                if (_xflsbuf(iop) == EOF)
	                        return (count - (nleft + size - 1)/size);
	        n = MIN(nleft, n);
	        (void) memcpy((char *) cptr, ptr, n);
	        iop->_cnt -= n;
	        iop->_ptr += n;
	        _BUFSYNC(iop);
		/* done; flush if linebuffered with a newline */
	        if ((nleft -= n) == 0)  {
			if (iop->_flag & (_IOLBF | _IONBF)) {
	               		if ((iop->_flag & _IONBF) || (memchr(cptr,
					'\n',count * size) != NULL))  {
				     	(void) _xflsbuf(iop);
				}
			}
	                return (count);
	        }
	}
}
