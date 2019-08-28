/*~!unixio.c*/
/* Name:  unixio.c Part No.: _______-____r
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

#ident	"@(#)nbclib:unixio.c	1.2"

/*
 *      unixio.c
 *
 *      UNIX I/O emulation routines - by JCB
 *
 *	Most of the functions in this file simulate UNIX svc's.
 *	They have been modified to follow System V conventions.
 */

/* this version opens mode 1 as mpx update.   */
/* This is because write mode in MPX is not   */
/* sufficiently similar to write mode on UNIX */

/* For MPX1X make as small as possible at expense of speed */
#ifdef MPX1X
#define NOBBS
#endif

#define _ERRNODEF
#include <types.h>
#include <limits.h>
#include <errno.h>
#include "unixio.h"
#include <stat.h>
#include <string.h>
#include <fcntl.h>

#ifndef NOBBS
static struct ioc *ircont();
static int rmopen();
static int rmclose();
static int rmrwnd();
static int rmweof();
static int rmback();
static int rmread();
#ifdef NOT_FOR_NOW
static int rmadvr();
#endif
static int rmadvf();
static int rmwrit();
/* int rmwrit(); */
static int bfback();
/* int bfback(); */
static int bfredf();
static int bfwrit();
static int plredf();
static int plwrit();
static int plrwnd();
static int flposs();
static int irweof();
static int irfinis();
static int rmerr();
#endif

#ifndef	min
#define	min(x,y)	((x)<(y)?(x):(y))	/* Lesser of two args */
#endif
#ifndef max
#define	max(x,y)	((x)>(y)?(x):(y))	/* Greater of two args */
#endif

#define ERROR (-1)	/* error return value */
#define IOEND (-2)	/* this is EOF/EOM */
#define IOEOF (0)	/* this is an EOF */
#define GOOD (0)	/* good return value */

/*    data transfer routines */

/* write primitive */

int write(fd, buf, n)
int fd;
char *buf;
int n;
{
  register int mode;
  register int dev;
  int count = 0;
  int i;

  BADFD(fd, ERROR);
  INIT;
  if(n <= 0) {
    errno = EINVAL;
    mpxerr = E010;
    return(ERROR);
  }
  mode = curfprm->mode;
  dev =  curfprm->device;
  if(mode & NOTUSED) {
    errno = EBADF;
    mpxerr = E010;
    return(ERROR);
  }
  if(!(mode & (O_WRONLY | O_RDWR))) {
    errno = EACCES;
    mpxerr = E011;
    return(ERROR);
  }

  if(dev == NULLFILE)
    return(n);

  if(dev == PIPE) {	/* if pipe send data to parent task */
    snddata(fd,buf,n);
    return(n);
  }

  if(curfprm->eof || curfprm->eom) {	/* see if at eof/eom */
  curfprm->eof = 0;			/* reset EOF */
  curfprm->eom = 0;			/* reset EOM */
    return(IOEOF);			/* this means eof/eom */
  }

  if(curfprm->block) {
    int zz;
    int yy;

    if(!curfprm->binary) {
      char *p, *bp, *lp;

      /* we only do this after a linefeed char or 1st time */
      if(dev == TERMINAL)
	if(curfprm->crlf != 1) {
	  curfcb->cntl.dfi = 0;		/* allow cr/lf */
          i = _putrec(1, " ");		/* force c/r l/f to be output */
	  curfcb->cntl.dfi = 1;
	  curfprm->crlf = 1;
          if(i != GOOD)
    	    return(i == ERROR ? ERROR : IOEOF);
        }
      lp = curfil->line;
      bp = &curfil->line[curfprm->linptr];
      p = buf;

      for(i=0; i<n; i++) {
        if(lp == bp && dev == SPOOLFILE) {
          if(carcont) {
            /* put correct carriage control for terminal or SLO*/
            if(*p == 0x0c) {
               *bp++ = '1';
               p++;
    	       count++;
            } else {
               *bp++ = ' ';
            }
            curfprm->linptr++;
          }
        }

        if(*p == '\n') {
          if(dev != TERMINAL) {
            if(bp == lp) {
              *bp++ = ' ';
              curfprm->linptr++;
            }
	    p++;
            count++;
          } else {
	    if(curfprm->linptr) {
              yy = _putrec(curfprm->linptr, lp);
              if(yy != GOOD)
    		return(count ? count : (yy == ERROR ? ERROR : IOEOF));
    	    }
	    curfcb->cntl.dfi = 0;	/* allow cr/lf */
            yy = _putrec(1, " ");	/* force c/r l/f to be output */
	    curfcb->cntl.dfi = 1;	/* restore user status */
	    curfprm->crlf = 1;		/* don't do again */
            bp = lp = curfil->line;
            curfprm->linptr = 0;
            p++;
            if(yy != GOOD)
    	      return(count ? count : (yy == ERROR ? ERROR : IOEOF));
            count++;
          }
    	  yy = GOOD;
          zz = bp - lp;
          while((zz > 254) && ((yy = _putrec(254, lp)) == GOOD)) {
            zz -= 254;
            lp += 254;
          }
          if(yy != GOOD)
    	    return(count ? count : (yy == ERROR ? ERROR : IOEOF));
          if(zz)
    	    yy = _putrec(zz, lp);
          if(yy != GOOD)
    	    return(count ? count : (yy == ERROR ? ERROR : IOEOF));
          bp = lp = curfil->line;
          curfprm->linptr = 0;
        } else {
          *bp++ = *p++;
          curfprm->linptr++;
          count++;
        }
      }
      if((lp != bp) && curfprm->device == TERMINAL) {
    	yy = GOOD;
        zz = bp - lp;
        if(zz)
    	  yy = _putrec(zz, lp);
        bp = lp = curfil->line;
        curfprm->linptr = 0;
        if(yy != GOOD)
    	  return(count ? count : (yy == ERROR ? ERROR : IOEOF));
      }
      return(n);
    }
    /* process blocked binary file */
    yy = GOOD;
    zz = n;
    while((zz > 254) && ((yy = _wbl(buf, 254)) == GOOD)) {
      zz -= 254;
      buf += 254;
      count += 254;
    }
    if(yy != GOOD)
      return(count ? count : (yy == ERROR ? ERROR : IOEOF));
    if(zz)
      yy = _wbl(buf, zz);
    if(yy != GOOD)
      return(count ? count : (yy == ERROR ? ERROR : IOEOF));
    count += zz;
    return(n);
  }
  /* process unblocked file */
  return(_wub(buf, n));
}

/* read1line primitive */
/* reads only until an EOL */
int read1ln(fd, buf, n)
int fd;
char *buf;
int n;
{
    return(readcom(fd, buf, n, 1));	/* read one line */
}

/* read primitive */
int read(fd, buf, n)
int fd;
char *buf;
int n;
{
    return(readcom(fd, buf, n, 0));	/* read n chars */
}

/* read primitive */
int readcom(fd, buf, n, one)
int fd;
char *buf;
int n;
int one;
{
  register int mode;
  register int dev;

  BADFD(fd, ERROR);
  INIT;
  curfprm->oneln = one;
  mode = curfprm->mode;
  dev =  curfprm->device;
  if(mode & NOTUSED) {
    errno = EBADF;
    mpxerr = E012;
    return(ERROR);
  }
  if(mode & O_WRONLY) {
    errno = EACCES;
    mpxerr = E013;
    return(ERROR);
  }
  if(dev == NULLFILE) {
    curfprm->eof = 1;
    curfprm->eom = 1;
    return(IOEOF);		/* return EOF */
  }
  if(n <= 0)
    return(IOEOF);

  return((curfprm->block ? _rbl : _rub)(buf, n));
}

/* seek primitive */

int seek(fd, off, rel)
int  fd, rel;
long off;
{

  BADFD(fd, ERROR);
  INIT;
  if((rel > 2) || (rel < 0)) {
    errno = EINVAL;
    mpxerr = E014;
    return(ERROR);
  }
  if(curfprm->mode & NOTUSED) {
    errno = EBADF;
    mpxerr = E015;
    return(ERROR);
  }
  if(curfprm->device == NULLFILE)
    return(IOEOF);

  if(curfprm->block && (rel==1 || off)) {
    errno = EINVAL;
    mpxerr = E016;
    return(ERROR);
  }
  if(curfprm->device != DISCFILE && curfprm->device != TERMINAL) {
    if(rel==1 || off) {
      errno = EINVAL;
      mpxerr = E016;
      return(ERROR);
    }
    else {
      return(_skdv(rel));
    }
  }
  else {
    return((curfprm->block ? _skbl : _skub)(off, rel));
  }
}

static int _wbl(buf, n)
char *buf;
int n;
{
  char *linadrs;
  int i;

  /* version of wbl for binary blocked files */
  linadrs = curfil->line;

  memcpy(linadrs, buf,n);	/* move the bytes */

  curfprm->linptr = n;

  /* write the data record */
  return(_putrec(n, linadrs));
}

static int _rbl(buf, n)
char *buf;
int n;
{
  register int count = 0;
  register char *cp;
  int i, j;
  char *linadrs;

  if(!curfprm->cmpop) {		/* see if we tested for compressed */
    curfprm->cmpop = 1;			/* set comp tested flag */
    /* read in the first record */
    if((i = _getrec()) == ERROR)
      return(ERROR);			/* this means error */
    if(i == IOEND)
      return(IOEOF);	/* this means eof */
    linadrs = curfil->line;
    curfprm->charcnt = 0;		/* no chars going out */
    curfprm->blanks = 0;		/* no blanks to output */
    if(*linadrs == 0xbf) {		/* is this file compressed */
      curfprm->cmpflg = 1;		/* set comp data flag */
      curfprm->bcnt = linadrs[1];	/* set record count */
      curfprm->bptr = &linadrs[6];      /* set data address */
      curfprm->state = CBLANKS;		/* next state is blanks */
    } else goto re00;
  }

  if(curfprm->cmpflg) {		/* reading compressed data? */
    /* this code has been changed to fill the entire buffer
     * like the normal System V Unix code
     */
re10:
    if(curfprm->bcnt == 0) {		/* any data left in buffer */
re18:
      curfprm->state = CBLANKS;		/* next state is blanks */
      if(curfprm->eof)			/* see if at eof */
        return(IOEOF);			/* this means eof */
      /* read in a data record */
      if((i = _getrec()) == ERROR)
    	return(count ? count : ERROR);	/* this means error */
      if(i == IOEND)
    	return(count ? count : IOEOF);	/* this means eof */
      linadrs = curfil->line;
      if((*linadrs & 0xdf) != 0x9f)    /* is this valid rec */
        return(count ? count : ERROR);	/* error if not */
      curfprm->bcnt = linadrs[1];	/* set record count */
      curfprm->bptr = &linadrs[6];	/* set data address */
      curfprm->charcnt = 0;		/* no chars going out */
      curfprm->blanks = 0;		/* no blanks to output */
      curfprm->state = CBLANKS;		/* next state is blanks */
    }
re20:
    /* 1st thing after a read is to check for blanks */
    if(curfprm->state == CBLANKS) {	/* see if state is blanks */

      /* see if any blanks left to output from previous call */
      if(curfprm->blanks) {

        while(curfprm->blanks) {
    	  if(count < n) {
    	    *buf++ = ' ';		/* put blank in buffer */
    	    count++;
    	    curfprm->blanks--;		/* decr count */
    	  } else {
    	    return(count);		/* that's all the user wants */
    	  }
    	}
    	curfprm->state = CCHARS;	/* next state is chars */

      } else {

        /* check for any blanks to output, this is 1st time after read */
    	if(curfprm->blanks = *curfprm->bptr++) { /* next buffer pointer */

    	  /* see if this is the end of the line */
    	  if(curfprm->blanks == 0xff) {
    	    curfprm->blanks = 0;	/* no blanks to output */
    	    /* if eol, get out */
    	    curfprm->bcnt--;		/* decr count */
    	    if((*--buf == ' ') && (count == 1)) {
    	      *buf = '\n';		/* put new line at eol */
    	    } else {
    	      *++buf = '\n';		/* put new line at eol */
    	      count++;
    	    }
    	    buf++;			/* next open position */
    	    if(curfprm->oneln)		/* just 1 line wanted */
    	      return(count);		/* return 1 lines worth */
    	    if(count < n)
    	      goto re10;		/* keep filling buffer */
    	    return(count);		/* return for now */
    	  }

    	  /* not at EOL and blanks to output */
    	  while(curfprm->blanks) {
    	    if(count < n) {
    	      *buf++ = ' ';		/* put blank in buffer */
    	      count++;
    	      curfprm->blanks--;	/* decr count */
    	    } else {
    	      return(count);		/* that's all the user wants */
    	    }
    	  } /* end of while */

        } /* end if blanks */

      } /* end of else for blanks */
    curfprm->state = CCHARS;	/* next state is chars */

    } /* end if in CBLANKS state */
    	
    /* see if state is CCHARS */
    if(curfprm->state == CCHARS) {

      /* we are processing characters */
      /* see if any chars left */
      if(curfprm->charcnt) {

        while(curfprm->charcnt) {
    	  if(count < n) {
    	    *buf++ = *curfprm->bptr;	/* put char in buffer */
    	    curfprm->bcnt--;		/* decr count */
    	    curfprm->bptr++;		/* next buffer pointer */
    	    count++;
    	    curfprm->charcnt--;		/* decr count */
    	  } else
    	    return(count);		/* that's all the user wants */
    	}
    	curfprm->state = CBLANKS;	/* next state is blanks */

      } else {

        /* if nothing left in buffer, go get next */
    	/* state will go to CBLANKS when we do read */
    	if(--curfprm->bcnt <= 0)
    	  goto re18;			/* read next record */

    	/* get number of chars to output */
    	if(curfprm->charcnt = *curfprm->bptr++) { /* next buffer pointer */

    	  while(curfprm->charcnt) {
    	    if(count < n) {
    	      *buf++ = *curfprm->bptr;	/* put char in buffer */
    	      curfprm->bcnt--;		/* decr count */
    	      curfprm->bptr++;		/* next buffer pointer */
    	      count++;
    	      curfprm->charcnt--;	/* decr count */
    	    } else
    	      return(count);		/* that's all the user wants */
    	  }
    	}
    	curfprm->state = CBLANKS;	/* next state is blanks */

      }
    }

    if(--curfprm->bcnt <= 0)
      goto re18;			/* read next record */
    goto re20;				/* go process blanks */

  } else {

    /* non compressed read here */

    /* see if data left */
    if(curfprm->charcnt >= curfprm->blanks) {
    	if(curfprm->eof)		/* see if at eof */
    	    return(IOEOF);		/* this means eof */
    	/* none left, read the next record */
    	if((i = _getrec()) == ERROR)
    	    return(ERROR);		/* this means error */
    	if(i == IOEND)
    	    return(IOEOF);		/* this means eof */
re00:
    	/* 1st read merges here */
    	linadrs = curfil->line;		/* start at beginning of buffer */
    	curfprm->charcnt = 0;		/* nothing processed yet */
    	curfprm->blanks = curfcb->recl;	/* save num of chars read */

    	/* here we need to strip off blank put in during write */
    	/* this is because mpx does not support zero length blocks */
    	/* if reading in binary mode, leave buffer alone */
    	if(!curfprm->binary) {
    	    if((curfprm->blanks == 1) && (*linadrs == ' ') &&
    	      (curfprm->device != TERMINAL))
    		curfprm->blanks = 0;
    	    /* now append new line to end of buffer */
    	    /* if we have not read a full buffer */
    	    if(curfprm->blanks != 254) {
    		/* point to 1 char position past end */
    		/* and count added newline */
    		linadrs[curfprm->blanks++] = '\n';
    	    }
    	}
    }
    /* copy this layer buffer to upper caller's buffer.
     * start from where we left off and keep reading until
     * the request has been completed or eof found.
     */

    while(count < n) {
    	/* determine the number of chars left */
    	linadrs = curfil->line + curfprm->charcnt;
    	i = curfprm->blanks - curfprm->charcnt;
    	if(i <= 0) {
    	    if(curfprm->eof)			/* see if at eof */
    		return(count ? count : IOEOF);	/* this means eof */
    	    /* none left, read the next record */
    	    if((i = _getrec()) == ERROR)
    		return(count ? count : ERROR);	/* this means error */
    	    if(i == IOEND)
    		return(count ? count : IOEOF);	/* this means eof */
    	    goto re00;			/* go process buffer */
    	}
    	j = min(i, n-count);		/* how many to move */
    	memcpy(buf, linadrs, j);	/* move the bytes */
    	buf += j;			/* update buffer address */
    	curfprm->charcnt += j;		/* update count */
    	count += j;			/* update total */
    	/* if terminal read or mpx 1 line read, we are done */
        /* Added binary to fix cp, mv, etc in make4mpx 12/17/97 */
		if((curfprm->device == TERMINAL) || curfprm->oneln || curfprm->binary)
    	    break;
    }
  }
  return(count);

}

