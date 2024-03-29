/*~!ls.c*/
/* Name: ls.c Part No.: _______-____r
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

#ident	"Makef4MPX $Id: ls.c,v 1.2 1995/04/03 23:10:40 jbev Exp jbev $"

/*
 * $Log: ls.c,v $
 * Revision 1.2  1995/04/03 23:10:40  jbev
 * Fix warning errors.
 *
 * Revision 1.1  1995/03/14  02:43:39  jbev
 * Initial revision
 *
 */

/* ls.c - Unix/MPX directory reading routines */
/*
 * 	list file or directory;
 */

#ifndef mpx
#ifndef MPX
#define MPX
#endif
#endif

#include	<stdio.h>
#include	<sys/param.h>
#include	<sys/types.h>
#ifndef mpx
#include	<sys/sysmacros.h>
#include	<stdlib.h>
#include	<stdarg.h>
#include	<unistd.h>
#endif

#include	"dirent.h"
#include	<sys/stat.h>
#include	<string.h>

/* #define DBUG */

#ifndef mpx
#include <limits.h>
#include <ctype.h>
#endif

extern char *getcwd();
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
#endif
void mstat();
void pprintf();
void new_line();
void rddir();
void pem();
void pentry();
void column();
int getname();
void pmode();
void selectx();
void pdirectory();
int compar();
struct lbuf *gstat();

#define MAXN 256

#ifndef	__ARGS
#ifdef	ANSIPROTO
#define	__ARGS(x)	x
#else
#define	__ARGS(x)	()
#endif
#endif

#ifdef MPX
/*int wildmat __ARGS((char *s,char *p,char **argv));*/
extern int wildmat();
#endif

#ifndef NULL
#define NULL 0
#endif
#define FALSE 0
#define TRUE 1
#define NULLCHAR (char *)NULL
#define NULLCHARP (char **)NULL

#define ISARG   0100000 /* this bit equals 1 in lflags of structure lbuf 
                        *  if *namep is to be used;
                        */
#ifndef mpx
#define DIRECT	10	/* Number of direct blocks */
/* Number of pointers in an indirect block */
#define INDIR	128
/* Number of right shifts to divide by INDIR */
#define INSHFT	7
#endif

struct	lbuf	{
	union	{
		char	lname[MAXN];   /* used for filename in a directory */
		char	*namep;          /* for name in ls-command; */
	} ln;
#ifdef MPX
    	char	*fname;		/* filename in directory */
#endif
	char	ltype;  	/* filetype */
	unsigned short	lnum;   /* inode number of file */
	short	lflags; 	/* 0777 bits used as r,w,x permissions */
	short	lnl;    	/* number of links to file */
	unsigned short	luid;
	unsigned short	lgid;
	long	lsize;  	/* filesize or major/minor dev numbers */
	long	lmtime;
};

struct dchain {
	char *dc_name;		/* path name */
	struct dchain *dc_next;	/* next directory in the chain */
};

struct dchain *dfirst;	/* start of the dir chain */
struct dchain *cdfirst;	/* start of the durrent dir chain */
struct dchain *dtemp;	/* temporary - used for linking */
char *mycurdir;		/* the current directory */

int	nfiles = 0;	/* number of flist entries in current use */
int	nargs = 0;	/* number of flist entries used for arguments */
int	maxfils = 0;	/* number of flist/lbuf entries allocated */
int	maxn = 0;	/* number of flist entries with lbufs assigned */
int	quantn = 64;	/* allocation growth quantum */

struct	lbuf	*nxtlbf;	/* pointer to next lbuf to be assigned */
struct	lbuf	**flist;	/* pointer to list of lbuf pointers */
struct	lbuf	*gstat();

#ifndef mpx
FILE	*pwdfu, *pwdfg;
#endif

int	aflg, bflg, cflg, dflg, fflg, gflg, iflg, lflg, mflg;
int	nflg, oflg, pflg, qflg, sflg, tflg, uflg, xflg;
int	Cflg, Fflg, Rflg;
int	rflg = 1;   /* initialized to 1 for special use in compar() */
int	flags;
int	err = 0;	/* Contains return code */

char	*dmark;	/* Used if -p option active. Contains "/" or NULL. */

#ifndef mpx
unsigned	lastuid	= -1, lastgid = -1;
#endif
int	statreq;    /* is > 0 if any of sflg, (n)lflg, tflg are on */

char	*dotp = ".";
char	*makename();
char	tbufu[16], tbufg[16];   /* assumed 15 = max. length of user/group name */
char	*ctime();

long	nblock();
long	tblocks;  /* total number of blocks of files in a directory */
long	year, now;

int	num_cols = 80;
int	colwidth;
int	filewidth;
int	fixedwidth;
int	curcol;
int	compar();

