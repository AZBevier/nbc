/*~!dirutil.c*/
/* Name:  dirutil.c Part No.: _______-____r
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
 
#ident	"@(#)tcpip:dirutil.c	1.1"
 
/* dirutil.c - Unix/MPX directory reading routines */
 
#include	<stdio.h>
#include	<sys/param.h>
#include	<sys/types.h>
#ifndef MPX
#include	<sys/sysmacros.h>
#endif
#include	<sys/stat.h>
#include	<stdio.h>
#ifndef MPX
#define LX		/* define when we use nap nad -lx ld option */
#endif
#ifndef LX
#include	<dirent.h>
#else
#include	"dirent.h"
#endif
/*#include	"global.h"*/
#include	<string.h>
#include	<stdlib.h>
 
/* #define DBUG */
 
#ifdef MPX
#include <limits.h>
#endif
 
#ifdef MPX
#include <ctype.h>
#endif
 
#ifndef PATH_MAX
#define PATH_MAX 256
#endif
 
extern int wildmat();
int getdir();
void filedir();
static void free_clist();
static void mstat();
static void pentry();
static void pem();
static void pdirectory();
static void pprintf();
static void column();
static void new_line();
static void rddir();
static void pmode();
static void selectx();

/* Create a directory listing in a temp file and return the
 * resulting file descriptor. If full == 1, give a full listing;
 * else return just a list of names.
 */
