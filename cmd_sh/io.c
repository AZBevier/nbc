/*~!io.c*/
/* Name:  io.c Part No.: _______-____r
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

#ident	"$Id: io.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

/* #define NOTNOW */

#include	"defs.h"
#ifdef RES
#include	"dup.h"
#include	<sys/types.h>
#include	<sys/stat.h>
#else
#include	<fcntl.h>
#endif

#ifdef mpx
#include	<sys/types.h>
#include	<sys/stat.h>
#endif

#ifndef mpx
#include <stdlib.h>
#include <unistd.h>
#endif

extern int length();
extern int failed();
extern int cf();
extern void itos();
extern void chkpr();
extern char nextc();
extern char readc();
extern int error();

void chkpipe();

short topfd;

/* ========	input output and file copying ======== */

void initf(fd)
int fd;
{
    register struct fileblk *f = standin;

#ifdef NOTNOW
printf("initf: fd = %d\n", fd);
#endif
    f->fdes = fd;
    f->fsiz = ((flags & oneflg) == 0 ? FBUFSIZ : 1);
    f->fnxt = f->fend = f->fbuf;
    f->feval = 0;
    f->flin = 1;
    f->xfeof = FALSE;
}


int estabf(s)
register char *s;
{
    register struct fileblk *f;

#ifdef NOTNOW
printf("estabf: fd = %x, file = %s\n", standin->fdes, s);
#endif
    (f = standin)->fdes = -1;
    f->fend = length(s) + (f->fnxt = s);
    f->flin = 1;
    return(f->xfeof = (s == 0));
}


void push(af)
struct fileblk *af;
{
    register struct fileblk *f;

#ifdef NOTNOW
printf("push: fd = %x, file = %s\n", af->fdes, af->fnxt);
#endif
    (f = af)->fstak = standin;
    f->xfeof = 0;
    f->feval = 0;
    standin = f;
}


int pop()
{
    register struct fileblk *f;

#ifdef NOTNOW
printf("pop: fd = %x, file = %s\n", standin->fdes, standin->fnxt);
#endif
    if ((f = standin)->fstak) {
    	if (f->fdes >= 0) {
#ifdef NOTNOW
printf("pop: closing fd = %d\n", f->fdes);
#endif
    	    close(f->fdes);
    	}
    	standin = f->fstak;
    	return(TRUE);
    } else
    	return(FALSE);
}


struct tempblk *tmpfptr;

void pushtemp(fd, tb)
int fd;
struct tempblk *tb;
{
#ifdef NOTNOW
printf("pushtemp: fd = %x\n", fd);
#endif
    tb->fdes = fd;
    tb->fstak = tmpfptr;
    tmpfptr = tb;
}


int poptemp()
{
    if (tmpfptr) {
#ifdef NOTNOW
printf("poptemp: fd = %x\n", tmpfptr->fdes);
#endif
    	close(tmpfptr->fdes);
    	tmpfptr = tmpfptr->fstak;
    	return(TRUE);
    } else
    	return(FALSE);
}



void chkpipe(pv)
int *pv;
{
    if (pipe(pv) < 0 || pv[INPIPE] < 0 || pv[OTPIPE] < 0)
    	error(piperr);
}


int chkopen(idf)
char *idf;
{
    register int rc;

    if ((rc = open(idf, 0)) < 0)
    	failed(idf, badopen);
    	/*NOTREACHED*/
    else
    	return(rc);
#ifdef mpx
    return 0;
#endif
}


void rename(f1, f2)
register int f1, f2;
{
#ifdef RES
    if (f1 != f2) {
    	dup(f1 | DUPFLG, f2);
    	close(f1);
    	if (f2 == 0)
    	    ioset |= 1;
    }
#else
    int fs;

#ifndef mpx
    if (f1 != f2) {
    	fs = fcntl(f2, F_GETFD, 0);
    	close(f2);
    	fcntl(f1, F_DUPFD, f2);
    	close(f1);
    	if (fs == 1)
    	    fcntl(f2, F_SETFD, 1);
    	if (f2 == 0)
    	    ioset |= 1;
    }
#else
#ifndef TESTING
    if (f2 == 1)cstdout = f1;
    if (f2 == 2)cstderr = f1;
#endif
    if (f1 != f2) {
#ifdef NOTNOW
printf("rename: %d to %d\n", f1, f2);
#endif
#ifdef NOTNOW
printf("rename: closing f2 = %d\n", f2);
#endif
#ifdef NOTNOW
printf("rename: closing f1 = %d\n", f1);
#endif
#ifdef TESTING
    	close(f2);
    	f2 = dup(f1);
    	close(f1);
    	if (f2 == 0)
    	    ioset |= 1;
#endif
    }
#ifdef NOTNOW
printf("rename: cstdout %d cstderr %d\n", cstdout, cstderr);
#endif
#endif
#endif
}