int main(argc, argv)
int argc;
char *argv[];
{
	extern char	*optarg;
	extern int	optind;
	int	amino, opterr=0;
	int	c;
	register struct lbuf *ep;
	struct	lbuf	lb;
	int	i, width;
	long	time();
/*	char *malloc(); */
	void qsort(), exit();
#ifdef MPX
#ifndef mpx
	struct stat statb;
#endif
#endif
#ifdef MPX
    char dname[MAXN], fname[MAXN];
    char *file, *cp;
#ifdef mpx
    char *sp;
#endif
    int j;
#endif

	lb.lmtime = time((long *) NULL);
	year = lb.lmtime - 6L*30L*24L*60L*60L; /* 6 months ago */
	now = lb.lmtime + 60;
	while ((c=getopt(argc, argv,
	    "RrAaDdEeCcXxMmNnLlOoGgRrTtUuPpBbQqIiSsFfYyZz")) != EOF) switch(c) {
		case 'R':
		case 'r':
			Rflg++;
			statreq++;
			continue;
		case 'a':
		case 'A':
			aflg++;
			continue;
		case 'd':
		case 'D':
			dflg++;
			continue;
		case 'C':
		case 'c':
			Cflg = 1;
			mflg = 0;
			continue;
		case 'x':
		case 'X':
			xflg = 1;
			Cflg = 1;
			mflg = 0;
			continue;
		case 'm':
		case 'M':
			Cflg = 0;
			mflg = 1;
			continue;
		case 'n':
		case 'N':
			nflg++;
		case 'l':
		case 'L':
			lflg++;
			statreq++;
			continue;
		case 'o':
		case 'O':
			oflg++;
			lflg++;
			statreq++;
			continue;
		case 'g':
		case 'G':
			gflg++;
			lflg++;
			statreq++;
			continue;
		case 'z':	/* was -r on UNIX */
		case 'Z':	/* was -r on UNIX */
			rflg = -1;
			continue;
		case 't':
		case 'T':
			tflg++;
			statreq++;
			continue;
		case 'u':
		case 'U':
			uflg++;
			continue;
		case 'y':	/* was 'c' on UNIX */
		case 'Y':	/* was 'c' on UNIX */
			cflg++;
			continue;
		case 'p':
		case 'P':
			pflg++;
			statreq++;
			continue;
		case 'e':	/* was -F on UNIX */
		case 'E':	/* was -F on UNIX */
			Fflg++;
			statreq++;
			continue;
		case 'b':
		case 'B':
			bflg = 1;
			qflg = 0;
			continue;
		case 'q':
		case 'Q':
			qflg = 1;
			bflg = 0;
			continue;
		case 'i':
		case 'I':
			iflg++;
			continue;
		case 's':
		case 'S':
			sflg++;
			statreq++;
			continue;
		case 'f':
		case 'F':
			fflg++;
			continue;
		case '?':
			opterr++;
			continue;
		}
	if(opterr) {
		fprintf(stderr,"usage: ls -CRabdefgilmnopqstuxyz [files]\n");
		exit(2);
	}

	if (fflg) {
		aflg++;
		lflg = 0;
		sflg = 0;
		tflg = 0;
		statreq = 0;
	}

	fixedwidth = 2;
	if (pflg || Fflg)
		fixedwidth++;
	if (iflg)
		fixedwidth += 6;
	if (sflg)
		fixedwidth += 5;

	if (lflg) {
		if (!gflg && !oflg)
			gflg = oflg = 1;
		else
		if (gflg && oflg)
			gflg = oflg = 0;
		Cflg = mflg = 0;
#ifndef mpx
		if (oflg > 0)
			if ((pwdfu = fopen("/etc/passwd", "r")) == NULL) {
				fprintf(stderr,"%s file cannot be opened for reading\n","/etc/passwd");
				exit(2);
			}
		if (gflg > 0)
			if ((pwdfg = fopen("/etc/group", "r")) == NULL) {
				fprintf(stderr,"%s file cannot be opened for reading\n","/etc/group");
				exit(2);
			}
#endif
	}

#ifndef mpx
	if (Cflg || mflg) {
		char *getenv();
		char *clptr;
		if ((clptr = getenv("COLUMNS")) != NULL)
			num_cols = atoi(clptr);
		if (num_cols < 20 || num_cols > 160)
			/* assume it is an error */
			num_cols = 80;
	}
#endif

	/* allocate space for flist and the associated	*/
	/* data structures (lbufs)			*/
	maxfils = quantn;
	if((flist=(struct lbuf **)malloc((unsigned)(maxfils * sizeof(struct lbuf *)))) == NULL
	|| (nxtlbf = (struct lbuf *)malloc((unsigned)(quantn * sizeof(struct lbuf)))) == NULL) {
		fprintf(stderr, "ls: out of memory\n");
		exit(2);
	}
	if ((amino=(argc-optind))==0) { /* case when no names are given
					* in ls-command and current 
					* directory is to be used 
 					*/
#ifdef MPX
		argv[optind] = "*";
#else
		argv[optind] = dotp;
#endif /* MPX */
	}
	for (i=0; i < (amino ? amino : 1); i++) {

#ifdef MPX
    	dname[0] = fname[0] = '\0';
    	/* convert arg to a file name */
    	if((file = cvtfname(argv[optind])) == (char *)0) {
		err = 2;
		optind++;
		continue;
	}
    /* default a null name to * */
    if (file == NULL || *file == '\0')
    	file = "*";
    /* split path into directory and filename */
    if ((cp = strrchr(file, '/')) == NULL) {
    	strcpy(dname, ".");
    	strcpy(fname, file);
    } else {
    	strcpy(dname, file);
#ifdef mpx
    	/* see how many '/'s, must be at least 2 */
    	sp = file;
    	for (j=0; *sp; sp++)
    	    if (*sp == '/')j++;
    	if (j > 3) {	/* error if not 1, 2 or 3 */
		err = 2;
		optind++;
		continue;
	}
    	/* j = 1 */		/* we have just a volume name */
    	/* j = 2 */		/* we have a volume/directory name */
    	if (j == 1 || j == 2) {	/* we have /vol or /vol/dir */
    	    cp = " *";
    	}
    	if (j == 3) {		/* we have vol/dir/filename */
    	    dname[cp - file] = '\0';	/* trim to directory name */
    	}
#else
    	if ((j = stat (file, &statb)) >= 0) {
    	    if ((statb.st_mode & S_IFMT) == S_IFDIR) {
    		cp = " *";
    	    } else
    		dname[cp - file] = '\0';
    	} else
    	    dname[cp - file] = '\0';
#endif
    	strcpy(fname, cp + 1);
    	/* root directory */
    	if (dname[0] == '\0')
    	    strcpy(dname, "/");
        /* trailing '/' */
    	if (fname[0] == '\0')
    	    strcpy(fname, "*");
    }
#ifdef mpx
    /* make name lowercase */
    for (i=0; fname[i]; i++)
    	if (isupper(fname[i]))
    	    fname[i] = tolower(fname[i]);
#endif
#endif /* MPX */

		if (Cflg || mflg) {
#ifdef MPX
			width = strlen(fname);
#else
			width = strlen(argv[optind]);
#endif
			if (width > filewidth)
				filewidth = width;
		}
#ifdef MPX
	if ((ep = gstat((*dname ? dname : dotp), 1))==NULL)
#else
	if ((ep = gstat((*argv[optind] ? argv[optind] : dotp), 1))==NULL)
#endif
		{
			err = 2;
			optind++;
			continue;
		}
#ifdef MPX
		ep->ln.namep = (*dname ? strdup(dname) : dotp);
		ep->fname = strdup(fname);
#ifndef MPX1X
    	mstat(ep, ep->ln.namep, 1);
#else
    	ep->lnum = 0;
    	ep->lsize = 0;
    	ep->ltype = 'd';
    	ep->lflags = 0666;
    	/* mask ISARG and other file-type bits */
    	ep->luid = 0;
    	ep->lgid = 0;
    	ep->lnl = 0;
    	ep->lmtime = 0;
#endif
#else
		ep->ln.namep = (*argv[optind] ? argv[optind] : dotp);
#endif
		ep->lflags |= ISARG;
		optind++;
		nargs++;	/* count good arguments stored in flist */
	}
	colwidth = fixedwidth + filewidth;
	qsort(flist, (unsigned)nargs, sizeof(struct lbuf *), compar);
	for (i=0; i<nargs; i++)
		if (((flist[i]->ltype=='d') && (dflg==0)) || fflg)
			break;
	pem(&flist[0],&flist[i], 0);
	for (; i<nargs; i++) {
#ifdef MPX
		pdirectory(flist[i]->ln.namep, (amino>1), nargs, flist[i]->fname);
#else
		pdirectory(flist[i]->ln.namep, (amino>1), nargs);
#endif
		/* -R: print subdirectories found */
		while (dfirst || cdfirst) {
			/* Place direct subdirs on front in right order */
			while (cdfirst) {
				/* reverse cdfirst onto front of dfirst */
				dtemp = cdfirst;
				cdfirst = cdfirst->dc_next;
				dtemp->dc_next = dfirst;
				dfirst = dtemp;
			}
			/* take off first dir on dfirst & print it */
			dtemp = dfirst;
			dfirst = dfirst->dc_next;
#ifdef MPX
			pdirectory (dtemp->dc_name, 1, nargs, flist[i]->fname);
#else
			pdirectory (dtemp->dc_name, 1, nargs);
#endif
			free (dtemp->dc_name);
			free ((char *)dtemp);
		}
	}
	exit(err);
	/*NOTREACHED*/
}

