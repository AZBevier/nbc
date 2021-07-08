/*~!dosys.c*/
/* Name:  dosys.c Part No.: _______-____r
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

#ident	"$Id: dosys.c,v 1.4 2021/07/06 21:47:12 jbev Exp $"

#include "defs.h"
#ifndef mpx
#include <wait.h>
#endif

int doexec();
int doshell();
int metas();
void doclose();
#ifndef mpx
int await();
#endif
void touch();
extern void enbint();
extern void msetenv();
extern void fatal();
extern int Execvp();
extern int doexec();
extern int docd();
extern int mywaitpid;
extern void fatal1();

extern char Makecall;

int dosys (comstring, nohalt)
register CHARSTAR comstring;
int nohalt;
{
  register CHARSTAR p;
  int status;

  p = comstring;
  while (*p == BLANK ||
    *p == TAB ||
    *p == AT ||
    *p == MINUS ||
    *p == CNULL) p++;

  if (IS_ON (NOEX) && Makecall == NO)
    return (0);

  if (metas (comstring))
    status = doshell (comstring, nohalt);
  else
    status = doexec (comstring);

  return (status);
}

int metas (s) /* Are there are any  Shell meta-characters? */
register CHARSTAR s;
{
  while (*s)
#ifdef mpx_4shell_temp_fix
    if (*s != '>' && funny [*s] & META)
      return (YES);
    else
      s++;
#else
    if (funny [(int)*s++] & META)
      return (YES);
#endif

  return (NO);
}

int doshell (comstring, nohalt)
register CHARSTAR comstring;
register int nohalt;
{
  register CHARSTAR shell;
#ifdef mpx
  int status;
#endif

#ifndef mpx
  if ((mywaitpid = fork ()) == 0)
  {
    enbint (0);
    doclose ();

    msetenv ();
    shell = varptr ("SHELL")->varval;
    if (shell == 0 || shell [0] == CNULL)
      shell = SHELLCOM;
    execl (shell, "sh", (nohalt ? "-c" : "-ce"), comstring, (char *)0);
    fatal ("Couldn't load Shell");
  }

  return (await ());
#else
#ifdef NASA_DEBUG
  printf("DOSH program %s\n", SHELLCOM);
#endif
  doclose ();
  msetenv ();
  shell = varptr ("SHELL")->varval;
  if (shell == 0 || shell [0] == CNULL)
    shell = SHELLCOM;
#ifdef DEBUG
printf("vexecl %s comm %s\n", shell, comstring);
#endif
  status = vexecl (shell, "sh", (nohalt ? "-c" : "-ce"), comstring, 0);
#ifdef DEBUG
printf("vexecl status %d\n", status);
#endif
  if (status < 0)fatal ("Couldn't load Shell");
  if (status > 0)fatal ("Shell aborted");
  freenv();
  return (status);
#endif
}

#ifndef mpx
int await ()
{
  int intrupt ();
  int status;
  int pid;

  enbint (intrupt);
  while ((pid = wait (&status)) != mywaitpid) {
    if (pid == -1)
      fatal ("bad wait code");
  }
  mywaitpid = 0;
  return (status);
}
#endif

void doclose () /* Close open directory files before exec'ing */
{
#ifdef mpx
  register DIRLL od;

  for (od = firstod; od != 0; od = od->nextopendir)
    if (od->dirfc != NULL) {
#ifdef NASA_DEBUG
      printf("DOCLOSE directory %s fd %d\n", od->dirn, od->dirfc);
#endif
      closedir(od->dirfc);
      firstod = od->nextopendir;	/* set new entry */
      free (od->dirn);		/* free directory name */
      free (od);		/* free the node */
    }
#endif
}

char *
lastfield(s)
register char *s;
{
    register char *t;
    for (t = s; *s ; ++s)
    	if (*s == '/' || *s == ')')
    	    t = s+1;
    return(t);
}

int doexec (str)
register CHARSTAR str;
{
  register CHARSTAR t;
  register CHARSTAR *p;
  CHARSTAR argv [200];
#ifdef mpx
  int status;
#endif

  while (*str==BLANK || *str==TAB)
    ++str;
  if (*str == CNULL)
    return (-1); /* no command */

  p = argv;
  for (t = str ; *t ; )
  {
    *p++ = t;
    while (*t!=BLANK && *t!=TAB && *t!=CNULL)
      ++t;
    if (*t)
      for (*t++ = CNULL ; *t==BLANK || *t==TAB  ; ++t)
        ;
  }

  *p = NULL;

  /* see if command is a cd command, and if so, do it locally */
  t = lastfield(str);		/* get the command name */
  if (!strcmp(t,"cd")) {
    /* we found a cd command */
    if(docd(2, argv)) {
      fatal1 ("Cannot cd to directory %s", *argv);
    }
    return(0);
  }

#ifndef mpx
  if ((mywaitpid = fork ()) == 0)
  {
    enbint (0);
    doclose ();
    msetenv ();
    Execvp (str, argv);
    fatal1 ("Cannot load %s", str);
  }

  return (await ());
#else
#ifdef NASA_DEBUG
  printf("DOEXEC program %s\n", str);
#endif
  doclose ();
  msetenv ();
  status = Execvp (str, argv);
  if (status < 0)fatal1 ("Cannot load %s", str);
  if (status > 0)fatal1 ("%s aborted", str);
  freenv();
  return (status);
#endif
}

void touch (s)
register CHARSTAR s;
{
#ifdef mpx
  utime (s, 0);
#else
  if (junkname [0] == 0)
    sprintf (junkname, "MAKEJUNK%d", getpid ());

  link (s, junkname);
  unlink (junkname);
  sleep (1);
#endif
}