/*  getrec function   */

static int _getrec() {

  curfcb->bufaddr = curfil->line;
  curfcb->excount = (curfprm->block ? 254 : BUFSIZ);
  curfcb->exracc = curfprm->blkptr;

#ifndef NOBBS
  if(curfprm->bbs) {		/* see if using large blocking */
    rmread(iofd, curfcb->bufaddr, curfcb->excount); /* read a record */
  } else {
    asm(" lw r1,_curfcb");
    asm(" svc 1,x'31'");	/* read a record */
  }
#else
  asm(" lw r1,_curfcb");
  asm(" svc 1,x'31'");		/* read a record */
#endif

  if(curfcb->devstat & 0x40000000) {
    errno = EACCES;
    mpxerr = E017;
    return(ERROR);	/* error encountered */
  }
  if(curfcb->devstat & 0x01000000) {
    errno = EFBIG;
    mpxerr = E018;
    curfprm->eom = 1;
    return(IOEND);	/* eom encountered */
  }
  if(curfcb->devstat & 0x02000000) {  /* eof encountered */
    errno = 0;
    mpxerr = E019;
    curfprm->eof = 1;
    return(IOEND);	/* eof encountered */
  }
  return(GOOD);
}

/*  putrec function  */

static int _putrec(count, plinad)
int count;
char *plinad;
{

  curfcb->excount = count;
  curfcb->bufaddr = plinad;
  curfcb->exracc = curfprm->blkptr;

#ifndef NOBBS
  if(curfprm->bbs) {		/* see if using large blocking */
    rmwrit(iofd, plinad, count);	/* write a record */
  } else {
    asm(" lw r1,_curfcb");
    asm(" svc 1,x'32'");	/* write a record */
  }
#else
  asm(" lw r1,_curfcb");
  asm(" svc 1,x'32'");		/* write a record */
#endif

  if(curfcb->devstat & 0x40000000) {
    errno = EACCES;
    mpxerr = E020;
    return(ERROR);	 /* error */
  }
  if(curfcb->devstat & 0x02000000) {
    errno = EFBIG;
    mpxerr = E021;
    curfprm->eof = 1;
    return(IOEND);	/* eof */
  }
  curfprm->linptr = 0;
  if(curfcb->devstat & 0x01000000) {
    errno = EFBIG;
    mpxerr = E022;
    curfprm->eom = 1;
    return(IOEND);	/* eom encountered */
  }
  return(GOOD);
}

/*
    data transfer unblocked routines
    _wub() and _rub
 */

static int _wub(buf, n)
char *buf;
int n;
{
  int i;
  register int count = 0;
  register int mode = curfprm->mode;    /* should be 1 or 2 */
  register int useable;
  long l, m;

  char *linadrs;

  linadrs = curfprm->linptr + curfil->line;

  if(!BUFVALID && (mode & O_RDWR)) {
    /* read in a data record */
    if((i = _getrec()) == ERROR)
      return(ERROR);			/* this means error */
    if(i == IOEND) {
      /* EOM is OK here, read is not allowed to extend file */
      curfprm->eof = 0;			/* reset eof */
      curfprm->eom = 0;			/* reset eom */
      memset(curfil->line, 0, BUFSIZ);	/* clear the block */
    }
    BUFALTER = 0;
    BUFVALID = 1;
  }

#ifndef NEWSTUFF
  m = n;				/* bytes left to go out */
  while(m) {
    useable = min(m, BUFSIZ - curfprm->linptr);	/* space left */
    memcpy(linadrs, buf, useable);	/* move the bytes */
    linadrs += useable;			/* new current address */
    count += useable;			/* count output so far */
    curfprm->linptr += useable;		/* new count */
    buf += useable;			/* next user address */
    m -= useable ;			/* bytes to go yet */
    BUFALTER = 1;			/* we wrote to it */
    BUFVALID = 1;			/* we wrote to it */

    /* see if time to write block */
    if(curfprm->linptr >= BUFSIZ) {
      if(BUFALTER) {
    	/* write out the record */
    	if(curfprm->eof)			/* see if at eof */
    	  return(count ? count : IOEOF);	/* this means eof */
    	if((i = _putrec(BUFSIZ, curfil->line)) == ERROR)
    	  return(count ? count : ERROR);	/* this means error */
    	if(i == IOEND)
    	  return(count ? count : IOEOF);	/* this means eof */
      }
      curfprm->blkptr++;			/* next block */
      l = (BUFSIZ * curfprm->blkptr);		/* new file offset */

      if((mode & O_RDWR) || (l <= curfprm->eofptr)) {
        /* read in a data record */
        if((i = _getrec()) == ERROR)
    	  return(count ? count : ERROR);	/* this means error */
        if(i == IOEND){
          /* EOM is OK here, read is not allowed to extend file */
          curfprm->eof = 0;			/* reset eof */
          curfprm->eom = 0;			/* reset eom */
    	  memset(curfil->line, 0, BUFSIZ);	/* clear the block */
          BUFALTER = 0;				/* not written to yet */
    	  BUFVALID = 1;
        }
      } else {
    	memset(curfil->line, 0, BUFSIZ);	/* clear the block */
        BUFALTER = 0;
    	BUFVALID = 0;
      }
      linadrs = curfil->line;
      curfprm->linptr = 0;
    }
  }
#else
  while(count < n) {

    if(curfprm->linptr >= BUFSIZ) {
      if(BUFALTER) {
    	/* write out the record */
    	if(curfprm->eof)			/* see if at eof */
    	  return(count ? count : IOEOF);	/* this means eof */
    	if((i = _putrec(BUFSIZ, curfil->line)) == ERROR)
    	  return(count ? count : ERROR);	/* this means error */
    	if(i == IOEND)
    	  return(count ? count : IOEOF);	/* this means eof */
      }
      curfprm->blkptr++;
      l = (BUFSIZ * curfprm->blkptr);

      if((mode & O_RDWR) || (l <= curfprm->eofptr)) {
        /* read in a data record */
        if((i = _getrec()) == ERROR)
    	  return(count ? count : ERROR);	/* this means error */
        if(i == IOEND){
          /* EOM is OK here, read is not allowed to extend file */
          curfprm->eof = 0;			/* reset eof */
          curfprm->eom = 0;			/* reset eom */
    	  memset(curfil->line, 0, BUFSIZ);	/* clear the block */
          BUFALTER = 0;
        }
      } else {
    	memset(curfil->line, 0, BUFSIZ);	/* clear the block */
        BUFALTER = 0;
      }
      linadrs = curfil->line;
      curfprm->linptr = 0;
    }
    *linadrs++ = *buf++;
    BUFALTER = 1;
    BUFVALID = 1;
    count++;
    curfprm->linptr++;
  }
#endif /* NEW_STUFF */

  l = curfprm->linptr + (BUFSIZ * curfprm->blkptr);
  if((mode & O_RDWR) || (mode & O_WRONLY)) {
    /* update mode, eofpos is max of previous and current */
    if(l > curfprm->eofptr) curfprm->eofptr = l;
  } else {
    /* write mode, eofpos is current */
    curfprm->eofptr = l;
  }
  return(count);

}

static int _rub(buf, n)
char *buf;
int n;
{
  register int count = 0;
  register int useable;
  int i, m;
  char *linadrs;

  if(curfprm->eof) {
    errno = 0;
    mpxerr = E023;
    return(IOEOF);
  }
  linadrs = curfprm->linptr + curfil->line;

  if(!BUFVALID) {
    /* none left, read the next record */
    if(curfprm->eof)		/* see if at eof */
      return(IOEOF);		/* this means eof */
    if((i = _getrec()) == ERROR)
      return(ERROR);		/* this means error */
    if(i == IOEND)
      return(IOEOF);		/* this means eof */
    /* otherwise we have a good buffer */
    BUFALTER = 0;
    BUFVALID = 1;
  }

#ifndef NEWSTUFF
  m = n;				/* bytes left to read */
  while(m) {
    useable = min(m, BUFSIZ - curfprm->linptr);	/* space left */
    memcpy(buf, linadrs, useable);	/* move the bytes */
    linadrs += useable;			/* new current address */
    count += useable;			/* count output so far */
    curfprm->linptr += useable;		/* new count */
    buf += useable;			/* next user address */
    m -= useable ;			/* bytes to go yet */

    if(BUFSIZ * curfprm->block + curfprm->linptr >= curfprm->eofptr) {
      curfprm->eof = 1;
      break;
    }
    /* see if time to read another block */
    if(curfprm->linptr >= BUFSIZ) {
      if(BUFALTER) {
    	/* mode presumed to be O_RDWR here */
    	/* write out the record */
    	if(curfprm->eof)			/* see if at eof */
    	  return(count ? count : IOEOF);	/* this means eof */
    	if((i = _putrec(BUFSIZ, curfil->line)) == ERROR)
    	  return(count ? count : ERROR);	/* this means error */
    	if(i == IOEND)
    	  return(count ? count : IOEOF);	/* this means eof */
      }
      curfprm->blkptr++;
      if(curfprm->eof)			/* see if at eof */
    	return(count ? count : IOEOF);	/* this means eof */
      /* none left, read the next record */
      if((i = _getrec()) == ERROR)
    	return(count ? count : ERROR);	/* this means error */
      if(i == IOEND)
    	return(count ? count : IOEOF);	/* this means eof */
      BUFALTER = 0;
      BUFVALID = 1;
      linadrs = curfil->line;
      curfprm->linptr = 0;
    }
  }	/* end while */
#else
  while(count < n) {

    if(curfprm->linptr >= BUFSIZ) {
      if(BUFALTER) {
    	/* mode presumed to be O_RDWR here */
    	/* write out the record */
    	if(curfprm->eof)			/* see if at eof */
    	  return(count ? count : IOEOF);	/* this means eof */
    	if((i = _putrec(BUFSIZ, curfil->line)) == ERROR)
    	  return(count ? count : ERROR);	/* this means error */
    	if(i == IOEND)
    	  return(count ? count : IOEOF);	/* this means eof */
      }
      curfprm->blkptr++;
      if(curfprm->eof)			/* see if at eof */
    	return(count ? count : IOEOF);	/* this means eof */
      /* none left, read the next record */
      if((i = _getrec()) == ERROR)
    	return(count ? count : ERROR);	/* this means error */
      if(i == IOEND)
    	return(count ? count : IOEOF);	/* this means eof */
      BUFALTER = 0;
      linadrs = curfil->line;
      curfprm->linptr = 0;
    }
    *buf++ = *linadrs++;
    count++;
    curfprm->linptr++;
    if(BUFSIZ * curfprm->block + curfprm->linptr >= curfprm->eofptr) {
      curfprm->eof = 1;
      break;
    }
  }	/* end while */
#endif /* NEW_STUFF */
  return(count);
}

/*    seek unblocked function */

