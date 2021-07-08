/*~!print.c*/
/* Name:  print.c Part No.: _______-____r
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

#ident	"$Id: print.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

#include	"defs.h"
#include	<sys/param.h>
#ifndef mpx
#include <unistd.h>
#endif

#define		BUFLEN		256

static char buffer[BUFLEN + 2];
static int index = 0;
char numbuf[12];

void itos();
int stoi();
void prs();

extern void	prc_buff();
extern void	prs_buff();
extern void	prn_buff();
extern void	prs_cntl();
extern void	prn_buff();
extern void	failed();
extern int length();

/*
 * printing and io conversion
 */
void prp()
{
    if ((flags & prompt) == 0 && cmdadr) {
    	prs_cntl(cmdadr);
    	prs(colon);
    }
}


void prs(as)
char *as;
{
    register char *s;

    if (s = as)
    	write(output, s, length(s) - 1);
}


void prc(c)
char c;
{
    if (c)
    	write(output, &c, 1);
}


void prt(t)
long t;
{
    register int hr, min, sec;

    t += HZ / 2;
    t /= HZ;
    sec = t % HZ;
    t /= HZ;
    min = t % HZ;

    if (hr = t / HZ) {
    	prn_buff(hr);
    	prc_buff('h');
    }

    if (min)	/* for consistency */ {
    	prn_buff(min);
    	prc_buff('m');
    }
    prn_buff(sec);
    prc_buff('s');
}


void prn(n)
int n;
{
    itos(n);

    prs(numbuf);
}


void itos(n)
int n;
{
    register char *abuf;
    register unsigned a, i;
    int pr, d;

    abuf = numbuf;

    pr = FALSE;
    a = n;
    for (i = 10000; i != 1; i /= 10) {
    	if ((pr |= (d = a / i)))
    	    *abuf++ = d + '0';
    	a %= i;
    }
    *abuf++ = a + '0';
    *abuf++ = 0;
}


int stoi(icp)
char *icp;
#define	base	10
{
    register char *cp = icp;
    register int r = 0;
    register char c;

    while ((c = *cp, digit(c)) && c && r >= 0) {
    	r = r * base + c - '0';
    	cp++;
    }
    if (r < 0 || cp == icp)
    	failed(icp, badnum);
    	/*NOTREACHED*/
    else
    	return(r);
    return(0);          /* make compiler happy */
    /*NOTREACHED*/
}


void prl(n)
long n;
{
    int i;

    i = 11;
    while (n > 0 && --i >= 0) {
    	numbuf[i] = n % 10 + '0';
    	n /= 10;
    }
    numbuf[11] = '\0';
    prs_buff(&numbuf[i]);
}


void flushb()
{
    if (index) {
    	buffer[index] = '\0';
#ifdef TESTING
    	write(1, buffer, length(buffer) - 1);
#else
    	write(cstdout, buffer, length(buffer) - 1);
#endif
    	index = 0;
    }
}


void prc_buff(c)
char c;
{
    if (c) {
    	if (index + 1 >= BUFLEN)
    	    flushb();

    	buffer[index++] = c;
    } else
     {
    	flushb();
#ifdef TESTING
    	write(1, &c, 1);
#else
    	write(cstdout, &c, 1);
#endif
    }
}


void prs_buff(s)
char *s;
{
    register int len = length(s) -1;

    if (index + len >= BUFLEN)
    	flushb();

    if (len >= BUFLEN)
#ifdef TESTING
    	write(1, s, len);
#else
    	write(cstdout, s, len);
#endif
    else
     {
    	movstr(s, &buffer[index]);
    	index += len;
    }
}


void clear_buff()
{
    index = 0;
}


void prs_cntl(s)
char *s;
{
    register char *ptr = buffer;
    register char c;

    while (*s != '\0') {
    	c = (*s & 0177) ;

    	/* translate a control character into a printable sequence */

    	if (c < '\040') {	/* assumes ASCII char */
    	    *ptr++ = '^';
    	    *ptr++ = (c + 0100);	/* assumes ASCII char */
    	} else if (c == 0177) {	/* '\0177' does not work */
    	    *ptr++ = '^';
    	    *ptr++ = '?';
    	} else		 {	/* printable character */
    	    *ptr++ = c;
    	}

    	++s;
    }

    *ptr = '\0';
    prs(buffer);
}


void prn_buff(n)
int n;
{
    itos(n);

    prs_buff(numbuf);
}

