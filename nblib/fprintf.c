/*~!fprintf.c*/
/* Name:  fprintf.c Part No.: _______-____r
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

#ident	"@(#)nbclib:fprintf.c	1.1"

#include <stdio.h>
#include <varargs.h>

extern int _doprnt();

/*VARARGS2*/
int
fprintf(iop, format, va_alist)
FILE *iop;
char *format;
va_dcl
{
    register int count;
    va_list ap;

    va_start(ap);
    if (!(iop->_flag & _IOWRT)) {
      /* if no write flag */
      if (iop->_flag & _IORW) {
    	/* if ok, cause read-write */
    	iop->_flag |= _IOWRT;
      } else {
    	/* else error */
    	return EOF;
      }
    }
    count = _doprnt(format, ap, iop);
    va_end(ap);
    return(ferror(iop)? EOF: count);
}