static int _skub(off, type)
int type;
long off;
{

  register int mode, despos;
  int curpos, desoff, desblk;
  int curblk, i;
  int ebl;

  mode = curfprm->mode;    /* should be 0 or 1 or 2 */

  /* evaluate to where seek is desired */

  curpos = curfprm->blkptr*BUFSIZ + curfprm->linptr;
  /* clear error status */
  curfcb->devstat &= 0x00ffffff;

  despos = off;
  if(type == 1)
    despos += curpos;
  if(type == 2)
    despos += curfprm->eofptr;
  if(despos < 0) {
    errno = EINVAL;
    mpxerr = E024;
    return(ERROR);
  }
  desoff = despos % BUFSIZ;
  desblk = despos / BUFSIZ;

  /* check eof validity */
  if(despos > curfprm->eofptr) {
    /* read mode can't go beyond eof */
    if(!(mode & (O_WRONLY | O_RDWR))) {
      curfprm->eof = 1;
      despos = curfprm->eofptr;
    }
  } else {
    curfprm->eof = 0;           /* clear eof flag */
    curfprm->eom = 0;           /* clear eom flag */
  }

  curblk = curfprm->blkptr;
  if(BUFVALID && BUFALTER && (mode & (O_WRONLY | O_RDWR))) {
    /* need to write out the current buffer */
    /* write out the record */
    if((i = _putrec(BUFSIZ, curfil->line)) == ERROR)
      return(ERROR);		/* this means error */
    if(i == IOEND)
      return(ERROR);		/* this means eof */
  }
  BUFALTER = 0;
  BUFVALID = 0;
  curfcb->cntl.ran = 1;		/* set random access */

  curfprm->blkptr = desblk;

  /* ebl is the current EOF block  */
  if((mode & (O_WRONLY | O_RDWR)) && ((ebl=curfprm->eofptr/BUFSIZ) < desblk))
    /* write mode, seeking into a block
    that we haven't written to before */
    memset(curfil->line, 0, BUFSIZ);	/* clear the block */
  else
    if(!BUFVALID || (desblk != curblk))
      GETR

  BUFVALID = 1;
  curfprm->linptr = desoff;

  if((mode & (O_WRONLY | O_RDWR)) && despos>curfprm->eofptr)
    curfprm->eofptr = despos;

  return(despos);
}

/* seek blocked function */

static int _skbl(off, mode)
long off;
int mode;
{

  /* clear error status */
  curfcb->devstat &= 0x00ffffff;
  if(curfprm->device == TERMINAL)
    return(GOOD);
  if((curfprm->mode & (O_WRONLY | O_RDWR)) && curfprm->linptr) {
    /* chars left in buff and write mode */
    curfcb->excount = curfprm->linptr;
    curfcb->bufaddr = curfil->line;
#ifndef NOBBS
  if(curfprm->bbs) {		/* see if using large blocking */
    rmwrit(iofd, curfcb->bufaddr, curfcb->excount); /* write file */
  } else {
    asm(" lw r1,_curfcb");
    asm(" svc 1,x'32'");	/* write remaining record */
  }
#else
    asm(" lw r1,_curfcb");
    asm(" svc 1,x'32'");	/* write remaining record */
#endif
  }

  if(mode) {
    /* goto end of file */
#ifndef NOBBS
  if(curfprm->bbs) {		/* see if using large blocking */
    rmadvf(iofd);		/* go to EOF */
    rmback(iofd);		/* backspace record */
  } else {
    asm(" lw r1,_curfcb");
    asm(" svc 1,x'34'");	/* seek EOF */
    asm(" svc 1,x'35'");	/* backspace record */
  }
#else
    asm(" lw r1,_curfcb");
    asm(" svc 1,x'34'");	/* seek EOF */
    asm(" svc 1,x'35'");	/* backspace record */
#endif
  } else {
    /* goto beginning of file */
    curfprm->eof = 0;		/* clear eof flag */
    curfprm->eom = 0;		/* clear eom flag */
    curfprm->charcnt = 0;	/* no chars going out */
    curfprm->blanks = 0;	/* no blanks to output */
    curfprm->bcnt = 0;		/* set record count to zero */
#ifndef NOBBS
  if(curfprm->bbs) {		/* see if using large blocking */
    rmrwnd(iofd);		/* rewind file */
  } else {
    asm(" lw r1,_curfcb");
    asm(" svc 1,x'37'");	/* rewind file */
  }
#else
    asm(" lw r1,_curfcb");
    asm(" svc 1,x'37'");	/* rewind file */
#endif
  }
  return(GOOD);
}

/* seek on non-disc device */

static int _skdv(rel)
int rel;
{

  if(rel) {
    asm(" lw r1,_curfcb");
    asm(" svc 1,x'34'");	/* goto end of file */
  } else {
    asm(" lw r1,_curfcb");
    asm(" svc 1,x'37'");	/* goto begining of file */
  }
}

int readraw(fd, buf, n)
int fd;
char *buf;
int n;
{
  register int mode, dev;

  BADFD(fd, ERROR);
  INIT;
  mode = curfprm->mode;
  dev =  curfprm->device;
  if(mode & NOTUSED) {
    errno = EBADF;
    mpxerr = E012;
    return(ERROR);
  }
  if(mode & O_WRONLY) {
    errno = EACCES;
    mpxerr = E013;
    return(ERROR);
  }
  if(dev == NULLFILE) {
    curfprm->eof = 1;
    return(IOEOF);
  }
  if(n <= 0)
    return(IOEOF);

/* insure sequential write, not random */
#ifndef NOBBS
  if(!curfprm->bbs)		/* see if using large blocking */
    curfcb->cntl.ran = 0;	/* reset random access */
#else
  curfcb->cntl.ran = 0;		/* reset random access */
#endif
/* clear error status */
  curfcb->devstat &= 0x00ffffff;

  curfcb->bufaddr = buf;
  curfcb->excount = n;

#ifndef NOBBS
  if(curfprm->bbs) {		/* see if using large blocking */
    rmread(iofd, buf, n);	/* read file */
  } else {
    asm(" lw r1,_curfcb");
    asm(" svc 1,x'31'");	/* issue read */
  }
#else
  asm(" lw r1,_curfcb");
  asm(" svc 1,x'31'");		/* issue read */
#endif

  if(curfcb->devstat & 0x40000000) {
    errno = EACCES;
    mpxerr = E017;
    return(ERROR);	/* error encountered */
  }
  if(curfcb->devstat & 0x01000000) {
    errno = EFBIG;
    mpxerr = E018;
    curfprm->eom = 1;
    return(IOEND);	/* eom encountered */
  }
  if(curfcb->devstat & 0x02000000) {	/* eof encountered */
    errno = 0;
    mpxerr = E019;
    curfprm->eof = 1;
    return(IOEND);	/* eof encountered */
  }
  return(curfcb->recl);
}

/*  writraw function  */

int writraw(fd, buf, n)
int fd;
char *buf;
int n;
{
  register int mode, dev;

  BADFD(fd, ERROR);
  INIT;
  mode = curfprm->mode;
  dev =  curfprm->device;
  if(mode & NOTUSED) {
    errno = EBADF;
    mpxerr = E010;
    return(ERROR);
  }
  if(!(mode & (O_WRONLY | O_RDWR))) {
    errno = EACCES;
    mpxerr = E011;
    return(ERROR);
  }
  if(dev == NULLFILE)
    return(n);

  /* insure sequential write, not random */
#ifndef NOBBS
  if(!curfprm->bbs)		/* see if using large blocking */
    curfcb->cntl.ran = 0;	/* reset random access */
#else
  curfcb->cntl.ran = 0;		/* reset random access */
#endif
  /* clear error status */
  curfcb->devstat &= 0x00ffffff;

  curfcb->excount = n;
  curfcb->bufaddr = buf;

#ifndef NOBBS
  if(curfprm->bbs) {		/* see if using large blocking */
    rmwrit(fd, buf, n);		/* write file */
  } else {
    asm(" lw r1,_curfcb");
    asm(" svc 1,x'32'");	/* issue write */
  }
#else
  asm(" lw r1,_curfcb");
  asm(" svc 1,x'32'");		/* issue write */
#endif

  if(curfcb->devstat & 0x40000000) {
    errno = EACCES;
    mpxerr = E020;
    return(ERROR);	 /* error */
  }
  if(curfcb->devstat & 0x02000000) {
    errno = EFBIG;
    mpxerr = E021;
    curfprm->eof = 1;
    return(IOEND);	/* eof */
  }

  if(curfcb->devstat & 0x01000000) {
    errno = EFBIG;
    mpxerr = E022;
    curfprm->eom = 1;
    return(IOEND);	/* eom encountered */
  }
  return(curfcb->recl);
}

/* set file type */
int defft = 0;		/* default to type 0 file */

/*
 * set new default file type
 * newtype is value from 0-ff
 * old default value is returned
 * -1 on error
 */

int
setdft(newtype)
int newtype;
{
    int retv = defft;
    if(newtype < 0 || newtype > 0xff)
    	return(-1);
    defft = newtype;
    return(retv);
}

/* place for storing default access rights */
unsigned int fileacc[3]={0x3f, 0x3f, 0x20};

/* place for storing default file sizes */
#ifndef MPX1X
static  int orgs = 0;
static  int minx = 0;
static  int maxx = 0;
#else
static  int orgs = 100;
static  int minx = 100;
static  int maxx = 300;
#endif

/*  setsiz - set default sizes for created files */
int setsiz(ssiz, mini, maxi)
int ssiz, mini, maxi;
{
  orgs = ssiz;		/* starting size */
  minx = mini;		/* minimum increment */
  maxx = maxi;		/* maximum increment */
  return(GOOD);	/* return o.k. */
}

/*  setacc - set default access for created files */
int setacc(owner, group, other)
int owner, group, other;
{
  fileacc[0] = owner;   /* set owner rights */
  fileacc[1] = group;   /* set group rights */
  fileacc[2] = other;   /* set other rights */
  return(GOOD);	/* return o.k. */
}

/* getacc - get access rights of file */

int * getacc(pname)
char *pname;
{
#ifndef MPX1X
  int reg[8];
  int rdu[192];
  int pnblk[18];
  int pnbvec;
  char path[PATH_MAX];

  strcpy(pname, path);   /* copy pathname */
  unix2mpx(pname);      /* make u/c mpx name */

  if(prspn(pname, pnblk, &pnbvec))
    return((int *)ERROR);
  ZREG(reg, 8);
  reg[1] = pnbvec;
  reg[6] = (int)rdu;
  mpxsvc(0x202c, reg, reg);    /* log resource */
  if(reg[7])
    return((int *)ERROR);
  return(&rdu[30]);        /* return pointer to access rights */
#else
  if(access(pname, 0666) == ERROR)
    return((int *)(ERROR));
  return((int *)fileacc);	/* return default 3X type of accesses */
#endif
}

/* _pop - open pipe */

int _pop(fd)
int fd;
{
  BADFD(fd, ERROR);
  INIT;
  /* change type from NULLFILE to PIPE */
  if (curfprm->device == NULLFILE)
    curfprm->device = PIPE;
  return(GOOD);		/* return o.k. */
}

/*    open function     */

