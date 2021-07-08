/*~!defs.h*/
/* Name:  defs.h Part No.: _______-____r
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

#ident	"$Id: defs.h,v 1.3 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

#ifndef DEFS_H
#define DEFS_H

#if defined(BSD) || defined(gould) || defined(pyr)
#define	void	int	/* avoid compiler bug */
#endif

#ifdef mpx
#ifndef i386
#define smpx
#define getpath Getpath
#endif
#endif

/* error exits from various parts of shell */
#define 	ERROR		1
#define 	SYNBAD		2
#define 	SIGFAIL 	2000
#define	 	SIGFLG		0200

/* command tree */
#define 	FPRS		0x0100
#define 	FINT		0x0200
#define 	FAMP		0x0400
#define 	FPIN		0x0800
#define 	FPOU		0x1000
#define 	FPCL		0x2000
#define 	FCMD		0x4000
#define 	COMMSK		0x00F0
#define		CNTMSK		0x000F

#define 	TCOM		0x0000
#define 	TPAR		0x0010
#define 	TFIL		0x0020
#define 	TLST		0x0030
#define 	TIF			0x0040
#define 	TWH			0x0050
#define 	TUN			0x0060
#define 	TSW			0x0070
#define 	TAND		0x0080
#define 	TORF		0x0090
#define 	TFORK		0x00A0
#define 	TFOR		0x00B0
#define		TFND		0x00C0

/* execute table */
#define 	SYSSET		1
#define 	SYSCD		2
#define 	SYSEXEC		3

#if defined(RES) || defined(BSD)	/* include login code */
#define 	SYSLOGIN	4
#else
#if !defined(BSD)
#define 	SYSNEWGRP 	4
#endif
#endif

#define 	SYSTRAP		5
#define 	SYSEXIT		6
#define 	SYSSHFT 	7
#define 	SYSWAIT		8
#define 	SYSCONT 	9
#define 	SYSBREAK	10
#define 	SYSEVAL 	11
#define 	SYSDOT		12
#define 	SYSRDONLY 	13
#define 	SYSTIMES 	14
#define 	SYSXPORT	15
#define 	SYSNULL 	16
#define 	SYSREAD 	17
#define		SYSTST		18

#ifndef RES	/* exclude umask code */
#define 	SYSUMASK 	20
#define 	SYSULIMIT 	21
#endif

#define 	SYSECHO		22
#define		SYSHASH		23
#define		SYSPWD		24
#define 	SYSRETURN	25
#define		SYSUNS		26
#define		SYSMEM		27
#define		SYSTYPE  	28

/* used for input and output of shell */
#define 	INIO 		19

/*io nodes*/
#define 	USERIO		10
#define 	IOUFD		15
#define 	IODOC		16
#define 	IOPUT		32
#define 	IOAPP		64
#define 	IOMOV		128
#define 	IORDW		256
#define		IOSTRIP		512
#define 	INPIPE		0
#define 	OTPIPE		1

/* arg list terminator */
#define 	ENDARGS		0

#include	"mac.h"
#include	"mode.h"
#include	"name.h"

/*	error catching */
extern int errno;

/* result type declarations */

#ifdef mpx
#define 	free 		afree
#define		setbrk		xsetbrk
extern char	*alloc();
#else
#define 	free 		afree
#define 	alloc 		mymalloc
/* extern void	*alloc(); */
extern char	*alloc();
#endif

/*extern char	*alloc();*/
extern char	*make();
extern char	*movstr();
extern char	*movstrn();
extern struct trenod *cmd();
extern struct trenod *makefork();
extern struct namnod *lookup();
extern struct namnod *findnam();
extern struct dolnod *useargs();
extern float 	expr();
extern char 	*catpath();
extern char	*getpath();
extern char 	*nextpath();
extern char 	**scan();
extern char 	*mactrim();
extern char 	*macro();
/*extern char 	*execs();*/
#ifdef TILDE_SUB
extern char 	*homedir();
extern char 	*retcwd();
#endif
extern void exname();
/*extern char *staknam();*/
extern void printnam();
extern void printro();
extern void printexp();
extern char **msetenv();
extern long time();

