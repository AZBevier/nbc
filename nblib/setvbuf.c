/*~!setvbuf.c*/
/* Name:  setvbuf.c Part No.: _______-____r
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

#ident	"@(#)nbclib:setvbuf.c	1.1"

#include <stdio.h>

extern void free();
extern int isatty();

int
setvbuf(iop, buf, type, size)
register FILE *iop;
register int type;
register char	*buf;
register int size;
{
	char *malloc();

	if ( size < 0 )
		return -1;
	if(iop->_base != NULL && iop->_flag & _IOMYBUF)
		free((char*)iop->_base);
	iop->_flag &= ~(_IOMYBUF | _IONBF | _IOLBF);
	switch (type)  {
	    /*note that the flags are the same as the possible values for type*/
	    case _IONBF:
		/* file is unbuffered */
		iop->_flag |= _IONBF;
		_bufend(iop) = iop->_base = NULL;
		break;
	    case _IOLBF:
	    case _IOFBF:
		/* buffer file */
		iop->_flag |= type;
		/*
		* need eight characters beyond bufend for stdio slop
		*/
		if (size <= 8) {
		    size = BUFSIZ;
		    buf = NULL;
		}
		if (buf == NULL) {
		    size += 8;
		    iop->_base = (unsigned char *)malloc((unsigned)size);
		}
		else
		    iop->_base = (unsigned char *)buf;
		_bufend(iop) = iop->_base + size -8;
		break;
	    default:
		return -1;
	}
	iop->_ptr = iop->_base;
	iop->_cnt = 0;
	return 0;
}
