/*~!exec.c*/
/* Name:  exec.c Part No.: _______-____r
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

#ident	"@(#)nbclib:exec.c	1.1"

#include <mosde.h>				/* !MOD */
#include <sys/types.h>
#include <psb.h>
#include <prb.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#ifndef NULL
#define NULL 0
#endif

extern  char** environ;  /* current environment pointers */
extern int curwdir[];	/* defined in mpxini.c */
static int taskdone = 0;	/* set none zero when task completes */

/*
 * this routine simulates the fork/exec pair of UNIX.
 * up to 768 bytes of parameters/environment can be passed
 * to the receiving task.
 *
 * the buffer is layed out as a series of strings, null terminated.
 * the end of the args is represented by two null chars in a row.
 * the environment is likewise a series of null terminated strings.
 * the end of the environment is signified by two null bytes.
 * if three null bytes are at the end of the arguments, no environment
 * is present.
 *
 * arg0 [null]
 * arg1 [null]
 * .
 * argn [null]
 * [null]
 * env0 [null]  or [null] if no environment.
 * env1 [null]
 * .
 * envn [null]
 * [null]
 *
 */

int   vexecl (path, arg0, arg1, argn)
char *path;   /* pathname of task to activate */
char *arg0;   /* 1st of n args in stack */
char *arg1;   /* 2nd of n args in stack */
char *argn;   /* this must be null to indicate end of args */
{
  /* pass address of parameters in stack */
  return (vexecv (path, &arg0));   /* activate the task */
}

#ifdef MPX1X						/* MAC */
asm(" bound 1d");	/* must be dw bounded */	/* MAC */
static struct psb psb;   /* this must be double word bounded */ /* MAC */
static char buf[768];  /* send buffer */		/* MAC */
#endif							/* MAC */

/* activate the task, returns following codes */
/*  0 - task ran to completion */
/*  1 - task aborted */
/* -1 - activation error, errno contains error value */

int   vexecv (path, args)
char *path;   /* pathname of task to activate */
char **args;  /* array of char pointer of args to pass. NULL terminated */
{
#ifndef MPX1X						/* MAC */
  struct psb psb;   /* this must be double word bounded *//* MAC */
  char buf[768];  /* send buffer */			/* MAC */
#endif
  int reg[8];
  char filename [PATH_MAX];
  char *p;        /* temp pointer */
  char *np;       /* filename pointer */	/* !MOD */
  char *pp;       /* temp pointer */		/* !MOD */
  char *arg;  /* current arg */
  char **ep;  /* temp environment pointer */
  int numbytes;
  int i;					/* !MOD */

  errno = 0;  /* clear error code */
  if (!(path != 0 && *path != 0)) {
    errno = ENOENT;   /* set file not found error */
    return (-1);      /* error return value */
  }
  strcpy (filename, path);  /* copy file to local buffer */
  unix2mpx(filename);       /* convert to u/c mpx name */

  p = buf;
#ifdef MPX1X
  /* we must set the current username here */
  getcwvd();		/* get current username info */
  pp = (char *)curwdir;	/* point to username */
  for (i=0; i<8; i++)*p++ = pp[i];	/* copy username */
#endif
  if (!(args != 0 && *args != 0)) {
    /* copy program name as first parameter */
    if (arg = strrchr(filename, ')')) {
      /* arg points to ')' in pathname */
      arg++;
      while (*p++ = *arg++);
    } else {
      arg = filename;
      while (*p++ = *arg++);
    }
  }

  numbytes = strlen(buf);

  /* now copy args to buffer */
  for (; arg = *args++; ) {
      numbytes += strlen(arg);
      if (numbytes >= 768) {
        errno = ENOEXEC;
        return (-1);
      }
      while (*p++ = *arg++);
  }
  *p++ = NULL;  /* mark end of args with double null */

  if (++numbytes >= 768) {
    errno = ENOEXEC;
    return (-1);
  }

  /* copy environment to buffer if any */
  ep = environ;;    /* current environment */
  if (!(ep != 0 && *ep != 0 && **ep != 0)) {
    /* no environment */
    *p++ = (char )NULL;    /* end of environment */
  } else {
    /* copy environment to buffer */
    for (; arg = *ep++; ) {
      numbytes += strlen(arg);
      if (numbytes >= 768) {
        errno = ENOEXEC;
        return (-1);
      }
      while (*p++ = *arg++);
    }
    *p++ = NULL;    /* end of environment */
  }

  if (++numbytes > 768) {
    errno = ENOEXEC;
    return (-1);
  }

  reg[2] = (int)&psb.lmn;  /* parameter send block addr in reg 2 for call */
  reg[6] = 0;         /* clear for call */
  reg[7] = 0;         /* clear for call */
#ifdef MPX1X
  psb.lmn = 0x20202020;		/* set to blanks */
  psb.pnv = 0x20202020;		/* set to blanks */
  if (np = strrchr(filename, ')')) {
    /* np points to ')' in pathname */
    np++;
  } else {
    np = filename;
  }
  pp = (char *)&psb.lmn;	/* point to where filename goes */
  for (i=0; i<8 && np[i]; i++)pp[i] = np[i];	/* copy filename */
#else
  psb.lmn = 0;  /* run req will be by pnv */
  psb.pnv = (int)filename;  /* set filename */
  psb.pnv |= (strlen(filename) << 24);  /* make pnv */
#endif
  psb.pri = 0;    /* no priority */
  psb.squa = p - buf;   /* number of bytes */
  psb.sba = (int*)buf;  /* send buffer */
  psb.rpbl = sizeof(buf); /* ret param buf length */
  psb.acrp = 0;         /* nothing returned yet */
  psb.rba = (int*)buf;  /* send is also receive buf */
/*  psb.eaa = 0;          /* no end action addr */
  psb.cst = psb.ist = psb.ust = psb.opt = 0; /* no status yet */
  psb.opt = 0x80;	/* send no-wait */
  /* no end action addr */
  psb.eaa = (int *)popi();	/* initialize pipe msg receiver */
  mpxsvc (0x106d, reg, reg);  /* m.srunr svc call */
                              /* r6 & r7 has status */
  if (reg[6]) {     /* we have an initial error */
    switch (reg[6]) {
      case 2:
      case 9:
        errno = ENOENT;
        break;
      case 4:
        errno = ENOEXEC;
        break;
      case 5:
      case 15:
        errno = EAGAIN;
        break;
      case 6:
      case 7:
      case 10:
      case 11:
      case 12:
      case 13:
      case 16:
      default:
        errno = EFAULT;
        break;
      case 8:
      case 14:
        errno = ENOMEM;
        break;
      }
      return (-1);  /* return error indication */
  } else {          /* good run request, see if task aborted */
    asm(" svc 1,x'1b'");	/* m.sync */
    while(!taskdone) {
        asm(" li r6,-10");	/* ten timer units */
    	asm(" svc 1,x'7c'");	/* m.anywait */
    }
    taskdone = 0;
    if (psb.cst)    /* we have an abort */
      return(1);
    return (0);     /* aok */
  }
}

