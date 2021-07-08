/*~!ar.c*/
/* Name:  ar.c Part No.: _______-____r
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

#ident	"$Id: ar.c,v 1.4 2021/07/01 23:49:36 jbev Exp $"

/*
 * $Log: ar.c,v $
 * Revision 1.4  2021/07/01 23:49:36  jbev
 * Correct warning errors.
 *
 * Revision 1.3  1996/03/25 18:14:29  jbev
 * Mods for alpha port.
 *
 * Revision 1.2  1995/03/14 01:36:10  jbev
 * Fix warning errors.
 *
 * Revision 1.1  1995/03/14  00:14:50  jbev
 * Initial revision
 *
 */

/*
 * ar command:
 *	ar -drtx[cnuv] A[lib/dir] file1 file2 ....
 *
 * A - name of archive. Prepend to lid/dir.
 *
 * d - delete files from archive
 * r - replace file in archive
 * q - ignore
 * t - table of contents
 * m - ignore
 * p - ignore
 * x - extract named files from archive
 *
 * n - set extract time to now (only with x)
 * v - verbose mode
 * u - replace only if newer than archive date (only with r)
 * c - create new archive
 * l - ignore
 * a - ignore
 * b - ignore
 * i - ignore
 */

#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifndef mpx
#include <stdlib.h>
#endif

#include <string.h>
#include <ctype.h>

char *dname();
extern char *getcwd();
static char *cvtdname();
static char *cvtfname();
static char *pathname();
static void crunch();
#ifdef mpx
extern char curvol[];
extern char curdir[];
extern char *getcwvd();
extern char *str2lc();
static void conv2unix();
static void blcpy();
static void strlcpy();
#else
#include <unistd.h>
#endif
extern void usage();
extern int writc();
extern int copylib();
extern int readbb();
extern int writdc();

#ifndef mpx
#define O_UNBLK	0
#define O_BIN	0
int mpxbb();
#endif

#define	DOT	"."
#define	DELIM	'/'
#define	MAXN	128
#define BLKSIZE    768

char tfn[MAXN];

struct stat s1, s2, s3;

int dflg = 0;		/* delete named files */
int rflg = 0;		/* replace named files */
int ruflg = 0;		/* replace named files if newer */
int tflg = 0;		/* table of contents (log) */
int xflg = 0;		/* extract named files, set old date */
int xnflg = 0;		/* extract named files, set current date */
int vflg = 0;		/* verbose mode */
int cflg = 0;		/* create archive file */
int comflg = 0;		/* d, r, t, or x specified */

int lfd = 0;		/* library file descriptor */
int dfd = 0;		/* directory file descriptor */
int tlfd = 0;		/* temp library file descriptor */
int tdfd = 0;		/* temp directory file descriptor */
int cffd = 0;		/* current file descriptor */
int rdummy;

int libcnt = 0;		/* lib block count */
int dircnt = 0;		/* dir block count */
int tlibcnt = 0;	/* temp lib block count */
int tdircnt = 0;	/* temp dir block count */

int rob = 0;		/* record in block written */
int madeld = 0;		/* non zero if had to create lib/dir */

char fbuf[BLKSIZE];
char obuf[BLKSIZE];
char dbuf[BLKSIZE];
char idbuf[80];

int getname();
char *getdef();
char *readl();
int writl();
int writd();

/* get basename of arg without .o */
char *
basename(cp)
char *cp;
{
    int cc;

    strcpy(tfn, cp);
    cc = strlen(cp);
    if (cp[cc - 2] == '.' && (cp[cc - 1] == 'o' || cp[cc - 1] == 'O'))
    	tfn[cc - 2] = '\0';
    return(tfn);
}

/*
 * Compare translated upercase strings
 *	returns: s1>s2; >0  s1==s2; 0  s1<s2; <0
 */

int
stricmp (xs1, xs2)
register char *xs1, *xs2;
{

    if(xs1 == xs2)
    	return(0);
    while(toupper(*xs1) == toupper(*xs2++))
    	if(*xs1++ == '\0')
    	    return(0);
    return(*xs1 - *--xs2);
}