/*
 * pdirectory: print the directory name, labelling it if title is
 * nonzero, using lp as the place to start reading in the dir.
 */
#ifdef MPX
void pdirectory (name, title, lp, fname)
#else
void pdirectory (name, title, lp)
#endif
char *name;
int title;
int lp;
#ifdef MPX
char *fname;
#endif
{
	register struct dchain *dp;
	register struct lbuf *ap;
	register char *pname;
	register int j;

	filewidth = 0;
	mycurdir = name;
	if (title) {
		putc('\n', stdout);
		pprintf(name, ":");
		new_line();
	}
	nfiles = lp;
#ifdef MPX
	rddir(name, fname);
	if (lflg || sflg) {
    	    for (j=lp; j<nfiles; j++) {
    		mstat (flist[j], makename (name, flist[j]->ln.lname), 0);
    	    }
    	}
#else
	rddir(name);
#endif
	if (fflg==0)
		qsort(&flist[lp],(unsigned)(nfiles - lp),sizeof(struct lbuf *),compar);
	if (Rflg) for (j = nfiles - 1; j >= lp; j--) {
		ap = flist[j];
		if (ap->ltype == 'd' && strcmp(ap->ln.lname, ".") &&
				strcmp(ap->ln.lname, "..")) {
			dp = (struct dchain *)calloc(1,sizeof(struct dchain));
			if (dp == NULL)
				fprintf(stderr,"ls: out of memory\n");
			pname = makename(mycurdir, ap->ln.lname);
			dp->dc_name = (char *)calloc(1,strlen(pname)+1);
			if (dp->dc_name == NULL) {
				fprintf(stderr,"ls: out of memory\n");
				free(dp);
			}
			else {
				strcpy(dp->dc_name, pname);
				dp -> dc_next = dfirst;
				dfirst = dp;
			}
		}
	}
	if (lflg || sflg)
		curcol += printf("total %ld", tblocks);
	pem(&flist[lp],&flist[nfiles],lflg||sflg);
}

