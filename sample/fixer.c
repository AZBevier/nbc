/*~!fixer.c*/
/* Name:  fixer.c Part No.: _______-____r
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

#ident	"@(#)sample:fixer.c	1.0"

/* this is a program to change the name of a program
 * within the load module to be the filename.  It is
 * useful for MPX.1X which requires the filename to
 * agree with the load module name.  Notice open option
 * of u to specify unblocked read.  A b can be used on
 * binary (object) files to not do end-of-line conversion.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
void exit();
void fixfile();

int main (argc, argv)
int	argc;
char	**argv;
{
    FILE *fp, *fopen();

    if (argc == 1) {	/* no args; that's an error */
    	fprintf(stderr, "fixer: no file specified\n");
    	exit(1);
    } else
    	while (--argc > 0)
    	    /* open r/w unblocked */
    	    if ((fp = fopen(*++argv, "r+u")) == NULL) {
    		fprintf(stderr, "fixer: can't open %s\n", *argv);
    		exit(1);
    	    } else {
    		fixfile(*argv,fp);
    		fclose(fp);
    	    }
    	exit(0);
}

char fname[16];
char buffer[768];

void fixfile(np,fp)	/* change 1st 8 chars of file to be name of file */
char *np;
FILE *fp;
{
    int	i;

    memset(fname, ' ', 16);	/* blank filename */
    for (i=0; i<8; i++) {
    	/* make sure filename is upper case */
    	if (islower(np[i]))
    	    np[i] = toupper(np[i]);
    	if (np[i] == '\0')
    	    break;
    	fname[i] = np[i];
    }

    /* now read in the 1st block of the file */
    if (fread(buffer, 1, 768, fp) <= 0) {
    	fprintf(stderr, "fixer: can't read %s\n", np);
    	return;
    }

    for (i=0; i<8; i++)
    	buffer[i] = fname[i];	/* set new name */
    fseek(fp, 0, 0);		/* reset to beginning */

    /* now write out modified file */
    if (fwrite(buffer, 1, 768, fp) <= 0) {
    	fprintf(stderr, "fixer: can't write %s\n", np);
    	return;
    }

    fprintf(stderr, "fixer: file %s renamed\n", np);
}