#define 	attrib(n,f)		(n->namflg |= f)
#define 	round(a,b)		(((int)(((char *)(a)+b)-1))&~((b)-1))
#define 	closepipe(x)	(close(x[INPIPE]), close(x[OTPIPE]))
#define 	eq(a,b)			(cf(a,b)==0)
#define 	max(a,b)		((a)>(b)?(a):(b))
#define 	assert(x)		;

/* temp files and io */
extern int output;
extern int ioset;
extern struct ionod *iotemp;	/* files to be deleted sometime */
extern struct ionod *fiotemp;	/* function files to be deleted sometime */
extern struct ionod *iopend;	/* documents waiting to be read at NL */
extern struct fdsave fdmap[];
extern int cstdin;
extern int cstdout;
extern int cstderr;

/* substitution */
extern int dolc;
extern char **dolv;
extern struct dolnod *argfor;
extern struct argnod *gchain;

/* stak stuff */
#include		"stak.h"

/* string constants */
extern char atline[];
extern char readmsg[];
extern char colon[];
extern char minus[];
extern char nullstr[];
extern char sptbnl[];
extern char unexpected[];
extern char endoffile[];
extern char synmsg[];
extern char setstr[];
extern char sicrstr[];
extern char bang[];
extern char pdstr[];
extern char dotdot[];
extern char slstr[];
extern char eqlstr[];
extern char neqstr[];
extern char lbstr[];
extern char lpstr[];
extern char rbstr[];
extern char rpstr[];
extern char dasheq[];
extern char dashne[];
extern char dashgt[];
extern char dashlt[];
extern char dashge[];
extern char dashle[];
extern char dasha[];
extern char dashb[];
extern char dashc[];
extern char dashd[];
extern char dashf[];
extern char dashg[];
extern char dashk[];
extern char dashn[];
extern char dasho[];
extern char dashp[];
extern char dashr[];
extern char dashs[];
extern char dasht[];
extern char dashu[];
extern char dashw[];
extern char dashx[];
extern char dashz[];
extern char ptrcolon[];
extern char shell[];
extern char sfuncstr[];
extern char efuncstr[];
extern char amperstr[];
extern char lparstr[];
extern char rparstr[];
extern char pipestr[];
extern char andstr[];
extern char orstr[];
extern char forstr[];
extern char instr[];
extern char dostr[];
extern char donestr[];
extern char whilestr[];
extern char untilstr[];
extern char ifstr[];
extern char thenstr[];
extern char elsestr[];
extern char fistr[];
extern char casestr[];
extern char dsemistr[];
extern char esacstr[];
extern char fromstr[];
extern char toastr[];
extern char fromastr[];
extern char ontostr[];
extern char hashhdr[];
extern char isbuiltin[];
extern char isfunct[];
extern char efnlstr[];
extern char nfstr[];
extern char ishashed[];
extern char rpnlstr[];
extern char isstr[];
extern char rdwstr[];
#if SYMLINK
extern char nolstat[];
#endif

/* name tree and words */
extern struct sysnod reserved[];
extern int no_reserved;
extern struct sysnod commands[];
extern int no_commands;

extern int wdval;
extern int wdnum;
extern int fndef;
extern int nohash;
extern struct argnod *wdarg;
extern int wdset;
extern BOOL	reserv;

/* prompting */
extern char stdprompt[];
extern char supprompt[];
extern char profile[];
extern char sysprofile[];

/* built in names */
extern struct namnod fngnod;
extern struct namnod cdpnod;
extern struct namnod ifsnod;
extern struct namnod homenod;
extern struct namnod mailnod;
extern struct namnod pathnod;
extern struct namnod ps1nod;
extern struct namnod ps2nod;
extern struct namnod mchknod;
extern struct namnod acctnod;
extern struct namnod mailpnod;