static int onetime = 0;		/* set if msg rec setup */

asm(" csect");
asm("MSGR sbm 31,_taskdone");
asm(" svc 1,x'7f'");		/* exit end action */

/* initialize message receiver address */
popi() {
  register int retv;

  asm(" la r7,MSGR");
  if (onetime)return(retv);
  onetime = 1;
  asm (" la r7,MSGRCV");	/* message receiver address */
  asm (" svc 1,x'6b'");		/* tell MPX about us */
  asm(" la r7,MSGR");
  return(retv);
}
  
/* PIPE msg receiver */

/*
 * message receiver for messages from server doing upcalls
 */
static struct prb prb;	/* parameter receive block */
static int msgret[2];	/* message return buf */
static char usa[260];	/* message parameters */
static int *rxb = msgret;	/* ret buffer address */
static int rxb2 = 0;	/* rxb 2nd word */

static msgdummy()	/* dummy entry */
{
    int retval;		/* return value */
    int errval;		/* error return value */

    asm ("MSGRCV sea");		/* entry */
    asm (" la r4,_usa");	/* receive buff addr */
    asm (" stw r4,_prb");	/* put in prb */
    asm (" li r4,260");		/* 260 bytes (max) to be returned */
    asm (" sth r4,_prb+1w");	/* set recv buff length */
    asm (" zmw _usa");		/* just for the hell of it */
    asm (" la r2,_prb");	/* parameter recv block addr */
    asm (" svc 1,x'7a'");	/* get data M.GMSGP */
    asm (" trr r6,r6");		/* test for error */
    asm (" bz MSG");		/* br if none */
    asm (" zmw _rxb2");		/* no return information */
    asm (" la r2,_rxb");	/* exit block */
    asm (" svc 1,x'5e'");	/* exit now */

    asm ("MSG la sp,stacke");	/* get a stack pointer */

process:			/* process the request */
    errval = 0;			/* error return value */
    retval = write(usa[3], &usa[4], prb.arq-4);

    /* the return value is returned in the exit parameter block buffer
     */

    msgret[0] = retval;		/* set return value */
    msgret[1] = errval;		/* set errno value */
    rxb2 = 8;			/* return 8 bytes */

    asm (" la r2,_rxb");	/* exit block */
    asm (" svc 1,x'5e'");	/* exit now M.XMSGR */

    asm (" dsect");
    asm (" bound 1d");
    asm (" rez 16f");		/* .5kb stack */
    asm (" bound 1f");
    asm ("stacke rez 1w");	/* end of stack */
    asm (" rez 3f");		/* parameter space */
    asm (" csect");
}

/* following are dummy unix system call entries */
/* they will return an error if called */

int execl(path, arg0, arg1, argn, zero)
char *path, *arg0, *arg1, *argn;
int zero;	/* just a 0 */
{
	errno = EFAULT;	/* show bad path */
	return(-1);	/* error return */
}

int execv(path, argv)
char *path, **argv;
{
	errno = EFAULT;	/* show bad path */
	return(-1);	/* error return */
}

int execle(path, arg0, arg1, argn, zero, envp)
char *path, *arg0, *arg1, *argn, **envp;
int zero;	/* just a 0 */
{
	errno = EFAULT;	/* show bad path */
	return(-1);	/* error return */
}

int execve(path, argv, envp)
char *path, **argv, **envp;
{
	errno = EFAULT;	/* show bad path */
	return(-1);	/* error return */
}

int execlp(file, arg0, arg1, argn, zero)
char *file, *arg0, *arg1, *argn;
int zero;	/* just a 0 */
{
	errno = EFAULT;	/* show bad path */
	return(-1);	/* error return */
}

int execvp(file, argv)
char *file, **argv;
{
	errno = EFAULT;	/* show bad path */
	return(-1);	/* error return */
}