int main(argc, argv)
int argc;
char *argv[];
{
    int i, rc, optc;
    extern int optind;
    int errflg = 0;
    int size, type;
    char *ip, *op;
    char *lp, *dp, *tlp, *tdp;

    while ((optc=getopt(argc, argv, "DdRrTtXxCcNnUuVvQqMmPpAaIiBbLl")) != EOF)
    	switch(optc) {
    	    /* Ignore these */
   	    case 'A':
   	    case 'a':
   	    case 'B':
   	    case 'b':
   	    case 'I':
   	    case 'i':
   	    case 'L':
   	    case 'l':
   	    case 'M':
   	    case 'm':
   	    case 'Q':
   	    case 'q':
    		break;

    	    /* delete named entries */
    	    case 'D':
   	    case 'd':
    		dflg++;
    		comflg++;
    		break;

    	    /* replace named entries */
    	    case 'R':
   	    case 'r':
    		rflg++;
    		comflg++;
    		break;

    	    /* log table of contents */
    	    case 'T':
   	    case 't':
    		tflg++;
    		comflg++;
    		break;

    	    /* extract named entries */
    	    case 'X':
   	    case 'x':
    		xflg++;
    		comflg++;
    		break;

    	    /* Be verbose */
    	    case 'V':
   	    case 'v':
    		vflg++;
    		break;

    	    /* create named archive */
    	    case 'C':
   	    case 'c':
    		cflg++;
    		break;

    	    /* Update if newer than archive file */
    	    case 'U':
   	    case 'u':
    		ruflg++;
    		break;

    	    /* Set current time for extracted files */
    	    case 'N':
   	    case 'n':
    		xnflg++;
    		break;

    	    case '?':		/* who knows what he wants */
    		errflg++;
    	}

    if ((((argc-optind) < 2) && (!tflg && !xflg)) || errflg) {
    	usage();
    }

    if (!comflg) {
    	fprintf(stderr, "ar: d, r, t, or x must be specified\n");
    	usage();
    }
    if (comflg > 1) {
    	fprintf(stderr, "ar: only one of d, r, t, or x can be specified\n");
    	usage();
    }

    /* convert 1st arg to archive library name */
    /* append lib to given name */
    strcpy(tfn, argv[optind]);
    strcat(tfn, "lib");
    if((lp = cvtfname(tfn)) == (char *)0) {
    	fprintf(stderr, "ar: can't resolve library name %s\n", argv[optind]);
    	usage();
    }
    /* convert 1st arg to archive directory name */
    /* append dir to given name */
    strcpy(tfn, argv[optind]);
    strcat(tfn, "dir");
    if((dp = cvtfname(tfn)) == (char *)0) {
    	fprintf(stderr, "ar: can't resolve directory name %s\n", argv[optind]);
    	usage();
    }

    /* see if 1st arg is a file and present.  If not create. */
    if (stat(lp, &s1) < 0) {
    	if (xflg || tflg || dflg) {
    	    fprintf(stderr, "ar: library not present %s\n", lp);
    	    exit(2);
    	}
    	if (!cflg)
    	    fprintf(stderr, "ar: library not present, creating %s\n", lp);
    	if ((lfd = creat(lp, 0666)) < 0) {
    	    fprintf(stderr, "ar: can't create library %s\n", lp);
    	    exit(2);
    	}
    	close(lfd);	/* close, so we can open unblocked */
    	madeld++;	/* show we made the library */
    	stat(lp, &s1);	/* restat the file */
    }

    /* if not regular file, error */
    if ((s1.st_mode & S_IFMT) != S_IFREG) {
    	fprintf(stderr, "ar: library not regular file %s\n", lp);
    	usage();
    }

    /* it's there, see if we can open unblocked */
    if ((lfd = open(lp, O_UNBLK | O_RDWR)) < 0) {
    	fprintf(stderr, "ar: can't open library %s\n", lp);
    	exit(2);
    }

    /* see if 1st arg is a file and present.  If not create. */
    if (stat(dp, &s2) < 0) {
    	if (xflg || tflg || dflg) {
    	    fprintf(stderr, "ar: directory not present %s\n", dp);
    	    exit(2);
    	}
    	if (!cflg)
    	    fprintf(stderr, "ar: directory not present, creating %s\n", dp);
    	if ((dfd = creat(dp, 0666)) < 0) {
    	    fprintf(stderr, "ar: can't create directory %s\n", dp);
    	    exit(2);
    	}
    	close(dfd);	/* close, so we can open unblocked */
    	madeld++;	/* show we made the directory */
    	stat(lp, &s2);	/* restat the file */
    }

    /* if not regular file, error */
    if ((s2.st_mode & S_IFMT) != S_IFREG) {
    	fprintf(stderr, "ar: directory not regular file %s\n", dp);
    	usage();
    }

    /* it's there, see if we can open */
    if ((dfd = open(dp, O_UNBLK | O_RDWR)) < 0) {
    	fprintf(stderr, "ar: can't open directory %s\n", dp);
    	exit(2);
    }

    /* if we created the lib/dir, initialize it before using */
    if (madeld) {
    	int xrc;

    	/* initialize library */
    	memset(obuf, 0, BLKSIZE);	/* clear output record */
    	obuf[1] = 0x80;		/* eof */
    	/* write next to last buffer */
#ifdef mpx
    	xrc = writraw(lfd, obuf, BLKSIZE);
#else
    	xrc = write(lfd, obuf, BLKSIZE);
#endif
    	if (xrc <= 0) {		/* see if EOF */
    	    fprintf(stderr, "ar: can't write to library %s\n", lp);
    	    exit(2);
    	}
    	memset(obuf, 0, BLKSIZE);	/* clear output record */
    	*obuf = 0x0f;		/* pseudo eof */
    	/* write last buffer */
#ifdef mpx
    	xrc = writraw(lfd, obuf, BLKSIZE);
#else
    	xrc = write(lfd, obuf, BLKSIZE);
#endif
    	*obuf = 0;		/* clear buffer */
    	if (xrc <= 0) {		/* see if EOF */
    	    fprintf(stderr, "ar: can't write to library %s\n", lp);
    	    exit(2);
    	}
#ifdef mpx
    	rdummy = fcbadr(lfd);
    	asm (" lw r1,_rdummy");
    	asm (" svc 1,x'37'");
#else
    	lseek(lfd, 0 , 0);	/* rewind file */
#endif

    	/* initialize directory */
    	memset(dbuf, 0, BLKSIZE);	/* clear buffer */
    	/* write next to last buffer */
#ifdef mpx
    	xrc = writraw(dfd, dbuf, BLKSIZE);
#else
    	xrc = write(dfd, dbuf, BLKSIZE);
#endif
    	if (xrc <= 0) {		/* see if EOF */
    	    fprintf(stderr, "ar: can't write to directory %s\n", dp);
    	    exit(2);
    	}
    	memset(dbuf, 0, BLKSIZE);	/* clear output record */
    	*dbuf = 0x0f;		/* pseudo eof */
    	/* write last buffer */
#ifdef mpx
    	xrc = writraw(dfd, dbuf, BLKSIZE);
#else
    	xrc = write(dfd, dbuf, BLKSIZE);
#endif
    	*dbuf = 0;			/* clear buffer */
    	if (xrc <= 0) {		/* see if EOF */
    	    fprintf(stderr, "ar: can't write to directory %s\n", dp);
    	    exit(2);
    	}
#ifdef mpx
    	rdummy = fcbadr(dfd);
    	asm (" lw r1,_rdummy");
    	asm (" svc 1,x'37'");
#else
    	lseek(dfd, 0 , 0);	/* rewind file */
#endif
    }

    /* see if u option present without r option */
    if (ruflg && !rflg) {
    	fprintf(stderr, "ar: u option specified without r option\n");
    	usage();
    }

    /* see if n option present without x option */
    if (xnflg && !xflg) {
    	fprintf(stderr, "ar: n option specified without x option\n");
    	usage();
    }

    setuid(getuid());

    /* we are finally ready to do something */
    /* the lib and dir files are open */

    /* see if just a log, if so, do it */
    if (tflg) {
    	int seq;		/* sequence number */
    	char name[9];		/* prog name */
    	int oneflg;		/* first time flag */
    	int form[2];		/* type of def */

    	while ((ip = readl(lfd,120)) > (char *)0) {
    	    seq = (ip[4] << 8) | ip[5];	/* get sequence # */
    	    if (seq == 1) {		/* start of function */
    		if (getname (ip, name) < 0) {
    		    /* bad object, abort */
    		    fprintf(stderr, "ar: bad object in file %s\n", lp);
    		    exit(2);		/* done */
    		}
    		printf ("%s\n", name);
    	    }
    	    op = ip;		/* save pointer */
    	    oneflg = 0;
    	    while ((ip = getdef(oneflg, ip, name, form)) != (char *)0) {
    		oneflg++;
    		/* print a definition */
    		if(*form)
    		    /* section definition */
    		    printf("   SECT %-8s  %6x\n", name, form[1]);
    		else
    		    /* external definition */
    		    printf("    DEF %-8s  %6x\n", name, form[1]);
    	    }
    	    /* record exhausted, get next record */
    	    if((*op & 0xff) == 0xdf) {
    		/* this is EOF, write info record */
    		printf("     ID %s\n", idbuf);
    	    }
    	}
    	/* we is done, print stats? */
    	/* no stats now */
    }

    /* see if extract, if so, do it */
    if (xflg) {
    	int seq;		/* sequence number */
    	char name[12];		/* prog name */
    	int doall = 0;		/* non zero if all */
    	int bypass;		/* bypass writing file */
    	int nr;
    	char cp;

    	/* if one arg specified, all files are to be extracted */
    	if ((argc-optind) == 1)
    	    /* extract all files */
    	    doall = 1;
    	bypass = 0;
    	while ((ip = readl(lfd,120)) > (char *)0) {
    	    seq = (ip[4] << 8) | ip[5];	/* get sequence # */
    	    /* if seq is zero, we are done */
    	    if (seq == 0)
    		break;
    	    if (seq == 1) {		/* start of function */
    		if (getname (ip, name) < 0) {
    		    /* bad object, abort */
    		    fprintf(stderr, "ar: bad object in file %s\n", lp);
    		    exit(2);		/* done */
    		}
    		if (!doall) {
    		    bypass = 1;		/* bypass this file */
    		    /* extract just named files */
    		    for (rc = optind+1; rc < argc; rc++) {
    			if (*argv[rc])
    			    /* test for equal file name */
    			    if (!stricmp(name, basename(argv[rc]))) {
    				bypass = 0;	/* don't bypass this file */
    				*argv[rc] = '\0';	/* we got it */
    				break;
    			    }
    		    }
    		} else
    		    bypass = 0;
    		if (!bypass) {
    		    /* create the file */
#ifdef mpx
    		    str2lc(name);		/* make lower case */
#else
    		    for (op = name; *op; op++) {
    			if(isupper(*op))
    			    *op = tolower(*op);
    		    }
#endif
    		    strcat(name, ".o");	/* add .o to name */
    		    if((cffd = open(name, O_BIN | O_CREAT | O_WRONLY, 0666)) < 0) {
    			fprintf(stderr, "ar: can't create object file %s\n", name);
    			bypass = 1;
    		    } else
    			if(vflg)
    			    printf ("extracting %s\n", name);
    		}
	    }
    	    if (!bypass) {
#ifdef mpx
    		nr = writraw(cffd, ip, 120);
#else
#ifdef USE_BB
    		nr = write(cffd, ip, 120);
#else
    		nr = mpxbb(cffd, ip, 120);
#endif
#endif
    		if(nr <= 0) {
    		    fprintf(stderr, "ar: can't write object file %s\n", name);
    		    close(cffd);
    		    bypass = 1;
    		}
    	    }
    	    if((*ip & 0xff) == 0xdf) {
    		/* this is EOF, close this file */
    		if (!bypass)
    		    close(cffd);
    		bypass = 0;
    	    }
    	}
    	/* we is done, print stats? */
    	/* no stats now */
    	for (rc = optind+1; rc < argc; rc++) {
    	    if (*argv[rc]) {
    		printf ("%s not extracted\n", argv[rc]);
    	    }
    	}
    }

    /* see if delete or replace option, if so need temps */
    if (dflg || (rflg && !cflg)) {
    	/* get its type/size for temp file creation */
    	type = s1.st_nlink;
    	size = s1.st_size/768;	/* disk blocks */
#ifdef mpx
    	setdft(type);		/* set new creat type */
    	setsiz(size,size/16,size/16);	/* set default size */
#endif
#ifdef mpx
    	ip = "temp";
#else
    	ip = "templib";
#endif
    	/* see if we can open */
    	if ((tlfd = open(ip, O_UNBLK | O_TRUNC | O_RDWR | O_CREAT, 0666)) < 0) {
    	    fprintf(stderr, "ar: can't open temp library %s\n", "templib");
    	}
    	/* get its type/size for temp file creation */
    	type = s2.st_nlink;
    	size = s2.st_size/768;	/* disk blocks */
#ifdef mpx
    	setdft(type);		/* set new creat type */
    	setsiz(size,size/16,size/16);	/* set default size */
#else
    	unlink(ip);
#endif
#ifdef mpx
    	ip = "temp";
#else
    	ip = "tempdir";
#endif
    	/* see if we can open */
    	if ((tdfd = open(ip, O_UNBLK | O_TRUNC | O_RDWR | O_CREAT, 0666)) < 0) {
    	    fprintf(stderr, "ar: can't open temp directory %s\n", "tempdir");
    	}
#ifdef mpx
    	setdft(0);		/* set back to default type */
    	setsiz(0,0,0);		/* set back to default size */
#else
    	unlink(ip);
#endif
    }

    /* see if delete, if so, do it */
    if (dflg) {
    	int seq;		/* sequence number */
    	char name[12];		/* prog name */
    	int doall = 0;		/* non zero if all */
    	int bypass;		/* bypass writing file */
    	int oneflg;		/* first time flag */
    	int form[2];		/* type of def */
    	int nr;
    	char cp;
    	int cblk, crec;		/* current blk and rec in temp dir */

    	/* more than one arg must be specified */
    	if ((argc-optind) <= 1) {
    	    fprintf(stderr, "ar: no objects specified for delete\n");
    	    usage();
    	}
    	bypass = 0;
    	tlibcnt = 0;
    	rob = 0;
    	tdircnt = 0;
    	while ((ip = readl(lfd,120)) > (char *)0) {
    	    seq = (ip[4] << 8) | ip[5];	/* get sequence # */
    	    /* if seq is zero, we are done */
    	    if (seq == 0)
    		break;
    	    if (seq == 1) {		/* start of function */
    		if (getname (ip, name) < 0) {
    		    /* bad object, abort */
    		    fprintf(stderr, "ar: bad object in file %s\n", lp);
    		    exit(2);		/* done */
    		}
    		bypass = 0;		/* don't bypass this file */
    		/* delete just named files */
    		for (rc = optind+1; rc < argc; rc++) {
    		    if (*argv[rc])
    			/* test for equal file name */
    			if (!stricmp(name, basename(argv[rc]))) {
    			    bypass = 1;		/* bypass this file */
    			    *argv[rc] = '\0';	/* we got it */
    			    goto doneit;
    			}
    		} 
    		cblk = tlibcnt;		/* current blk in temp dir */
    		crec = rob;		/* current rec in tmp dir */
doneit:;
	    }
    	    if (!bypass) {
    		nr = writl(tlfd, ip, 120);
    		if(nr <= 0) {
    		    fprintf(stderr, "ar: can't write temp lib file\n");
    		    close(tlfd);
    		    bypass = 1;
    		}
    		oneflg = 0;
    		while ((ip = getdef(oneflg, ip, name, form)) != (char *)0) {
    		    oneflg++;
    		    /* write to tmp dir */
    		    nr = writd(tdfd, name, cblk, crec);
    		    if(nr <= 0) {
    			fprintf(stderr, "ar: can't write temp dir file\n");
    			close(tdfd);
    			bypass = 1;
    			continue;
    		    }
    		} 
    		/* record exhausted, get next record */
    		continue;
    	    }
    	    if((*ip & 0xff) == 0xdf) {
    		/* this is EOF, file done, reset bypass */
    		bypass = 0;
    	    }
    	}
    	/* we is done, print stats? */
    	/* no stats now */
    	for (rc = optind+1; rc < argc; rc++) {
    	    if (*argv[rc]) {
    		fprintf (stderr, "%s not deleted\n", argv[rc]);
    	    }
    	}
    	/* now close out temp lib file */
    	if (!bypass) {
    	    nr = writc(tlfd);
    	    if(nr <= 0) {
    		fprintf(stderr, "ar: can't close temp lib file\n");
    		close(tlfd);
    	    }
    	}
    	/* now close out temp dir file */
    	if (!bypass) {
    	    nr = writdc(tdfd);
    	    if(nr <= 0) {
    		fprintf(stderr, "ar: can't close temp dir file\n");
    		close(tdfd);
    	    }
    	}
    	/* copy temp lib/dir to original lib/dir */
    	copylib();
    }

    /* see if replace, if so, do it */
    if (rflg) {
    	int seq;		/* sequence number */
    	char name[12];		/* prog name */
    	int doall = 0;		/* non zero if all */
    	int bypass;		/* bypass writing file */
    	int nr, ns;
    	char cp;
    	int oneflg;		/* first time flag */
    	int form[2];		/* type of def */
    	int cblk, crec;		/* current blk and rec in temp dir */

    	/* more than one arg must be specified */
    	if ((argc-optind) <= 1) {
    	    fprintf(stderr, "ar: no objects specified for replace\n");
    	    usage();
    	}
    	bypass = 0;
    	libcnt = 0;
    	dircnt = 0;
    	tlibcnt = 0;
    	rob = 0;
    	/* if create, just use lib/dir */
    	if(cflg) {
    	    tlfd = lfd;
    	    tdfd = dfd;
    	    goto addfiles;
    	}
    	/* read all of the library entries */
    	while ((ip = readl(lfd,120)) > (char *)0) {
    	    seq = (ip[4] << 8) | ip[5];		/* get sequence # */
    	    /* if seq is zero, we are done */
    	    if (seq == 0)
    		break;
    	    if (seq == 1) {		/* start of function */
    		if (getname (ip, name) < 0) {
    		    /* bad object, abort */
    		    fprintf(stderr, "ar: bad object in file %s\n", lp);
    		    exit(2);		/* done */
    		}
    		bypass = 0;		/* don't bypass this file */
    		/* delete just named files */
    		for (rc = optind+1; rc < argc; rc++) {
    		    if (*argv[rc]) {
    			/* test for equal file name */
    			if (!stricmp(name, basename(argv[rc]))) {
#ifdef DBUG
fprintf(stderr, "ar/replace: testing %s against arg %d file %s\n",
 name, rc, basename(argv[rc]));
#endif
    			    bypass = 1;		/* bypass this file */
    			    goto dunit;
    			}
    		    }
    		} 
    		cblk = tlibcnt;		/* current blk in temp dir */
    		crec = rob;		/* current rec in tmp dir */
dunit:;
	    }
    	    if (!bypass) {
    		nr = writl(tlfd, ip, 120);
    		if(nr <= 0) {
    		    fprintf(stderr, "ar: can't write temp lib file\n");
    		    close(tlfd);
    		    bypass = 1;
    		    continue;
    		}
    		oneflg = 0;
    		while ((ip = getdef(oneflg, ip, name, form)) != (char *)0) {
    		    oneflg++;
    		    /* write to tmp dir */
    		    nr = writd(tdfd, name, cblk, crec);
    		    if(nr <= 0) {
    			fprintf(stderr, "ar: can't write temp dir file\n");
    			close(tdfd);
    			bypass = 1;
    			continue;
    		    }
    		} 
    		/* record exhausted, get next record */
    		continue;
    	    }
    	    if((*ip & 0xff) == 0xdf) {
    		/* this is EOF, file done, reset bypass */
    		bypass = 0;
    	    }
    	}

    	/* we is done, templib and tempdir have been copied */
    	/* now we need to add in the new entries */

addfiles:
    	for (rc = optind+1; rc < argc; rc++) {
    	    if((cffd = open(argv[rc], O_BIN | O_RDONLY)) < 0) {
    		fprintf(stderr, "ar: can't open object file %s\n", argv[rc]);
    		continue;
    	    } else {
readobj:
    		ip = fbuf;
#ifdef mpx
    		nr = readraw(cffd, ip, 120);
#else
    		nr = readbb(cffd, ip, 120);
#endif
    		if(nr <= 0) {		/* if eof, we done */
    		    *argv[rc] = '\0';	/* show got it */
    		    close(cffd);
    		    continue;
    		}
    		if(((*ip & 0xff) != 0xdf) && ((*ip & 0xff) != 0xff)) {
    			goto readobj;
    		}
    		seq = (ip[4] << 8) | ip[5];	/* get sequence # */
    		if (seq == 1) {		/* start of function */
    		    if (getname (ip, name) < 0) {
    			/* bad object, abort */
    			fprintf(stderr, "ar: bad object in file %s\n", argv[rc]);
    			close(cffd);
    			continue;
    		    }
#ifdef DBUG
fprintf(stderr, "ar/adding: testing %s against arg %d file %s\n",
 name, rc, basename(argv[rc]));
#endif
    		    cblk = tlibcnt;	/* current blk in temp dir */
    		    crec = rob;		/* current rec in tmp dir */
    		}
    		nr = writl(tlfd, ip, 120);
    		if(nr <= 0) {
    		    fprintf(stderr, "ar: can't write temp lib file\n");
    		    close(cffd);
    		    close(tlfd);
    		    break;
    		}
    		oneflg = 0;
    		while ((ip = getdef(oneflg, ip, name, form)) != (char *)0) {
    		    oneflg++;
    		    /* write to tmp dir */
    		    nr = writd(tdfd, name, cblk, crec);
    		    if(nr <= 0) {
    			fprintf(stderr, "ar: can't write temp dir file\n");
    			close(tdfd);
    			close(cffd);
    			goto wedone;
    		    }
    		} 
    		/* record exhausted, get next record */
    		goto readobj;
    	    }
    	}
wedone:
    	for (rc = optind+1; rc < argc; rc++) {
    	    if (*argv[rc]) {
    		fprintf (stderr, "%s not replaced\n", argv[rc]);
    	    }
    	}
    	/* now close out temp lib file */
    	nr = writc(tlfd);
    	if(nr <= 0) {
    	    fprintf(stderr, "ar: can't close temp lib file\n");
    	    close(tlfd);
    	    exit(2);
    	}
    	/* now close out temp dir file */
    	nr = writdc(tdfd);
    	if(nr <= 0) {
    	    fprintf(stderr, "ar: can't close temp dir file\n");
    	    close(tdfd);
    	    exit(2);
    	}
    	if (!cflg) {
    	    /* copy temp lib/dir to original lib/dir */
    	    copylib();
    	}
    }
    exit(0);			/* all was O.K. */
}