FILE *
dir (path,full)
char *path;
int full;
{
    FILE *fp;
 
#ifdef DBUG
    printf("dir called with path %s\n", path);
#endif
#ifdef MPX
    if ((fp = fopen("TEMP", "w+")) != (FILE *)0){
    	fprintf (fp, "no entries in directory %s\n", path);
#else
    if ((fp = tmpfile()) != (FILE *)0) {
#endif
    	rewind (fp);
    	if (getdir (path,full,fp) < 0) {
    	    fclose (fp);
    	    return ((FILE *)0);
    	}
#ifndef MPX
    	if (ftell(fp) <= 0)
    	    fprintf (fp, "no entries in directory %s\n", path);
#endif
    	rewind (fp);
    }
    return fp;
}
 
/* wildcard filename lookup */
void filedir (name, times, ret_str)
char	*name;
int	times;
char	*ret_str;
{
	static char	dname[PATH_MAX], fname[PATH_MAX];
	static DIR *xdirp = NULL;
	struct dirent *dp;
#ifndef MPX
	struct stat sbuf;
	char	temp[128];
#endif
	char	*cp;
 
	/*
	 * Make sure that the NULL is there in case we don't
    	 * find anything
	 */
	ret_str[0] = '\0';
 
	if (times == 0) {
#ifdef MPX
    		int i;
#endif
 
		/* default a null name to * */
		if (name == NULL || *name == '\0')
			name = "*";
		/* split path into directory and filename */
		if ((cp = strrchr(name, '/')) == NULL) {
			strcpy(dname, ".");
			strcpy(fname, name);
		} else {
			strcpy(dname, name);
			dname[cp - name] = '\0';
			strcpy(fname, cp + 1);
			/* root directory */
			if (dname[0] == '\0')
				strcpy(dname, "/");
			/* trailing '/' */
			if (fname[0] == '\0')
				strcpy(fname, "*");
		}
#ifdef MPX
    for (i=0; dname[i]; i++)
    	if (isupper(dname[i]))
    	    dname[i] = tolower(dname[i]);
    for (i=0; fname[i]; i++)
    	if (isupper(fname[i]))
    	    fname[i] = tolower(fname[i]);
#endif
 
		/* close directory left over from another call */
		if (xdirp != NULL)
			closedir(xdirp);
		/* open directory */
		if ((xdirp = opendir(dname)) == NULL) {
			printf("Could not open DIR (%s)\n", dname);
			return;
		}
	} else {
		/* for people who don't check return values */
		if (xdirp == NULL)
			return;
	}
 
	/* scan directory */
	while ((dp = readdir(xdirp)) != NULL) {
		/* test for name match */
		if (wildmat(dp->d_name, fname, 0)) {
			/* test for regular file */
#ifndef MPX
			sprintf(temp, "%s/%s", dname, dp->d_name);
			if (stat(temp, &sbuf) < 0)
				continue;
			if ((sbuf.st_mode & S_IFMT) != S_IFREG)
				continue;
#endif
			strcpy(ret_str, dp->d_name);
			break;
		}
	}
 
	/* close directory if we hit the end */
	if (dp == NULL) {
		closedir(xdirp);
		xdirp = NULL;
	}
}
 
/*
* 	list file or directory;
*/
 
#define ISARG   0100000 /* this bit equals 1 in lflags of
    			 * structure lbuf if *namep is to be used;
                        */
struct	lbuf	{
	union	{
    		/* used for filename in a directory */
		char	lname[PATH_MAX];
		char	*namep;          /* for name in ls-command; */
	} ln;
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
 
static struct dchain *dfirst;	/* start of the dir chain */
static struct dchain *cdfirst;	/* start of the current dir chain */
static struct dchain *dtemp;	/* temporary - used for linking */
static char *curdir;		/* the current directory */
 
static int	nfiles = 0;	/* number of flist entries in current use */
static int	nargs = 0;	/* number of flist entries used for arguments */
static int	maxfils = 0;	/* number of flist/lbuf entries allocated */
static int	maxn = 0;	/* number of flist entries with lbufs assigned */
static int	nomocore;
 
static struct	lbuf	**flist;	/* pointer to list of lbuf pointers */
static struct	lbuf	*gstat();
 
static int	lflg;
static int	flags;
static int	err = 0;	/* Contains return code */
 
static int	statreq = 0;
 
static char	*dotp = ".";
static char	*makename();
char	*ctime();
 
static long	year, now;
 
static int	curcol;
static int	compar();
 
int getdir (file, full, fp)
char *file;
int full;
FILE *fp;
{
    register struct lbuf *ep;
    struct lbuf	lb;
    int	i;
    long time();
    char *cp;
#ifdef MPX
    char *sp;
#endif
    char dname[PATH_MAX], fname[PATH_MAX];
#ifndef MPX
    struct stat statb;
#endif
 
    curcol = maxn = nargs = err = nomocore = lflg = statreq = 0;
    flags = nfiles = 0;
    flist = 0;
 
    dname[0] = fname[0] = '\0';
    /* default a null name to * */
    if (file == NULL || *file == '\0')
    	file = "*";
    /* split path into directory and filename */
    if ((cp = strrchr(file, '/')) == NULL) {
    	strcpy(dname, ".");
    	strcpy(fname, file);
    } else {
    	strcpy(dname, file);
#ifdef MPX
    	/* see how many '/'s, must be at least 2 */
    	sp = file;
    	for (i=0; *sp; sp++)
    	    if (*sp == '/')i++;
    	if (i > 3)return -1;	/* error if not 1, 2 or 3 */
    	/* i = 1 */		/* we have just a volume name */
    	/* i = 2 */		/* we have a volume/directory name */
    	if (i == 1 || i == 2) {	/* we have /vol or /vol/dir */
    	    cp = " *";
    	}
    	if (i == 3) {		/* we have vol/dir/filename */
    	    dname[cp - file] = '\0';	/* trim to directory name */
    	}
#else
    	if ((i = stat (file, &statb)) >= 0) {
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
#ifdef OLD
    i = strlen(file);
    if (i == 1 && *file == '*')*file = '.';
    if (i >=2 ) {
    	if (file[i] == '*' && file[i-1] == '/')
    	    file[i-1] = '\0';
    }
#endif
 
#ifdef MPX
    for (i=0; fname[i]; i++)
    	if (isupper(fname[i]))
    	    fname[i] = tolower(fname[i]);
#endif
 
#ifdef DBUG
printf("getdir called with file %s\n", file);
printf("split into dname=%s, fname=%s\n", dname, fname);
#endif
 
    lb.lmtime = time((long *) NULL);
    year = lb.lmtime - 6L*30L*24L*60L*60L; /* 6 months ago */
    now = lb.lmtime + 60;
    if (full) {
    	lflg++;
    	statreq++;
    }
 
    /* allocate space for flist and the associated */
    /* data structures (lbufs) */
    maxfils = 128;
    if ((flist = (struct lbuf **)calloc(1, (unsigned)
    	(maxfils * sizeof(struct lbuf *)))) == NULL) {
    	fprintf(fp, "ls: out of memory\n");
    	free_clist();
    	return (-1);	/* return error */
    }
 
    for (i=0; i < 1; i++) {
    	if ((ep = gstat(fp))==NULL) {
    	    err = -1;
    	    continue;
    	}
    	ep->ln.namep = (*dname ? dname : dotp);
    	ep->lflags |= ISARG;
#ifndef MPX1X
    	mstat(ep, (*dname ? dname : dotp));
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
    	nargs++;	/* count good arguments stored in flist */
    }
 
    qsort (flist, (unsigned)nargs, sizeof(struct lbuf *), compar);
 
    for (i=0; i<nargs; i++)
    	if (flist[i]->ltype=='d')
    	    break;
    pem (&flist[0], &flist[i], fp);
    for (; i<nargs; i++) {
    	pdirectory (flist[i]->ln.namep, 0, nargs, fp, fname, full);
 
    	while (dfirst || cdfirst) {
#ifdef NOTNOW
printf("getdir: got to use dfirst\n");
#endif
    	    /* Place direct subdirs on front in right order */
    	    while (cdfirst) {
    		/* reverse cdfirst onto front of dfirst */
    		dtemp = cdfirst;
    		cdfirst = cdfirst -> dc_next;
    		dtemp -> dc_next = dfirst;
    		dfirst = dtemp;
    	    }
    	    /* take off first dir on dfirst & print it */
    	    dtemp = dfirst;
    	    dfirst = dfirst->dc_next;
    	    pdirectory (dtemp->dc_name, 1, nargs, fp, fname, full);
    	    if (dtemp->dc_name)
    		free (dtemp->dc_name);
    	    if (dtemp)
    		free ((char *)dtemp);
    	}
    }
    /* Give back all the memory we temporarily needed... */
    free_clist();
 
    return (err);
    /*NOTREACHED*/
}
 
/*
 * pdirectory: print the directory name, labelling it if title is
 * nonzero, using lp as the place to start reading in the dir.
 */
static void pdirectory (name, title, lp, fp, fname, full)
char *name;
int title;
int lp;
FILE *fp;
char * fname;
int full;
{
	register int j;
 
#ifdef DBUG
printf("pdirectory name = %s, file = %s\n", name, fname);
#endif
	curdir = name;
	if (title) {
		putc ('\n', fp);
		pprintf (name, ":", fp);
		new_line (fp);
	}
	nfiles = lp;
	rddir (name, fp, fname);
    	if (full)
    	    for (j=lp; j<nfiles; j++) {
    		mstat (flist[j], makename (name, flist[j]->ln.lname));
    	    }
#ifdef DBUG
    	for (j=lp; j<nfiles; j++) {
printf("file entry %d file = %s\n", j, flist[j]->ln.lname);
    	}
#endif
	qsort (&flist[lp],(unsigned)(nfiles - lp),
    		sizeof(struct lbuf *),compar);
	pem (&flist[lp], &flist[nfiles], fp);
}
 
/*
 * pem: print 'em.  Print a list of files (e.g. a directory) bounded
 * by slp and lp.
 */
static void pem (slp, lp, fp)
register struct lbuf **slp, **lp;
FILE *fp;
{
    register struct lbuf **ep;
 
    for (ep = slp; ep < lp; ep++) {
    	pentry (*ep, fp);
    }
    new_line (fp);
    return;
}
 
static void pentry (ap, fp)	/*  print one output entry;
    		 *  print uid/gid instead of
    		 *  user/group name;
    		 */
struct lbuf *ap;
FILE *fp;
{
#ifdef HUH
    struct {
    	char	dminor, dmajor;
    };
#endif
    register struct lbuf *p;
    register char *cp;
 
    p = ap;
#ifdef DBUG
printf("enter pentry: ap = %x, fp = %d\n", ap, fp);
printf("enter pentry: ISARG = %d, namep = %x\n",
    p->lflags & ISARG, p->ln.namep);
printf("enter pentry: ISARG = %d, lname = %s\n",
p->lflags & ISARG, p->ln.lname);
#endif
    column (fp);
    if (lflg) {
    	putc (p->ltype, fp);
    	curcol++;
    	pmode (p->lflags, fp);
#ifndef MPX1X
    	curcol += fprintf (fp, "%4x ", p->lnl);
#ifndef MPX
    	curcol += fprintf (fp, "%-6u", p->luid);
    	curcol += fprintf (fp, "%-6u", p->lgid);
#endif
    	if (p->ltype=='b' || p->ltype=='c')
    	    curcol += fprintf (fp, "%3d,%3d",
    		 ((int)p->lsize>>8), ((int)p->lsize&0xff));
    	else
    	    curcol += fprintf (fp, "%7ld", p->lsize);
#else
    	curcol += fprintf (fp, "%4d ", p->lgid);
    	curcol += fprintf (fp, "%-9x", p->luid);
    	curcol += fprintf (fp, "%-9x", p->lnl);
    	curcol += fprintf (fp, "%7ld", p->lsize);
    	p->lmtime = now - 60;
#endif
    	cp = ctime (&p->lmtime);
    	if ((p->lmtime < year) || (p->lmtime > now))
    	    curcol += fprintf (fp, " %-7.7s %-4.4s ", cp+4, cp+20);
    	else
    	    curcol += fprintf (fp, " %-12.12s ", cp+4);
    }
#ifdef DBUG
printf("pentry: ISARG = %d, namep = %x, lname = %s\n",
p->lflags & ISARG, p->ln.namep, p->ln.lname);
#endif
    if (p->lflags & ISARG) {
        curcol += fprintf (fp, "%s",p->ln.namep);
    }
    else {
        curcol += fprintf (fp, "%s",p->ln.lname);
    }
}
 
/* these arrays are declared static to allow initializations */
static int	m0[] = { 1, S_IREAD>>0, 'r', '-' };
static int	m1[] = { 1, S_IWRITE>>0, 'w', '-' };
static int	m2[] = { 3, S_ISUID|S_IEXEC, 's', S_IEXEC, 'x',
		 S_ISUID, 'S', '-' };
static int	m3[] = { 1, S_IREAD>>3, 'r', '-' };
static int	m4[] = { 1, S_IWRITE>>3, 'w', '-' };
static int	m5[] = { 3, S_ISGID|(S_IEXEC>>3),'s', S_IEXEC>>3,
		'x', S_ISGID,'l', '-'};
static int	m6[] = { 1, S_IREAD>>6, 'r', '-' };
static int	m7[] = { 1, S_IWRITE>>6, 'w', '-' };
static int	m8[] = { 3, S_ISVTX|(S_IEXEC>>6),'t', S_IEXEC>>6,
		'x', S_ISVTX,'T', '-'};
 
static int  *m[] = { m0, m1, m2, m3, m4, m5, m6, m7, m8};
 
/* print various r,w,x permissions
 */
static void pmode (aflag, fp)
int aflag;
FILE *fp;
{
	register int **mp;
 
	flags = aflag;
	for (mp = &m[0]; mp < &m[sizeof(m)/sizeof(m[0])];)
		selectx (*mp++, fp);
}
 
static void selectx (pairp, fp)
register int *pairp;
FILE *fp;
{
    register int n;
 
    n = *pairp++;
    while (n-->0) {
    	if ((flags & *pairp) == *pairp) {
    	    pairp++;
    	    break;
    	} else {
    	    pairp += 2;
    	}
    }
    putc (*pairp, fp);
    curcol++;
}
 
/*
 * column: get to the beginning of the next column.
 */
static void column (fp)
FILE *fp;
{
 
    if (curcol == 0)
    	return;
    putc ('\n', fp);
    curcol = 0;
    return;
}
 
static void new_line (fp)
FILE *fp;
{
    if (curcol) {
    	putc('\n',fp);
    	curcol = 0;
    }
}
 
/*  read each filename in directory dir and store its
 *  status in flist[nfiles]
 *  use makename() to form pathname dir/filename;
 */
static void rddir (tdir, fp, fname)
char *tdir;
FILE *fp;
char * fname;
{
    struct dirent *dentry;
    DIR *dirf;
    register int j;
    register struct lbuf *ep;
 
#ifdef DBUG
printf("rddir dir %s, fname %s\n", tdir, fname);
#endif
/* strcat(tdir, "/"); */
    if ((dirf = opendir(tdir)) == NULL) {
    	fflush (fp);
    	fprintf (fp, "can not access directory %s\n", tdir);
#ifdef DBUG
printf("rddir can not read dir %s, fname %s\n", tdir, fname);
#endif
    	err = -1;
    	return;
    } else {
    	while ((dentry = readdir(dirf))) {
    	    if (dentry->d_name[0]=='.')
    		    /* check for directory items '.', '..',
    		     * and items without valid inode-number;
    		     */
    		    continue;
#ifdef DBUG
printf("rddir: wildmat call d_name %s, fname %s\n", dentry->d_name, fname);
#endif
    	    if (!(wildmat(dentry->d_name, fname, 0)))
    		    continue;
    	    ep = gstat (fp);
    	    if (ep==NULL)
    		    continue;
    	    else {
    		    ep->lnum = dentry->d_ino;
    		    for (j=0; dentry->d_name[j] != '\0'; j++)
    		        ep->ln.lname[j] = dentry->d_name[j];
    		    ep->ln.lname[j] = '\0';
    	    }
    	}
#ifdef DBUG
printf("rddir: closing directory %s\n", tdir);
#endif
    	(void) closedir (dirf);
    }
#ifdef DBUG
printf("rddir: returning dir = %s\n", tdir);
#endif
}
 
/* recomputes tblocks;
 * stores a pointer in flist[nfiles] and
 * returns that pointer;
 * returns NULL if failed;
 */
static struct lbuf *
gstat (fp)
FILE *fp;
{
    register struct lbuf *rep;
 
    if (nomocore)
    	return(NULL);
    else if (nfiles >= maxfils) {
        /* all flist/lbuf pair assigned files,
    	 * time to get some more space */
    	maxfils += 64;
    	if ((flist = (struct lbuf **)realloc ((char *)flist,
    	  (unsigned)(maxfils * sizeof(struct lbuf *)))) == NULL) {
    	    fprintf(fp, "ls: out of memory\n");
    	    nomocore = 1;
    	    return(NULL);
    	}
    }
 
    /* nfiles is reset to nargs for each directory
     * that is given as an argument maxn is checked
     * to prevent the assignment of an lbuf to a flist entry
     * that already has one assigned.
     */
    if (nfiles >= maxn) {
    	rep = (struct lbuf *)calloc(1, (unsigned)(sizeof(struct lbuf)));
    	if (rep == NULL) {
    	    fprintf(fp, "ls: out of memory\n");
    	    nomocore = 1;
    	    return(NULL);
    	}
    	flist[nfiles++] = rep;
    	maxn = nfiles;
    } else {
    	rep = flist[nfiles++];
    }
    rep->lflags = 0;
    return(rep);
}
 
static void mstat(rep, file)
register struct lbuf *rep;
char *file;
{
    int tmp;
    struct stat statb;
 
#ifdef DBUG
printf("mstat: file = %s\n", file);
#endif
    if ((tmp = stat (file, &statb)) < 0) {
#ifdef DBUG
printf("mstat - stat error for file %s, ret = %x\n", file, tmp);
#endif
    	return;
    } else {
    	rep->lnum = statb.st_ino;
    	rep->lsize = statb.st_size;
#ifdef DBUG
printf("mstat - stat directory found %x for file %s\n", statb.st_mode&S_IFMT, file);
#endif
    	switch (statb.st_mode&S_IFMT) {
 
    	    case 0:
    	    case S_IFDIR:
    		rep->ltype = 'd';
#ifdef DBUG
printf("mstat - stat directory found for file %s\n", file);
#endif
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
    	rep->lmtime = statb.st_mtime;
    }
    return;
}
 
/* returns pathname of the form dir/file;
 *  tdir is a null-terminated string;
 */
static char *makename(tdir, file)
char *tdir, *file;
{
    static char dfile[PATH_MAX];  /*  Maximum length of a
    				   *  file/dir name in ls-command;
    				   *  dfile is static as this is returned
    				   *  by makename();
    				   */
    register char *dp, *fp;
    register int i;
 
#ifdef DBUG
    printf("makename entry dir %s, file %s\n", tdir, file);
#endif
    dp = dfile;
    fp = tdir;
    while (*fp)
    	*dp++ = *fp++;
    if (dp > dfile && *(dp - 1) != '/')
    	*dp++ = '/';
    fp = file;
    for (i=0; *fp != '\0'; i++)
    	*dp++ = *fp++;
    *dp = '\0';
#ifdef DBUG
    printf("makename returns %s\n", dfile);
#endif
    return (dfile);
}
 
/* return >0 if item pointed by pp2 should appear first */
static int compar (pp1, pp2)
struct lbuf **pp1, **pp2;
{
    register struct lbuf *p1, *p2;
 
    p1 = *pp1;
    p2 = *pp2;
    /* compare two names in ls-command one of which is file
     *  and the other is a directory;
     *  this portion is not used for comparing files within
     *  a directory name of ls-command;
     */
    if (p1->lflags & ISARG && p1->ltype=='d') {
    	if (!(p2->lflags & ISARG && p2->ltype=='d'))
    	    return (1);
    }
    else {
    	if (p2->lflags & ISARG && p2->ltype=='d')
    	    return (-1);
    }
    return (strcmp(p1->lflags & ISARG? p1->ln.namep: p1->ln.lname,
    	p2->lflags & ISARG? p2->ln.namep: p2->ln.lname));
}
 
static void pprintf (s1, s2, fp)
char *s1, *s2;
FILE *fp;
{
    register char *s;
    register int   c;
    int i;
 
    for (s = s1, i = 0; i < 2; i++, s = s2)
    	while ((c = *s++)) {
    	    curcol++;
    	    putc (c, fp);
    	}
}
 
static void
free_clist()
{
    int i;
 
    while (dfirst) {
    	dtemp = dfirst;
    	dfirst = dfirst->dc_next;
    	if (dtemp->dc_name)
    	    free (dtemp->dc_name);
    	if (dtemp)
    	    free ((char *)dtemp);
    }
    for (i=0; i < maxn; i++) {
        if (flist[i])
    	    free(flist[i]);
    }
    free (flist);
}
 
