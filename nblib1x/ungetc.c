/*~!ungetc.c*/
/* Name:  ungetc.c Part No.: _______-____r
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

#ident	"@(#)nbclib:ungetc.c	1.1"

#include <stdio.h>

extern _findbuf();

int
ungetc(c, iop)
int	c;
register FILE *iop;
{
    if(c == EOF)
      return(EOF);
    if((iop->_flag & _IOREAD) == 0 || iop->_ptr <= iop->_base)
      if(iop->_ptr == iop->_base && iop->_cnt == 0)
    	++iop->_ptr;
      else
    	return(EOF);
    if (iop->_base == NULL)
      _findbuf(iop);
    *--iop->_ptr = c;
    ++iop->_cnt;
    return(c);
}