int open(path, mode, perm)
char *path;
int mode, perm;
{
  int fd;
  struct rrstag *rptr = &_rrs;
#ifdef MPX1X
  extern struct finfo * _fib;	/* defined in _cassg */
#else
  struct rcbtag rcb;
#endif
  int reg[8];
  char pname[PATH_MAX];

  if(!(path != 0 && *path != 0)) {
    errno = EINVAL;
    mpxerr = E025;
    return(ERROR);	/* bad pathname */
  }
  strcpy(pname, path);   /* copy pathname */
  unix2mpx(pname);      /* make u/c mpx name */

  fd = getfd();
  BADFD(fd, ERROR);

  INIT;

  if(_cassg(pname)) {
    errno = EINVAL;
    mpxerr = E025;
    return(ERROR);		/* parse pathname and build RRS */
  }

  if(mode & O_UNBLK) {
#ifdef MPX1X
    rptr->flags |= 0x04;	/* show assignment to be unblocked */
    curfprm->block = 0;		/* unblocked */
#else
    rptr->opts.unblk = 1;
    rptr->opts.blk = 0;
#endif
  }
  if(mode & O_BIN) {
    curfprm->binary = 1;	/* user wants binary mode */
  }
#ifdef MPX1X
  if((mode & O_CREAT) && (rptr->flags & 0x80)
    && (access(pname, 0) == ERROR)) {
    /* create perminate file */

    /* set username for this file, save old */
    if(setuser(_fib->username, _fib->userkey) != NULL) {
      errno = EACCES;			/* can't creat file, error */
      mpxerr = E002;			/* show RM09 err, invalid usage */
      return(ERROR);			/* show RM09 err, invalid usage */
    }
    ZREG(reg, 8);
    reg[1] = 0xee;			/* filetype will be EE */
    if(mode & O_UNBLK)			/* if unblocked, assume type CA */
    	reg[1] = 0xca;			/* filetype will be CA */
    if((strncmp((char*)_fib->username, "SYSTEM  ", 8) == 0) ||
      (strncmp((char*)_fib->username, "        ", 8) == 0) ||
      ((_fib->username[0] == 0) && (_fib->username[1] == 0)))
      reg[1] |= 0x80000000;		/* set system file */
    reg[2] = rptr->size;		/* get file size to create */
    if(reg[2] == 0)			/* see if no size given */
      reg[2] = orgs;			/* set default size */
    reg[3] = rptr->wd2 & 0x8000ffff;	/* get chan/sa */
    reg[3] |= ((rptr->wd2 & 0x7f000000) >> 8);  /* get dev type */
    if((reg[3] & 0x00ff0000) == 0)	/* see if device given */
      reg[3] |= 0x00010000;		/* set any disk will do */
    if(_fib->password[0] || _fib->password[1]) {
      /* we have a password, set password req'd */
      reg[2] |= 0x01000000;		/* set password flag */
      reg[4] = _fib->password[0];	/* set password */
      reg[5] = _fib->password[1];	/* set password */
    }
    reg[6] = _fib->filename[0];  	/* first part of filename */
    reg[7] = _fib->filename[1];  	/* second part of filename */
    mpxsvc(0x1075, reg, reg); 		/* m.create service */
    /* if r6 returned 0, file not found */
    if(reg[6] == 0) {
      resetuser();			/* reset username to what it was */
      errno = EACCES;			/* can't creat file, error */
      mpxerr = E002;			/* show RM09 err, invalid usage */
      return(ERROR);			/* show RM09 err, invalid usage */
    }
    /* must reset username to what it was before file creation */
    resetuser();			/* reset username to what it was */
  }
#else
  if((mode & O_CREAT) && (rptr->type == 1) &&
    !prspn(pname, curfil->_pnb, &PNBWRDX) && exist(PNBWRDX)) {
    /* it's a type 1 RRS, so a permanent file,
    it can make a pathname block, and it doesn't currently exist */

    ZINT(&rcb, (sizeof(rcb)/sizeof(int)));
    /* set defaults in rcb */
    rcb._owri = ((fileacc[0] << 26) | ((fileacc[0] & 1)?0x400000:0));
    rcb._ugri = ((fileacc[1] << 26) | ((fileacc[1] & 1)?0x400000:0));
    rcb._otri = ((fileacc[2] << 26) | ((fileacc[2] & 1)?0x400000:0));
    rcb._osiz = orgs; /* starting size */
    rcb._mnei = minx; /* minimum increment */
    rcb._mxei = maxx; /* maximum increment */
    rcb._flags._ftyp = (unsigned)defft;

    if(perm) {
      char own, pro, oth;
      /* MPX access rights R W M U A D done here */
      /* UNIX are R W X */
      /* if perm & ~0x1ff is not zero, them MPX, else */
      /* assume UNIX flags given and translate to MPX */

      if((perm & ~0x1ff) == 0) {
        /* simulate UNIX */
        if((oth = (perm & 6) << 3) & 0x10)
    	  oth |= 0x3f;		/* if write, allow all access */
        if((pro = ((perm >> 3) & 6) << 3) & 0x10)
    	  pro |= 0x3f;
        if((own = ((perm >> 6) & 7) << 3) & 0x10)
    	  own |= 0x3f;
	own |= 0x3f;		/* owner gets read/delete access */
      } else {
        oth = perm & 63;
        pro = (perm >> 8) & 63;
        own = (perm >> 16) & 63;
	own |= 0x3f;		/* owner gets read/delete access */
      }
      rcb._otri = (((unsigned)(oth & 62) << 26) | ((oth & 1)?0x400000:0));
      rcb._ugri = (((unsigned)(pro & 62) << 26) | ((pro & 1)?0x400000:0));
      rcb._owri = (((unsigned)(own & 62) << 26) | ((own & 1)?0x400000:0));
    }

    ZREG(reg, 8);
    reg[1] = PNBWRDX;
    reg[2] = (int)&rcb;
    if(rptr->opts.unblk)
      rcb._flags._eofm = 1;
    mpxsvc(0x2020, reg, reg);
    if(reg[7]) {
      errno = EACCES;			/* can't creat file, error */
      mpxerr = E002;			/* show RM09 err, invalid usage */
      return(ERROR);			/* show RM09 err, invalid usage */
    }
  }
#endif /* MPX1X */

#ifdef MPX1X
  /* set username for this file, save old */
  if(rptr->flags & 0x80) {		/* this means a file */
    if(setuser(_fib->username, _fib->userkey) != NULL) {
      errno = EACCES;			/* can't creat file, error */
      mpxerr = E002;			/* show RM09 err, invalid usage */
      return(ERROR);			/* show RM09 err, invalid usage */
    }
  }
#endif /* MPX1X */
  if(assn(mode)) {
#ifdef MPX1X
    if(rptr->flags & 0x80) {		/* this means a file */
      resetuser();			/* reset username to what it was */
    }
#endif /* MPX1X */
    return(ERROR);			/* assign with correct acc rghts */
  }
#ifdef MPX1X
  if(rptr->flags & 0x80) {		/* this means a file */
    resetuser();			/* reset username to what it was */
  }
#endif /* MPX1X */
  if(cnpo(mode))
    return(ERROR);			/* open */
#ifdef MPX1X
  if(rptr->flags & 0x80) {		/* this means a file */
    filtabl[fd].fib = *_fib;		/* set the file stuff */
  }
#endif /* MPX1X */

  if((mode & O_RDWR) &&
    ((curfprm->device == TERMINAL) || (curfprm->device == SPOOLFILE)))
  {
    errno = EACCES;			/* can't creat file, error */
    mpxerr = E001;			/* show RM09 err, invalid usage */
    return(ERROR);			/* show RM09 err, invalid usage */
  }
  if(mode & O_CREAT)
    curfprm->eofptr = 0;	/* all created files have 0 len */

  curfil->line = bufrsio + (BUFSIZ*fd);
  curfprm->mode = mode;		/* mark table entry open */

  if((curfprm->block) && (curfprm->device == DISCFILE) &&
    (ieofbl == 0) && (mode & O_WRONLY)) {
    /* we assume here that the file was created by TSM or Volmgr
    but has had nothing written into it: hence it has no end of
    file markers in it, and a subsequent seek to end of file
    would give IO06 errors without this. */

#ifndef NOBBS
  /* if file is a bbs file, use rmopen to open file */
  if(curfprm->bbs) {		/* see if bbs file */
    if(rmopen(fd) <= 0) {	/* open file */
      errno = EACCES;		/* can't access file, error */
      return(ERROR);		/* show RM09 err, invalid usage */
    }
    if(rmweof(fd) <= 0) {	/* write EOF on file */
      errno = EACCES;		/* can't access file, error */
      return(ERROR);		/* show RM09 err, invalid usage */
    }
#ifdef MPX1X
    if(rmrwnd(fd) <= 0) {	/* rewind file */
      errno = EACCES;		/* can't access file, error */
      return(ERROR);		/* show RM09 err, invalid usage */
    }
#else
    if(rmback(fd) <= 0) {	/* backspace file */
      errno = EACCES;		/* can't access file, error */
      return(ERROR);		/* show RM09 err, invalid usage */
    }
#endif
  } else {			/* std I/O routines */
    asm(" lw r1,_curfcb");
    asm(" svc 1,x'38'");	/* write EOF on file */
#ifdef MPX1X
    asm(" svc 1,x'37'");	/* and rewind to BOF */
#else
    asm(" svc 1,x'35'");	/* and backspace over the EOF */
#endif
  }
#else /* NOBBS */
    asm(" lw r1,_curfcb");
    asm(" svc 1,x'38'");	/* write EOF on file */
#ifdef MPX1X
    asm(" svc 1,x'37'");	/* and rewind to BOF */
#else
    asm(" svc 1,x'35'");	/* and backspace over the EOF */
#endif
#endif /* NOBBS */
  }
#ifndef NOBBS
  /* if file is a bbs file, use rmopen to open file */
  if(curfprm->bbs) {		/* see if bbs file */
    if(rmopen(fd) <= 0) {	/* open file */
      errno = EACCES;		/* can't access file, error */
      return(ERROR);		/* show RM09 err, invalid usage */
    }
  }
#endif
#ifdef MAKE_SMALLER
  /* if blocked disk file, use large blocking buffers */
  if((curfprm->block) && (curfprm->device == DISCFILE)) {
#define NUMB 8			/* use 8 sector blocking buffer */
#define BIGBLOCK NUMB*BUFSIZ	/* use 8 sector blocking buffer */
    int * bbufp;
    if((bbufp = (int *)malloc(BIGBLOCK)) != 0) {
    curfcb->blkbuff = (int *)(((unsigned)NUMB << 24) | (int)bbufp);
    }
  }
#endif

  return(fd);
}

/*    creat function    */

int creat(path, perm)
char *path;
int perm;                  /* permissions */
{
  int mode = (O_CREAT | O_WRONLY);
  return(open(path, mode, perm));	/* let open handle */
}

/*    creatd function  -  create directory  */

int creatd(path, perm)
char *path;
int perm;                                 /* permissions */
{
  int reg[8];
  int mode;
  int fd;

  struct rrstag *rptr = &_rrs;
#ifndef MPX1X
  double dummy;		/* insure dw bounding */
  struct rcbtag rcb;	/* must be double word bounded */
#endif
  char pname[PATH_MAX];

  if(!(path != 0 && *path != 0)) {
    errno = EACCES;		/* can't creat file, error */
    mpxerr = E026;		/* show RM09 err, invalid usage */
    return(ERROR);		/* parse pathname and build RRS */
  }
  strcpy(pname, path);		/* copy pathname */
  unix2mpx(pname);		/* make u/c mpx name */

  fd = getfd();
  BADFD(fd, ERROR);

  INIT;

  if(_cassg(pname)) {
    errno = EACCES;		/* can't creat file, error */
    mpxerr = E026;		/* show RM09 err, invalid usage */
    return(ERROR);		/*parse pathname and build RRS */
  }

#ifdef MPX1X
/* MPX1X uses USERNAME for directory, anyone is o.k., so lets
 * just return o.k. here
 */
  return(GOOD);
#else /* MPX1X */

  if((rptr->type == 1) &&
    !prspn(pname, curfil->_pnb, &PNBWRDX) && exist(PNBWRDX)) {
    /* it's a type 1 RRS, so a permanent file,
    it can make a pathname block, and it doesn't currently exist */

    ZINT(&rcb, (sizeof(rcb)/sizeof(int)));
    /* set defaults in rcb */
    rcb._owri = 0xf8f00000;
    rcb._ugri = 0xf8f00000;
    rcb._otri = 0xf8f00000;
/*    rcb._osiz = 0;  /* starting size */
    rcb._osiz = orgs; /* starting size */
    rcb._mnei = 0;  /* minimum increment */
    rcb._mxei = 0;  /* maximum increment */

    ZREG(reg, 8);
    reg[1] = PNBWRDX;
    reg[2] = (int)&rcb;
    mpxsvc(0x2023, reg, reg);
    if(reg[7]) {
      errno = EACCES;			/* can't creat file, error */
      mpxerr = E002;			/* show RM09 err, invalid usage */
      return(ERROR);			/* show RM09 err, invalid usage */
    }
  }

  return(GOOD);
#endif /* MPX1X */
}

/*  close function  */

int close(fd)
int   fd;
{
  int reg[8];
  double dumbound;
  int usrrd[32];
  register int mode, dev;

  BADFD(fd, ERROR);
  INIT;
#ifndef MPX1X
  PNBWRDX = curfil->pnbw;
#endif

  if((mode=curfprm->mode) & NOTUSED)
    return(ERROR);

  /* if a pipe, change back to NULL */
  if(curfprm->device == PIPE)
    curfprm->device = NULLFILE;

  /* write or update */
  if((mode & (O_WRONLY | O_RDWR))) {
    curfcb->bufaddr = curfil->line;

    if(curfprm->block) {
      curfcb->excount = curfprm->linptr;
      if(curfprm->linptr) {
#ifndef NOBBS
        if(curfprm->bbs) {		/* see if using large blocking */
          rmwrit(iofd, curfcb->bufaddr, curfcb->excount); /* write file */
        } else {
          asm(" lw r1,_curfcb");
          asm(" svc 1,x'32'");		/* issue write */
        }
#else
        asm(" lw r1,_curfcb");
        asm(" svc 1,x'32'");		/* issue write */
#endif
        curfprm->linptr = 0;
      }
    } else {
      curfcb->excount = BUFSIZ;
      if(BUFVALID && BUFALTER) {
        curfcb->exracc = curfprm->blkptr;
        asm(" lw r1,_curfcb");
        asm(" svc 1,x'32'");
      }
    }
  }

#ifndef MPX1X
  /* there is no user rd area in MPX1X, so just delete code */

  /* write back the eof position  */
  if((curfprm->device==DISCFILE) && (mode & (O_WRONLY | O_RDWR))) {
    ZREG(reg, 8);
    reg[1] = curfil->_pnb[8];   /* keeping the RID here */
    reg[6] = (int)usrrd;
    mpxsvc(0x2031, reg, reg);
    if(!reg[7]) {
      if(curfprm->block) {
        /* try to type the file as CBLFIL */
        usrrd[CUBFL1 - CUBFUS] = CBLFIL;   /* type it */
      }
      else {
        usrrd[CUBFL1 - CUBFUS] = CUBFIL;   /* type it */
        usrrd[CUBFL2 - CUBFUS] = curfprm->eofptr;  /* length it */
      }
      ZREG(reg, 8);
      reg[6] = (int)usrrd;
      mpxsvc(0x2032, reg, reg);
    }
  }
#endif /* MPX1X */

  if(curfprm->block && (curfprm->device==DISCFILE) && (mode & O_WRONLY))
    {

    /* The purpose of this code here is to more completely emulate
    the UNIX write mode of file operation. If no data was written
    to the file, then an EOF should be written at the beginning.
    Here, an EOF is written to the current position (which will be
    at the start of the file if no data has been written). To avoid
    potential problems when two streams are opened to the same file,
    we backspace over the EOF after writing it. */

#ifndef NOBBS
  /* if file is a bbs file, use rmopen to close file */
  if(curfprm->bbs) {		/* see if bbs file */
    rmweof(iofd);		/* write EOF on file */
#ifndef TRY
    rmback(iofd);		/* backspace record */
#else
    rmrwnd(iofd);		/* rewind file */
#endif
  } else {			/* std I/O routines */
    asm(" lw r1,_curfcb");
    asm(" svc 1,x'38'");	/* write EOF on file */
#ifdef MPX1X
    asm(" svc 1,x'37'");	/* and rewind to BOF */
#else
    asm(" svc 1,x'35'");	/* and backspace over the EOF */
#endif
  }
#else /* NOBBS */
    asm(" lw r1,_curfcb");
    asm(" svc 1,x'38'");	/* write EOF on file */
#ifdef MPX1X
    asm(" svc 1,x'37'");	/* and rewind to BOF */
#else
    asm(" svc 1,x'35'");	/* and backspace over the EOF */
#endif
#endif /* NOBBS */
  }

  reg[1] = (int)curfcb;
  reg[7] = 0;			/* no CNP */

#ifdef MPX1X
  if((curfprm->device==DISCFILE) && (mode & (O_WRONLY | O_RDWR))) {
#ifdef TRYTHIS
    mpxsvc(0x1038, reg, reg);		/* write EOF on file */
    mpxsvc(0x1037, reg, reg);		/* rewind the file */
#endif
  }
#ifndef NOBBS
  /* if file is a bbs file, use rmclose to close file */
  if(curfprm->bbs)		/* see if bbs file */
    rmclose(iofd);		/* close the file */
  else
    mpxsvc(0x1039, reg, reg);		/* close the file */
#else
  mpxsvc(0x1039, reg, reg);		/* close the file */
#endif
  reg[5] = (int)(*(int*)curfcb) & 0xffffff; /* get lfc */
  mpxsvc(0x1041, reg, reg);		/* deallocate the file */
#else
#ifndef NOBBS
  /* if file is a bbs file, use rmclose to close file */
  if(curfprm->bbs)		/* see if bbs file */
    rmclose(iofd);		/* close the file */
  else
    mpxsvc(0x1039, reg, reg);		/* close the file */
#else
  mpxsvc(0x1039, reg, reg);		/* close the file */
#endif
  mpxsvc(0x2053, reg, reg);		/* deassign the file */
  if(reg[7]) {
    errno = EACCES;			/* can't creat file, error */
    mpxerr = E003;
    return(ERROR);			/* show RM09 err, invalid usage */
  }
#endif

  curfprm->mode = NOTUSED;
  curfprm->linptr = curfprm->blkptr = curfprm->block = curfprm->binary =
    curfprm->eofptr = curfprm->eof = curfprm->device = curfprm->eom = 0;
#ifndef NOBBS
    curfprm->bbs = 0;
#endif
  BUFVALID = BUFALTER = 0;   /* Version G Fix */

  return(GOOD);
}