/*
 * pem: print 'em.  Print a list of files (e.g. a directory) bounded
 * by slp and lp.
 */
void pem(slp, lp, tot_flag)
	register struct lbuf **slp, **lp;
	int tot_flag;
{
	int ncols, nrows, row, col;
	register struct lbuf **ep;

	if (Cflg || mflg)
		ncols = num_cols / colwidth;

	if (ncols == 1 || mflg || xflg || !Cflg) {
		for (ep = slp; ep < lp; ep++)
			pentry(*ep);
		new_line();
		return;
	}
	/* otherwise print -C columns */
	if (tot_flag)
		slp--;
	nrows = (lp - slp - 1) / ncols + 1;
	for (row = 0; row < nrows; row++) {
		col = (row == 0 && tot_flag);
		for (; col < ncols; col++) {
			ep = slp + (nrows * col) + row;
			if (ep < lp)
				pentry(*ep);
		}
		new_line();
	}
}

void pentry(ap)  /* print one output entry;
            *  if uid/gid is not found in the appropriate
            *  file (passwd/group), then print uid/gid instead of 
            *  user/group name;
            */
struct lbuf *ap;
{
#ifdef HUH
	struct	{
		char	dminor,
			dmajor;
	};
#endif
	register struct lbuf *p;
	register char *cp;

	p = ap;
	column();
	if (iflg) {
		if (mflg && !lflg)
			curcol += printf("%u ", p->lnum);
		else
			curcol += printf("%5u ", p->lnum);
    }
	if (sflg)
		curcol += printf( (mflg && !lflg) ? "%ld " : "%4ld " ,
			(p->ltype != 'b' && p->ltype != 'c') ?
				nblock(p->lsize) : 0L );
	if (lflg) {
		putchar(p->ltype);
		curcol++;
		pmode(p->lflags);
#ifndef MPX1X
#ifdef mpx
		curcol += printf("%4x ", p->lnl);
#else
		curcol += printf("%4d ", p->lnl);
#endif
#ifndef mpx
		if (oflg) {
			if(!nflg && getname(p->luid, tbufu, 0)==0)
				curcol += printf("%-9.9s", tbufu);
			else
				curcol += printf("%-9u", p->luid);
        }
		if (gflg) {
			if(!nflg && getname(p->lgid, tbufg, 1)==0)
				curcol += printf("%-9.9s", tbufg);
			else
				curcol += printf("%-9u", p->lgid);
        }
#endif
		if (p->ltype=='b' || p->ltype=='c')
#ifdef mpx
			curcol += printf("%3d,%3d",
    			 ((int)p->lsize>>8), ((int)p->lsize&0xff));
#else
			curcol += printf("%3d,%3d", major((int)p->lsize), minor((int)p->lsize));
#endif
		else
			curcol += printf("%7ld", p->lsize);
#else /* MPX1X */
		curcol += printf("%4d ", p->lgid);
		curcol += printf("%-9x", p->luid);
		curcol += printf("%-9x", p->lnl);
		curcol += printf("%7ld", p->lsize);
    		p->lmtime = now - 60;
#endif /* MPX1X */
		cp = ctime(&p->lmtime);
		if((p->lmtime < year) || (p->lmtime > now))
			curcol += printf(" %-7.7s %-4.4s ", cp+4, cp+20);
		else
			curcol += printf(" %-12.12s ", cp+4);
	}
	if ((pflg || Fflg) && p->ltype == 'd')
		dmark = "/";
	else
	if (Fflg && (p->lflags & 0111))
		dmark = "*";
	else
		dmark = "";
	if (p->lflags & ISARG) {
		if (qflg || bflg)
			pprintf(p->ln.namep,dmark);
		else
			curcol += printf("%s%s",p->ln.namep,dmark);
	}
	else {
		if (qflg || bflg)
			pprintf(p->ln.lname,dmark);
		else
			curcol += printf("%s%s",p->ln.lname,dmark);
	}
}

