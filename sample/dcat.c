/* cat.c */

#include <stdio.h>

void filecopy();
void exit();

int main (argc, argv)
int	argc;
char	**argv;
{
    FILE	*fp, *fopen();

    if(argc == 1) /* no args; copy std in */
    	filecopy(stdin);
    else
    	while (--argc > 0)
    	    if ((fp = fopen(*++argv, "r")) == NULL) {
    		fprintf(stderr, "list: can't open %s\n", *argv);
    		    exit(1);
    	    } else {
    		filecopy(fp);
    		fclose(fp);
    	    }
    exit(0);
}

void filecopy(fp)	/* copy file fp to std out */
FILE	*fp;
{
    int	c;

    while ((c = getc(fp)) != EOF)
    	putc(c, stdout);
}
