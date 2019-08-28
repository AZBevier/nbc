/*~!ctscan.c*/
/* Name:  ctscan.c Part No.: _______-____r
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

#ident	"@(#)nbclib:ctscan.c	1.0"

/*
 * ctscan - syntax scanner for command line
 *
 *	Gets a string from the line buffer at current cursor position
 *	Each call gets one argument of a maximum of N characters
 *
 *	3X - T_LINBUF + 17b is scan index
 *	     T_LINBUF + 16b is total line buffer length in words
 *
 *	1X - T_LINBUF + 9b is scan index
 *	     T_LINBUF + 8b is total line buffer length in words
 *
 *	Calling sequence len = ctscan(buffer, maxlen)
 *	where:
 *		len:	length of line returned, 0 if end of line
 *		buffer:	char pointer to callers return buffer
 *		maxlen:	maximum length of buffer to be returned
 *
 */

#include <mosde.h>

static char input[255];	/* local copy of scan line */
static char *linep = 0;	/* current position in input array */
static int eol = 0;	/*  end of line flag, set when c/r or ! found */

int ctscan(bufr, mlen)
char *	bufr;
int	mlen;
{
  char cib;	/* current input byte */
  char sb = 0;	/* zero if skipping leading blanks */
  char pt = 0;	/* non zero if skipping text */
  char pt2 = 0;	/* non zero if skipping text */
  int cnt = 0;	/* num of chars in bufr */

  /* set output string to null,to show no output yet */
  *bufr = '\0';		/* terminate output line */
  if (eol) {		/* at end of line, reset & return null */
    eol = 0;
    return (0);		/* return null */
  }
  if (linep == 0 && get_lbuf() == 0) return(0);	/* all done if nothing */
  /* process chars till end of line or max count */
  while ((cib = *linep++) && mlen--) {
    switch (cib) {
      case ' ':		/* a blank */
        if (pt||pt2)goto putout;	/* if passing text, output blank */
        if (!sb) continue;	/* ignore leading blanks */
        /* drop thru if not ignoring blanks */
      case ',':		/* comma is delimiter */
      case '=':		/* equal sign is delimiter */
        if (pt||pt2)goto putout;	/* if passing text, output character */
        if (cnt == 0) continue;	/* if nothing found yet, ignor delimiter */
        goto detok;		/* done with is entry */
      case '\n':	/* new line is delimiter */
      case '\r':	/* c/r is delimiter */
      case '\0':	/* null is delimiter */
      case '!':		/* ! is delimiter */
        eol = 1;	/* we are at end of input */
        goto detok;		/* done with is entry */
      case '\'':	/* apost is delimiter */
        if (pt2)continue;	/* if passing text, skip apost */
        if (pt) goto detok;	/* if passing text, now a delimiter */
        pt = 1;		/* now passing text, throw away apost */
        continue;
      case '\"':	/* quote is delimiter */
        if (pt)continue;	/* if passing text, skip quote */
        if (pt2) goto detok;	/* if passing text, now a delimiter */
        pt2 = 1;	/* now passing text, throw away quote */
        continue;
      default:
putout:
        sb = 1;		/* not skipping blanks anymore */
        *bufr++ = cib;	/* put char in output buffer */
        cnt++;		/* bump the count */
        continue;	/* continue processing */
    }
  }
detok:
  *bufr = '\0';		/* null terminate line */
  if (eol) linep = 0;	/* reset linepointer to read input again */
  return (cnt);		/* return what we go */

}

int get_lbuf()
{
  int * tsaa = (int *)(*((int *)C_TSAD));	/* get tsa address */
  char * llba = (char *)tsaa[T_LINBUF/sizeof(int)]; /* get ptr to line bufr */
  int maxl = llba[T_LBLEN] << 2;	/* get max length in bytes */
  int lbsi = llba[T_LBSI];		/* get current scan index */
  int gotone = 0;			/* set when a char found */

  if (linep != 0)return(0);		/* return if scan buffer active */
  linep = input;			/* set local pointer address */

  while (lbsi < maxl) {
    if (llba[lbsi] == '\n') break;	/* if C/R, all done */
    *linep++ = llba[lbsi++];		/* put char in output */
    gotone++;				/* count of chars copied */
  }
  if (gotone) {				/* see if any chars copied */
    *linep = 0;				/* null terminate line */
    linep = input;			/* reset buffer pointer */
  } else
    linep = 0;				/* nothing found reset buffer ptr */
  return (gotone);			/* return count */
}
