/*~!finfo.h*/
/* Name:  finfo.h Part No.: _______-____r
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

#ident	"@(#)nbinclude:finfo.h	1.0"

#ifndef FINFO_H
#define FINFO_H

#include   <mosde.h>		/* machine and o/s equates */
#include   <stdio.h>		/* now included to get _NFILE */

#ifdef MPX1X
/* added for MPX1X */
#define CPYNAME(SRC,DST) {char *s=(char *)(SRC);char *d=(char *)(DST);\
int i;for(i=0;i<8;i++,s++)*d++=((*s)!=' ')?*s:'\0';}
#endif

#ifdef MPX1X
/* finfo structure defines the current file assigned */
struct finfo {
 int	username[2];	/* Username associated with file */
 int	userkey[2];	/* key, if any associated with username */
 int	filename[2];	/* file name */
 int	password[2];	/* password, if any associate with file */
 short  key;		/* compressed key for username if any */
 short	passwd;		/* compressed file password if any */
};

extern struct finfo* pn2fib();	/* 1x filename conversion pgm */

#endif

/*    macros      */

#define ZREG(ari,sz)  {int i;for(i=0;i<sz;i++)ari[i]=0;}
#define ZINT(ptr,sz)  {int i,*p=(int*)(ptr);for(i=0;i<sz;i++)*p++ =0;}

#endif /* FINFO_H */