int rib = 0;			/* record in block read */

/* read an object record from the library */
/* read into fbuf */
char *
readl(fd, cnt)
int fd;
int cnt;
{
    char *bp;
    int rc;
#ifdef mpx
    int *fcbp = (int *)fcbadr(fd);
#endif

    if (*fbuf == 0) {		/* num records left in buffer */
    	/* none left, read next sector */
#ifdef mpx
    	rc = readraw(fd, fbuf, BLKSIZE);
#else
    	rc = read(fd, fbuf, BLKSIZE);
#endif
    	libcnt++;
    	if (rc <= 0) {		/* see if EOF */
#ifdef mpx
    	    if(fcbp[3] & 0x01000000) {	/* test for EOM */
    		exit(2);		/* error */
    	    }
#endif
    	    return((char *)0);		/* return EOF */
    	}
    	if (*fbuf == 0 && (fbuf[1] & 0xff) == 0x80)
    	    return((char *)0);		/* return EOF */
#ifndef mpx
    	if (*fbuf == 0x0f && fbuf[1] == 0)
    	    return((char *)0);		/* return EOF */
#endif
    	rib = *fbuf;		/* records in buffer */
    }
    rc = (rib - *fbuf) * (fbuf[8] + 1);
    bp = fbuf + rc + 9;		/* current pointer */
    *fbuf -= 1;			/* buffers remaining */
    return(bp);			/* where data is */
}

