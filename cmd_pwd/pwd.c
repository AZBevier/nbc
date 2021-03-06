/*~!pwd.c*/
/* Name:  pwd.c Part No.: _______-____r
 *
 * Copyright 1995 - J B Systems, Morrison, CO
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

#ident	"Make4MPX $Id: pwd.c,v 1.2 2021/07/05 19:13:32 jbev Exp $"

/*
 * $Log: pwd.c,v $
 * Revision 1.2  2021/07/05 19:13:32  jbev
 * Fix warnings.
 *
 * Revision 1.1  1995/03/14 03:07:29  jbev
 * Initial revision
 *
 */

/*
 * Print current working directory
 */

#include	<stdio.h>
#include	<limits.h>
#include	<string.h>
#ifndef mpx
#include <stdlib.h>
#include <unistd.h>
#endif

#ifndef PATH_MAX
#define PATH_MAX 128
#endif

char	name[PATH_MAX+1];
extern char *getcwd();

int main()
{
    int length;
    if (getcwd(name, PATH_MAX + 1) == (char *)0) {
    	fprintf(stderr, "pwd: cannot determine current directory!\n");
    	exit(2);
    }
    length = strlen(name);
    name[length] = '\n';
    write(1, name, length + 1);
/*    write(1, name, length); */
    exit(0);
}
