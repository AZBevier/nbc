/*~!tmpfile.c*/
/* Name:  tmpfile.c Part No.: _______-____r
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

#ident	"@(#)nbclib:tmpfile.c	1.1"

/*
 *	tmpfile - return a pointer to an update file that can be
 *		used for scratch. The file will automatically
 *		go away if the program using it terminates.
 */

#include <stdio.h>

extern FILE *fopen();
#ifndef mpx
extern int unlink();
extern char *tmpnam();
#endif

FILE *
tmpfile()
{
    register FILE *p;
#ifndef mpx
    char tfname[L_tmpnam];
#endif

#ifdef mpx
    if((p = fopen("TEMP", "w+")) == NULL)
      return NULL;
#else
    (void) tmpnam(tfname);
    if((p = fopen(tfname, "w+")) == NULL)
      return NULL;
    else
      (void) unlink(tfname);
#endif
    return(p);
}
