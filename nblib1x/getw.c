/*~!getw.c*/
/* Name:  getw.c Part No.: _______-____r
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

#ident	"@(#)nbclib:getw.c	1.1"

/*
 * This version reads directly from the buffer rather than looping on getc.
 * Ptr args aren't checked for NULL because the program would be a
 * catastrophic mess anyway.  Better to abort than just to return NULL.
 */

#include <stdio.h>
#include "stdiom.h"

extern int _filbuf();
extern _bufsync();
extern char *memccpy();

char *
gets(ptr)
char *ptr;
{
	char *p, *ptr0 = ptr;
	register int n;

	for ( ; ; ) {
		if (stdin->_cnt <= 0) { /* empty buffer */
			if (_filbuf(stdin) == EOF) {
				if (ptr0 == ptr)
					return (NULL);
				break; /* no more data */
			}
			stdin->_ptr--;
			stdin->_cnt++;
		}
		n = stdin->_cnt;
		if ((p = memccpy(ptr, (char *) stdin->_ptr, '\n', n)) != NULL)
			n = p - ptr;
		ptr += n;
		stdin->_cnt -= n;
		stdin->_ptr += n;
		_BUFSYNC(stdin);
		if (p != NULL) { /* found '\n' in buffer */
			ptr--; /* step back over '\n' */
			break;
		}
	}
	*ptr = '\0';
	return (ptr0);
}
