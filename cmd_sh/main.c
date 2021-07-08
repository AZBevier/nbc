/*~!main.c*/
/* Name:  main.c Part No.: _______-____r
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

#ident	"$Id: main.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

/* #define NOTNOW */

#ifdef NOTNOW
#include <stdio.h>
#endif
#include	"defs.h"
#include	"sym.h"
#include	"timeot.h"
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<signal.h>
#ifdef RES
#include        "dup.h"
#endif

#ifdef RES
#include	<sgtty.h>
#else
#include	<fcntl.h>
#endif

#ifndef mpx
#include <stdlib.h>
#include <unistd.h>
#endif

#ifndef mpx
void setmail();
void chkmail();
#endif

extern char readc();

extern char *simple();

extern void prc();
extern void prs();
extern void itos();
extern void settmp();
extern void stakchk();
extern void ignsig();
extern void tdystak();
extern void stdsigs();
extern void addblok();
extern void setup_env();
extern void initf();
extern void hcreate();
extern void replace();
extern void assnum();
extern void dfault();
extern void estabf();
extern void ignsig();
extern void set_dotpath();

extern int execute();
extern int chkopen();
extern int options();
extern int pathopen();
extern int any();
extern int stoi();

static BOOL	beenhere = FALSE;
char tmpout[20] = "/tmp/sh-";
struct fileblk stdfile;
struct fileblk *standin = &stdfile;
int mailchk = 0;

static char *mailp;
static long *mod_time = 0;

static void exfile();
int Ldup();

int main(c, v, e)
int c;
char *v[];
char *e[];
{
    register int rflag = ttyflg;
    int rsflag = 1;	/* local restricted flag */
    struct namnod *n;
    int i;

#ifdef NOTNOW
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
#endif
    stdsigs();

    /*
     * initialize storage allocation
     */

#ifdef MAYBENOT
#ifndef smpx
    stakbot = 0;
#endif
#endif
#ifdef NOTNOW
printf("SHELL entered\n");
#endif
    addblok((unsigned)0);
#ifdef NOTNOW
printf("SHELL2 entered\n");
#endif

#ifdef NOTNOW
printf("main: argc = %d\n", c);
for (i=0; i<c; i++)
printf("main: arg%d = %s\n", i, v[i]);
#endif

    /*
     * set names from userenv
     */

    setup_env();

#ifdef NOTNOW1
printf("after setup_env\n");
#endif
    /*
     * 'rsflag' is non-zero if SHELL variable is
     *  set in environment and contains an'r' in
     *  the simple file part of the value.
     */
    if (n = findnam("SHELL")) {
    	if (any('r', simple(n->namval)))
    	    rsflag = 0;
    }

    /*
     * a shell is also restricted if argv(0) has
     * an 'r' in its simple name
     */

#ifndef RES
    if (c > 0 && any('r', simple(*v)))
    	rflag = 0;
#endif

    hcreate();
    set_dotpath();

#ifdef NOTNOW1
printf("after set_dotpath\n");
#endif
    /*
     * look for options
     * dolc is $#
     */
    dolc = options(c, v);

#ifdef NOTNOW1
printf("after options\n");
#endif
    if (dolc < 2) {
    	flags |= stdflg;
    	 {
    	    register char *flagc = flagadr;

    	    while (*flagc)
    	    	flagc++;
    	    *flagc++ = STDFLG;
    	    *flagc = 0;
    	}
    }
    if ((flags & stdflg) == 0)
    	dolc--;
    dolv = v + c - dolc;
    dolc--;

#ifdef NOTNOW
printf("main: dolc = %d\n", dolc);
for (i=0; i<dolc; i++)
printf("main: arg%d = %s\n", i, dolv[i]);
#endif
    /*
     * return here for shell file execution
     * but not for parenthesis subshells
     */
    setjmp(subshell);

    /*
     * number of positional parameters
     */
    replace(&cmdadr, dolv[0]);	/* cmdadr is $0 */
#ifdef NOTNOW1
printf("after replace, cmdadr = %s\n", cmdadr);
#endif

    /*
     * set pidname '$$'
     */
    assnum(&pidadr, getpid());
#ifdef NOTNOW1
printf("after assnum, pidadr = %s\n", pidadr);
#endif

    /*
     * set up temp file names
    */
    settmp();
#ifdef NOTNOW1
printf("after settmp, cmdadr = %s\n", cmdadr);
#endif

    /*
     * default internal field separators - $IFS
    */
    dfault(&ifsnod, sptbnl);

#ifndef mpx
    dfault(&mchknod, MAILCHECK);
    mailchk = stoi(mchknod.namval);
#endif
    if ((beenhere) == FALSE) {	/* ? profile */ 

    	++beenhere;		/* DAG */
    	if (*(simple(cmdadr)) == '-') {		/* system profile */

#ifndef RES
#ifdef NOTNOW1
printf("pathopen sysprofile, %s\n", sysprofile);
#endif
    	    if ((input = pathopen(nullstr, sysprofile)) >= 0)
    	    	exfile(rflag);		/* file exists */
#endif
#ifdef NOTNOW1
printf("pathopen profile, %s\n", profile);
#endif
    	    if ((input = pathopen(nullstr, profile)) >= 0) {
    		exfile(rflag);
    		flags &= ~ttyflg;
    	    }
    	}
    	if (rsflag == 0 || rflag == 0)
    	    flags |= rshflg;
    	/*
	 * open input file if specified
	 */
    	if (comdiv) {
#ifdef NOTNOW1
printf("comdiv estabf (%d)\n", comdiv);
#endif
    	    estabf(comdiv);	/* set stdin to specified file */
    	    input = -1;
    	} else {
#ifdef NOTNOW1
printf("no comdiv, cmdadr = %s\n", cmdadr);
#endif
    	    input = ((flags & stdflg) ? 0 : chkopen(cmdadr));
    	    comdiv--;
    	}
    }
#ifdef NOTNOW
printf("before exfile(0) input = %x\n", input);
printf("cmdadr = %s\n", cmdadr);
#endif
    exfile(0);
#ifdef NOTNOW
printf("after exfile(0)\n");
#endif
    done();
}


