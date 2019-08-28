/*~!setbuf.c*/
/* Name:  setbuf.c Part No.: _______-____r
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

#ident	"@(#)nbclib:setbuf.c	1.1"

#include <stdio.h>

extern void free();
extern int isatty();
extern unsigned char _smbuf[][_SBFSIZ];

/* extern unsigned char *_stdbuf[]; */
extern unsigned char _sibuf[], _sobuf[];

void
setbuf(iop, buf)
register FILE *iop;
char	*buf;
{
    register int fno = fileno(iop);	/* file number */

    if(iop->_base != NULL && iop->_flag & _IOMYBUF)
      free((char*)iop->_base);
    iop->_flag &= ~(_IOMYBUF | _IONBF | _IOLBF);

    if((iop->_base = (unsigned char*)buf) == NULL) {
      iop->_flag |= _IONBF;	/* file unbuffered except in fastio */

      if (fno < 2)		/* for stdin, stdout, use the existing bufs */
    	_bufend(iop) = (iop->_base = (fno == 0 ? _sibuf : _sobuf)) + BUFSIZ ;
      else   /* otherwise, use small buffers reserved for this */
    	_bufend(iop) = (iop->_base = _smbuf[fno]) + _SBFSIZ;

    } else {			/* regular buffered I/O, standard buffer size */

      _bufend(iop) = iop->_base + BUFSIZ;
      if (isatty(fno))
    	iop->_flag |= _IOLBF;
    }
    iop->_ptr = iop->_base;
    iop->_cnt = 0;
}
