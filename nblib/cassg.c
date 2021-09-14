/*~!cassg.c*/
/* Name:  cassg.c Part No.: _______-____r
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

#ident	"@(#)nbclib:cassg.c	1.0"

/*
 * cassg - syntax scanner for assignments - this is MPX 1X version
 *
 *	Parse an assignment line into it's rrs
 *
 *	Calling sequence ret = _cassg(buffer)
 *	where:
 *		ret:	returns 0 for O.K., else error
 *		buffer:	char pointer to callers buffer
 */

#define CASSG
#include "unixio.h"
#include <string.h>
#include <ctype.h>

struct rrstag _rrs;		/* where current rrs is built */
struct finfo* _fib;		/* where file information block goes */

static int _parse();
struct finfo* pn2fib();		/* parse pathname into _fib */

static char input[256];		/* local copy of scan line */
static char *linep = 0;		/* current position in input array */
static int eol = 0;		/* end of line flag, set when c/r or ! found */
static int	mlen;		/* maximum length */
static int delim;		/* last delimiter found */

int _cassg(bufr)
char *	bufr;
{
  char token[64];		/* where token is to be parsed into */
  int  ccnt;			/* curr char count */
  char *tp;			/* temp pointer */
  char *p;			/* temp pointer */
  int  i,dt;			/* temp */

  bzero ((char *)&_rrs, sizeof (struct rrstag));	/* clear local rrs */
  strcpy (input, bufr);		/* make local copy of buffer */
  str2up (input);		/* make upper case */
  linep = input;		/* set buffer addres to be scanned */
  mlen = strlen(bufr);		/* set it's length */
  eol = 0;			/* not at eol yet */

  if ((ccnt = _parse(token, 0)) == 0)	/* parse off a token */
    return (-1);		/* nothing to parse, return error */

  /* get the base token to determine the type of rrs to be built */
  /* see if LFC=, DEV=, or TEMP= */
  if (delim == '=') {

    if (strcmp (token, "LFC") == 0) {

      /* process LFC = */
      _rrs.flags = 0x08;	/* show an LFC assign */

      /* parse off the LFC to assign */
      if ((ccnt = _parse(token, 0)) == 0)	/* parse off a token */
        return (-1);		/* nothing to parse, return error */

      /* copy the LFC into the rrs and blank fill */
      for (i=0, tp=(char *)&_rrs.wd2; i < 3; i++)
        if (!token[i])
    	  *++tp = ' ';
        else
    	  *++tp = token[i];

      if (_parse(token, 0))
    	return (-1);		/* error if anything else */
      return (0);		/* return O.K. if EOL found */

    } else if (strncmp (token, "DEV", 3) == 0) {

      /* process DEV= */
      _rrs.flags |= 0x10;	/* show a type 3 assign */

      /* scan for device=dtchsa */
      if (_pdevi(token) != 0)
    	return (-1);		/* error parsing devi */

      /* get next token if any */
      if (_parse(token, 0) == 0)
    	return (0);		/* o.k. if nothing else */

      dt = (_rrs.wd2 & 0x7f000000) >> 24;	/* get device type code */

      /* if mag tape get blocked=, id=, and/or multi= */
      if (dt >= 4 && dt <= 6) {

        /* default reel id to SCR */
        _rrs.size = 0x53435320;	/* SCR */

        while (!eol) {

          /* scan for reel=  or id= */
          if ((i = _preel(token)) < 0)
    	    return (-1);	/* error parsing reel id */

          if (!i) 		/* found reel, scan next token */
            if (_parse(token, 0) == 0)
    	      return (0);	/* o.k. if nothing else */

          /* scan for multi= or vol= */
          if ((i = _pmult(token)) < 0)
    	    return (-1);	/* error parsing id */

          if (!i) 		/* found id, scan next token */
            if (_parse(token, 0) == 0)
    	      return (0);	/* o.k. if nothing else */

          /* scan for blocked= */
          if ((i = _pbloc(token)) < 0)
    	    return (-1);	/* error parsing bloc */

          if (!i) 		/* found bloc, scan next token */
            if (_parse(token, 0) == 0)
    	      return (0);	/* o.k. if nothing else */
        }
      }

      /* if disk, get blocked= and/or size */
      if (dt >= 1 && dt <= 3) {

        /* default size to 400 blocks */
        _rrs.size = 400;

        while (!eol) {

          /* scan for size= */
          if ((i = _psize(token)) < 0)
    	    return (-1);	/* error parsing size */

          if (!i) 		/* found size, scan next token */
            if (_parse(token, 0) == 0)
    	      return (0);	/* o.k. if nothing else */

          /* scan for blocked= */
          if ((i = _pbloc(token)) < 0)
    	    return (-1);	/* error parsing bloc */

          if (!i) 		/* found bloc, scan next token */
            if (_parse(token, 0) == 0)
    	      return (0);	/* o.k. if nothing else */
        }
      }
      return (0);		/* return O.K. if EOL found */

    } else if (strcmp (token, "TEMP") == 0) {

      /* process TEMP=dtchsa,size,u */

    }

  /* check for filename in quotes, if not check for "special" files */
  } else if (delim != '\'') {

    /* check for "special" files: SLO, SBO, SYC, SGO, or TEMP */
    if (strcmp (token, "SLO") == 0) {

      /* process SLO */
      _rrs.flags |= 0x40;	/* show an SLO assign */
      _rrs.wd2 = 0x00534c4f;	/* lfc = SLO */

      /* if terminator was a ',' then # lines follow */
      if (delim == ',') {
        if ((ccnt = _parse(token, 0)) == 0)	/* parse off a token */
          return (-1);		/* nothing to parse, return error */

        /* check for valid numbers only */
        for (p=token; *p; p++)
    	  if (!isdigit(*p))
    	    return(-1);

        /* 5 lines per block */
        _rrs.size = (atol(token) + 4)/5; /* get number of lines */
      }

      /* if no # lines, then nothing else should follow */
      /* NOTE: should allow DEVICE= for 3X compatability, but not now */
      if (_parse(token, 0))
    	return (-1);		/* error if anything else */
      return (0);		/* return O.K. if EOL found */

    } else if (strcmp (token, "SBO") == 0) {

      /* process SBO */
      _rrs.flags |= 0x40;	/* show an SBO assign */
      _rrs.wd2 = 0x0053424f;	/* lfc = SBO */

      /* if terminator was a ',' then # cards follow */
      if (delim == ',') {
        if ((ccnt = _parse(token, 0)) == 0)	/* parse off a token */
          return (-1);		/* nothing to parse, return error */

        /* check for valid numbers only */
        for (p=token; *p; p++)
    	  if (!isdigit(*p))
    	    return(-1);

        /* 6 lines per block */
        _rrs.size = (atol(token) + 5)/6; /* get number of lines */
      }

      /* if no # cards, then nothing else should follow */
      if (_parse(token, 0))
    	return (-1);		/* error if anything else */
      return (0);		/* return O.K. if EOL found */

    } else if (strcmp (token, "SYC") == 0) {

      /* process SYC */
      _rrs.flags |= 0x20;	/* show an SYC assign */
      _rrs.wd2 = 0x00535943;	/* lfc = SYC */

      if (_parse(token, 0))
    	return (-1);		/* error if anything else */
      return (0);		/* return O.K. if EOL found */

    } else if (strcmp (token, "SGO") == 0) {

      /* process SGO */
      _rrs.flags |= 0x20;	/* show an SGO assign */
      _rrs.wd2 = 0x0053474f;	/* lfc = SGO */

      if (_parse(token, 0))
    	return (-1);		/* error if anything else */
      return (0);		/* return O.K. if EOL found */

    } else if (strcmp (token, "TEMP") == 0) {

      /* process TEMP with no volume */
      _rrs.flags |= 0x10;	/* show a type 3 assign */
      _rrs.size = 400;		/* default to 400 blocks */
      _rrs.wd2 = 0x01000000;	/* default to any disk  - DC */

      /* now look for an option  keywords */
      /* size=nnnn   blocked=t/f y/n  device=dtchsa */
      /* or temp,size,u NOTE: add later if necessary */
      if (_parse(token, 0) == 0)
    	return (0);		/* o.k. if nothing else */

      while (!eol) {

        /* scan for size= */
        if ((i = _psize(token)) < 0)
    	  return (-1);		/* error parsing size */

        if (!i) 		/* found size, scan next token */
          if (_parse(token, 0) == 0)
    	    return (0);		/* o.k. if nothing else */

        /* scan for blocked= */
        if ((i = _pbloc(token)) < 0)
    	  return (-1);		/* error parsing bloc */

        if (!i) 		/* found bloc, scan next token */
          if (_parse(token, 0) == 0)
    	    return (0);		/* o.k. if nothing else */

        /* scan for device=dtchsa */
        if ((i = _pdevi(token)) < 0)
    	  return (-1);		/* error parsing devi */

        if (!i) 		/* found devi, scan next token */
          if (_parse(token, 0) == 0)
    	    return (0);		/* o.k. if nothing else */
      }
      return (0);		/* return O.K. if EOL found */
    }
  }

  /* it must be a file name, process path */
  /* reset parser, and scan for pn */
  linep = input;		/* set buffer addres to be scanned */
  mlen = strlen(bufr);		/* set it's length */
  eol = 0;			/* not at eol yet */
  if (_parse(token, 1) == 0)
    return (-1);		/* error if nothing */

  if ((_fib = pn2fib(token)) == 0)
    return (-1);		/* pn parse error */

  /* now set up rrs */
  _rrs.flags |= 0x80;		/* show a type 1 assign */

  /* see if blocked= on line */
  if (_parse(token, 0) ==0)
    return (0);			/* nothing else, return */

  if (_pbloc (token) < 0)
    return(-1);			/* error parsing block= */

  return (0);			/* return O.K. if EOL found */

}

