/*~!main.c*/
/* Name:  main.c Part No.: _______-____r
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

#ident	"$Id: main.c,v 1.6 2021/07/06 21:47:12 jbev Exp $"

/* must define INIT for defs.h definitions. Only here! */
#define INIT

#include "defs.h"
/*
command make to update programs.
Flags:  'd'  print out debugging comments
'p'  print out a version of the input graph
's'  silent mode--don't print out commands
'f'  the next argument is the name of the description file;
     makefile is the default
'i'  ignore error codes from the shell
'l' ('S') stop after any command fails (normally do parallel work)
'n'  don't issue, just print, commands
't'  touch (update time of) files but don't issue command
'q'  don't do anything, but check if object is up to date;
     returns exit code 0 if up to date, -1 if not
*/

char makefile [] = "makefile";
extern char Nullstr [];
char Makefile [] = "Makefile";
char RELEASE [] = "RELEASE";
extern CHARSTAR badptr;

NAMEBLOCK mainname ;
NAMEBLOCK firstname;
LINEBLOCK sufflist;
VARBLOCK firstvar;
PATTERN firstpat ;
DIRLL firstod;

#include <sys/signal.h>
#ifndef mpx
#include <stdlib.h>
#include <unistd.h>
#endif

void getmflgs();
void setflags();
int rdd1();
void rdmakecomm();
void printdesc();
void enbint();
void intrupt();
int isprecious();
int rddescf();
void prname();
void optswitch();
void setmflgs();

extern void fatal();
extern void fatal1();
extern void readenv();
extern int yyparse();
extern void setvar();
extern int eqsign();
extern int doname();
extern int sindex();
extern void exitm();
extern int any();
extern int get();

int sigivalue=0;
int sigqvalue=0;
int mywaitpid=0;

int Mflags=MH_DEP;
int ndocoms=0;
int okdel=YES;

#ifdef NEWWAY
CHARSTAR prompt="\t"; /* other systems -- pick what you want */
#else
CHARSTAR prompt="===> "; /* other systems -- pick what you want */
#endif
char junkname [20];
char funny [128];

char Makeflags []="MAKEFLAGS";

