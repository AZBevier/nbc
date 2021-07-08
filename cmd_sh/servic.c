/*~!servic.c*/
/* Name:  servic.c Part No.: _______-____r
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

#ident	"$Id: servic.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

/* #define NOTNOW */

#include	"defs.h"
#include	<errno.h>
#include	"hash.h"
#ifdef mpx
#include	<stdio.h>
#endif
#include    <string.h>
#ifndef mpx
#include <wait.h>
#include <unistd.h>
#include <fcntl.h>
#endif
extern int errno;

char iostr[128];
#define ARGMK	01

extern void failed();
extern void makearg();
extern void clearup();
extern void exitsh();
extern int expand();
extern char *sysmsg[];
extern short topfd;
extern int cmdtype;
extern int cf();
extern int stoi();
extern int any();
extern void prc();
extern void prn();
extern void prp();
extern void prs();
extern void setargs();
extern void rename();
extern void subst();
extern int create();
extern int savefd();
extern int poptemp();
extern int tmpfil();
extern int chkopen();

static void gsort();
int getarg();
static int split();
void trim();
static char *execs();

/*
 * service routines for `execute'
 */
int initio(iop, save)
struct ionod *iop;
int save;
{
    extern long lseek();
    register char *ion;
    register int iof, fd;
    int ioufd;
    short lastfd;
    char *iosptr = iostr;
    *iosptr = '\0';

#ifdef NOTNOW1
printf("initio: entry iop = %x, save = %x, topfd = %d, flags = %x, cmdtype = %x\n",
 iop, save, topfd, flags, cmdtype);
#endif
    lastfd = topfd;
    while (iop) {
    	iof = iop->iofile;
    	ion = mactrim(iop->ioname);
    	ioufd = iof & IOUFD;
#ifdef NOTNOW1
printf("initio: while iofx = %x, ion = %s, ioufd = %x flags = %x\n",
iof, ion, ioufd, flags);
#endif

    	if (*ion && (flags & noexec) == 0) {
    	    if (save) {
#ifdef NOTNOW1
printf("initio: saving fd = %d\n", ioufd);
#endif
    	    	fdmap[topfd].org_fd = ioufd;
    	    	fdmap[topfd++].dup_fd = savefd(ioufd);
    	    }

    	    if (iof & IODOC) {
    	    	struct tempblk tb;
#ifdef NOTNOW1
printf("initio: IODOC iof = %x, ion = %s, ioufd = %x\n",iof, ion, ioufd);
#endif

    	    	subst(chkopen(ion), (fd = tmpfil(&tb)));

    	    	poptemp();	/* pushed in tmpfil() --
			   	bug fix for problem with
			   	in-line scripts
				*/

    	    	fd = chkopen(tmpout);
    	    	unlink(tmpout);
    	    } else if (iof & IOMOV) {
#ifdef NOTNOW1
printf("initio: IOMOV iof = %x, ion = %s, ioufd = %x\n",iof, ion, ioufd);
#endif
    	    	if (eq(minus, ion)) {
    	    	    fd = -1;
    	    	    close(ioufd);
    	    	} else if ((fd = stoi(ion)) >= USERIO)
    	    	    failed(ion, badfile);
    	    	else
    	    	    fd = dup(fd);
    	    } else if (iof & IORDW) {
#ifdef NOTNOW1
printf("initio: IORDW iof = %x, ion = %s, ioufd = %x\n",iof, ion, ioufd);
#endif
/* #ifdef smpx */
    	      if (cmdtype != BUILTIN) {
    		/* stderr redirect */
    		if (iof & IOAPP)
    		    strcpy(iosptr, "2>>");
    		else
    		    strcpy(iosptr, "2>");
    		strcat(iosptr, ion);	/* append file name */
#ifdef smpx
    		fd = -1;
#else
    	        if ((fd = open(ion, 2)) < 0)
    	    	    failed(ion, badopen);
#endif
    	      } else {
/* #else */
    	    	if ((fd = open(ion, 2)) < 0)
    	    	    failed(ion, badopen);
    	      }
/* #endif */
    	    } else if ((iof & IOPUT) == 0) {
#ifdef NOTNOW1
printf("initio: IOPUT iof = %x, ion = %s, ioufd = %x\n",iof, ion, ioufd);
#endif
/* #ifdef smpx */
    	      if (cmdtype != BUILTIN) {
    		/* stdout redirect */
    		if (iof & IOAPP)
    		    strcpy(iosptr, ">>");
    		else
    		    strcpy(iosptr, ">");
    		strcat(iosptr, ion);	/* append file name */
#ifdef smpx
    		fd = -1;
#else
    	    	fd = chkopen(ion);
#endif
    	     } else {
/* #else */
    	    	fd = chkopen(ion);
    	     }
/* #endif */
    	    }
#ifndef mpx
    	    else if (flags & rshflg)
    	    	failed(ion, restricted);
#endif
    	    else if (iof & IOAPP) {
#ifdef NOTNOW1
printf("initio: IOAPP iof = %x, ion = %s, ioufd = %x\n",iof, ion, ioufd);
#endif
/* #ifdef smpx */
    	      if (cmdtype != BUILTIN) {
    		/* stdout redirect */
    		strcpy(iosptr, ">>");
    		strcat(iosptr, ion);	/* append file name */
#ifdef smpx
    		fd = -1;
#else
    	        if ((fd = open(ion, 1)) >= 0)
    	    	    lseek(fd, 0L, 2);
#endif
    	      } else {
/* #else */
    	        if ((fd = open(ion, 1)) >= 0)
    	    	    lseek(fd, 0L, 2);
    	      }
/* #endif */
    	    }
    	    else {
#ifdef NOTNOW1
printf("initio: create iof = %x, ion = %s, ioufd = %x\n",iof, ion, ioufd);
#endif
/* #ifdef smpx */
    	      if (cmdtype != BUILTIN) {
    		/* stdout redirect */
    		strcpy(iosptr, ">");
    		strcat(iosptr, ion);	/* append file name */
#ifdef smpx
    		fd = -1;
#else
    	    	fd = create(ion);
#endif
    	      } else {
/* #else */
    	    	fd = create(ion);
    	      }
/* #endif */
    	    }
    	    if (fd >= 0) {
#ifdef NOTNOW1
printf("initio: rename fd = %d, ion = %s, ioufd = %d\n", fd, ion, ioufd);
#endif
#ifdef mpx
    	        if (save)
    	    	  fdmap[topfd-1].dup_fd = fd;
#endif
    	    	rename(fd, ioufd);
    	    }
    	}

    	iop = iop->ionxt;
    }
#ifdef NOTNOW1
printf("initio: exit fd = %x, ion = %s, iostr = %s, lastfd = %d, flags = %x\n",
  fd, ion, iostr, lastfd, flags);
#endif
    return(lastfd);
}