#ifdef MPX1X
static int reg5, reg6, reg7;
#endif

/* assign function */
static int assn(mode)
int mode;
{
  int i, reg[8];
  struct rrstag *rptr = &_rrs;
#ifdef MPX1X
  extern struct finfo * _fib;	/* defined in _cassg */

  reg5 = *(int *)(curfcb);	/* get LFC */
  reg5 &= 0xffffff;		/* clean the LFC */
  curfcb->cntl.exp = 1;         /* ensure expanded fcb */
  reg5 |= 0x20000000;		/* wait for resource */
  if(rptr->flags & 0x04)
    reg5 |= 0x40000000;		/* set unblocked */
  if(rptr->flags & 0x02)
    reg5 |= 0x80000000;		/* set inhib mnt */
  if(rptr->flags & 0x80) {	/* perm file */
    reg5 |= 0x01000000;		/* type 1 rrs */
    reg6 = (int)_fib->filename;	/* set filename address */
    if(_fib->password[0] || _fib->password[1])
      reg7 = (int)_fib->password;	/* set password address */
  }
  if(rptr->flags & 0x60) {     /* sys file code */
    reg5 |= 0x02000000;		/* type 2 rrs */
    reg6 = (int)&rptr->wd2;	/* slo or sbo */
    reg7 = (int)&rptr->size;	/* file size */
  }
  if(rptr->flags & 0x10) {     /* device code */
    reg5 |= 0x03000000;		/* type 3 rrs */
    reg6 = (int)&rptr->wd2;	/* type, ch, sa*/
    reg7 = (int)&rptr->size;	/* file size or reel id */
  }
  if(rptr->flags & 0x08) {     /* as lfc=lfc */
    reg5 |= 0x04000000;		/* type 4 rrs */
    reg6 = (int)&rptr->wd2;	/* lfc to assign */
    reg7 = 0;			/* zero */
  }
  asm(" la 1,altret");		/* set error ret addr */
  asm(" lw 5,_reg5");		/* get type & LFC */
  asm(" lw 6,_reg6");		/* get chan & sa */
  asm(" lw 7,_reg7");		/* get size */
  asm(" svc 1,x'40'");		/* M.ALOC	 */
  asm(" li 6,-1");		/* o.k. return	 */
  asm("altret stw 6,_reg6");	/* save error code */
  if(reg6 == -1)
    return(GOOD);		/* return ok */
  errno = EACCES;		/* can't creat file, error */
  mpxerr = E004;		/* invalid usage */
  return(reg6);			/* return error */

#else /* MPX1X */

  for(i = 0; i < 3; i++)
    rptr->lfc[i] = curfcb->lfc[i]; /* put LFC in RRS */

  if((mode & (O_WRONLY | O_RDWR)))
    rptr->accs.updat = 1;
  else
    rptr->accs.read  = 1;

  curfcb->cntl.exp = 1;              /* ensure expanded fcb */

  if(rptr->type == 4) {
    rptr->accs.read = 0;
    rptr->accs.write = 0;
    rptr->accs.modfy = 0;
    rptr->accs.updat = 0;
    rptr->accs.appnd = 0;
  }

  ZREG(reg, 8);
  reg[1] = (int)rptr;
  if(mode & O_DWAIT) {		/* see if we don't want to wait */
    int cnp[6];			/* define a cnp */

    ZREG(cnp, 6);
    cnp[0] = 1;			/* return immediately */
    reg[7] = (int)cnp;		/* the cnp address */
    mpxsvc(0x2052, reg, reg);	/* assign */
    reg[7] = cnp[2] & 0xffff;	/* status value */
  } else {
    mpxsvc(0x2052, reg, reg);	/* assign */
  }

  if(reg[7]) {
    errno = EACCES;		/* can't creat file, error */
    mpxerr = E004;		/* invalid usage */
  }
  return(reg[7]);
#endif /* MPX1X */
}

static int cnpo(mode)
int mode;
{
  int reg[8], i;
#ifndef MPX1X
  int *parinq[8];
  struct fattag *fatptr;
  double dumb1;
  int rd[192];
  struct cnptag cnp;
#else
  int diskfile=0;
#endif
  struct rrstag *rptr = &_rrs;
  int sgofil = 0;

  ZREG(reg, 8);
#ifdef MPX1X
  for(i = 0; i < 3; i++) {
    reg[5] <<= 8;
    reg[5] |= curfcb->lfc[i];
  }
  mpxsvc(0x1042, reg, reg);            /* device inquiry */
  if(!reg[6]) {                        /* error if r6 = 0 */
    errno = EACCES;			/* can't creat file, error */
    mpxerr = E005;			/* no FAT space */
    return(ERROR);			/* can be zero for console */
  }                                     /* so we test r6 for zero */
  sgofil = (reg[7] & 0x00070000) >> 16;   /* get sys file type if any */
  switch((reg[7] >> 24) & 0xff) {      /* switch on device type */
    case 0:     /* console */
    case 0x0c:  /* tty */
    case 0x0d:  /* console ct */
      curfprm->device = TERMINAL;	/* terminal */
      break;
    case 0x01:  /* disk */
    case 0x02:  /* disk */
    case 0x03:  /* disk */
      diskfile = 1;
    default:
      curfprm->device = DISCFILE;	/* file */
      break;
    case 0x0f:  /* null device */
      curfprm->device = NULLFILE;
      return(GOOD);
    case 0x0a:  /* lineprinter */
      curfprm->device = SPOOLFILE;	/* SLO */
  }
  if(sgofil == 3)
    curfprm->device = SPOOLFILE;	/* SLO */

  /* get correct blocking info */
  curfprm->block = ((reg[7] & 0x00800000) ? 1 : 0);	/* set blocked bits */

  /* ensure terminals are opened blocked */
  if(curfprm->device == TERMINAL || curfprm->device == SPOOLFILE)
    curfprm->block = 1;

  /* fudge blocking and access rights for some special files */
  if(rptr->flags & 0x08) {
    if(mode & (O_WRONLY | O_RDWR)) {
      /* mode is write or update */
      if((sgofil == 3) || curfprm->device == TERMINAL) {
        curfprm->block = 1;
      }
      else if(sgofil) {		/* open in default mode */
        curfprm->block = 1;
      }
    }
  }
#else
  for(i=0; i<3; i++) {
    reg[4] <<= 8;
    reg[4] |= curfcb->lfc[i];
  }
  reg[1] = (int)parinq;
  mpxsvc(0x2048, reg, reg);            /* resource inquiry service */

  fatptr = (struct fattag *)parinq[1];
  if(!fatptr) {
    errno = EACCES;			/* can't creat file, error */
    mpxerr = E005;			/* no FAT space */
    return(ERROR);			/* can be zero for console */
  }
#endif

#ifndef MPX1X
  /* set device info */
  if(fatptr->null) {			/* null device */
    curfprm->device = NULLFILE;
    return(GOOD);
  }
  else if((fatptr->acf & 0x7) ==3)
    curfprm->device = SPOOLFILE;	/* SLO */
  else if(fatptr->tsm)
    curfprm->device = TERMINAL;		/* terminal */
  else  curfprm->device = DISCFILE;	/* file */

  sgofil = ((fatptr->acf&0x7) == 2);

  /* get correct blocking info */
  curfprm->block = ((fatptr->attr & UNBLASS) ? 0 : 1);
  /* set blocked bits */
  /* ensure terminals are opened blocked */
  if(curfprm->device == TERMINAL || curfprm->device == SPOOLFILE)
    curfprm->block = 1;

  cnp.abrtn = cnp.status = cnp.resvd[0] = cnp.resvd[1] =
    cnp.resvd[2] = cnp.timeout = 0;
  cnp.options = 0;
  if(curfprm->block) {
    cnp.options = OBL;
    curfcb->cntl.bl = 1;
  }
  else{
    cnp.options = OUB;
    curfcb->cntl.bl = 0;
  }

  /* fudge blocking and access rights for
  some special files */
  if(rptr->type == 4) {
    if(mode & (O_WRONLY | O_RDWR)) {
      /* mode is write or update */
      if(((fatptr->acf & 0x7) == 3) || fatptr->tsm) {
        curfprm->block = 1;
        cnp.options &= ~(OBL|OUB); /* clear blocking info */
        cnp.options |= OBL;
      }
      else if(sgofil) {        /* open in default mode */
      }
      else {
        cnp.options |= OUPD;    /* open in update mode */
      }
    }
  }
#endif
#ifdef MPX1X
  if(curfprm->block) {
    curfcb->cntl.bl = 1;
  }
  else{
    curfcb->cntl.bl = 0;
  }
#endif
  curfcb->cntl.ran = (curfprm->block ? 0 : 1);

#ifndef NOBBS
  /* if blocked disk file, use large blocking buffers */
  if((curfprm->block) && (curfprm->device == DISCFILE)) {

#ifndef MPX1X
      cnp.options &= ~(OBL|OUB); /* clear blocking info */
      cnp.options |= OUBBS;	/* unblocked open w/blocked data */
#endif
      curfcb->cntl.bl = 0;	/* unblocked in FCB */
      curfcb->cntl.ran = 0;	/* no random access */
      curfprm->bbs = 1;		/* use large blocking buffers */
    /* leave the blocked bit set in curfprm */
  }
#endif

#ifdef MPX1X
  reg[1] = (int)curfcb;
  if((mode & (O_WRONLY | O_RDWR)) && (sgofil != 1))
    reg[1] |= 0x40000000;               /* set read/write */
  mpxsvc(0x1030, reg, reg);            /* open resource */
#else
  if(mode & O_DWAIT) {		/* see if we don't want to wait */
    cnp.timeout = 1;
  }
  ZREG(reg, 8);
  reg[7] = (int)&cnp;
  reg[1] = (int)curfcb;
  mpxsvc(0x2042, reg, reg);            /* open resource */

  if(cnp.status) {
    errno = EACCES;			/* can't creat file, error */
    mpxerr = E006;			/* open error */
    return(ERROR);			/* can be zero for console */
  }
#endif
  curfprm->blkptr = 0;
  curfprm->linptr = 0;
  curfprm->eof    = 0;
  curfprm->cmpop   = 0;     /* clear tested for compressed flag */
  curfprm->cmpflg  = 0;     /* clear compressed file flag */
#ifndef MPX1X
  ZREG(curfil->_pnb, 9);              /* for the RID */
#endif

  curfprm->eofptr = 0x7FFFFFFF;
#ifdef MPX1X
  if(curfprm->device == DISCFILE && diskfile) {  /* file */
    curfprm->eofptr = (BUFSIZ * reg[5]) - 1;
    /* if no value in RD, try to work out a value */
    ieofbl = 0;
  }
#else
  if(curfprm->device == DISCFILE) {  /* file */
    ZREG(reg, 8);
    reg[1] = (int)curfcb;
    reg[6] = (int)rd;
    mpxsvc(0x202c, reg, reg);
    ieofbl = EOF;
    if(!reg[7]) {
      int i;         /* save RID */
      for(i = 0; i < 8; i++)
        curfil->_pnb[i] = rd[i];  /* RID copy */
      curfil->_pnb[8] = (32 << 24) | (int)curfil->_pnb;
      if((rd[7]&0x0000ffff) == 12)
        /* it's a TEMP file, so length is zero */
        curfprm->eofptr = 0;
      else if(rd[CUBFL1] == CUBFIL)
        /* if the file has been previously typed by
          the C library, it will have been lengthed */
        curfprm->eofptr = rd[CUBFL2];
      else
        curfprm->eofptr = BUFSIZ * rd[69] - 1;
      /* if no value in RD, try to work out a value */
      ieofbl = rd[REOFBL];
      }
  }
#endif
  return(GOOD);
}