int main (argc, argv)
int argc;
CHARSTAR argv [];
{
  register NAMEBLOCK p;
  int i;
  int descset, nfargs;
  TIMETYPE tjunk;
  CHARSTAR s;

#ifdef METERFILE
  meter (METERFILE);
#endif

setbuf(stdout, 0);	/* DEBUG */

  descset = 0;

  for (s = "|=^();&<>*?[]:$`'\"\\\n" ; *s ; ++s)
    funny [(int)*s] |= META;
  for (s = "\n\t :=;{}&>|" ; *s ; ++s)
    funny [(int)*s] |= TERMINAL;
  funny ['\0'] |= TERMINAL;

  TURNON (INTRULE);	/* Default internal rules, turned on */

  /*
  * Set command line flags
  */

  getmflgs ();		/* Init $(MAKEFLAGS) variable */
  setflags (argc, argv);

  setvar ("$", "$");

  /* set get flag as default */
  if (IS_OFF (GET)) TURNON (GET);

  /*
  * Read command line "=" type args and make them readonly.
  */
  TURNON (INARGS|EXPORT);
  if (IS_ON (DBUG)) printf ("Reading \"=\" type args on command line.\n");
  for (i=1; i<argc; ++i)
    if (argv [i]!=0 && argv [i] [0]!=MINUS && (eqsign (argv [i]) == YES))
      argv [i] = 0;
  TURNOFF (INARGS|EXPORT);

  /*
  * Read internal definitions and rules.
  */

  if (IS_ON (INTRULE))
  {
    if (IS_ON (DBUG)) printf ("Reading internal rules.\n");
    rdd1 (NULL);
  }

  /*
  * Done with internal rules, now.
  */
  TURNOFF (INTRULE);

  /*
  * Read environment args.  Let file args which follow override.
  * unless 'e' in MAKEFLAGS variable is set.
  */
  if (any ((varptr (Makeflags)) ->varval, 'e'))
    TURNON (ENVOVER);
  if (IS_ON (DBUG)) printf ("Reading environment.\n");
  TURNON (EXPORT);
  readenv ();
  TURNOFF (EXPORT|ENVOVER);

  /*
  * Read command line "-f" arguments.
  */

  rdmakecomm ();

  for (i = 1; i < argc; i++)
    if (argv [i] && argv [i] [0] == MINUS &&
	argv [i] [1] == 'f' && argv [i] [2] == CNULL)
    {
      argv [i] = 0;
      if (i >= argc-1)
        fatal ("No description argument after -f flag");
      if (rddescf (argv [++i], YES))
        fatal1 ("Cannot open %s", argv [i]);
      argv [i] = 0;
      ++descset;
    }

  /*
  * If no command line "-f" args then look for some form of "makefile"
  */
  if (!descset)
#ifdef unix
    if (rddescf (makefile, NO))
      if (rddescf (Makefile, NO))
        if (rddescf (makefile, YES))
          rddescf (Makefile, YES);

#endif
#ifdef mpx
  if (rddescf (makefile, NO))
    if (rddescf (makefile, YES))
#endif

  if (IS_ON (PRTR)) printdesc (NO);

  if (srchname (".IGNORE")) TURNON (IGNERR);
  if (srchname (".SILENT")) TURNON (SIL);
  if ((p=srchname (".SUFFIXES"))) sufflist = p->linep;
  if (!sufflist) fprintf (stderr, "No suffix list.\n");

#ifndef mpx
  sigivalue = (int) signal (SIGINT, (void (*)())1) & 01;
  sigqvalue = (int) signal (SIGQUIT, (void (*)())1) & 01;
#else
  sigivalue = (int) signal (SIGINT, 1) & 01;
  sigqvalue = (int) signal (SIGQUIT, 1) & 01;
#endif
  enbint (intrupt);

  nfargs = 0;

  for (i=1; i<argc; ++i)
    if ((s=argv [i]) != 0)
    {
      if ((p=srchname (s)) == 0)
      {
        p = makename (s);
      }
      ++nfargs;
      doname (p, 0, &tjunk);
      if (IS_ON (DBUG)) printdesc (YES);
    }

  /*
  If no file arguments have been encountered, make the first
  name encountered that doesn't start with a dot
  */

  if (nfargs == 0) {
    if (mainname == 0)
      fatal ("No arguments or description file");
    else
    {
      doname (mainname, 0, &tjunk);
      if (IS_ON (DBUG)) printdesc (YES);
    }
  }
  exitm (0);
}

void intrupt ()
{
  CHARSTAR p;

  if (okdel && IS_OFF (NOEX) && IS_OFF (TOUCH) &&
    (p = varptr ("@") ->varval) && exists (srchname (p)) >0 &&
    !isprecious (p))
  {
    if (unlink (p) == 0)
      fprintf (stderr, "\n***  %s removed.", p);
  }

  if (junkname [0])
    unlink (junkname);
  fprintf (stderr, "\n");
  exitm (2);
}

int isprecious (p)
CHARSTAR p;
{
  register NAMEBLOCK np;
  register LINEBLOCK lp;
  register DEPBLOCK dp;

  if ((np = srchname (".PRECIOUS")))
    for (lp = np->linep ; lp ; lp = lp->nextline)
      for (dp = lp->depp ; dp; dp = dp->nextdep)
        if (equal (p, dp->depname->namep))
          return (YES);

  return (NO);
}

void enbint(k)
#ifdef mpx
int (*k)();
#else
void (*k)();
#endif
{
  if (sigivalue == 0)
    signal (SIGINT, k);
  if (sigqvalue == 0)
    signal (SIGQUIT, k);
}

extern CHARSTAR builtin [];
CHARSTAR *linesptr=builtin;
FILE * fin;
int firstrd=0;

