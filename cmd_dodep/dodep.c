/*~!dodep.c*/
/* Name:  dodep.c Part No.: _______-____r
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

#ident	"Make4MPX $Id: dodep.c,v 1.3 2021/07/04 02:09:16 jbev Exp $"

/*
 * $Log: dodep.c,v $
 * Revision 1.3  2021/07/04 02:09:16  jbev
 * Correct warnings.
 *
 * Revision 1.2  1996/03/25 18:14:29  jbev
 * Mods for alpha port.
 *
 * Revision 1.1  1995/03/14 01:30:33  jbev
 * Initial revision
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef mpx
#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#endif

void docopy();
void filecopy();
int callsys();

char ll[] = "# DO NOT DELETE THIS LINE -- the dependencies begin here\n";
#ifndef mpx
#ifdef llinux
char cc[] = "/lib/cpp";
#else
char cc[] = "/system/bin/nbcpp";
#endif
#else
char cc[] = "/system/bin/nbcpp";
#endif

int main (argc, argv)
int	argc;
char	**argv;
{
    FILE	*fp, *fopen();
    int i, c;
    char *parm[1000];

    /* dodep makefile f0 f1 f2 ..... */
    /* call nbcpp -M on all files specified with output to file xxx */

    if(argc < 3) {		/* not enough args; error */
        fprintf(stderr, "Usage: dodep [-defs] makefile f1 f2 ... fn\n");
    	exit(2);
    }
#ifdef llinux
    parm[0] = "cpp";
#else
    parm[0] = "nbcpp";
#endif
    c = 1;
    i = 1;
#ifndef OLD_WAY
    parm[i++] = "-M";
#endif
    while(*argv[c] == '-' && c < argc)
    	parm[i++] = argv[c++];	/* set user args */
    if (c >= argc) {
        fprintf(stderr, "Usage: dodep [-defs] makefile f1 f2 ... fn\n");
    	exit(2);
    }
#ifdef OLD_WAY
    parm[i++] = "-M";
#endif
    if ((fp = fopen(argv[c], "r")) == (FILE *)NULL) {
    	fprintf(stderr, "dodep: can't open %s\n", argv[c]);
    	exit(1);
    }
    c++;
    filecopy(fp);	/* copy make file to output */
    fclose(fp);
    /* now get cc dependencies */
    for (; c < argc; c++) {
    	parm[i] = argv[c];
    	parm[i+1] = "tmp.dep";
    	parm[i+2] = (char *)NULL;
#ifdef DEBUG_ME
fprintf(stderr, "parms %s, %s, %s %s\n", parm[0], parm[1], parm[2], parm[3]);
#endif
    	callsys(cc, parm);
    	fp = fopen("tmp.dep", "r");
    	printf("# Source file %s\n", argv[c]);
    	docopy(fp);
    	fclose(fp);
    	unlink("tmp.dep");
    }
    printf("# End of dependencies\n");
    exit(0);
}

void filecopy(fp)		/* copy file fp to std out */
FILE	*fp;
{
    char *cp;
    char line[8192];

    /* read lines of input from file */
    while ((cp = fgets(line, 8192, fp)) != (char *)NULL) {
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

void docopy(fp)		/* copy file fp to std out */
FILE	*fp;
{
    char *cp;
    char line[8192];

    /* read lines of input from file */
    while ((cp = fgets(line, 8192, fp)) != (char *)NULL) {
    	/* Just output line */
    	printf("%s", line);
    }
}

int callsys(f, v)
char *f, **v;
{
  int t, status;

#if defined(linux) || defined(__alpha)
  t = fork();
  if (t == -1) {
    fprintf(stderr, "No more processes\n");
    return (100);
  }
  if (t == 0) {
    execv(f, v);
    fprintf(stderr, "Can't find %s\n", f);
    fflush(stderr);
    _exit(100);
  }
  while (t != wait(&status))
    ;
  if ((t=(status&0377)) != 0 && t!=14) {
    if (t!=2) {
      fprintf(stderr, "Fatal error in %s\n", f);
    }
    return(1);
  }
  return ((status>>8) & 0377);
#else
  if ((t = vexecv(f, v)) == -1) {
    fprintf(stderr, "Can't find %s\n", f);
    fflush(stderr);
    return(1);
  }
  if (t == 0) {
    return (0);	/* all was a ok */
  }
  fprintf(stderr, "Fatal error in %s\n", f);
  return (1);	/* to shutup warnings */

#endif
}

