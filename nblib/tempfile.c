/*~!tempfile.c*/
/* Name:  tempfile.c Part No.: _______-____r
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

#ident	"@(#)nbclib:tempfile.c	1.1"

/*
 *	tempfile - returns a pointer to an update file that can be
 *		used for scratch. The file must be removed by the
 *		caller, otherwise it will not go away.
 */

#include <stdio.h>

extern FILE *fopen();
extern char *tmpnam();

FILE *
tempfile()
{
    register FILE *p;
    char tfname[L_tmpnam];

    (void) tmpnam(tfname);	/* get a tempfile name */
    if((p = fopen(tfname, "w+")) == NULL)
      return ((FILE *)0);

    return(p);
}