char *simple(s)
char *s;
{
    char *sname;

    sname = s;
    while (1) {
    	if (any('/', sname))
    	    while (*sname++ != '/')
    	    	;
    	else
    	    return(sname);
    }
}


char *getpath(s)
char *s;
{
    register char *path;

    if (any('/', s) || any(('/' | QUOTE), s)) {
    	if (flags & rshflg) {
    	    failed(s, restricted);
    	    /*NOTREACHED*/
    	} else {
#ifdef NOTNOW
    	    printf("getpath: s = %s nullstr = %s\n", s, nullstr);
#endif
    	    return(nullstr);
    	}
    } else if ((path = pathnod.namval) == 0) {
#ifdef NOTNOW
    	printf("getpath: s = %s path = %s defpath = %s\n", s, path, defpath);
#endif
    	return(defpath);
    } else {
#ifdef NOTNOW
    	printf("getpath: s = %s path = %s\n", s, path);
#endif
    	return(cpystak(path));
    }
    /*NOTREACHED*/
    return(0);
}


int pathopen(path, name)
register char *path, *name;
{
    register int f;

    do
     {
    	path = catpath(path, name);
    } while ((f = open(curstak(), 0)) < 0 && path);
    return(f);
}


char *catpath(path, name)
register char *path;
char *name;
{
    /*
     * leaves result on top of stack
     */
    register char *scanp = path;
    register char *argp = locstak();
#ifdef TILDE_SUB
    char *save = argp;
    char *cp;
#endif

    while (*scanp && *scanp != COLON)
    	*argp++ = *scanp++;
#ifdef TILDE_SUB
    /* try a tilde expansion */
    *argp = '\0';
    if ( *save == SQUIGGLE && (cp = homedir( save + 1 )) != nullstr ) {
    	movstr( cp, save );
    	argp = save + length( save ) - 1;
    }
#endif
    if (scanp != path)
    	*argp++ = '/';
    path = *scanp ? scanp + 1 : 0;
    scanp = name;
    while ((*argp++ = *scanp++))
    	;
    return(path);
}


char *nextpath(path)
register char *path;
{
    register char *scanp = path;

    while (*scanp && *scanp != COLON)
    	scanp++;

    return * scanp ? scanp + 1 : 0;
}