/* test for device=dtchsa in line */
static int _pdevi(tok)
char * tok;
{
  char *p = tok;
  char *tp;
  int i, d;
  int reg[8];

  if (!(*tok))
    return (-1);		/* error if nothing */

  if (delim != '=')
    return (-1);		/* error if not devi= */

  if (strncmp(tok, "DEV", 3) == 0) {

    if ((i = _parse(tok, 0)) == 0)	/* parse off a token */
      return (-1);		/* nothing to parse, return error */

    reg[6] = reg[7] = 0x20202020;	/* set r6 & r7 to blanks */
    tp = (char *)&reg[6];

    switch (i) {

      /* if size is 6 have dtchsa */
      case 6:			/* dtchsa, get sa */
        _rrs.wd2 |= 0x8000;	/* set sa present */
        tp[2] = tok[4];
        tp[3] = tok[5];

      /* if size is 4 have dtch */
      case 4:			/* dtch, get sa */
        _rrs.wd2 |= 0x80000000;	/* set ch present */
        tp[0] = tok[2];
        tp[1] = tok[3];
        mpxsvc(0x1029, reg, reg);	/* convert ascii hex to bin hex */
        if (reg[6] == 0)
    	  return (-1);		/* bad char in input */
        _rrs.wd2 |= reg[7];	/* set chan &| sa */

      /* if size is 2 have dt */
      case 2:			/* dt, get sa */
        reg[2] = ((int)tok[0] << 8) + (int)tok[1]; /* put dev mnemonic in r2 */
        mpxsvc(0x1014, reg, reg);	/* get device type code */
        if (reg[2] & 0x80000000)
    	  return(-1);		/* dev type not found */
        _rrs.wd2 |= ((unsigned)reg[2] << 24);	/* set dev type */
        return (0);		/* return O.K. */

      default:
        return (-1);		/* error */
    }
  }
  return (1);			/* DEVI not found */
}

