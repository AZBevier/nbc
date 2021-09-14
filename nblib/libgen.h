/*~!libgen.h*/
/* Name:  libgen.h Part No.: _______-____r
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

#ident	"@(#)nbclib:libgen.h	1.1"

#ifndef LIBGEN_H
#define LIBGEN_H

/*
	declarations of functions found in MPX version of libgen
*/


extern char *basename();

extern unsigned char *bgets();

extern unsigned bufsplit();

extern char *copylist();

extern char *day();

extern char *dirname();

extern int eaccess();

extern int incount();

extern int julian();

extern int leap();

extern int mkdirp();

extern int num();

extern int numd();

extern p2open();

extern int p2close();

extern char *pathfind();

extern char *regerror();

extern int rmdirp();

extern int sesystem();

extern short sgets();

extern char *smemcpy();

extern void sputs();

extern char *stradd();

extern char *strccpy();

extern char *strecpy();

extern int strnlen();

extern char *sweekday();

extern long tconv();

extern long tconvs();

extern void to_date();

extern long to_day();

extern char *triml();

extern char *trimt();

extern int waitpid();

extern int weekday();
#endif /* LIBGEN_H */
