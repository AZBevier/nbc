/*~!signal.h*/
/* Name:  signal.h Part No.: _______-____r
 *
 * Copyright 1991 - J B Systems, Morrison, CO
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

#ident	"@(#)nbinclude:signal.h	1.1"

#ifndef SIGNAL_H
#define SIGNAL_H

#define	SIGHUP	1	/* hangup */
#define	SIGINT	2	/* interrupt (rubout) */
#define	SIGQUIT	3	/* quit (ASCII FS) */
#define	SIGILL	4	/* illegal instruction (not reset when caught)*/
#define	SIGTRAP	5	/* trace trap (not reset when caught) */
#define	SIGIOT	6	/* IOT instruction */
#define SIGABRT 6	/* used by abort, replace SIGIOT in the  future */
#define	SIGEMT	7	/* EMT instruction */
#define	SIGFPE	8	/* floating point exception */
#define	SIGKILL	9	/* kill (cannot be caught or ignored) */
#define	SIGBUS	10	/* bus error */
#define	SIGSEGV	11	/* segmentation violation */
#define	SIGSYS	12	/* bad argument to system call */
#define	SIGPIPE	13	/* write on a pipe with no one to read it */
#define	SIGALRM	14	/* alarm clock */
#define	SIGTERM	15	/* software termination signal from kill */
#define	SIGUSR1	16	/* user defined signal 1 */
#define	SIGUSR2	17	/* user defined signal 2 */
#define	SIGCLD	18	/* death of a child */
#define	SIGPWR	19	/* power-fail restart */
#define SIGWINCH 20	/* window change */

			/* SIGPHONE only used in UNIX/PC */
/*#define SIGPHONE 21*/	/* handset, line status change */

#	define SIGPOLL 22	/* pollable event occured */

#define SIGCHLD SIGCLD  /* compatibility */

#	define SIGSTOP 23      /* sendable stop signal not from tty */
#	define SIGTSTP 24      /* stop signal from tty */
#	define SIGCONT 25      /* continue a stopped process */
#	define SIGTTIN 26      /* to readers pgrp upon background tty read */
#	define SIGTTOU 27      /* like TTIN for output if (tp->t_local&TOSTOP) */

#	define	SIGALL          (~(sigset_t)0L)		/* new for POSIX */

#	define	NSIG	28	/* The valid signal number is from 1 to NSIG-1 */
#	define MAXSIG	32	/* size of u_signal[], NSIG-1 <= MAXSIG*/
			/* MAXSIG is larger than we need now. */
			/* In the future, we can add more signal */
			/* number without changing user.h */

#	define	SIG_SETMASK	0	/* set mask in sigprocmask. new for POSIX */
#	define	SIG_BLOCK	1	/* union mask in sigprocmask. new for POSIX */
#	define	SIG_UNBLOCK	2	/* intrsct mask in sigprocmask. new for POSIX */

typedef	long	sigset_t;

#define         sigbit(n)       (1L << ((n) - 1))
#define         sigemptyset(s)  *(s) = ~SIGALL
#define         sigfillset(s)   *(s) = SIGALL
#define         sigaddset(s,n)  *(s) |= sigbit(n)
#define         sigdelset(s,n)  *(s) &= ~sigbit(n)
#define         sigismember(set,n) ((*(set) & sigbit(n)) == sigbit(n))

int (*signal ()) ();		/* mpx is int instead of void */

#define SIG_ERR	(int(*)())-1
#define	SIG_DFL	(int(*)())0
#define	SIG_IGN	(int(*)())1
#define SIG_HOLD (int(*)())2

#endif	/* SIGNAL_H */
