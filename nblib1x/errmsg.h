/*~!errmsg.h*/
/* Name:  errmsg.h Part No.: _______-____r
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

#ident	"@(#)nbclib:errmsg.h	1.1"

#ifndef ERRMSG_H
#define ERRMSG_H

/*	errmsg.h
	Include file for error message interface.
	Command and library version.
*/

#define	errmsg	errtag( __FILE__, __LINE__ ), errtext

extern  void 	erraction();
extern	int     errafter();	/* routine run after text is printed */
extern	void	errbefore();	/* routine run before text is printed */
extern	int	errexit();	/* exit(2) code for actions that exit */
extern	void	_errmsg();
extern	void	errprefix();	/* prefix to error message, unique to each
				supplier */
extern	void	errsource();	/* source of error message, usually command name
				*/
extern	void	errtag();
extern	void	errtext();
extern	void	errtofix();
extern	void	errusage();	/* routine to print command usage message */
extern	void	errverb();	/* adjust verbosity of error messages */

/* severities  first argument to errbefore(), errafter(), errtext() */
#define	EIGNORE	-1	/* special severity, no message, no action, returns */
#define	EINFO	0
#define	EWARN	1
#define	EERROR	2
#define	EHALT	3

/* special errtext() argument that prints a standard message based on errno */
#define	EERRNO	1

/* actions : returned by errafter() used as an argument to erraction()
 */
#define	EEXIT	100
#define	EABORT  200
#define ERETURN 300

/* used to set verbosity */
#define	ENO	0
#define	EYES	1
#define	EDEF	2   /* default value -- setting ersyserr */

struct Err {
			/* flags to adjust verbosity */
	char	vbell;	/* ring bell before message */
	char	vprefix;
	char	vsource;	/* source information, including prefix */
	char	vsevmsg;	/* severity message */
	char	vsyserr;	/* system error message, perror() */
	char	vfix;	/* to fix msg */
	char	vtag;
	char	vtext;
			/* message content and context */
	char	*prefix;	/* usually unique per manufacturer */
	char	*envsource;	/* source from ERRSOURCE environmental variable
				*/
	char	*source;	/* usually command name */
	int	severity;
	char	**sevmsg;	/* error messages that depend on severity */
	char	*tofix;  /* set by errtofix()  */
	int	tagnum;
	char	*tagstr;
	int	exit;	/* exit(2) code to use if error causes exit */
};
extern struct Err	Err;

#endif /* ERRMSG_H */
