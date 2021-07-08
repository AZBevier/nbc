/*~!mkdep.c*/
/* Name:  mkdep.c Part No.: _______-____r
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

#ident	"Makef4MPX $Id: mkdep.c,v 1.3 2021/07/05 02:46:18 jbev Exp $"

/*
 * $Log: mkdep.c,v $
 * Revision 1.3  2021/07/05 02:46:18  jbev
 * MPX build.
 *
 * Revision 1.2  1996/03/25 18:14:29  jbev
 * Mods for alpha port.
 *
 * Revision 1.1  1995/03/14 02:47:08  jbev
 * Initial revision
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void filecopy();

char ll[] = "# DO NOT DELETE THIS LINE -- the dependencies begin here\n";

int main (argc, argv)
int	argc;
char	**argv;
{
    FILE	*fp, *fopen();

    if(argc == 1)		/* no args; copy std in */
    	filecopy(stdin);
    else
    	if ((fp = fopen(*++argv, "r")) == (FILE *)NULL) {
    	    fprintf(stderr, "mkdep: can't open %s\n", *argv);
    	    exit(1);
    	} else {
    	    filecopy(fp);
    	    fclose(fp);
    	}
    exit(0);
}

void filecopy(fp)		/* copy file fp to std out */
FILE	*fp;
{
    char *cp;
    char line[256];

    /* read lines of input from file */
    while ((cp = fgets(line, 256, fp)) != (char *)NULL) {
    	/* see if dependency line */
    	if(!strncmp(line, ll, 25)) {
    	    /* we found line, output ll line and exit */
    	    /* This will truncate file */
    	    printf("%s", ll);
    	    return;
    	}
    	/* Just output line */
    	printf("%s", line);
    }
    /* dependency line not found, put one in */
    printf("%s", ll);
}