int create(s)
char *s;
{
    register int rc;

    if ((rc = creat(s, 0666)) < 0)
    	failed(s, badcreate);
    	/*NOTREACHED*/
    else {
#ifdef NOTNOW
printf("create: fd %d for file %s\n", rc, s);
#endif
    	return(rc);
    }
    /*NOTREACHED*/
#ifdef mpx
    return(0);
#endif
}


int tmpfil(tb)
struct tempblk *tb;
{
    int fd;

    itos(serial++);
    movstr(numbuf, xtmpnam);
    fd = create(tmpout);
    pushtemp(fd, tb);
    return(fd);
}


/*
 * set by trim
 */
extern BOOL		nosubst;
#define			CPYSIZ		512

void copy(ioparg)
struct ionod *ioparg;
{
    register char *cline;
    register char *clinep;
    register struct ionod *iop;
    char c;
    char *ends;
    char *start;
    int fd;
    int i;
    int stripflg;


    if (iop = ioparg) {
    	struct tempblk tb;

    	copy(iop->iolst);
    	ends = mactrim(iop->ioname);
    	stripflg = iop->iofile & IOSTRIP;
    	if (nosubst)
    	    iop->iofile &= ~IODOC;
    	fd = tmpfil(&tb);

    	if (fndef)
    	    iop->ioname = make(tmpout);
    	else
    	    iop->ioname = cpystak(tmpout);

    	iop->iolst = iotemp;
    	iotemp = iop;

    	cline = clinep = start = locstak();
    	if (stripflg) {
    	    iop->iofile &= ~IOSTRIP;
    	    while (*ends == '\t')
    	    	ends++;
    	}
    	for (; ; ) {
    	    chkpr();
    	    if (nosubst) {
    	    	c = readc();
    	    	if (stripflg)
    	    	    while (c == '\t')
    	    	    	c = readc();

    	    	while (!eolchar(c)) {
    	    	    *clinep++ = c;
    	    	    c = readc();
    	    	}
    	    } else
    	     {
    	    	c = nextc(*ends);
    	    	if (stripflg)
    	    	    while (c == '\t')
    	    	    	c = nextc(*ends);

    	    	while (!eolchar(c)) {
    	    	    *clinep++ = c;
    	    	    c = nextc(*ends);
    	    	}
    	    }

    	    *clinep = 0;
    	    if (eof || eq(cline, ends)) {
    	    	if ((i = cline - start) > 0)
    	    	    write(fd, start, i);
    	    	break;
    	    } else
    	    	*clinep++ = NL;

    	    if ((i = clinep - start) < CPYSIZ)
    	    	cline = clinep;
    	    else
    	     {
    	    	write(fd, start, i);
    	    	cline = clinep = start;
    	    }
    	}

    	poptemp();	/* pushed in tmpfil -- bug fix for problem
    			deleting in-line scripts */
    }
}


void link_iodocs(i)
struct ionod *i;
{
    while (i) {
    	free(i->iolink);

    	itos(serial++);
    	movstr(numbuf, xtmpnam);
    	i->iolink = make(tmpout);
    	link(i->ioname, i->iolink);

    	i = i->iolst;
    }
}


void swap_iodoc_nm(i)
struct ionod *i;
{
    while (i) {
    	free(i->ioname);
    	i->ioname = i->iolink;
    	i->iolink = 0;

    	i = i->iolst;
    }
}


int savefd(fd)
int fd;
{
    register int f;

#ifdef RES	/* bug fix */
    for ( f = 10; f <= INIO; ++f ) {
    	struct stat statb;

    	if (fstat(fd, &statb) != 0) {	/* if already in use, try another */
    	    dup(fd | DUPFLG, f);
    	    return f;
    	}
    }
    return -1;	/* no free file descriptors */
#else
#ifdef mpx
#ifdef TESTING
    if ((f = dup(fd)) < 0)
    	return -1;	/* no free file descriptors */
#else
    f = fd;		/* return old one */
#endif
#else
    f = fcntl(fd, F_DUPFD, 10);
#endif
#ifdef NOTNOW
printf("savefd: save %d to %d\n", fd, f);
#endif
    return(f);
#endif
}


void restore(last)
register int last;
{
    register int i;
    register int dupfd;

#ifdef NOTNOW
printf("restore: last = %d, topfd = %d\n", last, topfd);
#endif
    for (i = topfd - 1; i >= last; i--) {
    	if ((dupfd = fdmap[i].dup_fd) > 0) {
#ifdef NOTNOW
printf("restore: renaming %d to %d\n", dupfd, fdmap[i].org_fd);
#endif
#ifdef mpx
#ifdef NOTNOW
printf("restore: closing %d\n", dupfd);
#endif
    	if(dupfd != fdmap[i].org_fd) {
    	    close(dupfd);
    	    rename(fdmap[i].org_fd, fdmap[i].org_fd);
    	}
#else
    	    rename(dupfd, fdmap[i].org_fd);
#endif
    	} else {
#ifdef NOTNOW
printf("restore: closing %d\n", fdmap[i].org_fd);
#endif
    	    close(fdmap[i].org_fd);
    	}
    }
    topfd = last;
}