static char *xecmsg;
static char **xecenv;

int execa(at, pos)
char *at[];
short pos;
{
    register char *path = 0;
    register char **t = at;
    int cnt;

#ifdef NOTNOW
printf("execa: entry *at = %s pos = %x\n", *at, pos);
#endif
#ifdef NOTNOW1
printf("execa: flags&noexec = %x, cmdadr = %s\n", flags&noexec, cmdadr);
#endif
    if ((flags & noexec) == 0) {
    	xecmsg = notfound;
    	path = getpath(*t);
#ifdef NOTNOW
printf("execa: path = %s *t = %s, pos = %x, iostr(%s)\n",
 path, *t, pos, iostr);
#endif
    	xecenv = msetenv();
#ifdef NOTNOW1
printf("execa: xecenv = %s path = %s iostr(%s)\n", *xecenv, path, iostr);
#endif

    	if (pos > 0) {
	    cnt = 1;
    	    while (cnt != pos) {
    	    	++cnt;
    	    	path = nextpath(path);
    	    }
#ifdef NOTNOW
printf("execa: calling execs path = %s, *t = %s\n", path, *t);
#endif
#ifndef mpx
    	    execs(path, t);
#else
    	    if(execs(path, t) == 0) {
#ifdef NOTNOW
printf("execa: exit0, prompt (%s)\n", ps1nod.namval);
#endif
    		return;
    	    }
#endif
    	    path = getpath(*t);
    	}
#ifdef NOTNOW
fprintf(stderr,"execa:1 calling execs path = %s, *t = %s, iostr(%s)\n",
 path, *t, iostr);
#endif
    	while (path = execs(path, t))
#ifdef NOTNOW
fprintf(stderr,"execa:1 calling execs path = %s, *t = %s, iostr(%s)\n",
 path, *t, iostr);
#else
     	    ;
#endif
#ifdef mpx
    	if(path == 0) {
#ifdef NOTNOW
fprintf(stderr,"execa: exit1, iostr(%s)\n", iostr);
#endif
    	    return;
    	}
#endif
    	failed(*t, xecmsg);
    }
#ifdef NOTNOW
printf("execa: exit0\n");
#endif
}

#ifdef smpx
#define NENV  300
extern char **environ;
char **oldenvir = (char **)NULL;

/*
 * This routine frees the temp environment during exec.
 */

void free_env()
{
  char **ep;
  char *p;

  if (environ == NULL)return;
  environ = oldenvir;
  oldenvir = 0;

}

/*
 * This routine is called just before an exec.
 */

void set_env (ne)
char **ne;
{
    oldenvir = environ;
    environ=ne;
}
#endif

#ifdef mpx
char *tmpt[512];
#endif