void rdmakecomm ()
{
#ifdef PWB
  register char *nlog;
  char s [128];

  if (rddescf (concat ((nlog=getenv ("HOME")), "/makecomm", s), NO))
    rddescf (concat (nlog, "/Makecomm", s), NO);

  if (rddescf ("makecomm", NO))
    rddescf ("Makecomm", NO);
#endif
}

extern int yylineno;
extern CHARSTAR zznextc;

int rddescf (descfile, flg)
CHARSTAR descfile;
int flg;	/* if YES try s.descfile */
{
  FILE * k;

  /* read and parse description */

  if (equal (descfile, "-"))
    return (rdd1 (stdin));

retry:
  if ((k = fopen (descfile, "r")) != NULL)
  {
    if (IS_ON (DBUG)) printf ("Reading %s\n", descfile);
    return (rdd1 (k));
  }

  if (flg == NO)
    return (1);
  if (get (descfile, CD, varptr (RELEASE) ->varval) == NO)
    return (1);
  flg = NO;
  goto retry;

}

int rdd1 (k)
FILE * k;
{
  fin = k;
  yylineno = 0;
  zznextc = 0;

  if (yyparse ())
    fatal ("Description file error");

  if (fin != NULL)
    fclose (fin);

  return (0);
}

void printdesc (prntflag)
int prntflag;
{
  NAMEBLOCK p;
  VARBLOCK vp;
  DIRLL od;
  /*
  DEPBLOCK dp;
  SHBLOCK sp;
  LINEBLOCK lp;
  */

  if (prntflag)
  {
    fprintf (stderr, "Open directories:\n");
    for (od=firstod; od!=0; od = od->nextopendir)
#ifdef mpx
      fprintf (stderr, "\t%d: %s\n", od->dirfc->dd_fd, od->dirn);
#else
      fprintf (stderr, "\tdir: %s\n", od->dirn);
#endif
  }

  if (firstvar != 0) fprintf (stderr, "Macros:\n");
  for (vp=firstvar; vp!=0; vp=vp->nextvar)
    if (vp->v_aflg == NO)
      printf ("\t%s = %s\n" , vp->varname , vp->varval);
    else
    {
      CHAIN pch;

      fprintf (stderr, "Lookup chain: %s\n\t", vp->varname);
      for (pch = (CHAIN)vp->varval; pch; pch = pch->nextchain)
        fprintf (stderr, " %s",
          ((NAMEBLOCK) pch->datap) ->namep);
      fprintf (stderr, "\n");
    }

  for (p=firstname; p!=0; p = p->nextname)
    prname (p, prntflag);
  printf ("\n");
  fflush (stdout);
}

void prname (p, prntflag)
register NAMEBLOCK p;
int prntflag;
{
  register LINEBLOCK lp;
  register DEPBLOCK dp;
  register SHBLOCK sp;

  if (p->linep != 0)
    printf ("\n\n%s:", p->namep);
  else
    fprintf (stderr, "\n\n%s", p->namep);
  if (prntflag)
  {
    fprintf (stderr, "  done=%d", p->done);
  }
  if (p==mainname) fprintf (stderr, "  (MAIN NAME)");
  for (lp = p->linep ; lp!=0 ; lp = lp->nextline)
  {
    if ((dp = lp->depp))
    {
      fprintf (stderr, "\n depends on:");
      for (; dp!=0 ; dp = dp->nextdep)
        if (dp->depname != 0)
        {
          printf (" %s", dp->depname->namep);
          printf (" ");
        }
    }
    if ((sp = lp->shp))
    {
      printf ("\n");
      fprintf (stderr, " commands:\n");
      for (; sp!=0 ; sp = sp->nextsh)
        printf ("\t%s\n", sp->shbp);
    }
  }
}

void setflags (ac, av)
int ac;
CHARSTAR *av;
{
  register int i, j;
  register char c;
  int flflg=0;		/* flag to note `-f' option. */

  for (i=1; i<ac; ++i)
  {
    if (flflg)
    {
      flflg = 0;
      continue;
    }
    if (av [i]!=0 && av [i] [0]==MINUS)
    {
      if (any (av [i], 'f'))
        flflg++;
      if (any (av [i], 'F'))
        flflg++;
      for (j=1 ; (c=av[i][j]) != CNULL ; ++j)
        optswitch (c);
      if (flflg)
        av [i] = "-f";
      else
        av [i] = 0;
    }
  }
}

