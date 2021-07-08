/*~!rules.c*/
/* Name:  rules.c Part No.: _______-____r
 *
 * Copyright 1995 - J B Systems, Morrison, CO
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

#ident	"$Id: rules.c,v 1.5 1995/06/02 15:46:25 jbev Exp $"

#include "defs.h"

/* DEFAULT RULES FOR MPX */

/*
* These are the internal rules that "make" trucks around with it at
* all times. One could completely delete this entire list and just
* conventionally define a global "include" makefile which had these
* rules in it. That would make the rules dynamically changeable
* without recompiling make. This file may be modified to local
* needs.
*/

CHARSTAR builtin [] =
  {
#ifdef mpx
  ".SUFFIXES: .o .c .c~ .y .y~ .x .x~ .s .s~ .sh .sh~ .h .h~ .f .f~",
#else
  ".SUFFIXES: .o .c .c~ .y .y~ .l .l~ .s .s~ .sh .sh~ .h .h~ .f .f~",
#endif

  /* PRESET VARIABLES */
  "MAKE=make",
#ifdef mpx
    "YACC=nbyacc", "YFLAGS=",
    "LEX=nblex", "LFLAGS=",
    "LD=nbcat", "LDFLAGS=",
#else
    "YACC=yacc", "YFLAGS=",
    "LEX=lex", "LFLAGS=",
    "LD=ld", "LDFLAGS=",
#endif
#ifdef mpx
    "CC=nbcc", "CFLAGS=-C",
    "F77=nbcc", "FFLAGS=-C",
    "AS=nbcas", "ASFLAGS=-C", "PRE=/system/system/mpxpre",
	"MAC=-M/system/system/m.mpxmac",
    "GET=co", "GFLAGS=",
#else
    "CC=cc", "CFLAGS=-O",
    "AS=as", "ASFLAGS=",
    "GET=co", "GFLAGS=",
#endif

  /* SINGLE SUFFIX RULES */
  ".c:",
    "\t$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@",
    ".c~:",
    "\t$(GET) $(GFLAGS) $< ",
    "\t$(CC) $*.c -o $*",
    "\t-rm -f $*.c",
  ".f:",
    "\t$(F77) $(FFLAGS) $(LDFLAGS) $< -o $@",
    ".f~:",
    "\t$(GET) $(GFLAGS) $< ",
    "\t$(F77) $*.f -o $*",
    "\t-rm -f $*.f",
    ".sh:",
    "\tcp $< $@",
    ".sh~:",
    "\t$(GET) $(GFLAGS) $< ",
    "\tcp $*.sh $*",
    "\t-rm -f $*.sh",

  /* DOUBLE SUFFIX RULES */
  ".c.o:",
    "\t$(CC) $(CFLAGS) -c $<",
    ".c~.o:",
    "\t$(GET) $(GFLAGS) $< ",
    "\t$(CC) $(CFLAGS) -c $*.c",
    "\t-rm -f $*.c",
    ".c~.c:",
    "\t$(GET) $(GFLAGS) $< ",
  ".f.o:",
    "\t$(F77) $(FFLAGS) -c $<",
    ".f~.o:",
    "\t$(GET) $(GFLAGS) $< ",
    "\t$(F77) $(FFLAGS) -c $*.f",
    "\t-rm -f $*.f",
    ".f~.f:",
    "\t$(GET) $(GFLAGS) $< ",
    ".s.o:",
    "\t$(AS) $(ASFLAGS) $(MAC) -O$@ $(PRE) $<",
    ".s~.o:",
    "\t$(GET) $(GFLAGS) $< ",
    "\t$(AS) $(ASFLAGS) $(MAC) -O$*.o $(PRE) $*.s",
    "\t-rm -f $*.s",
    ".y.o:",
    "\t$(YACC) $(YFLAGS) $<",
    "\t$(CC) $(CFLAGS) -c y.tab.c",
    "\trm y.tab.c",
    "\tmv y.tab.o $@",
    ".y~.o:",
    "\t$(GET) $(GFLAGS) $< ",
    "\t$(YACC) $(YFLAGS) $*.y",
    "\t$(CC) $(CFLAGS) -c y.tab.c",
    "\trm -f y.tab.c $*.y",
    "\tmv y.tab.o $*.o",
#ifdef mpx
    ".x.o:",
#else
    ".l.o:",
#endif
    "\t$(LEX) $(LFLAGS) $<",
    "\t$(CC) $(CFLAGS) -c lex.yy.c",
    "\trm lex.yy.c",
    "\tmv lex.yy.o $@",
#ifdef mpx
    ".x~.o:",
    "\t$(GET) $(GFLAGS) $< ",
    "\t$(LEX) $(LFLAGS) $*.x",
    "\t$(CC) $(CFLAGS) -c lex.yy.c",
    "\trm -f lex.yy.c $*.x",
#else
    ".l~.o:",
    "\t$(GET) $(GFLAGS) $< ",
    "\t$(LEX) $(LFLAGS) $*.l",
    "\t$(CC) $(CFLAGS) -c lex.yy.c",
    "\trm -f lex.yy.c $*.l",
#endif
    "\tmv lex.yy.o $*.o",
    ".y.c :",
    "\t$(YACC) $(YFLAGS) $<",
    "\tmv y.tab.c $@",
    ".y~.c :",
    "\t$(GET) $(GFLAGS) $< ",
    "\t$(YACC) $(YFLAGS) $*.y",
    "\tmv y.tab.c $*.c",
    "\t-rm -f $*.y",
#ifdef mpx
    ".x.c :",
#else
    ".l.c :",
#endif
    "\t$(LEX) $<",
    "\tmv lex.yy.c $@",
    ".c.a:",
    "\t$(CC) -c $(CFLAGS) $<",
    "\tar rv $@ $*.o",
    "\trm -f $*.o",
    ".c~.a:",
    "\t$(GET) $(GFLAGS) $< ",
    "\t$(CC) -c $(CFLAGS) $*.c",
    "\tar rv $@ $*.o",
    "\trm -f $*.[co]",
    ".s~.a:",
    "\t$(GET) $(GFLAGS) $< ",
    "\t$(AS) $(ASFLAGS) -o $*.o $*.s",
    "\tar rv $@ $*.o",
    "\t-rm -f $*.[so]",
    ".h~.h:",
    "\t$(GET) $(GFLAGS) $< ",
    "markfile.o:  markfile",
    "\tA=@;echo \"static char _sccsid[] = \\042`grep $$A'(#)' markfile`\\042;\" > markfile.c",
    "\tcc -c markfile.c",
    "\trm -f markfile.c",
    0 };

