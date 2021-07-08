/*~!timeb.h*/
/* Name: timeb.h Part No.: _______-____r
 *
 * Copyright 1990 - J B Systems, Morrison, CO
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

#ifndef TIMEB_H
#define TIMEB_H

#ident	"@(#)nbinclude:timeb.h	1.0"

/* Structure input to the stime system call  */
/* and returned by ftime system call.        */

struct timeb {
  int time;
  unsigned short millitm;
  short timezone;
  short dstflag;
#ifdef NOT_ANY_MORE
  char *mnemonic;
#endif
  };

/*
 * New time entry-- return TOD with milliseconds, timezone,
 * DST flag
 * These must be set for the local environment 
 */

#define TZ "EST5EDT"	/* default is EST */
#define TIMEZONE (5*60); /* default to EST  */
/* 6 == CST, 7 == MST, 8 == PST, etc */
#define DSTFLAG 1; /* Daylight savings time applicable here */
/* set when it is */
#define TIMEDIF 0xe45; /* 3653 days from 1960 to 1970 */

#endif