/* print various r,w,x permissions */
void pmode(aflag)
int aflag;
{
        /* these arrays are declared static to allow initializations */
	static int	m0[] = { 1, S_IREAD>>0, 'r', '-' };
	static int	m1[] = { 1, S_IWRITE>>0, 'w', '-' };
	static int	m2[] = { 3, S_ISUID|S_IEXEC, 's', S_IEXEC, 'x', S_ISUID, 'S', '-' };
	static int	m3[] = { 1, S_IREAD>>3, 'r', '-' };
	static int	m4[] = { 1, S_IWRITE>>3, 'w', '-' };
	static int	m5[] = { 3, S_ISGID|(S_IEXEC>>3),'s', S_IEXEC>>3,'x', S_ISGID,'l', '-'};
	static int	m6[] = { 1, S_IREAD>>6, 'r', '-' };
	static int	m7[] = { 1, S_IWRITE>>6, 'w', '-' };
	static int	m8[] = { 3, S_ISVTX|(S_IEXEC>>6),'t', S_IEXEC>>6,'x', S_ISVTX,'T', '-'};

        static int  *m[] = { m0, m1, m2, m3, m4, m5, m6, m7, m8};

	register int **mp;

	flags = aflag;
	for (mp = &m[0]; mp < &m[sizeof(m)/sizeof(m[0])];)
		selectx(*mp++);
}

void selectx(pairp)
register int *pairp;
{
	register int n;

	n = *pairp++;
	while (n-->0) {
		if((flags & *pairp) == *pairp) {
			pairp++;
			break;
		}else {
			pairp += 2;
		}
	}
	putchar(*pairp);
	curcol++;
}

/*
 * column: get to the beginning of the next column.
 */
void column()
{

	if (curcol == 0)
		return;
	if (mflg) {
		putc(',', stdout);
		curcol++;
		if (curcol + colwidth + 2 > num_cols) {
			putc('\n', stdout);
			curcol = 0;
			return;
		}
		putc(' ', stdout);
		curcol++;
		return;
	}
	if (Cflg == 0) {
		putc('\n', stdout);
		curcol = 0;
		return;
	}
	if ((curcol / colwidth + 2) * colwidth > num_cols) {
		putc('\n', stdout);
		curcol = 0;
		return;
	}
	do {
		putc(' ', stdout);
		curcol++;
	} while (curcol % colwidth);
}

void new_line()
{
	if (curcol) {
		putc('\n',stdout);
		curcol = 0;
	}
}

/* read each filename in directory dir and store its
 *  status in flist[nfiles] 
 *  use makename() to form pathname dir/filename;
 */
void rddir(dir, fname)
char *dir;
char *fname;
{
	struct dirent *dentry;
	DIR *dirf;
	register int j;
	register struct lbuf *ep;
	register int width;

	if ((dirf = opendir(dir)) == NULL) {
		fflush(stdout);
		fprintf(stderr, "can not access directory %s\n", dir);
		err = 2;
		return;
	}
        else {
          	tblocks = 0;
		while ((dentry = readdir(dirf))) {
          		if (aflg==0 && dentry->d_name[0]=='.' 
#ifdef NODOTDOT
			&& (dentry->d_name[1]=='\0' || dentry->d_name[1]=='.'
			&& dentry->d_name[2]=='\0')
#endif
          			)  /* check for directory items '.', '..', 
                                   *  and items without valid inode-number;
                                   */
          			continue;
#ifdef MPX
    			if (!(wildmat(dentry->d_name, fname, 0)))
    				continue;
#endif
			if (Cflg || mflg) {
				width = strlen(dentry->d_name);
				if (width > filewidth)
					filewidth = width;
			}
          		ep = gstat(makename(dir, dentry->d_name), 0);
          		if (ep==NULL)
          			continue;
                        else {
          		     ep->lnum = dentry->d_ino;
			     for (j=0; dentry->d_name[j] != '\0'; j++)
          		         ep->ln.lname[j] = dentry->d_name[j];
			     ep->ln.lname[j] = '\0';
                        }
          	}
          	(void) closedir(dirf);
		colwidth = fixedwidth + filewidth;
	}
}