static char *execs(ap, t)
char *ap;
register char *t[];
{
    register char *p, *prefix;
#ifdef mpx
    int stat;
    int ii = 0;
    char **xx;
#endif

#ifdef NOTNOW1
fprintf(stderr,"execs: entry ap = %s, *t0 = %s, iostr(%s)\n",
 ap, t[0], iostr);
fflush(stderr);
#endif
    prefix = catpath(ap, t[0]);
    trim(p = curstak());
#ifdef NOTNOW
fprintf(stderr,"execs: entry1 iostr(%s), prefix = %s, p = %s\n", iostr, prefix, p);
fflush(stderr);
#endif
#ifndef mpx
    sigchk();
    execve(p, &t[0] , xecenv);
#else
#ifdef NOTNOW
fprintf(stderr,"execs: p = %s, t0 = %s, iostr[0,1] = %x,%x\n", p, *t, iostr[0], iostr[1]);
#endif
    while (t[ii])
    	tmpt[ii] = t[ii++];
    tmpt[ii] = (char *)0;	/* null terminate */

    if (iostr[0]) {
#ifdef NOTNOW
fprintf(stderr,"execs: p = %s, t0 = %s, iostr = %s\n", p, *t, iostr);
#endif
    	tmpt[ii] = iostr;		/* setup the I/O */
    	tmpt[ii+1] = (char *)0;
    }
#ifdef NOTNOW1
fprintf(stderr,"execs: before vexecv p = %s *t0 = %s *t1 = %s\n",
 p, t[0], t[1]);
fprintf(stderr,"execs: before vexecv p = %s *tmp0 = %s *tmp1 = %s\n",
 p, tmpt[0], tmpt[1]);
fflush(stderr);
#endif
#ifdef NOTNOW1
/* */
xx = tmpt;
ii = 0;
while (xx[ii])
  fprintf(stderr,"exec: args[%d] = %s\n", ii, xx[ii++]);
#endif
#ifdef NOTNOW1
xx = xecenv;
ii = 0;
while (xx[ii])
  fprintf(stderr,"exec: env[%d] = %s\n", ii, xx[ii++]);
fflush(stderr);
/* */
#endif
#ifdef smpx
#ifdef NOTNOW1
fprintf(stderr,"execs: before vexecv p = %s *tmp0 = %s *tmp1 = %s\n",
 p, tmpt[0], tmpt[1]);
fflush(stderr);
#endif
    set_env(xecenv);
    stat = vexecv(p, tmpt);
    free_env();
#else
#ifdef NOTNOW1
fprintf(stderr,"execs: before vexecv p = %s *t0 = %s *t1 = %s\n",
 p, t[0], t[1]);
fflush(stderr);
#endif
    ii = fork();
    if (ii == -1)
    	error(nofork);
    if (ii == 0) {
/*    	stat = execv(p, tmpt); */
    	stat = execv(p, t);
    	error(nofork);
    }
    while (ii != wait(&stat))
    	;
#endif /* smpx */

#ifdef NOTNOW
fprintf(stderr,"execs: vexecp %s stat = %x\n", p, stat);
#endif
    if (iostr[0]) {
/*    	t[ii-1] = (char *)0; */
    	iostr[0] = '\0';
    }
    if (stat == 0) {
    	/*
	 * set up new args
	 */

    	setargs(t);
    	return(0);
    }
#endif
    switch (errno) {
    case ENOEXEC:		/* could be a shell script */
#ifdef NOTNOW
fprintf(stderr,"execs: ENOEXEC errno=%x\n", errno);
#endif
    	funcnt = 0;
    	flags = 0;
    	*flagadr = 0;
    	comdiv = 0;
    	ioset = 0;
    	clearup();	/* remove open files and for loop junk */
    	if (input)
    	    close(input);
    	input = chkopen(p);

    	/*
	 * set up new args
	 */

    	setargs(t);
    	longjmp(subshell, 1);

    case ENOMEM:
    	failed(p, toobig);

    case E2BIG:
    	failed(p, arglist);

    case ETXTBSY:
    	failed(p, txtbsy);

    case ENOENT:
    	if(prefix == 0)
    	   failed(p, badexec);
    	return(prefix);
    default:
    	xecmsg = badexec;
/*    	failed(p, badexec); */
/*    	failed(p, "can't execute non NBC task"); */
    	failed(p, "Unknown activation error");
    }
#ifdef NOTNOW
fprintf(stderr,"execs: exit\n");
#endif
    return(0);
}


#ifndef mpx
/*
 * for processes to be waited for
 */
#define MAXP 20
static int pwlist[MAXP];
static int pwc;

void postclr()
{
    register int *pw = pwlist;

    while (pw <= &pwlist[pwc]) {
    	*pw++ = 0;
    }
    pwc = 0;
}


void post(pcsid)
int pcsid;
{
    register int *pw = pwlist;

    if (pcsid) {
    	while (*pw)
    	    	pw++;
    	if (pwc >= MAXP - 1)
    	    pw--;
    	else
    	 {
    	    pwc++;
    	}
    	*pw = pcsid;
    }
}


void await(i, bckg)
int i, bckg;
{
    int rc = 0, wx = 0;
    int w;
    int ipwc = pwc;
    	post(i);
    	while (pwc) {
    	    register int p;
    	    register int sig;
    	    int w_hi;
    	    int found = 0;

    	     {
    	    	register int *pw = pwlist;

    	    	p = wait(&w);
    	    	if (wasintr) {
    	    	    wasintr = 0;
    	    	    if (bckg) {
    	    	    	break;
    	    	    }
    	    	}
    	    	while (pw <= &pwlist[ipwc]) {
    	    	    if (*pw == p) {
    	    	    	*pw = 0;
    	    	    	pwc--;
    	    	    	found++;
    	    	    } else
    	    	    	pw++;
    	    	}
    	    }
    	    if (p == -1) {
    	    	if (bckg) {
    	    	    register int *pw = pwlist;

    	    	    while (pw <= &pwlist[ipwc] && i != *pw)
    	    	    	pw++;
    	    	    if (i == *pw) {
    	    	    	*pw = 0;
    	    	    	pwc--;
    	    	    }
    	    	}
    	    	continue;
    	    }
    	    w_hi = (w >> 8) & LOBYTE;
    	    if (sig = w & 0177) {
    	    	if (sig == 0177) {	/* ptrace! return */
    	    	    sig = w_hi;
    	    	    prs(ptrcolon);
    	    	}
    	    	if (sysmsg[sig]) {
    	    	    if (i != p || (flags & prompt) == 0) {
    	    	    	prp();
    	    	    	prn(p);
    	    	    	blank();
    	    	    }
    	    	    prs(sysmsg[sig]);
    	    	    if (w & 0200)
    	    	    	prs(coredump);
    	    	}
    	    	newline();
    	    }
    	    if (rc == 0 && found != 0)
    	    	rc = (sig ? sig | SIGFLG : w_hi);
    	    wx |= w;
    	    if (p == i) {
    	    	break;
    	    }
    	}
    if (wx && flags & errflg)
    	exitsh(rc);
    flags |= eflag;
    exitval = rc;
    exitset();
}
#endif /* mpx */