/* read commands from input fd, if 0, we are reading stdin */
static void exfile(prof)
BOOL	prof;
{
    long mailtime = 0;	/* Must not be a register variable */
    long curtime = 0;
    register int userid;

    /*
     * move input
     */
    if (input > 0) {
#ifdef mpx
#ifdef NOTNOW1
printf("exec: Ldup input %d\n", input);
#endif
/*    	input = Ldup(input); */
#else
    	Ldup(input, INIO);
    	input = INIO;
#endif
    }

    userid = geteuid();

    /*
     * decide whether interactive
     */
    if ((flags & intflg) || 
      ((flags & oneflg) == 0 && 
      isatty(output) && 
      isatty(input)) ) {

    	dfault(&ps1nod, (userid ? stdprompt : supprompt));
    	dfault(&ps2nod, readmsg);
    	flags |= ttyflg | prompt;
#ifndef mpx
    	ignsig(SIGTERM);
    	if (mailpnod.namflg != N_DEFAULT)
    	    setmail(mailpnod.namval);
    	else
    	    setmail(mailnod.namval);
#endif /* mpx */
    } else {
    	flags |= prof;
    	flags &= ~prompt;
    }

    if (setjmp(errshell) && prof) {
#ifdef NOTNOW1
printf("exec: close input %d\n", input);
#endif
    	close(input);
    	return;
    }
    /*
     * error return here
     */

    loopcnt = peekc = peekn = 0;
    fndef = 0;
    nohash = 0;
    iopend = 0;

    if (input >= 0) {
#ifdef NOTNOW1
printf("exec: initf - input %d\n", input);
#endif
    	initf(input);	/* set stdin to current input fd */
    }
    /*
     * command loop
     */
#ifdef NOTNOW
printf("exfile: entering command loop, cmdadr = %s\n", cmdadr);
#endif
    for (; ; ) {
    	tdystak(0);
    	stakchk();	/* may reduce sbrk */
    	exitset();

#ifdef NOTNOW
printf("exfile: loop, flags = %x, prompt = %s\n", flags, ps1nod.namval);
#endif
    	if ((flags & prompt) && standin->fstak == 0 && !eof) {

    	    if (mailp) {
    	    	time(&curtime);

#ifndef mpx
    		if ((curtime - mailtime) >= mailchk) {
    		    chkmail();
    		    mailtime = curtime;
    		}
#endif
    	    }

#ifdef mpx
    	    prs("$ ");
#else
    	    prs(ps1nod.namval);
#endif
    	    flags |= waiting;
    	    trapnote = 0;
    	    peekc = readc();
/*    	    newline(); */
    	} else {
    	    trapnote = 0;
    	    peekc = readc();
    	}

    	if (eof)
    	    return;

    	flags &= ~waiting;

#ifdef NOTNOW
printf("exfile: before execute\n");
#endif
    	execute(cmd(NL, MTFLG), 0, eflag, (int *)0, (int *)0);
#ifdef NOTNOW
printf("exfile: after execute\n");
#endif
    	eof |= (flags & oneflg);
    }
}