/* get status of file and recomputes tblocks;
 * argfl = 1 if file is a name in ls-command and  = 0
 * for filename in a directory whose name is an
 * argument in the command;
 * stores a pointer in flist[nfiles] and
 * returns that pointer;
 * returns NULL if failed;
 */
struct lbuf *gstat(file, argfl)
char *file;
int argfl;
{
#ifndef MPX
	struct stat statb;
#endif
	register struct lbuf *rep;
	static int nomocore;
/*	char *malloc(), *realloc(); */

	if (nomocore)
		return(NULL);
	else if (nfiles >= maxfils) { 
/* all flist/lbuf pair assigned files time to get some more space */
		maxfils += quantn;
		if((flist=(struct lbuf **)realloc((char *)flist, (unsigned)(maxfils * sizeof(struct lbuf *)))) == NULL
		|| (nxtlbf = (struct lbuf *)malloc((unsigned)(quantn * sizeof(struct lbuf)))) == NULL) {
			fprintf(stderr, "ls: out of memory\n");
			nomocore = 1;
			return(NULL);
		}
	}

/* nfiles is reset to nargs for each directory
 * that is given as an argument maxn is checked
 * to prevent the assignment of an lbuf to a flist entry
 * that already has one assigned.
 */
	if(nfiles >= maxn) {
#ifdef NOTNOW
    	    rep = (struct lbuf *)calloc(1, (unsigned)(sizeof(struct lbuf)));
    	    if (rep == NULL) {
	    	fprintf(fp, "ls: out of memory\n");
    	    	nomocore = 1;
    	    	return(NULL);
    	    }
#endif
		rep = nxtlbf++;
		flist[nfiles++] = rep;
		maxn = nfiles;
	}else {
		rep = flist[nfiles++];
	}
	rep->lflags = 0;
#ifndef MPX
	if (argfl || statreq) {
		if (stat(file, &statb)<0) {
			perror(file);
			nfiles--;
			return(NULL);
		}
                else {
	            	rep->lnum = statb.st_ino;
	            	rep->lsize = statb.st_size;
	            	switch(statb.st_mode&S_IFMT) {

	            	case S_IFDIR:
	            		rep->ltype = 'd';
	            		break;

	            	case S_IFBLK:
	            		rep->ltype = 'b';
#ifndef MPX1X
	            		rep->lsize = statb.st_rdev;
#endif
	            		break;

	            	case S_IFCHR:
	            		rep->ltype = 'c';
#ifndef MPX1X
	            		rep->lsize = statb.st_rdev;
#endif
	            		break;

	            	case S_IFIFO:
                 		rep->ltype = 'p';
                 		break;
                        default:
                                rep->ltype = '-';
                 	}
	          	rep->lflags = statb.st_mode & ~S_IFMT;
                                    /* mask ISARG and other file-type bits */
	          	rep->luid = statb.st_uid;
	          	rep->lgid = statb.st_gid;
	          	rep->lnl = statb.st_nlink;
	          	if(uflg)
	          		rep->lmtime = statb.st_atime;
	          	else if (cflg)
	          		rep->lmtime = statb.st_ctime;
	          	else
	          		rep->lmtime = statb.st_mtime;
                        if (rep->ltype != 'b' && rep->ltype != 'c')
	          	   tblocks += nblock(statb.st_size);
                }
	}
#endif /* MPX */
        return(rep);
}

#ifdef MPX
void mstat(rep, file, argfl)
register struct lbuf *rep;
char *file;
int argfl;
{
    struct stat statb;

	if (argfl || statreq) {
		if (stat(file, &statb)<0) {
			perror(file);
			nfiles--;
			return;
		}
                else {
	            	rep->lnum = statb.st_ino;
	            	rep->lsize = statb.st_size;
	            	switch(statb.st_mode&S_IFMT) {

    			case 0:
	            	case S_IFDIR:
	            		rep->ltype = 'd';
	            		break;

	            	case S_IFBLK:
	            		rep->ltype = 'b';
#ifndef MPX1X
	            		rep->lsize = statb.st_rdev;
#endif
	            		break;

	            	case S_IFCHR:
	            		rep->ltype = 'c';
#ifndef MPX1X
	            		rep->lsize = statb.st_rdev;
#endif
	            		break;

	            	case S_IFIFO:
                 		rep->ltype = 'p';
                 		break;
                        default:
                                rep->ltype = '-';
                 	}
	          	rep->lflags = statb.st_mode & ~S_IFMT;
                        /* mask ISARG and other file-type bits */
	          	rep->luid = statb.st_uid;
	          	rep->lgid = statb.st_gid;
	          	rep->lnl = statb.st_nlink;
	          	if(uflg)
	          		rep->lmtime = statb.st_atime;
	          	else if (cflg)
	          		rep->lmtime = statb.st_ctime;
	          	else
	          		rep->lmtime = statb.st_mtime;
                        if (rep->ltype != 'b' && rep->ltype != 'c')
	          	   tblocks += nblock(statb.st_size);
                }
	}
}
#endif /* MPX */