/* test for blocked=t/f y/n in line */
static int _pbloc(tok)
char * tok;
{
  if (!(*tok))
    return (-1);		/* error if nothing */

  if (delim != '=')
    return (-1);		/* error if not blocked= */

  if (strncmp(tok, "BLOC", 4) == 0) {

    if (_parse(tok, 0) == 0)	/* parse off a token */
      return (-1);		/* nothing to parse, return error */

    /* check for n or f in line, set unblocked if found */
    if (*tok == 'N' || *tok == 'F')
      _rrs.flags |= 4;		/* set unblocked */

    else if (*tok == 'Y' || *tok == 'T')
      ;				/* just test for y/t */

    else return(-1);		/* not valid char */
    return (0);			/* return O.K. */
  }
  return (1);			/* BLOC not found */
}

/* test for reel=abcd or id=abcd in line */
static int _preel(tok)
char * tok;
{
  char * p;
  int i;

  if (!(*tok))
    return (-1);		/* error if nothing */

  if (delim != '=')
    return (-1);		/* error if not size= */

  if ((strcmp(tok, "REEL") == 0) || (strncmp(tok, "ID", 2))) {

    if ((i = _parse(tok, 0)) == 0)	/* parse off a token */
      return (-1);		/* nothing to parse, return error */

    if (i < 1 || i > 4)
      return(-1);		/* not right char count */

    /* first set reel id to all blanks */
    _rrs.size = 0x20202020;	/* blank it */
    p = (char*)&_rrs.size;	/* point where reel id goes */
    for (; i >0; i--)
      *p++ = *tok++;		/* copy in id */
    return (0);			/* return O.K. */
  }
  return (1);			/* REEL not found */
}