/* write an object record to the library */
/* write obuf */
int
writl(fd, ip, cnt)
int fd;
char *ip;
int cnt;
{
    char *bp;
    int rc;
#ifdef mpx
    int *fcbp = (int *)fcbadr(fd);
#endif

    rc = *obuf * (cnt + 1);
    bp = obuf + rc + 8;		/* current pointer */
    *bp = cnt;			/* set record count */
    memcpy(&bp[1], ip, cnt);	/* copy in data */
    *obuf += 1;			/* buffers written */
    rob += 1;			/* buffers written */
    if (*obuf == 6) {		/* num records in buffer */
    	/* buffer full, write it */
#ifdef mpx
    	rc = writraw(fd, obuf, BLKSIZE);
#else
    	rc = write(fd, obuf, BLKSIZE);
#endif
    	memset(obuf, 0, BLKSIZE);	/* clear output record */
    	tlibcnt++;
    	rob = 0;		/* records in buffer */
    	if (rc <= 0) {		/* see if EOF */
#ifdef mpx
    	    if(fcbp[3] & 0x01000000) {	/* test for EOM */
    		exit(2);		/* error */
    	    }
#endif
    	    return(0);		/* return EOF */
    	}
    }
    return(cnt);		/* return cnt */
}

/* write last object record to the library */
/* write obuf */
int
writc(fd)
int fd;
{
    char *bp;
    int rc;
#ifdef mpx
    int *fcbp = (int *)fcbadr(fd);
#endif

#ifndef NASA_FIX
    if(rob != 0) {	/* if data in buffer, write it */
#endif
    /* write last buffer */
#ifdef mpx
    rc = writraw(fd, obuf, BLKSIZE);
#else
    rc = write(fd, obuf, BLKSIZE);
#endif
    libcnt = ++tlibcnt;
    if (rc <= 0) {		/* see if EOF */
#ifdef mpx
    	if(fcbp[3] & 0x01000000) {	/* test for EOM */
    	    exit(2);		/* error */
    	}
#endif
    	return(0);		/* return EOF */
    }
#ifndef NASA_FIX
    }
#endif
    memset(obuf, 0, BLKSIZE);	/* clear output record */
    obuf[1] = 0x80;		/* eof */
    /* write next to last buffer */
#ifdef mpx
    rc = writraw(fd, obuf, BLKSIZE);
#else
    rc = write(fd, obuf, BLKSIZE);
#endif
    if (rc <= 0) {		/* see if EOF */
#ifdef mpx
    	if(fcbp[3] & 0x01000000) {	/* test for EOM */
    	    exit(2);		/* error */
    	}
#endif
    	return(0);		/* return EOF */
    }
    memset(obuf, 0, BLKSIZE);	/* clear output record */
    *obuf = 0x0f;		/* pseudo eof */
    /* write last buffer */
#ifdef mpx
    rc = writraw(fd, obuf, BLKSIZE);
#else
    rc = write(fd, obuf, BLKSIZE);
#endif
    *obuf = 0;			/* clear buffer */
    if (rc <= 0) {		/* see if EOF */
#ifdef mpx
    	if(fcbp[3] & 0x01000000) {	/* test for EOM */
    	    exit(2);		/* error */
    	}
#endif
    	return(0);		/* return EOF */
    }
    return(1);			/* return O.K. */
}

