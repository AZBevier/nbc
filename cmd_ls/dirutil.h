/*~!dirutil.h*/
/* Name:  dirutil.h Part No.: _______-____r
 *
 * Copyright 1994 - J B Systems, Morrison, CO
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
 
#ident	"@(#)tcpip:dirutil.h	2.0"
 
#ifndef	_DIRUTIL_H
#define	_DIRUTIL_H
 
#include "global.h"
 
/* In dirutil.c */
FILE *dir __ARGS((char *path,int full));
int filedir __ARGS((char *name,int times,char *ret_str));
int getdir __ARGS((char *path,int full,FILE *file));
 
/* In pathname.c: */
char *pathname __ARGS((char *cd,char *path));
 
#endif /* _DIRUTIL_H */
 
