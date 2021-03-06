/*~!defs.c*/
/* Name:  defs.c Part No.: _______-____r
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

#ident	"$Id: defs.c,v 1.1 1995/04/04 22:25:34 jbev Exp $"

/*	$Log $
 */

#include 	<setjmp.h>
#include	"mode.h"
#include	"name.h"
#include	<sys/param.h>

/* temp files and io */

int output = 2;
int ioset;
struct ionod *iotemp;	/* files to be deleted sometime */
struct ionod *fiotemp;	/* function files to be deleted sometime */
struct ionod *iopend;	/* documents waiting to be read at NL */
struct fdsave fdmap[NOFILE];
/* current settings for I/O */
int cstdin = 0;		/* default to stdin */
int cstdout = 1;	/* default to stdout */
int cstderr = 2;	/* default to stderr */

/* substitution */
int dolc;
char **dolv;
struct dolnod *argfor;
struct argnod *gchain;

/* name tree and words */
int wdval;
int wdnum;
int fndef;
int nohash;
struct argnod *wdarg;
int wdset;
BOOL	reserv;

/* special names */
char *pcsadr;
char *pidadr;
char *cmdadr;

/* transput */
char *xtmpnam;
int serial;
int peekc;
int peekn;
char *comdiv;

long flags;
int rwait;	/* flags read waiting */

/* error exits from various parts of shell */
jmp_buf	subshell;
jmp_buf	errshell;

/* fault handling */
BOOL	trapnote;

/* execflgs */
int exitval;
int retval;
BOOL	execbrk;
int loopcnt;
int breakcnt;
int funcnt;

int wasintr;	/* used to tell if break or delete is hit
		   while executing a wait
		*/

int eflag;

/* The following stuff is from stak.h	*/

char *stakbas;
char *staktop;
char *stakbot;
char *stakbsy;
char *brkend;