long nblock(size)
long size;
{
	long blocks, tot;

#ifdef mpx
    tot = size/768;
#else
#ifndef BSHIFT
#define BSHIFT 10
#endif
#ifndef BSIZE
#define BSIZE 512
#endif
	blocks = tot = (size + BSIZE - 1) >> BSHIFT;
	if(blocks > DIRECT)
		tot += ((blocks - DIRECT - 1) >> INSHFT) + 1;
	if(blocks > DIRECT + INDIR)
		tot += ((blocks - DIRECT - INDIR - 1) >> (INSHFT * 2)) + 1;
	if(blocks > DIRECT + INDIR + INDIR*INDIR)
		tot++;
#endif
	return(tot);
}

/* returns pathname of the form dir/file;
 *  dir is a null-terminated string;
 */
char *makename(dir, file) 
char *dir, *file;
{
	static char dfile[MAXN];  /*  Maximum length of a
                                        *  file/dir name in ls-command;
                                        *  dfile is static as this is returned
                                        *  by makename();
                                        */
	register char *dp, *fp;
	register int i;

	dp = dfile;
	fp = dir;
	while (*fp)
		*dp++ = *fp++;
	if (dp > dfile && *(dp - 1) != '/')
		*dp++ = '/';
	fp = file;
	for (i=0; *fp != '\0'; i++)
		*dp++ = *fp++;
	*dp = '\0';
	return(dfile);
}

#ifndef mpx
/* get name from passwd/group file for a given uid/gid
 *  and store it in buf; lastuid is set to uid;
 *  returns -1 if uid is not in file
 */
int getname(uid, buf, type)
unsigned int uid;
int type;
char buf[];
{
        int c;
        register int i, j, n;

	if (uid==(type ? lastgid : lastuid))
		return(0);
	rewind(type ? pwdfg : pwdfu);
	if(type)
		lastgid = -1;
	else	lastuid = -1;
	do {
		i = 0;
		j = 0;
		n = 0;
                while((c=fgetc(type ? pwdfg : pwdfu)) != '\n') {  /* '\n' indicates end of 
                                                  *  a per user/group record
                                                  *  in passwd/group file;
                                                  */
                     if (c==EOF)
                        return(-1);  
                     else if (c==':') j++;
                          else if (j==0) buf[i++] = c;
                               else if (j==2)
                                       n = n*10 + (c-'0');
		}
	} while (n != uid);
	buf[i] = '\0';
	if (type)
		lastgid = uid;
	else	lastuid = uid;
	return(0);
}
#endif

int compar(pp1, pp2)  /* return >0 if item pointed by pp2 should appear first */
struct lbuf **pp1, **pp2;
{
	register struct lbuf *p1, *p2;

	p1 = *pp1;
	p2 = *pp2;
	if (dflg==0) {
/* compare two names in ls-command one of which is file
 *  and the other is a directory;
 *  this portion is not used for comparing files within
 *  a directory name of ls-command;
 */
		if (p1->lflags&ISARG && p1->ltype=='d') {
			if (!(p2->lflags&ISARG && p2->ltype=='d'))
				return(1);
                }
                else {
			if (p2->lflags&ISARG && p2->ltype=='d')
				return(-1);
		}
	}
	if (tflg) {
		if(p2->lmtime == p1->lmtime)
			return(0);
		else if(p2->lmtime > p1->lmtime)
			     return(rflg);
		else return(-rflg);
	}
        else
             return(rflg * strcmp(p1->lflags&ISARG? p1->ln.namep: p1->ln.lname,
				p2->lflags&ISARG? p2->ln.namep: p2->ln.lname));
}

void pprintf(s1,s2)
char *s1, *s2;
{
	register char *s;
	register int   c;
	register int  cc;
	int i;

	for (s = s1, i = 0; i < 2; i++, s = s2)
		while((c = *s++)) {
			if (c < ' ' || c >= 0177) {
				if (qflg)
					c = '?';
				else if (bflg) {
					curcol += 3;
					putc ('\\', stdout);
					cc = '0' + (c>>6 & 07);
					putc (cc, stdout);
					cc = '0' + (c>>3 & 07);
					putc (cc, stdout);
					c = '0' + (c & 07);
				}
			}
			curcol++;
			putc(c, stdout);
		}
}