int rdr = 0;			/* record in block written */

/* write a directory entry to the library */
/* write dbuf */
int
writd(fd, ip, blk, entr)
int fd;
unsigned char *ip;
int blk;
int entr;
{
    int cnt = 12;	/* always 12 bytes per entry */
    int rc;
    char *bp;
#ifdef mpx
    int *fcbp = (int *)fcbadr(fd);
#endif

    bp = dbuf + (rdr * cnt);	/* current pointer */
    memset(bp, 0x20, 8);	/* preblank name */
    cnt = strlen(ip);		/* get name length */
    memcpy(bp, ip, cnt);	/* copy in name */
    ip[8] = (blk >> 8) & 0xff;	/* set 1st part of block num */
    ip[9] = blk & 0xff;		/* set 2nd part of block num */
    ip[10] = (entr >> 8) & 0xff; /* set 1st part of rec num */
    ip[11] = entr & 0xff;	/* set 2nd part of rec num */
    memcpy(&bp[8], &ip[8], 4);	/* copy in location */
    rdr += 1;			/* buffers written */
    if (rdr >= 64) {		/* num records in buffer */
    	/* buffer full, write it */
#ifdef mpx
    	rc = writraw(fd, dbuf, BLKSIZE);
#else
    	rc = write(fd, dbuf, BLKSIZE);
#endif
    	memset(dbuf, 0, BLKSIZE);	/* clear output record */
    	tdircnt++;
    	rdr = 0;		/* records in buffer */
    	if (rc <= 0) {		/* see if EOF */
#ifdef mpx
    	    if(fcbp[3] & 0x01000000) {	/* test for EOM */
    		exit(2);		/* error */
    	    }
#endif
    	    return(0);		/* return EOF */
    	}
    }
    return(cnt);		/* return cnt */
}

/* write last directory entry to directory */
/* write dbuf */
int
writdc(fd)
int fd;
{
    char *bp;
    int rc;
#ifdef mpx
    int *fcbp = (int *)fcbadr(fd);
#endif

#ifndef NASA_FIX
    if(rdr != 0) {	/* if data in buffer, write it */
#endif
    /* write last buffer */
#ifdef mpx
    rc = writraw(fd, dbuf, BLKSIZE);
#else
    rc = write(fd, dbuf, BLKSIZE);
#endif
    dircnt = ++tdircnt;
    if (rc <= 0) {		/* see if EOF */
#ifdef mpx
    	if(fcbp[3] & 0x01000000) {	/* test for EOM */
    	    exit(2);		/* error */
    	}
#endif
    	return(0);		/* return EOF */
    }
    if (rdr < 64)		/* was it full when we wrote it */
    	goto doeof;		/* no, just do EOF */
    memset(dbuf, 0, BLKSIZE);	/* clear buffer */
    dircnt++;
    /* write next to last buffer */
#ifdef mpx
    rc = writraw(fd, dbuf, BLKSIZE);
#else
    rc = write(fd, dbuf, BLKSIZE);
#endif
    if (rc <= 0) {		/* see if EOF */
#ifdef mpx
    	if(fcbp[3] & 0x01000000) {	/* test for EOM */
    	    exit(2);		/* error */
    	}
#endif
    	return(0);		/* return EOF */
    }
#ifndef NASA_FIX
    }
#endif
doeof:
    rdr = 0;			/* no records anymore */
    dircnt++;			/* directory blocks */
    memset(dbuf, 0, BLKSIZE);	/* clear output record */
    *dbuf = 0x0f;		/* pseudo eof */
    /* write last buffer */
#ifdef mpx
    rc = writraw(fd, dbuf, BLKSIZE);
#else
    rc = write(fd, dbuf, BLKSIZE);
#endif
    *dbuf = 0;			/* clear buffer */
    if (rc <= 0) {		/* see if EOF */
#ifdef mpx
    	if(fcbp[3] & 0x01000000) {	/* test for EOM */
    	    exit(2);		/* error */
    	}
#endif
    	return(0);		/* return EOF */
    }
    return(1);			/* return O.K. */
}

int orc = 0;		/* object record count */