/*
* Handle a single char option.
*/
void optswitch (c)
register char c;
{

  switch (c)
  {

  case 'B': /* use MH version of test for whether a cmd exists */
  case 'b': /* use MH version of test for whether a cmd exists */
    TURNON (MH_DEP);
    setmflgs ('b');
    break;

  case 'C': /* turn off -b flag */
  case 'c': /* turn off -b flag */
    TURNOFF (MH_DEP);
/*    setmflgs ('B'); was 'B' */
    setmflgs ('c');
    break;

  case 'D': /* debug flag */
  case 'd': /* debug flag */
    TURNON (DBUG);
    setmflgs ('d');
    break;

  case 'E': 	/* environment override flag */
  case 'e': 	/* environment override flag */
    setmflgs ('e');
    break;

  case 'F': /* Named makefile; already handled by setflags(). */
  case 'f': /* Named makefile; already handled by setflags(). */
    break;

  case 'G': /* turn default $(GET) of files not found */
  case 'g': /* turn default $(GET) of files not found */
    TURNON (GET);
    setmflgs ('g');
    break;

  case 'I': /* ignore errors */
  case 'i': /* ignore errors */
    TURNON (IGNERR);
    setmflgs ('i');
    break;

  case 'K':
  case 'k':
    TURNON (KEEPGO);
    setmflgs ('k');
    break;

  case 'L':
  case 'l':
    TURNOFF (KEEPGO);
/*    setmflgs ('S'); was 'S' */
    setmflgs ('l');
    break;

  case 'M': /* print memory map */
  case 'm': /* print memory map */
    TURNON (MEMMAP);
    setmflgs ('n');
    break;

  case 'N': /* do not exec any commands, just print */
  case 'n': /* do not exec any commands, just print */
    TURNON (NOEX);
    setmflgs ('n');
    break;

  case 'P': /* print description */
  case 'p': /* print description */
    TURNON (PRTR);
    break;

  case 'R': /* turn off internal rules */
  case 'r': /* turn off internal rules */
    TURNOFF (INTRULE);
    break;

  case 'S': /* silent flag */
  case 's': /* silent flag */
    TURNON (SIL);
    setmflgs ('s');
    break;

  case 'T': /* touch flag */
  case 't': /* touch flag */
    TURNON (TOUCH);
    setmflgs ('t');
    break;

  case 'Q': /* question flag */
  case 'q': /* question flag */
    TURNON (QUEST);
    setmflgs ('q');
    break;

  default:
    fatal1 ("Unknown flag argument %c", c);
  }
}

/*
* getmflgs() set the cmd line flags into an EXPORTED variable
* for future invocations of make to read.
*/
char dfs[] = "ZZZZZZZZZZZZZZZZ";

void getmflgs ()
{
  register VARBLOCK vpr;
  register CHARSTAR *pe;
  register CHARSTAR p;

  vpr = varptr (Makeflags);
#ifdef OLDWAY
  setvar (Makeflags, "ZZZZZZZZZZZZZZZZ");
#else
  setvar (Makeflags, dfs);
#endif
  vpr->varval [0] = CNULL;
  vpr->envflg = YES;
  vpr->noreset = YES;
  optswitch ('b');
  for (pe = environ; *pe; pe++)
  {
    if (sindex (*pe, "MAKEFLAGS=") == 0)
    {
      for (p = (*pe)+sizeof Makeflags; *p; p++)
        optswitch (*p);
      return;
    }
  }
}

/*
* setmflgs(c) sets up the cmd line input flags for EXPORT.
*/

void setmflgs (c)
register char c;
{
  register VARBLOCK vpr;
  register CHARSTAR p;

  vpr = varptr (Makeflags);
  for (p = vpr->varval; *p; p++)
  {
    if (*p == c)
      return;
  }
  *p++ = c;
  *p = CNULL;
}