/* test for size=nnnn in line */
static int _psize(tok)
char * tok;
{
  char * p;

  if (!(*tok))
    return (-1);		/* error if nothing */

  if (delim != '=')
    return (-1);		/* error if not size= */

  if (strcmp(tok, "SIZE") == 0) {

    if (_parse(tok, 0) == 0)	/* parse off a token */
      return (-1);		/* nothing to parse, return error */

    /* check for valid numbers only */
    for (p=tok; *p; p++)
      if (!isdigit(*p))
    	return(-1);

    /* convert size to binary and put in rrs */
    _rrs.size = atol(tok);	/* get number of blocks */
    return (0);			/* return O.K. */
  }
  return (1);			/* SIZE not found */
}

/* test for multi=nnn or vol=nnn */
static int _pmult(tok)
char * tok;
{
  char * p;
  int i;

  if (!(*tok))
    return (-1);		/* error if nothing */

  if (delim != '=')
    return (-1);		/* error if not size= */

  if ((strcmp(tok, "VOL") == 0) || (strncmp(tok, "MUL", 3))) {

    if (_parse(tok, 0) == 0)	/* parse off a token */
      return (-1);		/* nothing to parse, return error */

    /* check for valid numbers only */
    for (p=tok; *p; p++)
      if (!isdigit(*p))
    	return(-1);

    /* convert size to binary and put in rrs */
    i = atol(tok);		/* get volume number */
    if (i < 0 || i > 255)
      return(-1);		/* number out of range */
    _rrs.wd2 |= (i << 16);	/* put in vol number */
    return (0);			/* return O.K. */
  }
  return (1);			/* VOL not found */
}

/* parse buffer */
static int _parse(bufr, pn)
char *	bufr;
int     pn;			/* set if reparse for parthname */
{
  char cib;			/* current input byte */
  char sb = 0;			/* zero if skipping leading blanks */
  int cnt = 0;			/* num of chars in bufr */

  /* set output string to null,to show no output yet */
  *bufr = '\0';			/* terminate output line */
  if (eol) 			/* at end of line, reset & return null */
    return (0);			/* return null */

  /* process chars till end of line or max count */
  while ((cib = *linep++) && mlen--) {

    switch (cib) {

      case ' ':			/* a blank */
        if (!sb)
    	  continue;		/* ignore leading blanks */
        /* drop thru if not ignoring blanks */
        goto dond;		/* done with is entry */

      case '=':			/* equal sign is delimiter */
      case ',':			/* comma is delimiter */
      case '(':			/* left paren is delimiter */
      case ')':			/* right paren is delimiter */
        if (pn)
    	  goto ignore;		/* if pathname, scan till blank or EOL */
        goto dond;		/* done with is entry */

      case '\n':		/* new line is delimiter */
      case '\r':		/* c/r is delimiter */
      case '\0':		/* null is delimiter */
      case '!':			/* ! is delimiter */
        eol = 1;		/* we are at end of input */
        goto dond;      	/* done with is entry */

      default:
ignore:
        sb = 1;			/* not skipping blanks anymore */
        *bufr++ = cib;		/* put char in output buffer */
        cnt++;			/* bump the count */
        continue;		/* continue processing */
    }
  }

dond:
  delim = cib;			/* tell caller what delimiter was */
  *bufr = '\0';			/* null terminate line */
  if (!mlen)
    eol = 1;			/* reset linepointer to read input again */
  return (cnt);			/* return what we go */
}