/* get a def name from object */
char *
getdef(nth, ip, np, form)
int nth;
unsigned char *ip;
char *np;
int *form;		/* format type */
{
    int cnt;				/* record length */
    int fc;				/* function code */

    /* if first time, get object record count */
    if (!nth) {
    	orc = ip[1];			/* get record count */
    }
    memset(np, 0, 9);			/* clear name record */

    if (orc <= 0)			/* if we have more */
    	return((char *)0);		/* done with record */
loop:
    cnt = ip[6] & 0xf;			/* record length */
    fc = (ip[6] >> 4) & 0xf;		/* function code */
    if (fc == 7) {			/* function code for def */
    	memcpy(np, &ip[7], cnt - 3);	/* copy in name */
    	orc -= (cnt + 1);		/* new record count */
    	*form = 0;			/* show it is def */
    	form[1] = ip[7+cnt-3] << 16 | ip[8+cnt-3] << 8 | ip[9+cnt-3];
    	form[1] &= 0x7fffff;		/* turn off rel bit */
    	return(char *)(ip + cnt + 1);	/* return new pointer */
    }
    if (fc == 0x0d) {			/* expanded loader code */
        cnt = ip[8];			/* entry byte count */
    	orc -= cnt;			/* new record count */
    	if (ip[7] == 5) {		/* external def */
    	    memcpy(np, &ip[14], cnt - 8);	/* copy in name */
    	    *form = 0;			/* show it is def */
    	    form[1] = ip[11] << 16 | ip[12] << 8 | ip[13];
    	    form[1] &= 0x7fffff;	/* turn off rel bit */
    	    ip += cnt;			/* new pointer */
    	    return((char *)ip);		/* return new pointer */
    	}
    	if (ip[7] == 1) {		/* section def */
    	    memcpy(np, &ip[15], cnt - 9);	/* copy in name */
    	    *form = 1;			/* show it is section def */
    	    form[1] = ip[11] << 16 | ip[12] << 8 | ip[13];
    	    form[1] &= 0x7fffff;	/* turn off rel bit */
    	    ip += cnt;			/* new pointer */
    	    return((char *)ip);		/* return new pointer */
    	}
    	/* check for date/time */
    	if (ip[7] == 0x0c) {		/* information record */
    	    if(ip[6] == 0xd0) {		/* date/time */
    		memcpy(&idbuf[10], &ip[10], 8);	/* copy in date */
    		memcpy(&idbuf[20], &ip[18], 8);	/* copy in time */
    		if(idbuf[30] == ' ')
    		    idbuf[30] = '\0';	/* if we only have date/time */
    	    }
    	    if (ip[6] == 0xd1) {	/* program I.D. */
    		memcpy(&idbuf[30], &ip[10], cnt - 4);	/* copy in info */
    		idbuf[30+cnt-4] = '\0';	/* null terminate */
    	    }
    	}
        ip += cnt;			/* new pointer */
    	if (orc > 0)			/* if we have more */
    	    goto loop;			/* continue */
    	return((char *)0);		/* done with record */
    }
    /* not for us, update counts and loop */
    if (cnt == 0)			/* if zero, this means 16 */
    	cnt = 16;			/* set new cnt */
    orc -= (cnt + 1);			/* new record count */
    ip += (cnt + 1);			/* return new pointer */
    if (orc > 0)			/* if we have more */
    	goto loop;			/* continue */
    return((char *)0);			/* done with record */
}


/* get the program name from object */
int
getname(ip, np)
char * ip;
char * np;
{
    int cnt = ip[6] & 0xf;		/* name length */

    if (((ip[6] >> 4) & 0xf) == 5) {	/* function code for name */
    	memset(np, 0, 9);		/* we have a name */
    	memcpy(np, &ip[7], cnt-3);	/* copy in name */
    	memset(idbuf, 0x20, sizeof(idbuf));	/* clear id buffer */
    	memcpy(idbuf, &ip[7], cnt-3);	/* set name */
    	idbuf[10] = '\0';
    	return(0);			/* return ok */
    }
    return(-1);			/* bad object */
}

/* copy lib and dir */
int
copylib()
{
    int rc, nr, ns;

    /* now copy temp lib/dir to std lib/dir */
    /* we should use the m.replac command for MPX */
#ifdef mpx
    rdummy = fcbadr(tlfd);
    asm (" lw r1,_rdummy");
    asm (" svc 1,x'37'");
    rdummy = fcbadr(tdfd);
    asm (" lw r1,_rdummy");
    asm (" svc 1,x'37'");
    rdummy = fcbadr(lfd);
    asm (" lw r1,_rdummy");
    asm (" svc 1,x'37'");
    rdummy = fcbadr(dfd);
    asm (" lw r1,_rdummy");
    asm (" svc 1,x'37'");
#else
    lseek (tlfd, 0, 0);
    lseek (tdfd, 0, 0);
    lseek (lfd, 0, 0);
    lseek (dfd, 0, 0);
#endif
docopylib:
    /* none left, read next sector */
#ifdef mpx
    rc = readraw(tlfd, obuf, BLKSIZE);
#else
    rc = read(tlfd, obuf, BLKSIZE);
#endif
    if (rc <= 0) {		/* see if EOF */
#ifdef mpx
    	int *fcbp = (int *)fcbadr(tlfd);
    	if(fcbp[3] & 0x01000000) {	/* test for EOM */
    	    exit(2);		/* error */
    	}
#endif
    }
    /* buffer full, write it */
#ifdef mpx
    rc = writraw(lfd, obuf, BLKSIZE);
#else
    rc = write(lfd, obuf, BLKSIZE);
#endif
    if (rc <= 0) {		/* see if EOF */
#ifdef mpx
    	int *fcbp = (int *)fcbadr(lfd);
    	if(fcbp[3] & 0x01000000) {	/* test for EOM */
    	    exit(2);		/* error */
    	}
#endif
    }
    if ((obuf[1] & 0xff) == 0x80) {	/* eof on tlib */
    	memset(obuf, 0, 768);	/* clear output record */
    	*obuf = 0x0f;		/* pseudo eof */
    	/* write last buffer */
#ifdef mpx
    	rc = writraw(lfd, obuf, BLKSIZE);
#else
    	rc = write(lfd, obuf, BLKSIZE);
#endif
    	if (rc <= 0) {		/* see if EOF */
#ifdef mpx
    	    int *fcbp = (int *)fcbadr(lfd);
    	    if(fcbp[3] & 0x01000000) {	/* test for EOM */
    		exit(2);		/* error */
    	    }
#endif
    	}
    } else
    	goto docopylib;
copydir:
    /* none left, read next sector */
#ifdef mpx
    rc = readraw(tdfd, obuf, BLKSIZE);
#else
    rc = read(tdfd, obuf, BLKSIZE);
#endif
    if (rc <= 0) {		/* see if EOF */
#ifdef mpx
    	int *fcbp = (int *)fcbadr(tdfd);
    	if(fcbp[3] & 0x01000000) {	/* test for EOM */
    	    exit(2);		/* error */
    	}
#endif
    }
    /* buffer full, write it */
#ifdef mpx
    rc = writraw(dfd, obuf, BLKSIZE);
#else
    rc = write(dfd, obuf, BLKSIZE);
#endif
    if (rc <= 0) {		/* see if EOF */
#ifdef mpx
    	int *fcbp = (int *)fcbadr(dfd);
    	if(fcbp[3] & 0x01000000) {	/* test for EOM */
    	    exit(2);		/* error */
    	}
#endif
    }
    nr = 0;
    for (ns = 0; ns < 64; ns++) {
    	if(obuf[ns*12] != 0)
    	    continue;
    	nr = 1;
    }
    /* if all 64 entries, do next sector */
    if (!nr)
    	goto copydir;
    memset(obuf, 0, BLKSIZE);	/* clear output record */
    *obuf = 0x0f;		/* pseudo eof */
    /* write last buffer */
#ifdef mpx
    rc = writraw(dfd, obuf, BLKSIZE);
#else
    rc = write(dfd, obuf, BLKSIZE);
#endif
    if (rc <= 0) {		/* see if EOF */
#ifdef mpx
    	int *fcbp = (int *)fcbadr(dfd);
    	if(fcbp[3] & 0x01000000) {	/* test for EOM */
    	    exit(2);		/* error */
    	}
#endif
    }
    return(0);			/* we done */
}

#ifndef mpx
static	unsigned  char	bb[BLKSIZE];	/* blocking buffer */
static	char	first = 0;		/* 1st time thru flag */

