/*~!getcwd.c*/
/* Name:  getcwd.c Part No.: _______-____r
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

#ident	"@(#)nbclib:getcwd.c	1.1"

/*
 * Library routine to GET the Current Working Directory.
 * arg1 is a pointer to a character buffer into which the
 * path name of the current directory is placed by the
 * subroutine.  arg1 may be zero, in which case the
 * subroutine will call malloc to get the required space.
 * arg2 is the length of the buffer space for the path-name.
 * If the actual path-name is longer than (arg2-2), or if
 * the value of arg2 is not at least 3, the subroutine will
 * return a value of zero, with errno set as appropriate.
 */

#include <stdio.h>
#include <sys/errno.h>
#include <types.h>
#include <ctype.h>

extern char curvol[];
extern char curdir[];

extern char *malloc(), *strchr(), *strcat(), *strcpy();
extern int errno;

char *
getcwd(arg1, arg2)
char	*arg1;
int	arg2;
{
	char	*trm;

	if(arg2 == 0) {
		errno = EINVAL;
		return(0);
	}
	if(arg2 < 0) {
		errno = ERANGE;
		return(0);
	}
	if(arg1 == 0)
		if((arg1 = malloc((unsigned)arg2)) == 0) {
			errno = ENOMEM;
			return(0);
		}
	errno = 0;
#ifndef FIX_040494
    	getcwvd();		/* get current default */
#endif
	strcpy(arg1, "/");
	strcat(arg1, (char *)curvol);
	strcat(arg1, "/");
#ifdef MPX1X
    	if ((curdir[0] == 0) || (curdir[0] == 0x20))
    	    strcat(arg1, "SYSTEM");
    	else
    	    strcat(arg1, curdir);
#else
	strcat(arg1, curdir);
#endif
    	/* now make lower case */
    	trm = arg1;
    	while (*trm) {
    	  if(isupper(*trm))
    	    *trm = tolower(*trm);
    	  trm++;
    	}
	
	return(arg1);
}