#ifndef MPX1X
/* pathname parse */

static int prspn(pname, pnblk, pnbvec)
char *pname;
int  *pnblk;
int *pnbvec;
{
  struct rrstag *rptr = &_rrs;
  int reg[8];
  register int l;

  *pnbvec = 0;

  if((l = strlen(pname)) > 52) {
    errno = EINVAL;
    mpxerr = E007;
    return(ERROR);
  }
  else if(!l) {
    errno = EINVAL;
    mpxerr = E008;
    return(ERROR);
  }

  ZREG(reg, 8);
  reg[1] = l;
  reg[1] <<= 24;
  reg[1] |= (int)pname;
  reg[4] = 18 * sizeof(int);
  reg[4] <<= 24;
  reg[4] |= (int)pnblk;
  mpxsvc(0x202e, reg, reg);    /* make pathname block */

  if(reg[7]) {
    errno = EINVAL;
    mpxerr = E009;
    return(ERROR);
  }
  *pnbvec = reg[4];
  return(GOOD);
}
#endif

#ifndef MPX1X
/*    exist internal function */

static int exist(pnbvec)
int pnbvec;
{
  int reg[8];
  int rdu[192];

  ZREG(reg, 8);
  reg[1] = pnbvec;
  reg[6] = (int)rdu;
  mpxsvc(0x202c, reg, reg);
  return(reg[7]);
}
#endif

/*   getfd function     */

static int getfd()
{
  int fd;

  for(fd = 0; fd < _NFILE; fd++)
    if(filtabl[fd].filparm.mode & NOTUSED)
      return(fd);
  return(EOF);
}

/*  __isblk function */

int __isblk(fd)
int fd;
{
  struct flprmtag  *p;

  BADFD(fd, IOEOF);
  p = &(filtabl[fd].filparm);
  if(p->mode & NOTUSED)
    return(IOEOF);
  return(p->block);
}

/* isatty function */

int isatty(fd)
int fd;
{
  struct flprmtag *p;

  BADFD(fd, IOEOF);
  p = &(filtabl[fd].filparm);
  if(p->mode & NOTUSED)
    return(IOEOF);
#ifdef TRY_THIS_AT_VISTA
  return((p->device == TERMINAL) || (p->block && !p->binary));
#else
  return(p->device == TERMINAL);
#endif
}

/*  fcbadr function   */

struct fcbtag *fcbadr(fd)
int fd;
{
  BADFD(fd, IOEOF);
  if(filtabl[fd].filparm.mode & NOTUSED)
    return(IOEOF);
  return(&(filtabl[fd].fcb));
}

/* delete function (unlink if you insist) */

int delete(pname)
char *pname;
{
  return(unlink(pname));       /* delete the file */
}

/* carriage control toggler */
void mpxccset(tog)
int tog;
{
  carcont = tog;
}

#include <sys/types.h>
#include <psb.h>

/* PIPE support */
/* send a message to our parent task */
int snddata(fd,buf,n)
int fd;		/* fd to write */
char *buf;	/* address of data */
int n;		/* number of bytes */
{
    char sendbuf[260];		/* parameter send block */
    int retbuf[8];		/* parameter return block */
    struct psb psb;		/* message block */
    register int *pp = (int *)&psb;	/* must be 1st reg var (r7) */
    register int status = 0;		/* must be 2nd reg var (r6) */
    int i;

    if (n > 254)return(-1);	/* error */
    /* now send the wakeup to the client task */
    for (i=0; i<(sizeof(psb)/sizeof(int)); i++)
      pp[i] = 0;		/* clear psb */
    psb.lmn = getppid();	/* process to wake */

    sendbuf[0] = 'P';		/* POP in ascii */
    sendbuf[1] = 'O';		/* POP in ascii */
    sendbuf[2] = 'P';		/* POP in ascii */
    sendbuf[3] = fd;		/* output device */
    for (i=0; i<n; i++)		/* copy in data */
      sendbuf[i+4] = buf[i];

    psb.pnv = 0;
    psb.opt = 0x00;		/* send wait, 0x80 for no wait */
    psb.squa = n+4;		/* send count */
    psb.sba = (int *)sendbuf;	/* send buffer address */
    psb.rpbl = 8;		/* 8 bytes to return max */
    psb.rba = (int *)retbuf;	/* return buffer */
    psb.eaa = 0;		/* no end action routine for now */

    /* note parameter send block address is FIRST register variable
     * and address will be in r7
     * status is SECOND register variable
     * and address will be in r6
     */
    asm (" trr r7,r2");		/* psb address */
    asm (" svc 1,x'6c'");	/* send message M.SMSGR */

    /* see if error.  This should not happen */
    if (status) {		/* if non zero, we have an error */
    	return (-1);		/* return an error */
    }
    /* if msg sent O.K., the return status and errno value
     * will be returned in the retbuf
     */
    if (psb.acrp == 0) {
    	/* if no bytes returned, we have an error */
    	return (-1);		/* return an error */
    }
    return (retbuf[0]);		/* return the user status */
}

#ifndef NOBBS
/*~!bbio.c*/
/* Name:  bbio.c Part No.: _______-____r
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

#ident	"@(#)nblib:bbio.c	1.1"

#ifdef mpx
#include <fcb.h>
#endif

/********************************************************************/
/* These routines handle blocked and optionally compressed MPX files */

#define IOCMAX 10	/* max users, start with 10 for now */
#ifdef MPX1X
#define BLKMAX 4	/* buffered disk blocks per user */
#else
#define BLKMAX 10	/* buffered disk blocks per user */
#endif

struct ioc {
    int 	fd;		/* file descriptor for i/o */
    struct fcb *afcb;		/* callers fcb address */
    unsigned char * cba;	/* current buffer address */
    unsigned char * rcba;	/* record control block pointer */
    int		cpp;		/* current pool position */
    int		cfp;		/* current file position */
    char	cbn;		/* current buffer number */
    char	nab;		/* number of active buffers */
    struct {			/* ioc bit flags */
    	unsigned openop	 : 1;	/* open flag */
    	unsigned writop	 : 1;	/* last op was write */
    	unsigned weofop	 : 1;	/* last op was write EOF */
    	unsigned outaop	 : 1;	/* output active flag */
	unsigned iocaloc : 1;	/* ioc allocated */
	unsigned free	 : 3;	/* free flags, available */
    } flag;
    unsigned char * bufa;	/* start of contiguous buffers */
    unsigned int iostat;	/* I/O status from operation */
#define ERRFLAG 0x40000000
#define BOMFLAG 0x04000000
#define EOFFLAG 0x02000000
#define EOMFLAG 0x01000000
};

int rmerror;			/* current error code */
struct ioc ioc[IOCMAX];

#define RCBEOF	0x80		/* bit 0 */
#define RCBBOB	0x40		/* bit 1 */
#define RCBEOB	0x20		/* bit 2 */
#define RCBNULL	0x10		/* bit 3 */
#define RCBCONT	0x08		/* bit 4 */

#define SBLR 0			/* status byte, last record */
#define BCLR 1			/* byte count, last record */
#define SBTR 2			/* status byte, this record */
#define BCTR 3			/* byte count, this record */

#define BLKSIZE 768
#define BLKS (BLKMAX*BLKSIZE)

/* ircont - establish ioc address for this file descriptor */
/* input - file descriptor */
/* output - ioc address */

static struct ioc * ircont(cfd)
register int cfd;
{
    register int	i;
    register struct ioc * wioc;		/* current ioc */

    rmerror = 0;			/* no errors yet */
    for(i = 0, wioc = &ioc[0]; i < IOCMAX; wioc = &ioc[++i]) {
      /* see if allocated */
      if(wioc->flag.iocaloc)
    	/* set callers file descriptor */
    	if(wioc->fd == cfd) {
    	  /* initialize callers fcb */
    	  wioc->afcb->sflg = 0;		/* status flags */
    	  wioc->afcb->errt |= 0x00ffffff;	/* special flags */
    	  wioc->afcb->recl = 0;		/* transfer count */
    	  wioc->afcb->ist1 = 0;		/* expanded status */
    	  wioc->afcb->ist2 = 0;		/* expanded status */
    	  return(wioc);
    	}
    }
    /* not yet allocated, get a new one */
    for(i = 0, wioc = &ioc[0]; i < IOCMAX; wioc = &ioc[++i]) {
      /* see if allocated yet */
      if(!wioc->flag.iocaloc) {
    	/* no, try to allocate buffer first */
    	/* get a big blocking buffer */
    	if((wioc->bufa = (unsigned char *)malloc(BLKS)) <= 0) {
#ifdef DBUG
    	  fprintf(stderr, "ioc malloc error\n");
#endif
    	  rmerror = 15;		/* can not malloc buffer space */
    	  return(0);
    	}
    	/* allocate it */
    	wioc->flag.iocaloc = 1;		/* ioc allocated */
    	/* initialize new ioc */
    	/* set callers file descriptor */
    	wioc->fd = cfd;
    	/* save callers fcb address */
    	wioc->afcb = (struct fcb *)curfcb;	/* fcbadr(cfd) */
    	/* initialize callers fcb */
    	wioc->afcb->sflg = 0;		/* status flags */
    	wioc->afcb->errt |= 0x00ffffff;	/* special flags */
    	wioc->afcb->recl = 0;		/* transfer count */
    	wioc->afcb->ist1 = 0;		/* expanded status */
    	wioc->afcb->ist2 = 0;		/* expanded status */
    	wioc->afcb->erwa = (char *)wioc->bufa;	/* set buffer addr in fcb */
    	wioc->afcb->cbra = 0x02000000;	/* just exp fcb in cntrl flags */
    	wioc->cba = wioc->bufa;		/* set current buffer addr */
    	wioc->cbn = 0;			/* no curr buf number */
    	wioc->nab = 0;			/* no active bufs */
    	/* clear flags */
    	wioc->flag.openop = 0;		/* open ioc */
    	wioc->flag.weofop = 0;
    	wioc->flag.writop = 0;
    	wioc->flag.outaop = 0;
    	wioc->cpp = 0;			/* pool empty */
    	wioc->cfp = 1;			/* curr position is 1st blk */
    	return(wioc);
      }
    }
#ifdef DBUG
    fprintf(stderr, "no ioc space left\n");
#endif
    rmerror = 3;			/* show no space left */
    return(0);
}

/* rmopen - open up a file stream */
static int rmopen(cfd)
int cfd;
{
    register struct ioc * wioc;

    wioc = ircont(cfd);
    /* wioc is 0 if bad open */
    if(wioc == (struct ioc *)0)	/* see if error */
      return(0);		/* return error */
    /* not open yet, do open */
    wioc->flag.openop = 1;	/* mark open */
    return(1);			/* return o.k. */
}

