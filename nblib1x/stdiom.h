/*~!stdiom.h*/
/* Name:  stdiom.h Part No.: _______-____r
 *
 * Copyright 1991 - J B Systems, Morrison, CO
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

#ident	"@(#)nbclib:stdiom.h	1.1"

#ifndef STDIOM_H
#define STDIOM_H

/* The following macros improve performance of the stdio by reducing the
	number of calls to _bufsync and _wrtchk.  _BUFSYNC has the same
	effect as _bufsync, and _WRTCHK has the same effect as _wrtchk,
	but often these functions have no effect, and in those cases the
	macros avoid the expense of calling the functions.  */

#define _BUFSYNC(iop) if(_bufend(iop)-iop->_ptr<\
(iop->_cnt<0?0:iop->_cnt))_bufsync(iop)

#define _WRTCHK(iop) ((((iop->_flag&(_IOWRT|_IOEOF))!=_IOWRT)\
||(iop->_base==NULL)||(iop->_ptr==iop->_base&&iop->_cnt==0\
&&!(iop->_flag&(_IONBF|_IOLBF))))?_wrtchk(iop):0)
#endif /* STDIOM_H */