void chkpr()
{
    if ((flags & prompt) && standin->fstak == 0)
    	prs(ps2nod.namval);
}


void settmp()
{
    itos(getpid());
    serial = 0;
    xtmpnam = movstr(numbuf, &tmpout[TMPNAM]);
}


#ifdef smpx
#define CASSG
#undef eof
#include <unixio.h>

int dup(fd)
register int fd;
{
    int fn = fd;

    if (fd >= 0) { 
    	char lfc[10];
    	INIT;
    	sprintf(lfc, "LFC=UX%X", fd);
    	fn = open(lfc, curfprm->mode);
    }
    return(fn);
}
#endif

#ifdef mpx
int Ldup(fa)
register int fa;
#else
int Ldup(fa, fb)
register int fa, fb;
#endif
{
#ifdef mpx
    register int fb = fa;
#endif
#ifdef RES

    dup(fa | DUPFLG, fb);
    close(fa);
    ioctl(fb, FIOCLEX, 0);

#else

#ifndef mpx
    if (fa >= 0) { 
    	close(fb);
    	fcntl(fa, F_DUPFD, fb);		/* normal dup */
    	close(fa);
    	fcntl(fb, F_SETFD, 1);	/* autoclose for fb */
    }
#else /* mpx */

#ifdef smpx
#ifndef mpx_newway
    if (fa >= 0) { 
    	fb = dup(fa);
    	close(fa);
    }
#else
    if (fa >= 0) { 
    	char lfc[10];
    	sprintf(lfc, "LFC=UX%X", fa);
    	fb = open(lfc, 0);
    	close(fa);
    }
#endif
#else
    if (fa >= 0) { 
    	fb = dup(fa);
#ifdef NOTNOW1
printf("Ldup: close fa %d\n", fa);
#endif
    	close(fa);
    }
#endif
#endif /* mpx */

#ifdef NOTNOW
printf("Ldup: fa %d, bb %d\n", fa, fb);
#endif

#ifdef mpx
    return fb;
#endif
#endif
}


#ifndef mpx
void chkmail()
{
    register char *s = mailp;
    register char *save;

    long *ptr = mod_time;
    char *start;
    BOOL	flg;
    struct stat statb;

    while (*s) {
    	start = s;
    	save = 0;
    	flg = 0;

    	while (*s) {
    	    if (*s != COLON) {
    	    	if (*s == '%' && save == 0)
    	    	    save = s;

    	    	s++;
    	    } else
    	     {
    	    	flg = 1;
    	    	*s = 0;
    	    }
    	}

    	if (save)
    	    *save = 0;

    	if (*start && stat(start, &statb) >= 0) {
    	    if (statb.st_size && *ptr
    	       && statb.st_mtime != *ptr) {
    	    	if (save) {
    	    	    prs(save + 1);
    	    	    newline();
    	    	} else
    	    	    prs(mailmsg);
    	    }
    	    *ptr = statb.st_mtime;
    	} else if (*ptr == 0)
    	    *ptr = 1;

    	if (save)
    	    *save = '%';

    	if (flg)
    	    *s++ = COLON;

    	ptr++;
    }
}
#endif


#ifndef mpx
void setmail(mailpath)
char *mailpath;
{
    register char *s = mailpath;
    register int cnt = 1;

    long *ptr;

    free(mod_time);
    if (mailp = mailpath) {
    	while (*s) {
    	    if (*s == COLON)
    	    	cnt += 1;

    	    s++;
    	}

    	ptr = mod_time = (long *)alloc(sizeof(long) *cnt);

    	while (cnt) {
    	    *ptr = 0;
    	    ptr++;
    	    cnt--;
    	}
    }
}
#endif /* mpx */