/* rmclose - close a file stream */
static int rmclose(cfd)
int cfd;
{
    register struct ioc * wioc;

    wioc = ircont(cfd);
    /* wioc is 0 if bad open */
    if(wioc == (struct ioc *)0)	/* see if error */
    	return(0);		/* return error */

    /* see if file open, must close if it is */
    if(wioc->flag.openop) {
#ifdef DBUG
printf("rmclose(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
      /* open, do close */
      if(wioc->flag.writop) {
    	if(!wioc->flag.weofop)	/* did we need an EOF */
    	    irweof(wioc);	/* yes, write eof */
      }
      if(wioc->flag.outaop)
    	plwrit(wioc);		/* if pool active, purge */
    }

    wioc->flag.openop = 0;	/* mark closed */
    wioc->flag.iocaloc = 0;	/* mark unallocated */
    free(wioc->bufa);		/* free buffer */
    wioc->bufa = 0;		/* clear buffer address */
    wioc->fd = -1;		/* clear file descriptor */
    return(1);
}

/* rmrwnd - rewind a file stream */
static int rmrwnd(cfd)
int cfd;
{
    register struct ioc * wioc;

    wioc = ircont(cfd);
    if(wioc == (struct ioc *)0)	/* see if error */
    	return(0);		/* return error */
    if(!wioc->flag.openop) {
        wioc->flag.openop = 1;	/* set open */
    	goto rwd01;		/* if not open, return o.k. */
    }
#ifdef DBUG
printf("rmrwnd(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
    if(wioc->flag.writop) {	/* if writing, see if EOF needed */
    	if(!wioc->flag.weofop)	/* did we need an EOF */
    	    irweof(wioc);	/* yes, write eof */
    }
    if(wioc->cpp == 0)		/* pool initialized */
    	goto rwd01;		/* no, just return O.K. */
    /* set buffer tables for rewind */
    plrwnd(wioc);		/* rewind pool to 1st block */
    if(wioc->cpp) {		/* 1st pool in memory */
      wioc->cbn = 1;		/* 1st buffer */
      wioc->cba = wioc->bufa;	/* beginning of buffer */
      wioc->rcba = wioc->cba + 4;	/* set rec cont buf address */
    } else {
      wioc->cbn = 0;		/* no buffers in memory */
    }
rwd01:
    wioc->afcb->sflg &= ~EOFFLAG;	/* turn off eof in callers fcb */
    wioc->afcb->sflg |= BOMFLAG;	/* turn on bom in callers fcb */
    return(1);
}

/* rmweof - write eof on file stream */
static int rmweof(cfd)
int cfd;
{
    register struct ioc * wioc;

    wioc = ircont(cfd);
    if(wioc == (struct ioc *)0)	/* see if error */
    	return(0);		/* return error */
    if(!wioc->flag.openop) {
        wioc->flag.openop = 1;	/* set open */
    }
#ifdef DBUG
printf("rmweof(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
    irweof(wioc);		/* write eof */
    wioc->flag.writop = 1;	/* set writing */
    return(1);
}

/* rmback - backspace record on file stream */
static int rmback(cfd)
register int cfd;
{
    register struct ioc * wioc;
    register int cnt;

    wioc = ircont(cfd);
    if(wioc == (struct ioc *)0)	/* see if error */
    	return(0);		/* return error */
    if(!wioc->flag.openop) {
        wioc->flag.openop = 1;	/* set open */
    	goto bsxt;		/* if not open, return o.k. */
    }
#ifdef DBUG
printf("rmback(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
    if(wioc->flag.writop) {	/* if writing, see if EOF needed */
    	if(!wioc->flag.weofop) {	/* do we need an EOF */
    	    irweof(wioc);	/* yes, write eof */
#ifdef FFIX
    	    bfback(wioc);	/* back over eof just written */
#else
    	    wioc->rcba -= 4;	/* back over eof just written */
#endif
    	}
    }
    /* see if pool empty */
    if(wioc->cpp != 0) {	/* if not empty */
    	bfback(wioc);		/* back over previous record */
    }
bsxt:
    wioc->flag.writop = 0;		/* not writing */
    wioc->afcb->sflg &= ~EOFFLAG;	/* turn off eof in callers fcb */
    return(1);
}

/* rmread - read from file stream */
static int rmread(cfd, buffer, rcnt)
int cfd;
unsigned char * buffer;
int rcnt;
{
    register struct ioc * wioc;
    int	fillcnt, i, bytecnt;
    unsigned char * buffp;

    wioc = ircont(cfd);
    if(wioc == (struct ioc *)0)	/* see if error */
    	return(0);		/* return error */
    if(!wioc->flag.openop) {
        wioc->flag.openop = 1;	/* set open */
    }
#ifdef DBUG
printf("rmread(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
#ifdef DBUG
printf("rmread in: rcnt = %d, buffer = %x\n", rcnt, buffer);
#endif
    /* see if read after a write */
    if(wioc->flag.writop) {
#ifdef DBUG
      printf("read after write not allowed\n");
#endif
      rmerr(wioc, 9);		/* user tried to read after write */
      return(0);		/* return error */
    }
    bytecnt = 0;		/* no bytes to caller yet */
    buffp = buffer;		/* save caller buff addr */
    /* see if any data in pool yet */
    if((wioc->cpp == 0) ||	/* if no data in pool yet, read it in */
      /* see if end of the block */
      (wioc->rcba[SBLR] & RCBEOB)) {
      /* yes, read next block */
      if(bfredf(wioc) == -1) {		/* test for EOF */
        wioc->afcb->sflg |= EOFFLAG;	/* set EOF for caller */
    	return(-1);
      }
      wioc->rcba = wioc->cba + 4;	/* where we start */
    }
    /* test for end of file */
    if(wioc->rcba[SBTR] & RCBEOF) {
      /* at EOF, set EOF bit in FCB */
      wioc->afcb->sflg |= EOFFLAG;
      return(-1);			/* return EOF */
    }

    /* get byte count to transfer */
    bytecnt = wioc->rcba[BCTR];
    /* copy data to user */
    if(bytecnt > 8)
      memcpy(buffer, &wioc->rcba[4], bytecnt);
    else
      for(i = 0; i < bytecnt; i++)
    	buffer[i] = wioc->rcba[i+4];
    wioc->afcb->recl = bytecnt;		/* save count in fcb */
    wioc->afcb->erwa = (char *)buffer;	/* reset buffer address in caller fcb */
    wioc->rcba += (bytecnt + 4);	/* point to next record */
#ifdef DBUG
printf("rmread: recl = %d, buffer = %x\n", bytecnt, buffer);
#endif
    return(bytecnt);			/* return byte count */
}

#ifdef NOT_FOR_NOW
/* rmadvr - advance record on file stream */
static int rmadvr(cfd)
int cfd;
{
    register struct ioc * wioc;

    wioc = ircont(cfd);
    if(wioc == (struct ioc *)0)	/* see if error */
    	return(0);		/* return error */
    if(wioc->flag.writop) {	/* was last op a write */
#ifdef DBUG
      printf("adv record after write not allowed\n");
#endif
      rmerr(wioc, 9);		/* user tried adv after write */
      return(-1);		/* return error */
    }
    if(!wioc->flag.openop) {
        wioc->flag.openop = 1;	/* set open */
        bfredf(wioc);		/* read in a block */
        wioc->rcba = wioc->cba + 4;	/* calc rcb address */
        goto adv02;
    }
    /* see if any data in memory */
    if(wioc->cpp == 0) {	/* if no data in pool yet, read it in */
      bfredf(wioc);		/* read in a block */
      wioc->rcba = wioc->cba + 4;	/* calc rcb address */
    }
    /* see if at EOB */
    if(wioc->rcba[SBLR] & RCBEOB) {
      bfredf(wioc);		/* EOB, get next record */
      wioc->rcba = wioc->cba + 4;	/* calc rcb address */
    }
adv02:
    /* see if at EOF */
    if(wioc->rcba[SBTR] & RCBEOF) {
      wioc->afcb->sflg |= EOFFLAG;	/* set EOF for user */
      return(1);
    }
    wioc->rcba += (wioc->rcba[BCTR] + 4);	/* point to next record */
    return(1);
}
#endif

/* rmadvf - advance to EOF on file stream */
static int rmadvf(cfd)
int cfd;
{
    register struct ioc * wioc;

    wioc = ircont(cfd);
    if(wioc == (struct ioc *)0)	/* see if error */
    	return(0);		/* return error */
    if(wioc->flag.writop) {
#ifdef DBUG
      printf("adv file after write not allowed\n");
#endif
      rmerr(wioc, 9);		/* user tried adv after write */
      return(-1);
    }
    if(!wioc->flag.openop) {
      wioc->flag.openop = 1;	/* set open */
      bfredf(wioc);		/* read in a block */
      wioc->rcba = wioc->cba + 4;
#ifdef DFIX
      goto af02;
#endif
    }
af00:
    if(wioc->cpp == 0) {	/* if no data in pool yet, read it in */
      bfredf(wioc);		/* read in a block */
      wioc->rcba = wioc->cba + 4;
    }
    /* see if at EOB */
    if(wioc->rcba[SBLR] & RCBEOB) {
      bfredf(wioc);		/* yes, read in next block */
      wioc->rcba = wioc->cba + 4;
    }
af02:
    /* see if at EOF yet */
    if(wioc->rcba[SBTR] & RCBEOF) {
      wioc->afcb->sflg |= EOFFLAG;	/* set EOF for caller */
      return(1);		/* return O.K. */
    }
    wioc->rcba += (wioc->rcba[BCTR] + 4);	/* next record address */
    goto af00;			/* continue looking for EOF */
}

/* rmwrit - write data on file stream */
static int rmwrit(cfd, buffer, cnt)
/* int rmwrit(cfd, buffer, cnt) */
int cfd;
unsigned char * buffer;		/* callers buffer */
int cnt;			/* byte count */
{
    register struct ioc * wioc;
    unsigned char * buffp;
    int bcnt, i;

    wioc = ircont(cfd);
    if(wioc == (struct ioc *)0)	/* see if error */
    	return(0);		/* return error */
    if(!wioc->flag.openop) {
        wioc->flag.openop = 1;	/* set open */
    }
#ifdef DBUG
printf("rmwrit(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
#ifdef DBUG
printf("rmwrit in: cnt = %d, buffer = %x\n", cnt, buffer);
#endif
    wioc->flag.writop = 1;	/* show output active */
    wioc->flag.outaop = 1;	/* show pool output active */
    wioc->flag.weofop = 0;	/* last op was not weof */
    if(wioc->cpp == 0) {	/* if no data in pool yet, initialize */
      wioc->cba = wioc->bufa;	/* point to 1st buffer */
      wioc->nab = 1;		/* 1st active block */
      wioc->cbn = 1;		/* 1st buffer */
      wioc->cpp = 1;		/* 1st pool */
      irbinit(wioc);		/* initialize buffer */
    }
    buffp = buffer;		/* save caller buff addr */
    bcnt = cnt;
#ifdef DBUG
    if(bcnt >= 0xff) {
      printf("write: char cnt over 254 bytes\n");
      rmerr(wioc, 8);		/* record too big error */
      return(-1);
    }
#endif
#ifndef GFIX
    /* see if we are setting on EOF & EOB */
    if(wioc->rcba[SBLR] & (RCBEOF | RCBEOB)) {	/* is it an EOF/EOB */
      wioc->rcba -= 4;		/* back over EOF/EOB */
    }
    /* set new block cnt */
    *(int *)wioc->cba = wioc->rcba - wioc->cba;
#endif
    /* see if enough space in current block */
    if((bcnt + 4) > (wioc->cba + BLKSIZE - wioc->rcba - 2)) {
    	irfinis(wioc);		/* finish block with zero fill */
    	bfwrit(wioc);		/* write it out */
    	irbinit(wioc);		/* initialize next block */
    }
    /* transfer user data to buffer */
    wioc->rcba[SBTR] = 0;	/* zero status byte */
    wioc->rcba[BCTR] = bcnt;	/* set byte count */
    cnt = bcnt;			/* save for caller */
    /* copy in user data */
    if(bcnt > 8)
      memcpy(&wioc->rcba[4], buffer, bcnt);
    else
      for(i = 0; i < bcnt; i++)
    	wioc->rcba[i+4] = buffer[i];
    wioc->rcba += (bcnt + 4);		/* next record address */
    wioc->rcba[SBLR] = 0;		/* zero status byte */
    wioc->rcba[BCLR] = bcnt;		/* set byte count */
    bcnt = wioc->rcba - wioc->cba;	/* set new block cnt */
#ifdef mpx
    *(int *)wioc->cba = bcnt;		/* set block count */
#else
    wioc->cba[2] = (bcnt >> 8) & 0xff;	/* upper byte */
    wioc->cba[3] = bcnt & 0xff;		/* lower byte */
#endif
    wioc->afcb->recl = cnt;		/* save count in fcb */
    wioc->afcb->erwa = (char *)buffer;	/* reset buffer address in caller fcb */
#ifdef DBUG
printf("rmwrit: recl = %d, buffer = %x\n", cnt, buffer);
#endif
    return(cnt);			/* return O.K. */
}

/* bfback - position to previous record */
static int bfback(wioc)
/* int bfback(wioc) */
register struct ioc * wioc;
{
    register int cnt;

#ifdef DBUG
printf("bfback(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
    if(wioc->cpp == 0)			/* if pool empty, return */
        return(1);			/* get out */
#ifndef FFIX
    if(wioc->rcba[SBTR] & RCBEOF)	/* is it an EOF */
    	return(1);			/* ignore, get out */
#endif
    if(wioc->rcba[SBLR] & RCBBOB) {	/* is it a beg of blk */
      /* 1st block in pool? */
      if(wioc->cbn > 1)		/* ignore if not 1st blk */
    	goto bs02;
      /* 1st pool in memory? */
      if(wioc->cpp == 1) {
    	/* we are already at BOM */
#ifdef DBUG
printf("return0 bfback(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
        return(1);			/* get out */
      }
bs02:
      /* read previous buffer from pool */
      /* see if previous buffer in memory */
      if(wioc->cbn == 1) {
        /* we are at 1st buffer, read in previous pool */
        /* position file to previous pool*/
        flposs(wioc, wioc->cpp - BLKMAX);	/* position file */
        plredf(wioc);		/* now read in the pool */
        wioc->cbn = BLKMAX;	/* we start at last buffer */
        /* reset address pointer to start of last block */
        wioc->cba = wioc->bufa + BLKS - BLKSIZE;
      } else {
        --wioc->cbn;		/* last buffer number */
        wioc->cba -= BLKSIZE;	/* last buffer address */
      }
#ifdef mpx
      cnt = *(int *)wioc->cba;		/* get count */
#else
      cnt = (wioc->cba[2] << 8) | wioc->cba[3];	/* get count */
#endif
      wioc->rcba = wioc->cba + cnt;
    }
    /* backspace to previous record in this block */
    wioc->rcba -= (wioc->rcba[BCLR] + 4);
#ifdef DBUG
printf("return bfback(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
    return(1);				/* get out */
}

/* bfredf - read next buffer from file stream */
static int bfredf(wioc)
register struct ioc * wioc;
{
    int bcnt;

#ifdef DBUG
printf("bfredf(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
    /* see if next buffer in memory */
    if(wioc->cbn >= wioc->nab) {
      /* no, read in next pool */
      if(plredf(wioc) == -1)	/* read next pool */
    	return(-1);		/* show EOF */
      wioc->cbn = 1;		/* we start at 1st buffer */
      wioc->cba = wioc->bufa;	/* reset address pointer */
    } else {
      ++wioc->cbn;		/* bump buffer number */
      wioc->cba += BLKSIZE;	/* next buffer address */
    }
#ifndef TRY_THIS_FRIDAY
#ifdef mpx
    bcnt = *(int *)wioc->cba;	/* get count */
#else
    bcnt = (wioc->cba[2] << 8) | wioc->cba[3];	/* get count */
#endif
    /* check for cnt < 0x300 (768) */
    if(bcnt >= 0x300) {
#ifdef DBUG
      printf("bfredf - block count greater than 768 bytes\n");
#endif
      rmerr(wioc, 5);		/* bad block count */
      return(-1);
    }
    /* check for just BOB on in control bits */
    wioc->rcba = wioc->cba + 4;
    if(((wioc->rcba[SBLR] & (RCBBOB | RCBEOB | RCBEOF)) == RCBBOB))
      return(1);		/* return O.K. */
    /* no BOB, set EOF in user FCB */
    wioc->afcb->sflg |= EOFFLAG;	/* set EOF for caller */
    rmerr(wioc, 5);		/* bad block count */
    return(-1);
#else
    return(1);		/* return O.K. */
#endif
}

/* bfwrit - write this buffer into pool */
static int bfwrit(wioc)
register struct ioc * wioc;
{
#ifdef DBUG
printf("bfwrit(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
    /* see if more buffers in memory */
    if(wioc->cbn < BLKMAX) {
      ++wioc->cbn;		/* current buffer number */
      wioc->nab = wioc->cbn; 	/* set number of active buffers */
      wioc->cba += BLKSIZE;	/* next buffer address */
      return(1);		/* return O.K. */
    }
    /* no, write out current pool */
    plwrit(wioc);		/* write out current pool */
    wioc->cpp += BLKMAX;	/* incr current pool position */
    wioc->nab = 1;		/* set number of active buffers */
    wioc->cbn = 1;		/* buffer number one */
    wioc->cba = wioc->bufa;	/* point to start of buffer */
    return(1);			/* return O.K. */
}

/* plredf - read next buffer pool from file stream */
static int plredf(wioc)
register struct ioc * wioc;
{
    register int fcba = (int)wioc->afcb;
    int retc;

#ifdef DBUG
printf("plredf(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
    /* read the file */
#ifdef mpx
    wioc->afcb->eqty = BLKS;	/* set byte count */
    wioc->afcb->erwa = (char *)wioc->bufa;	/* set buffer address */
    wioc->afcb->sflg = 0;	/* clear any error flags */
    asm(" trr r6,r1");		/* get fcb address */
    asm(" svc 1,x'31'");	/* do read */
    if(wioc->afcb->sflg & ERRFLAG) {
      rmerr(wioc, 4);		/* error condition found */
      return(-1);		/* return error */
    }
    if(wioc->afcb->sflg & EOFFLAG) {
      rmerr(wioc, 5);		/* premature EOF */
      return(-1);		/* return error */
    }
    if(wioc->afcb->sflg & EOMFLAG) {
      rmerr(wioc, 6);		/* EOM encountered */
      return(-1);		/* return error */
    }
    retc = wioc->afcb->recl;	/* get amount read */
#ifdef DBUG
printf("plredf: retc = %d\n", retc);
#endif
#else
    retc = read(wioc->fd, wioc->bufa, BLKS);
    wioc->afcb->recl = retc;	/* set amount read */
#ifdef DBUG
printf("plredf: retc = %d\n", retc);
#endif
#endif
    if(retc <= 0 || (retc % BLKSIZE != 0)) {
      wioc->afcb->sflg |= ERRFLAG;
      rmerr(wioc, 1);		/* less than 1 block read */
      return(-1);		/* show EOF for error */
    }
    /* compute # of blocks we read */
    wioc->nab = retc / BLKSIZE;
    wioc->cpp = wioc->cfp;	/* update curr pool position */
    wioc->cfp += wioc->nab;	/* update current file position */
#ifdef DBUG
printf("return plredf(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
    return(1);			/* return O.K. */
}

/* plwrit - write this buffer pool to file stream */
static int plwrit(wioc)
register struct ioc * wioc;
{
    register int fcba = (int)wioc->afcb;
    int retc;
    int bytcnt;

#ifdef DBUG
printf("plwrit(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
#ifdef DBUG
    /* see if file at correct poition */
    if(wioc->cpp > wioc->cfp) {
      /* this should never happen */
      rmerr(wioc, 12);		/* internal positioning error */
      return(-1);		/* error */
    }
#endif
    if(wioc->cpp < wioc->cfp) {
      /* file needs positioning */
      flposs(wioc, wioc->cpp);	/* position file */
    }
    /* determine bytes to write */
    bytcnt = wioc->nab * BLKSIZE;
    /* write the file */
#ifdef mpx
    wioc->afcb->eqty = bytcnt;	/* set byte count */
    wioc->afcb->erwa = (char *)wioc->bufa;	/* set buffer address */
    asm(" trr r6,r1");		/* get fcb address */
    asm(" svc 1,x'32'");	/* do write */
    if(wioc->afcb->sflg & ERRFLAG) {
      rmerr(wioc, 10);		/* error condition found */
      return(-1);		/* return error */
    }
    if(wioc->afcb->sflg & EOMFLAG) {
      rmerr(wioc, 11);		/* EOM encountered */
      return(-1);		/* return error */
    }
    retc = wioc->afcb->recl;	/* get amount written */
#ifdef DBUG
printf("plwrit: retc = %d, bytcnt = %d\n", retc, bytcnt);
#endif
#else
    retc = write(wioc->fd, wioc->bufa, bytcnt);
    wioc->afcb->recl = retc;	/* get amount written */
#ifdef DBUG
printf("plwrit: retc = %d, bytcnt = %d\n", retc, bytcnt);
#endif
#endif
    if(retc < bytcnt) {
      rmerr(wioc, 10);		/* error condition found */
      return(-1);		/* show EOF for error */
    }
    /* update current file position with # block we wrote */
    wioc->cfp += wioc->nab;	/* update current file position */
#ifdef DBUG
printf("return plwrit(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
    return(1);			/* return O.K. */
}

/* plrwnd - rewind this file */
static int plrwnd(wioc)
register struct ioc * wioc;
{
#ifdef DBUG
printf("plrwnd(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
#ifdef FIX_NBCAS_NOWRITE
    if(wioc->cpp != 1) {	/* 1st pool in memory? */
      /* no, see if output active */
      if(wioc->flag.outaop) {
    	/* write active pool first */
    	wioc->flag.outaop = 0;	/* not output active anymore */
    	wioc->flag.writop = 0;	/* not writing anymore */
    	plwrit(wioc);		/* write the pool */
      }
#ifdef FIX_NASA_CI
      wioc->cpp = 0;		/* no data in pool */
      wioc->nab = 0;		/* no active blocks */
      wioc->cbn = 0;		/* no current buffer */
    }
#else
    }
    wioc->cpp = 0;		/* no data in pool */
    wioc->nab = 0;		/* no active blocks */
    wioc->cbn = 0;		/* no current buffer */
#endif
    /* is file at beginning */
    if(wioc->cfp != 1) {	/* file at beginning? */
      flposs(wioc, 1);		/* position file to start */
    }
#else /* FIX_NBCAS_NOWRITE */
    /* see if output active */
    if(wioc->flag.outaop) {
      /* write active pool first */
      wioc->flag.outaop = 0;	/* not output active anymore */
      wioc->flag.writop = 0;	/* not writing anymore */
      plwrit(wioc);		/* write the pool */
    }
    flposs(wioc, 1);		/* position file to start */
    wioc->cpp = 0;		/* no data in pool */
    wioc->nab = 0;		/* no active blocks */
    wioc->cbn = 0;		/* no current buffer */
#endif /* FIX_NBCAS_NOWRITE */
    wioc->flag.writop = 0;	/* not writing anymore */
    return(1);			/* return O.K. */
}

/* flposs - position file to correct pool */
static int flposs(wioc, position)
register struct ioc * wioc;
int position;
{
    register int fcba = (int)wioc->afcb;
    register int delta = position - wioc->cfp;

#ifdef DBUG
printf("flposs(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
printf("flposs cpp = %d, cfp = %d, position = %d, delta = %d\n",
 wioc->cpp, wioc->cfp, position, delta);
#endif
    wioc->cfp = position;	/* set new position */
#ifdef FIX_NBCAS_NOWRITE
    if(delta == 0)
      return(1);		/* we are there, return O.K. */
#endif /* FIX_NBCAS_NOWRITE */
#ifdef mpx
    /* see if file is to be advanced */
    if(delta > 0) {
      /* skip to new poition */
      while(delta--) {
        asm(" trr r6,r1");	/* get fcb address */
    	asm(" svc 1,x'33'");	/* advance 1 record (sector) */
      }
      return(1);		/* return O.K. */
    }
    if(position <= 1) {	/* see if to beginning of file */
      asm(" trr r6,r1");	/* get fcb address */
      asm(" svc 1,x'37'");	/* rewind to BOF */
      return(1);		/* return O.K. */
    }
#ifndef FIX_NBCAS_NOWRITE
    if(delta == 0)
      return(1);		/* we are there, return O.K. */
#endif /* FIX_NBCAS_NOWRITE */
    /* here we want to backspace the file */
    while(delta++) {
      asm(" trr r6,r1");	/* get fcb address */
      asm(" svc 1,x'35'");	/* backspace 1 record (sector) */
    }
    return(1);			/* return O.K. */
#else
#ifndef FIX_NBCAS_NOWRITE
    if(delta == 0)
      return(1);		/* we are there, return O.K. */
#endif /* FIX_NBCAS_NOWRITE */
    /* seek to new position */
    if(lseek(wioc->fd, delta*BLKSIZE, 1) == -1) {
#ifdef DBUG
printf("flposs position error\n");
#endif
      return(-1);		/* go an error */
    }
    return(1);			/* return O.K. */
#endif
}

/* irweof - write EOF to block */
static int irweof(wioc)
register struct ioc * wioc;
{
    register int room;

#ifdef DBUG
printf("irweof(%d): cbn %d, nab %d, cpp %d, cfp %d\n",
 wioc->fd, wioc->cbn, wioc->nab, wioc->cpp, wioc->cfp);
#endif
    wioc->flag.writop = 1;	/* show output active */
    wioc->flag.outaop = 1;	/* show pool output active */
    if(wioc->cpp == 0) {	/* if no data in pool yet, initialize */
      wioc->cba = wioc->bufa;	/* point to 1st buffer */
      wioc->nab = 1;		/* 1st active block */
      wioc->cbn = 1;		/* 1st buffer */
      wioc->cpp = 1;		/* 1st pool */
      irbinit(wioc);		/* initialize buffer */
    } else {
      /* see if enough room for EOF */
#ifdef mpx
      room = *(int *)wioc->cba;	/* get count */
#else
      room = (wioc->cba[2] << 8) | wioc->cba[3];	/* get count */
#endif
      room = BLKSIZE - room;	/* space left */
      if(room < 6) {		/* need 6 bytes for EOF */
        /* not enough room, put EOF in next block */
        irfinis(wioc);		/* finish block */
        bfwrit(wioc);		/* write it */
        irbinit(wioc);		/* initialize next buffer */
      }
    }
    /* set up EOF flags */
    wioc->rcba[SBTR] = 0;
    wioc->rcba[BCTR] = 0;
    wioc->rcba[SBTR] |= (RCBEOF);	/* set EOF */
    wioc->rcba += 4;			/* next word */
    wioc->rcba[SBLR] = 0;
    wioc->rcba[BCLR] = 0;
    wioc->rcba[SBLR] |= (RCBEOF | RCBEOB);	/* set EOF & EOB */
    wioc->flag.weofop = 1;	/* show we just did EOF */
    room = (wioc->rcba - wioc->cba);	/* set new record cnt */
#ifdef mpx
    *(int *)wioc->cba = room;		/* set count */
#else
    wioc->cba[2] = (room >> 8) & 0xff;	/* upper byte */
    wioc->cba[3] = room & 0xff;		/* lower byte */
#endif
    /* EOF is always last block, so write it and ready new block */
    irfinis(wioc);		/* complete block */
    bfwrit(wioc);		/* write it */
    irbinit(wioc);		/* initialize next one */
#ifdef FFIX
    bfback(wioc);		/* now backup to EOF */
#endif
    wioc->nab = wioc->cbn;	/* reset current buffer number */
    return(1);			/* return O.K. */
}

/* irfinis - finish buffer by padding with zeros */
static int irfinis(wioc)
register struct ioc * wioc;
{
    register int cnt;

    wioc->rcba[SBLR] |= RCBEOB;		/* set EOB */
#ifdef mpx
    cnt = *(int *)wioc->cba;	/* get count */
#else
    cnt = (wioc->cba[2] << 8) | wioc->cba[3];	/* get count */
#endif
    cnt = BLKSIZE - cnt - 2;		/* chars to zero */
    memset(&wioc->rcba[SBTR], 0, cnt);	/* zero rest of buffer */
}

/* irbinit - initialize current buffer for write */
static int irbinit(wioc)
register struct ioc * wioc;
{
#ifdef mpx
    *(int *)wioc->cba = 4;	/* set byte count word */
#else
    wioc->cba[0] = 0;		/* clear the count word */
    wioc->cba[1] = 0;
    wioc->cba[2] = 0;
    wioc->cba[3] = 4;		/* set byte count, this record */
#endif
    wioc->rcba = wioc->cba + 4;	/* where to start */
    wioc->rcba[SBTR] = 0;	/* clear the rcb bytes */
    wioc->rcba[BCTR] = 0;
    wioc->rcba[SBLR] = RCBBOB;	/* set beginning of block bit */
    wioc->rcba[BCLR] = 0;	/* */
}

/* rmerr - handle errors encountered */
static int rmerr(wioc, num)
register struct ioc * wioc;
register int num;
{
#ifdef DBUG
printf("rmerr: error = %d\n", num);
#endif
    switch(num) {
      case 1:		/* less than 1 block on read */
      case 2:		/* not a multiple of blocks read */
/*    case 3:		/* no ioc's available */
      case 4:		/* error condition on read */
      case 7:		/* write attempted on unopen file */
      case 8:		/* user record too large (>254) */
      case 9:		/* read not allowed after write */
      case 10:		/* error on write */
      case 12:		/* internal file positioning error */
      case 13:		/* open resource error */
      case 14:		/* internal file positioning error */
    	wioc->afcb->sflg |= 0x40000000;	/* set error flag in fcb */
    	break;
      case 5:		/* premature EOF */
    	wioc->afcb->sflg |= 0x02000000;	/* set EOF in FCB */
    	break;
      case 6:		/* end of medium encountered */
      case 11:		/* EOM found */
    	wioc->afcb->sflg |= 0x01000000;	/* set EOM in FCB */
    	break;
    }
    wioc->flag.openop = 0;	/* close the ioc */
    wioc->flag.iocaloc = 0;	/* deallocate it */
    free(wioc->bufa);		/* free the buffer */
    wioc->bufa = 0;		/* clear buffer address */
    wioc->fd = -1;		/* clear file descriptor */
    rmerror = num;		/* set error number */
    return;
}
#endif /* NOBSS */