/* special names */
extern char flagadr[];
extern char *pcsadr;
extern char *pidadr;
extern char *cmdadr;

extern char defpath[];

/* names always present */
extern char mailname[];
extern char homename[];
extern char pathname[];
extern char cdpname[];
extern char ifsname[];
extern char ps1name[];
extern char ps2name[];
extern char mchkname[];
extern char acctname[];
extern char mailpname[];

/* transput */
extern char tmpout[];
extern char *xtmpnam;
extern int serial;

#define		TMPNAM 		7

extern struct fileblk *standin;

#define 	input		(standin->fdes)
#define 	eof		(standin->xfeof)

extern int peekc;
extern int peekn;
extern char *comdiv;
extern char devnull[];

/* flags */
#define		noexec		01
#define		sysflg		01
#define		intflg		02
#define		prompt		04
#define		setflg		010
#define		errflg		020
#define		ttyflg		040
#define		forked		0100
#define		oneflg		0200
#define		rshflg		0400
#define		waiting		01000
#define		stdflg		02000
#define		STDFLG		's'
#define		execpr		04000
#define		readpr		010000
#define		keyflg		020000
#define		hashflg		040000
#define		nofngflg	0200000
#define		exportflg	0400000

extern long flags;
extern int rwait;	/* flags read waiting */

/* error exits from various parts of shell */
#include	<setjmp.h>
extern jmp_buf	subshell;
extern jmp_buf	errshell;

/* fault handling */
#include	"brkinc.h"

extern unsigned brkincr;
#define 	MINTRAP		0
#define 	MAXTRAP		20

#define 	TRAPSET		2
#define 	SIGSET		4
#define 	SIGMOD		8
#define 	SIGCAUGHT	16

extern void	done();
extern void	fault();
extern BOOL	trapnote;
extern char *trapcom[];
extern BOOL	trapflg[];

/* name tree and words */
extern char **environ;
extern char numbuf[];
extern char export[];
extern char duperr[];
extern char readonly[];

/* execflgs */
extern int exitval;
extern int retval;
extern BOOL execbrk;
extern int loopcnt;
extern int breakcnt;
extern int funcnt;

/* messages */
extern char mailmsg[];
extern char coredump[];
extern char badopt[];
extern char badparam[];
extern char unset[];
extern char badsub[];
extern char nospace[];
extern char nostack[];
extern char notfound[];
extern char badtrap[];
extern char baddir[];
extern char badshift[];
extern char restricted[];
extern char execpmsg[];
extern char notid[];
extern char badulimit[];
extern char wtfailed[];
extern char badcreate[];
extern char nofork[];
extern char noswap[];
extern char piperr[];
extern char badopen[];
extern char badnum[];
extern char arglist[];
extern char txtbsy[];
extern char toobig[];
extern char badexec[];
extern char badfile[];
extern char badreturn[];
extern char badexport[];
extern char badunset[];
extern char nohome[];
extern char badperm[];
extern char no11trap[];
extern char argcount[];
extern char neworsemi[];
extern char dotstat[];
extern char paropen[];
extern char parstat[];
extern char parread[];

/*	'builtin' error messages	*/

extern char btest[];
extern char badop[];
extern char argexp[];
extern char parexp[];
extern char rbmiss[];

/*	fork constant	*/

#define 	FORKLIM 	32

#ifndef mpx
extern address	end[];
#else
extern char **end[];	/* start of heap */
#endif

#include	"c_type.h"

extern int wasintr;	/* used to tell if break or delete is hit
			 *  while executing a wait
			 */
extern int eflag;


/*
 * Find out if it is time to go away.
 * `trapnote' is set to SIGSET when fault is seen and
 * no trap has been set.
 */

#define	sigchk() if(trapnote&SIGSET)exitsh(exitval?exitval:SIGFAIL)

#define exitset() retval=exitval

#endif /*DEFS_H*/

