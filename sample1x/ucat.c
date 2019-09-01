/* cat.c */

#include <stdio.h>
char * getpath();

char buff[2048];

void filecopy();
void exit();

int main (argc, argv)
int	argc;
char	**argv;
{
    FILE	*fp, *fpo, *fopen();

    if(argc == 1)  {	/* no args; error */
	fprintf(stderr, "ucat: filename required\n");
    	exit(1);
    } else
    	while (--argc > 0)
    	    if ((fp = fopen(*++argv, "ru")) == NULL) {
    		fprintf(stderr, "ucat: can't open %s\n", *argv);
    		exit(1);
    	    } else {
#ifdef i386
    	        if ((fpo = fopen("unblocked", "wu")) == NULL) {
    		    fprintf(stderr, "ucat: can't open unblocked\n");
    		    exit(1);
    	        }
#else
    	        if ((fpo = freopen(getpath(fileno(stdout)), "wu", stdout))
                   == NULL) {
    		    fprintf(stderr, "ucat: can't reopen stdout\n");
    		    exit(1);
    	        }
#endif
    	    	filecopy(fp,fpo);
    	    	fclose(fp);
    	    	fclose(fpo);
    	    }
    exit(0);
}

void filecopy(fp,fpo)	/* copy file fp to std out */
FILE	*fp, *fpo;
{
    int	c, d;

    for(;;) {
    	c = fread(buff, 1, 2048, fp);
    	if (c == 0) {
    	    break;
    	}
    	d = fwrite(buff, 1, c, fpo);
    	if (d == 0) {
    	    fprintf(stderr, "EOF on output, val = %d\n", d);
    	    break;
    	}
    }
}
