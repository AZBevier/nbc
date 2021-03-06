/*~!fgets.c*/
/* Name:  fgets.c Part No.: _______-____r
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

#ident	"@(#)nbclib:fgets.c	1.1"

/*
 * This version reads directly from the buffer rather than looping on getc.
 * Ptr args aren't checked for NULL because the program would be a
 * catastrophic mess anyway.  Better to abort than just to return NULL.
 */
#include <stdio.h>
#include "stdiom.h"

#define MIN(x, y)	(x < y ? x : y)

extern int _filbuf();
extern char *memccpy();

char *
fgets(ptr, size, iop)
char *ptr;
register int size;
register FILE *iop;
{
    char *p, *ptr0 = ptr;
    register int n;

    if ((size <= 0) || !(iop->_flag & (_IOREAD | _IORW)))
      return (NULL);
    for (size--; size > 0; size -= n) {
      if (iop->_cnt <= 0) {	/* empty buffer */
    	if (_filbuf(iop) == EOF) {
    	  if (ptr0 == ptr)
    	    return (NULL);
    	  break;		/* no more data */
    	}
    	iop->_ptr--;
    	iop->_cnt++;
      }
      n = MIN(size, iop->_cnt);
      if ((p = memccpy(ptr, (char *) iop->_ptr, '\n', n)) != NULL)
    	n = p - ptr;
      ptr += n;
      iop->_cnt -= n;
      iop->_ptr += n;
      _BUFSYNC(iop);
      if (p != NULL)
    	break;			/* found '\n' in buffer */
    }
    *ptr = '\0';
    return (ptr0);
}