/*
 * mpxbb - make up mpx block file output
 * input - buffer address
 *	 - byte count
 */

int
mpxbb(fd, buf, cnt)
int fd;
unsigned char	*buf;
int	cnt;
{
	int	boff;			/* next write address offset */

	if (!first) {			/* is this 1st time thru */
	  first = 1;			/* set the flag */
	  memset (bb, '\0', BLKSIZE);	/* zero the buffer */
	  bb[3] = 4;			/* next write byte offset */
	  bb[4] = 0x60;			/* set beg/end of block */
	  bb[5] = 0;			/* 1st block count is 0 bytes */
	}
	boff = (bb[2] << 8) | (bb[3]);	/* get next write address offset */
	/* see if enough room in buffer for this record */
	/* add current offset + 2 (for last record info) plus new */
	/* record size plus 4 (2 for this rec, 2 for last) */
	if ((boff + 2 + cnt + 4) >= BLKSIZE) {
	  /* not enough space, write out this record */
	  if (write(fd, bb, BLKSIZE) < 0)
    	    return(-1);
	  memset (bb, '\0', BLKSIZE);	/* zero the buffer */
	  bb[4] = 0x60;			/* set beg/end of block */
	  bb[5] = 0;			/* 1st block count is 0 bytes */
					/* after 1st write */
	  boff = 4;			/* init count at 4 bytes */
	}
	/* we have enough room, move in the record */
	/* clear last record end of block flag, set up this record *
	/* info and last rec info at end of data, and update cnt */
	bb[boff] &= ~0x20;		/* clear end of block flag */
	bb[boff+2] = 0x00;		/* clear this blocks flags */
	bb[boff+3] = cnt;		/* set this record count */
	memcpy(&bb[boff+4], buf, cnt);	/* copy in the data */
	boff += (cnt+4);		/* update count */
	bb[boff] = 0x20;		/* set eob status flag */
	bb[boff+1] = cnt;		/* set last rec byte count */
	bb[2] = (boff & 0xff00) >> 8;	/* set hi byte of count */
	bb[3] = (boff & 0xff);		/* set lo byte of count */
	if (*buf != 0xdf)		/* was this the last rec */
	  return(cnt);			/* no, done */
	/* that was the last record, set eof flag in bb, write it and exit */
	/* see if enough room in buffer for EOM record */
	/* add current offset + 2 (for last record info) plus new */
	/* EOF record size of 4 (2 for this rec, 2 for last) */
	if ((boff + 2 + 4) >= BLKSIZE) {
	  /* not enough space, write out this record */
	  if (write(fd, bb, BLKSIZE) < 0)
    	    return(-1);
	  memset (bb, '\0', BLKSIZE);	/* zero the buffer */
	  bb[4] = 0x60;			/* set beg/end of block */
	  bb[5] = 0;			/* 1st block count is 0 bytes */
					/* after 1st write */
	  boff = 4;			/* init count at 4 bytes */
	}
	bb[boff] &= ~0x20;		/* clear end of block flag */
	bb[boff+2] = 0x80;		/* clear this blocks flags */
	bb[boff+3] = 0;			/* set record count of 0 */
	bb[boff+4] = 0xa0;		/* set EOF/EOB flags */
	boff += 4;			/* 4 more bytes */
	bb[2] = (boff & 0xff00) >> 8;	/* set hi byte of count */
	bb[3] = (boff & 0xff);		/* set lo byte of count */
	/* write out EOF record */
        if (write(fd, bb, BLKSIZE) < 0)
    	  return(-1);
	first = 0;			/* reset 1st time flag */
	return(cnt);			/* get out, done */
}

/*
 * This function reads MPX blocked files
 */

int bin = 0;
unsigned char si[BLKSIZE];

int
readbb (fd, ip, cnt)
int	fd;
char 	*ip;
int	cnt;
{
    int c;
    int i = 0;

    if (bin == 0) {
    	read(fd, si, BLKSIZE);
    	bin = 6;
    }
    /* check for EOF */
    if (si[bin] & 0x80) {
    	bin = 0;
    	return(0);		/* we have EOF */
    }
    /* check for EOB in last record */
    if (si[bin - 2] & 0x20) {
    	read(fd, si, BLKSIZE);	/* we have EOB */
    	bin = 6;
    }
    if ((c = si[bin+1]) > 0) {
    	for (i = 0; i < c; i++) {
    	    ip[i] = si[bin + 2 + i];
    	    if (i >= cnt)
    		break;
    	}
    	bin += (c + 4);
    	return (i);
    }
    bin = 0;
    return (i);
}
#endif /* mpx */


void usage()
{
    fprintf(stderr, "Usage: ar [-drtx][cnuv] Archive f1 f2 ... fn\n");
    exit(2);
}

/* cvtdname
 * convert an arbitrary directory name to a qualified unix pathname.
 * return pointer to malloc'd name or null if error.
 */
static char *
cvtdname(path)
char *path;
{
    char *dirp, *xdbuf, *retp;

    xdbuf = (char *)malloc(MAXN);
#ifdef mpx
    /* make sure pathname is l/c */
    str2lc(path);
#endif
    /* get default working directory */
    dirp = getcwd(0, MAXN);
#ifdef mpx
    /* see if just a name, if so add () around name */
    if (*path != '/' && *path != '@' && *path != '^' && *path != '('
      && *path != '.') {
    	/* put () around dir name to see if o.k. */
    	xdbuf[0] = '(';		/* start with ( */
    	strcpy(&xdbuf[1], path);	/* copy name */
    	strcat(xdbuf, ")");	/* put on ) */
    	retp = pathname(dirp, xdbuf);
    } else {
    	retp = pathname(dirp, path);
    }
#else
    retp = pathname(dirp, path);
#endif
    if (xdbuf)
    	free(xdbuf);
    if (dirp)
    	free(dirp);
    return(retp);
}

/* cvtfname
 * convert an arbitrary filename to a qualified unix pathname.
 * return pointer to malloc'd name or null if error.
 */
static char *
cvtfname(path)
char *path;
{
    char *dirp, *retp;

#ifdef mpx
    /* make sure pathname is l/c */
    str2lc(path);
#endif
    /* get default working directory */
    dirp = getcwd(0, MAXN);
    retp = pathname(dirp, path);
    if (dirp)
    	free(dirp);
    return(retp);
}

/* Convert relative to absolute pathnames */

/* Given a working directory and an arbitrary pathname, resolve them into
 * an absolute pathname. Memory is allocated for the result, which
 * the caller must free
 */
static char *
pathname(cd,path)
char *cd;	/* Current working directory */
char *path;	/* Pathname argument */
{
    register char *buf;

    if(cd == (char *)0 || path == (char *)0)
    	return (char *)0;

    /* Strip any leading white space on args */
    while(*cd == ' ' || *cd == '\t')
    	cd++;
    while(*path == ' ' || *path == '\t')
    	path++;

    /* Allocate and initialize output buffer; user must free
     * add fudge factor to malloc size in case user specified
     * just a / and we must replace it with /system/system
     */
    buf = (char *)malloc((unsigned)strlen(cd) + strlen(path) + 16);
    buf[0] = '\0';

    /* Interpret path relative to cd only if it doesn't begin with "/" */
    /* for MPX also see if @, ^, or ( */
    if(*path == '/'
#ifdef mpx
      || *path == '@' || *path == '^' || *path == '('
#endif
      ) {
    	crunch(buf,path);
    } else {
    	crunch(buf,cd);
    	crunch(buf,path);
    }

    /* Special case: null final path means the root directory */
    if(buf[0] == '\0'){
    	buf[0] = '/';
    	buf[1] = '\0';
    }
#ifdef mpx
    /* now convert to a qualified unix name if it was entered
     * as an MPX name
     */
    conv2unix(buf);
#endif

    return buf;
}