BOOL		nosubst;

void trim(at)
char *at;
{
    register char *p;
    register char *ptr;
    register char c;
    register char q = 0;

    if (p = at) {
    	ptr = p;
    	while (c = *p++) {
    	    if (*ptr = c & STRIP)
    	    	++ptr;
    	    q |= c;
    	}

    	*ptr = 0;
    }
    nosubst = q & QUOTE;
}


char *mactrim(s)
char *s;
{
    register char *t = macro(s);

    trim(t);
    return(t);
}


char **scan(argn)
int argn;
{
    register struct argnod *argp = (struct argnod *)(Rcheat(gchain) &~ARGMK);
    register char **comargn, **comargm;

    comargn = (char **)getstak(BYTESPERWORD * argn + BYTESPERWORD);
    comargm = comargn += argn;
    *comargn = ENDARGS;
    while (argp) {
    	*--comargn = argp->argval;

    	trim(*comargn);
#ifdef NOTNOW
printf("scan0: argval = %s\n", argp->argval);
#endif
    	argp = argp->argnxt;

    	if (argp == 0 || Rcheat(argp) & ARGMK) {
    	    gsort(comargn, comargm);
    	    comargm = comargn;
    	}
    	/* Lcheat(argp) &= ~ARGMK; */
    	argp = (struct argnod *)(Rcheat(argp) & ~ARGMK);
    }
    return(comargn);
}


static void gsort(from, to)
char *from[], *to[];
{
    int k, m, n;
    register int i, j;

    if ((n = to - from) <= 1)
    	return;
    for (j = 1; j <= n; j *= 2)
    	;
    for (m = 2 * j - 1; m /= 2; ) {
    	k = n - m;
    	for (j = 0; j < k; j++) {
    	    for (i = j; i >= 0; i -= m) {
    	    	register char **fromi;

    	    	fromi = &from[i];
    	    	if (cf(fromi[m], fromi[0]) > 0) {
    	    	    break;
    	    	} else
    	    	 {
    	    	    char *s;

    	    	    s = fromi[m];
    	    	    fromi[m] = fromi[0];
    	    	    fromi[0] = s;
    	    	}
    	    }
    	}
    }
}


/*
 * Argument list generation
 */
int getarg(ac)
struct comnod *ac;
{
    register int count = 0;
    register struct argnod *argp;
    register struct comnod *c;

    if (c = ac) {
    	argp = c->comarg;
    	while (argp) {
    	    count += split(macro(argp->argval));
#ifdef NOTNOW
printf("getarg: argval = %s\n", argp->argval);
#endif
    	    argp = argp->argnxt;
    	}
    }
    return(count);
}


static int split(s)		/* blank interpretation routine */
register char *s;
{
    register char *argp;
    register int c;
    int count = 0;

#ifdef NOTNOW
printf("split: s = %s\n", s);
#endif
    for (; ; ) {
    	sigchk();
    	argp = locstak() + BYTESPERWORD;
    	while ((c = *s++, !any(c, ifsnod.namval) && c))
    	    *argp++ = c;
    	if (argp == staktop + BYTESPERWORD) {
    	    if (c) {
    	    	continue;
    	    } else
    	     {
    	    	return(count);
    	    }
    	} else if (c == 0)
    	    s--;
    	/*
	 * file name generation
	 */

    	argp = endstak(argp);

    	if ((flags & nofngflg) == 0 && 
    	  (c = expand(((struct argnod *)argp)->argval, 0)))
    	    count += c;
    	else
    	 {
    	    makearg(argp);
    	    count++;
    	}
    	gchain = (struct argnod *)((int)gchain | ARGMK);
    }
}