#ifndef DEFFED_IN_WILDMAT_C
#ifdef MPX
/*
 * @(#)wildmat.c 1.3 87/11/06	Public Domain.
 *
From: rs@mirror.TMC.COM (Rich Salz)
Newsgroups: net.sources
Subject: Small shell-style pattern matcher
Message-ID: <596@mirror.TMC.COM>
Date: 27 Nov 86 00:06:40 GMT

There have been several regular-expression subroutines and one or two
filename-globbing routines in mod.sources.  They handle lots of
complicated patterns.  This small piece of code handles the *?[]\
wildcard characters the way the standard Unix(tm) shells do, with the
addition that "[^.....]" is an inverse character class -- it matches
any character not in the range ".....".  Read the comments for more
info.

For my application, I had first ripped off a copy of the "glob" routine
from within the find(1) source, but that code is bad news:  it recurses
on every character in the pattern.  I'm putting this replacement in the
public domain.  It's small, tight, and iterative.  Compile with -DTEST
to get a test driver.  After you're convinced it works, install in
whatever way is appropriate for you.

I would like to hear of bugs, but am not interested in additions; if I
were, I'd use the code I mentioned above.
*/

/*
**  Do shell-style pattern matching for ?, \, [], and * characters.
**  Might not be robust in face of malformed patterns; e.g., "foo[a-"
**  could cause a segmentation violation.
**
**  Written by Rich $alz, mirror!rs, Wed Nov 26 19:03:17 EST 1986.
*/

/*
 * Modified 6Nov87 by John Gilmore (hoptoad!gnu) to return a "match"
 * if the pattern is immediately followed by a "/", as well as \0.
 * This matches what "tar" does for matching whole subdirectories.
 *
 * The "*" code could be sped up by only recursing one level instead
 * of two for each trial pattern, perhaps, and not recursing at all
 * if a literal match of the next 2 chars would fail.
 */

/* Modified by Anders Klemets to take an array of pointers as an optional
   argument. Each part of the string that matches '*' is returned as a
   null-terminated, malloced string in this array.
 */

static int Star __ARGS((char *s,char *p,char **argv));

static int Star(s,p,argv)
register char *s;
register char *p;
register char **argv;
{
	char *cp = s;
	while (wildmat(cp, p, argv) == FALSE)
		if(*++cp == '\0')
			return -1;
	return cp - s;
}

int wildmat(s,p,argv)
register char *s;
register char *p;
register char **argv;
{
	register int last;
	register int matched;
	register int reverse;
	register int cnt;

	for(; *p; s++,p++){
		switch(*p){
		case '\\':
			/* Literal match with following character; fall through. */
			p++;
		default:
			if(*s != *p)
				return FALSE;
			continue;
		case '?':
			/* Match anything. */
			if(*s == '\0')
				return FALSE;
			continue;
		case '*':
			/* Trailing star matches everything. */
			if(argv == NULLCHARP)
				return *++p ? 1 + Star(s, p, NULLCHARP) : TRUE;
			if(*++p == '\0'){
				cnt = strlen(s);
			} else {
				if((cnt = Star(s, p, argv+1)) == -1)
					return FALSE;
			}
			*argv = (char *)malloc(cnt+1);
			strncpy(*argv,s,cnt);
			*(*argv + cnt) = '\0';
			return TRUE;
		case '[':
			/* [^....] means inverse character class. */
			reverse = (p[1] == '^') ? TRUE : FALSE;
			if(reverse)
				p++;
			for(last = 0400, matched = FALSE; *++p && *p != ']'; last = *p){
				/* This next line requires a good C compiler. */
				if(*p == '-' ? *s <= *++p && *s >= last : *s == *p)
					matched = TRUE;
			}
			if(matched == reverse)
				return FALSE;
			continue;
		}
	}
	/* For "tar" use, matches that end at a slash also work. --hoptoad!gnu */
	return *s == '\0' || *s == '/';
}


#ifdef	TEST
#include <stdio.h>

extern char *gets();

int main()
{
	char pattern[80];
	char text[80];
	char *argv[80], *cp;
	int cnt;

	while (TRUE){
		printf("Enter pattern:  ");
		if(gets(pattern) == NULL)
			break;
		while (TRUE){
			bzero(argv,80*sizeof(char *));
			printf("Enter text:  ");
			if(gets(text) == NULL)
				exit(0);
			if(text[0] == '\0')
				/* Blank line; go back and get a new pattern. */
				break;
			printf("      %d\n", wildmat(text, pattern, argv));
			for(cnt = 0; argv[cnt] != NULLCHAR; ++cnt){
				printf("String %d is: '%s'\n",cnt,argv[cnt]);
				free(argv[cnt]);
			}
		}
	}
	exit(0);
}
#endif	/* TEST */
#endif /* MPX */
#endif /* DEFED in WILDMAT */

#ifdef MPX
/* cvtfname
 * convert an arbitrary filename to a qualified unix pathname.
 * return pointer to malloc'd name or null if error.
 */
static char *cvtfname(path)
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
static char *pathname(cd,path)
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
static void crunch(buf,path)
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

static void conv2unix(s)
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
static void strlcpy(p1, p2)
char *p1;
char *p2;
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
static void blcpy (b1, b2, length)
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
#endif /* MPX */