/* Process a path name string, starting with and adding to
 * the existing buffer
 */
static void
crunch(buf,path)
char *buf;
register char *path;
{
    register char *cp;
	
    cp = buf + strlen(buf);	/* Start write at end of current buffer */
	
    /* Now start crunching the pathname argument */
    for(;;){
    	/* Strip leading /'s; one will be written later */
    	while(*path == '/')
    	    path++;
    	if(*path == '\0')
    	    break;		/* no more, all done */
    	/* Look for parent directory references, either at the end
    	 * of the path or imbedded in it
    	 */
    	if(strcmp(path,"..") == 0 || strncmp(path,"../",3) == 0) {
    	    /* Hop up a level */
    	    if((cp = strrchr(buf,'/')) == (char *)0)
    		cp = buf;		/* Don't back up beyond root */
    		*cp = '\0';		/* In case there's another .. */
    		path += 2;		/* Skip ".." */
    		while(*path == '/')	/* Skip one or more slashes */
    		    path++;
    		/* Look for current directory references, either at the end
    		 * of the path or imbedded in it
    		 */
    	} else if(strcmp(path,".") == 0 || strncmp(path,"./",2) == 0) {
    	    /* "no op" */
    	    path++;			/* Skip "." */
    	    while(*path == '/')		/* Skip one or more slashes */
    		path++;
    	} else {
    	    /* Ordinary name, copy up to next '/' or end of path */
#ifdef mpx
    if(cp == buf && (*path == '@' || *path == '^' || *path == '(')) {
    } else
#endif
    	    *cp++ = '/';
    	    while(*path != '/' && *path != '\0')
    		*cp++ = *path++;
    	}
    }
    *cp++ = '\0';
}

#ifdef mpx
/* convert unix or mpx filename to unix filename */
/* .'s and multiple /'s will have been removed by crunch above */
/* first char must be /, ., @, ^, or ( to be converted */
/* NOTE: string supplied must be big enough for conversion */

static void
conv2unix(s)
register char *s;
{
    register char *os = s;
    char *tp;

    if (s == 0 || *s == 0)return;
    	switch (*os) {
    	    case '/':		/* path starts with /, leave it */
    		/* check for just a '/', if yes, give /system/system */
    		if (*++os == '\0') {	/* see if just a '/' */
    		    strcat(os, "system/system"); /* copy in root */
    		    return;		/* we are done */
    		}
    		return;		/* done with conversion */

    	    case '^':		/* path starts with ^ put in /curvol */
    		getcwvd();	/* get current working vol, dir */
    		/* move over other "stuff" to make room for vol */
    		bcopy(&os[1], os+strlen(curvol)+1, strlen(os));
    		blcpy(curvol, os+1, strlen(curvol));
    		/* go to process dir name, if any */
    		goto dodir;

    	    case '(':		/* path starts with ( put in /curvol */
    		getcwvd();	/* get current working vol, dir */
    		/* move over other "stuff" to make room for vol */
    		bcopy(os, os+strlen(curvol)+1, strlen(os)+1);
    		blcpy(curvol, os+1, strlen(curvol));
    		/* drop thru to process dir name, if any */

    	    case '@':		/* path starts with @ put in / */
dodir:
    		*os++ = '/';
    		/* check for just an '@', if yes, give /system */
    		if (*os == '\0') {	/* see if just a '@' */
    		    strcat(os, "system/system"); /* copy in root */
    		    return;		/* we are done */
    		}
    		/* check to see if @vol^dir or @vol^(dir) */
    		if (tp = strchr(os, '^')) {       /* got end of vol */
    		    /* check to see if next char is '('.  If yes,
    		     * just delete the ^ and continue
    		     */
    		    if (tp[1] == '(') {		/* see if '(' */
    			bcopy(&tp[1], tp, strlen(tp));
    		    } else {
    			*tp++ = '/';	/* terminate volume name */
    		    }
    		    os = tp;		/* next char in input */
    		}
    		if (tp = strchr(os, '(')) {	/* got end of vol */
    		    *tp++ = '/';	/* terminate volume name */
    		    os = tp;		/* next char in input */
    		    if (tp = strchr(os, ')')) {  /* get end of dir */
    			if (tp[1] == '\0')  /* see if a file name */
    			    *tp = '\0';	/* no, leave off last / */
    			else
    			    *tp++ = '/';    /* terminate directory */
    			os = tp;        /* start of file name or null */
    		    } else {		/* have /vol/, will get error */
    			return;
    		    }
    		} else {		/* have /vol, just wants volume */
    		    return;
    		}
    		return;			/* done with conversion */

    	    case '.' :            /* curr directory? */
    		if (os[1] == '.') { /* have .. now what? */
    		    if (os[2] == '/') { /* have ../ put in cur vol */
    			getcwvd();	/* get current working vol, dir */
    			bcopy(&os[3], os+strlen(curvol)+2, strlen(os) - 1);
    			*os++ = '/';
    			blcpy(curvol, os, strlen(curvol));
    			os += (strlen(curvol)+1);
    			*os++ = '/';
    			return;
    		    }
    		    if (os[2] == 0) { /* have just .. give vol */
    			getcwvd();	/* get current working vol, dir */
    			*os++ = '/';
    			strlcpy (os, curvol);
    			os += strlen(curvol);
    			*os++ = '\0';        /* end of volume */
    			return;          /* return /vol */
    		    }
    		    return;            /* have ..? just an error */
    		}
    		if (os[1] == '/') {  /* have ./, just curr dir */
    		    /* copy down file name */
    		    bcopy(&os[2], os, strlen(os));
    		    return;
    		}
    		if (os[1] == 0) {    /* have just ., return curr dir */
    		    *os++ = '/';
    		    getcwvd();	/* get current working vol, dir */
    		    strlcpy(os, curvol); /* copy in volume */
    		    os += strlen(curvol);
    		    *os++ = '/';        /* start of dir */
    		    strlcpy(os, curdir); /* copy in dir */
    		    os += strlen(curdir);
    		    *os++ = '\0';        /* terminate dir */
    		    return;
    		}
    		return;              /* have .? just an error */
    	    default:
    		return;              /* everything else o.k. */
    	}
}

/*
 * copy string p2 to string p1, converting to l/c as we go.
 */
static void
strlcpy(p1, p2)
char * p1;
char * p2;
{
    int c;
    /* copy p2 to p1 */
    while (c = *p2++) {
    	if (isupper(c))
    	    c = tolower(c);
    	*p1++ = c;
    }
    *p1 = '\0';
}

/*
 * copy string b1 to l/c string b2, with overlap testing
 */
static void
blcpy (b1, b2, length)
     register char *b1;
     register char *b2;
     register int length;
{
    register int c;
    /* handle buffer overlap case */
    if (b1 < b2)	/* possible overlap */
    	for (b1 += length, b2 += length; length--; ) {
    	    c = *--b1;
    	    if (isupper(c))
    		c = tolower(c);
    	    *--b2 = c;
    	}
    else
    	for (;length--;) {
    	    c = *b1++;
    	    if (isupper(c))
    		c = tolower(c);
    	    *b2++ = c;
    	}
}

#endif /* mpx */
