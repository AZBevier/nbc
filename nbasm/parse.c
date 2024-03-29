/* parse.c */

#include	"defs.h"
#include	<ctype.h>
#include	<string.h>
/* #include	<stdlib.h> */

/*#define FPBUG*/   /* if defined, debugging */
/*#define MACS*/
/*#define MACP*/
/*#define MACD*/
/*
#ifndef MYATOF
#define MYATOF
#endif
*/

#ifdef DOS
int	runst(int32);
int	unst(int32);
int	cunst(int32);
void	upterm(char);		/* update terminator list */
int	gbyte(int32);
int	gbyt(int32);
int	getabyte(int32);
int	termchk (char, unsigned int32);
void	grps();
int	fac(int);
struct	tval	val(int);
void	tdat();
void	tmd(int);
void	tfn();
void	tcy();
void	tsh(int);
void	tdg(int32, int, int);
int32	*cnum(int);
void	negate(int32 *);
void	lefts(int32 *, int);
void	rights(unsigned int32 *, int);
void	add64(int32 *, int32 *);
void	mulfp64(int32 *, int32 *);
void	divfp64(int32 *, int32 *);
#else
int32	*cnum();		/* cnum function */
#endif
int32	cnumval[2];		/* two 32 bit ints */
char	cnumterm;		/* the terminator character */
char	hbcnul;			/* return the sign also */

char	unterm;			/* last terminator */
int	unstnp;			/* unstring counter */
uint8	mgbd[32];	/* internal label generation area */
uint8	munsta[MAXCHARS];	/* name substitution generation area */
int32	munstap;		/* char counter in munsta */
char	leftzero;		/* non-zero if ignoring leading blanks */
char	ccset;			/* set non zero by gbyt if flag set */
char	cc2set;			/* set non zero by gbyt if flag set */
uint8	*munsts6;	    /* macro pointer */
char	fsts6 = 0;		/* flag for skipping blanks */
char	insymarg;		/* save loc */

char	unstck;			/* delimiter check flags */
#define	NOPCK	1		/* no parameter checks if expanding macro */
#define VALDCK	2		/* valid delimiter check if set */

int32	hwindr;			/* contains the indirect flag, if any to be */
				/* merged into the current instr format */
int	grpw;			/* number of expressions to do */

struct	tval	expr[5];	/* expression variable information */

short	hhvfx;			/* this is a right to left bit stack */
short	hhvfo;			/* the number of bits in the stack */
short	hhvfs;			/* num of it req'd in the curr gen element */
short	hhvff;			/* num of bits sent to gen/vfd routn */
short	hhvfgb;			/* num of bits accepted for output to stack */

struct	tval	litorgs[32];	/* literal origins */

extern struct tval inac;	/* defined in goasm.c */
extern struct tval inag;	/* defined in goasm.c */
extern struct tval currpc;	/* defined in goasm.c */

/*
 * unst - unstring word into usname until terminator found
 * input - list of terminators
 * output - name in usname
 *	    number of chars returned
 *	    terminator in unterm
 */

int	runst(terms)
int32	terms;
{
	leftzero = 0;			/* don't ignore leading blanks */
	return(cunst(terms));
}

int	unst(terms)
int32	terms;
{
	leftzero = 1;			/* ignore leading blanks */
	return(cunst(terms));
}

int	cunst(terms)
int32	terms;
{

/*
*        UNSTRING ONE WORD INTO WORK AREA usname.  UNSTRINGING WILL
*        CONTINUE UNTIL A CHARACTER IS FOUND WHICH IS IN THE TERMINATOR
*        LIST# THE TERMINATOR LIST IS DESCRIBED AS ONE BYTE
*        OUTPUT IS THE UNSTRUNG NAME IN usname, THE NUMBER OF
*        BYTES IN THE UNSTRUNG NAME IN R3
*        THE TERMINATOR IN R7
*        AND THE UPDATED TERMINATOR LIST IN hbstac
*/
	int	cnt = 0;		/* clear counter */
	char	chr = 0;		/* current character */

	spmac &= ~INTGEN3;		/* clear internal3 bit */
	spmac |= UNS;			/* set unstring bit */
	unstnp = 0;			/* zero normal store pointer */
	memset (usname, ' ', MAXCHARS);	/* blank receiving area */
#ifdef MACP
printf("enter cunst terms = %x leftzero %x\n", terms, leftzero);
#endif
	if (leftzero) {			/* are we ignoring blanks */
unstblnk:
	  if (++cnt >= 12) {		/* check for blank field */
	    upterm(chr);		/* update terminator list */
	    return(0);			/* show no chars unstrung */
	  }
	  bits |= INSIG;		/* set insignificant flag */
	  chr = gbyt(terms);		/* get one byte U/C */
#ifdef MACP
printf("unstblnk: chr = %x, terms = %x\n", chr, terms);
#endif
	  if (cc2set) {			/* force termination */
	    upterm(chr);		/* update terminator list */
	    return(unstnp);		/* count of chars unstrung */
	  }
	  if (ccset) {			/* the character was a terminator */
	    if (!(unstck & NOPCK)) {	/* see if no parameter checks */
	      if (chr == ',')		/* check for valid parameter delim */
	        unstck |= VALDCK;	/* valid terminator found */
	    }
	    unstck &= ~NOPCK;		/* turn off check bit */
	    /* if char a space and nothing in usname and dummy was unstrung */
	    /* return, we unstrung a dummy with colon or blank terminator */
	    if (chr != ' ')		/* if not space exit */
	      goto unst6;		/* set terminator & exit */
	    if (unstnp)			/* anything in usname */
	      goto unst6;		/* set terminator & exit */
	    if (!(spmac & DUMMY))	/* was a dummy unstrung */ 
              goto unstblnk;		/* still doing blanks */
unst6:
	    upterm(chr);		/* update terminator list */
	    return(unstnp);		/* count of chars unstrung */
	  }
	  if (chr == ' ')goto unstblnk;	/* still doing blanks */
	  /* go process non blank, non terminator char */
	  goto unstcont;		/* go on */
	} 
	/* not ignoring left blanks */
unstnoblk:
	chr = gbyt(terms);		/* get one byte U/C */
#ifdef MACP
printf("unstnoblk: chr = %x, terms = %x ccset = %x\n", chr, terms, ccset);
#endif
	if (ccset) {			/* force termination */
	  upterm(chr);			/* update terminator list */
	  return(unstnp);		/* count of chars unstrung */
	}
unstcont:
	/* come here when char is not a terminator */
	unstck &= ~NOPCK;		/* turn off check bit */
	/* if an internal symbol has been processed and in macro call */
	if ((INTGEN3 & spmac) && (CALLUS & macstate)) {
	  /* we are in a macro call */
	  if (yeanay()) {		/* are we assembling */
	    seterr ('I');		/* set internal symbol error */
	  }
	  goto unstnoblk;		/* go get next char */
	}
	/* if internal symbol unstrung and not in macro call or repeat scan */
	if ((spmac & INTGEN3)&&(!(CALLUS & macstate))&&(!(RSCAN & macstate))) {
	  /* process the internal symbol */
	  unsigned char *cp = mgbd;	/* point to internal symbol */

	  unstnp -= 2;			/* backup count for internal symbol */
	  while (*cp != ' ') {		/* copy in new label */
	    if (unstnp < MAXCHARS) {	/* don't overun buffer */
	      usname[unstnp] = *cp;	/* copy char in */
	    }
	    cp++;			/* bump pointer */
	    unstnp++;			/* bump count */
	  }
	  spmac &= ~INTGEN3;		/* clear flag */
	}
	/* normal character processing */
	if (unstnp < MAXCHARS) {
	  usname[unstnp] = chr;		/* copy char in */
	}
	unstnp++;			/* bump count */
	goto unstnoblk;			/* go get next char */
}

/*
 * upterm - update terminator list and reset unstring bit
 * input - new terminator
 */

void	upterm(nterm)		/* update terminator list */
char	nterm;			/* new terminator */
{
	hbstac[3] = hbstac[2];
	hbstac[2] = hbstac[1];
	hbstac[1] = hbstac[0];
	hbstac[0] = nterm;	/* set last terminator */
	unterm = nterm;		/* set last terminator */
	spmac &= ~UNS;		/* clear unstring bit */
}

char	upcase;			/* if non zero, upper case convert */

/*
 * gbyte - get upper case byte
 * gbyt - get any case byte
 * input - list of terminators
 * output - the next character
 *	    ccset = 1 if terminator found, else zero
 *	    cc2set = 1 if special termination requested
 */

int	gbyte(terms)
int32	terms;
{
	upcase = 1;			/* we want uppercase */
	return(getabyte(terms));	/* return char */
}

int	gbyt(terms)
int32	terms;
{
	upcase = 0;			/* we want any case */
	return(getabyte(terms));	/* return char */
}

int	getabyte(terms)
int32	terms;
{
	unsigned char	thechar;
	int	offset;
	unsigned char *	cmpp;		/* the current macro pointer */
	unsigned char * tmp;		/* tmp pointer */

	ccset = 0;			/* clear terminator flag found */
	cc2set = 0;			/* clear spec termination flag found */
	spmac &= ~DUMMY;		/* clear dummy arg flag */
scanb:
#ifdef MACP
printf("scanb: terms = %x, macstate = %x, bits = %x, spmac = %x\n", terms, macstate, bits, spmac);
#endif
	if (macstate & REUNSTF) {	/* in middle of char */
unst9:					/* go pass out int sym number */
#ifdef MACP
printf("unst9: got REUNSTF flag, macstate = %x, bits = %x, spmac = %x\n", macstate, bits, spmac);
#endif
	  macstate &= ~REUNSTF;		/* clear more bytes in string flag */
	  thechar = *munsts6++;		/* get next character */
	  if (!(bits & ESCAPE2)) {	/* is this going to be escaped */
	    if (thechar != ' ')		/* not escaped, it it a space */
	      fsts6++;			/* no, finished with leading spaces */
	    if (thechar == ',')		/* at the end of macro string */
	      goto scanb;		/* yes, go get next char */
	    if (fsts6 && thechar == ' ') /* if not leading space, it is term */
	      goto scanb;		/* end of macro sub string, next char */
	  } /* it is an escaped char */
	  macstate |= REUNSTF;		/* show more bytes in the string */
	  goto unstl;			/* go check out the char */
	}
	if (inscnt >= 72) {		/* check for overscan */
#ifdef MACP
printf("overscan return\n");
#endif
	  inscnt = 80;			/* overrun the count */
	  thechar = ' ';		/* feed a blank */
	  if (macstate & UNSTFLAG)
	    goto unstb;			/* yes, go finish dummy processing */
	  ccset = 1;			/* it was terminator, tell caller */
	  bits &= ~INSIG;		/* force off insignificant flag */
	  return(thechar);		/* return the character */
	}

unsts:
#ifdef MACP
printf("unsts: unstringing %.72s\n term = %x [%c], inscnt = %d, REUNSTF is %s, CALLUS is %s\n",
 in, unterm, unterm, inscnt, (macstate & REUNSTF) ? "ON" : "OFF", (macstate & CALLUS) ? "ON" : "OFF");
#endif
	thechar = in[inscnt++];		/* get an input byte */
#ifdef MACP
printf("fetched thechar = %c\n", thechar);
#endif
	if (upcase)			/* uppercase read */
	  if (thechar >= 'a' && thechar <= 'z')	/* yes, l/c char */
	    thechar -= 0x20;		/* convert to upper case */
	if (macstate & REUNSTF) {	/* in middle of char */
	  /* get the pointer for this arg number */
	  if (!(spmac & INTGEN3))	/* has an int sym been processed */
	    insymarg = thechar;		/* no, store arg num in insymarg */
	  else 
	    if (!(macstate & CALLUS))	/* are we in a macro call */
	      insymarg = thechar;	/* no, store arg num in insymarg */
	    
	  offset = 24 * (int)thechar;	/* arg # x 3 double words */
	  /* mpp has parameter stack pointer for this level in stk */
	  cmpp = mpp->clev;		/* parameter base for this level */
#ifdef MACD
printf("unsts: offset = %d, thechar = %x, cmpp = %x, level = %x, inscnt = %d\n",
  offset, thechar, (uint32)cmpp, level, inscnt);
#endif
	  cmpp += offset;		/* point to current symbol for param */
#ifdef MACD
printf("unsts: stackp = %x, stkp = %x, mpp = %x, cmpp = %x\n",
  (uint32)stackp, (uint32)stkp, (uint32)mpp, (uint32)cmpp);
printf("unsts: parameter is %c%.7s\n",
 (*cmpp == 0xff ? '!' : *cmpp), &cmpp[1]);
#endif
	  if (*cmpp == 0xff) 		/* is internal sym defined */
	    macstate |= INTGEN;		/* yes, mark it and go process */
	  else
	    if (*cmpp == ' ') {		/* is name still undefined */
	      /* process a new internal tag */
	      char intsym[16];		/* new internal symbol */

	      memset(mgbd, ' ', 32); 	/* preblank buffer */
	      memset(cmpp, ' ', 24); 	/* preblank buffer */
	      /* get symbol num of 5 digits with leading 0 and trailing blanks */
	      sprintf(intsym, "%.5X   ", (inttag++ & 0xffff));
	      memcpy(mgbd, intsym, 8);	/* put symbol name */
	      memcpy(cmpp, intsym, 8);	/* copy into stack */

	      *mgbd = '!';		/* internal symbol lead printout char */
	      *cmpp = 0xff;		/* int sym lead char to stack */
#ifdef MACD
printf("unsts: int param %c%.7s\n",
 (*cmpp == 0xff ? '!' : *cmpp), &cmpp[1]);
#endif
	      macstate |= INTGEN;	/* indicate internal label generated */
	    }

#ifdef MACD
printf("unsts: final param %c%.7s\n",
 (*cmpp == 0xff ? '!' : *cmpp), &cmpp[1]);
#endif
	  if (!(spmac & INTGEN3)) {	/* has an int sym been processed */
	    if (macstate & RSCAN)	/* no, are we repeat scan */
	      spmac |= INTGEN3;		/* set internal3 flag */
	    else
	      spmac &= ~UNS;		/* trick gbyt into thinking it was */
					/* called by unst */
	  } else {
	    if ((!(macstate & CALLUS)) && (!(macstate & RSCAN))) {
	      unsigned char *tcp = mgbd;	/* point to internal symbol */

	      unstnp -=2;		/* backup count by 2 */
	      while (*tcp != ' ') {	/* copy name till 1st blank */
	        if (unstnp < MAXCHARS)	/* don't overrun buffer */
	          usname[unstnp] = *tcp;	/* put char in buffer */
	        unstnp++;		/* bump char count */
	        tcp++;			/* bump pointer */
	      }
	      spmac &= ~UNS;		/* trick gbyt into thinking it was */
					/* called by unst */
	    }
	  }

	  memset(mgbd, ' ', 32);	/* preblank buffer */
	  memcpy(mgbd, cmpp,  24);	/* copy in the int label */
	  if (*cmpp == 0xff) *mgbd = '!';  /* int sym print out char */
	  munsts6 = mgbd;		/* retrieval address */
	  fsts6 = 0;			/* we will skip leadin blanks */
	  if (!(spmac & UNS)) {		/* did we come from unst */
	    spmac &= ~INTGEN3;		/* clear internal3 flag */
	    goto unst9;			/* go pass out int sym number */
	  }

	  if (!(macstate & RSCAN)) {	/* are we repeat scan */
	    if (macstate & CALLUS) {	/* no, are we in macro call */
	      if (unstnp) {		/* anything in usname */
	        if (yeanay()) {		/* yes, are we assembling */
	          seterr ('I');		/* set internal error */
	        }
	        while ((thechar = *munsts6++) != ' ')  /* scan till blank */
	          pbyt(thechar);	/* put char to output buffer */
	        macstate &= ~REUNSTF;	/* clear int unstring flag */
	        goto scanb;		/* go get next char */
	      }
	    }
	    thechar = 0xff;		/* internal sym lead char */
	  } else {
	    mbyt('%');			/* dummy lead character */
	    mbyt(insymarg);		/* save internal sym arg number */
	    thechar = '%';		/* dummy lead character */
	  }
	  if (unstnp < MAXCHARS)
	    usname[unstnp] = thechar;	/* copy out the char */
	  unstnp++;			/* bump count */
	  if (unstnp < MAXCHARS)
	    usname[unstnp] = insymarg;	/* copy out the arg number */
	  unstnp++;			/* bump count */
	  while ((thechar = *munsts6++) != ' ')  /* scan till blank found */
	    pbyt(thechar);		/* put char to output buffer */
	  macstate &= ~REUNSTF;		/* clear int unstring flag */
	  goto scanb;			/* go get next char */

	}
	/* not middle of a char */

					/* go check out the char */
unstl:
#ifdef MACP
printf("unstl: unstringing %.72s\n term %x [%c], inscnt %d, REUNSTF %s, CALLUS %s, UNSTFLAG %s, ESCAPE2 %s, INSIG  %s\n",
 in, unterm, unterm, inscnt, (macstate & REUNSTF) ? "ON" : "OFF",
 (macstate & CALLUS) ? "ON" : "OFF",
 (macstate & UNSTFLAG) ? "ON" : "OFF",
 (bits & ESCAPE2) ? "ON" : "OFF",
 (bits & INSIG) ? "ON" : "OFF");
#endif
	if (macstate & UNSTFLAG)	/* processing dummy name */
	  goto unstb2;			/* yes, go finish dummy processing */
	if (bits & ESCAPE2)		/* is this escaped */
	  goto unstl2;			/* yes, then don't allow code sens */
	if (thechar == '%')		/* starting a macro dummy */
	  goto unstb1;			/* go do next dummy */

unstll:
	if (!(macstate & CALLUS))	/* are we in a real macro call */
	  goto unstl2;			/* no, pass any char */
	if (thechar == ';') {		/* is this a continuation char */
#ifdef MACP
printf("unstll: got a %c\n", thechar);
#endif
	  goto unstl3;			/* yes, don't copy to macro storage */
	}
	if (thechar == ' ') {		/* see if space */
	  if (bits & INSIG) {		/* are we ignoring this space */
	    bits &= ~INSIG;		/* indicate we have a non space */
	    if (termchk (thechar, terms))	/* see if a terminator */
	      ccset = 1;		/* it was terminator, tell caller */
#ifdef MACP
printf("termchk3 ret ccset = %x, usname = %s, term = %c\n", ccset, usname, thechar);
#endif
	    bits &= ~INSIG;		/* force off insignificant flag */
	    return(thechar);		/* return the character */
	  }
	}
	if (spmac & INTGEN3)		/* was an int sym unstrung */
	  goto unstl3;			/* don't copy to macro storage */
unstl2:
#ifdef MACP
printf("unstl2: char to mbyt %x [%c]\n", thechar, thechar);
#endif
	mbyt(thechar);			/* copy byte to macro prototype */
unstl3:
#ifdef MACP
printf("unstl3: char to pbyt %x [%c]\n", thechar, thechar);
#endif
	pbyt(thechar);			/* put char to output buffer */
	if (bits & ESCAPE2) {		/* was previous char escape */
	  bits &= ~ESCAPE2;		/* clear escape char coming flag */
	  bits &= ~INSIG;		/* force off insignificant flag */
	  return(thechar & 0x3f);	/* return the masked escape character */
	}
	if (thechar != ';') {		/* is this the continuation char */
#ifndef CAID
    	  /* ignore " if in stab call */
    	  if(bits & INSTAB)goto unstsrc; /* ignore if on */
#endif
	  if (thechar == '\"') {	/* no, is this the escape char */
	    bits |= ESCAPE2;		/* set escape char coming flag */
	    if (!(macstate & CALLUS))	/* are we in macro call */
	      goto scanb;		/* no, go get next char */
	    /* ignore escape char on macro call */
	  }
#ifndef CAID
unstsrc:			/* allow ';'and '"' in stab entries */
#endif
	  if (termchk (thechar, terms))	/* see if a terminator */
	    ccset = 1;			/* it was terminator, tell caller */
#ifdef MACP
printf("termchk ret ccset = %x, usname = %s, term = %c\n", ccset, usname, thechar);
#endif
	  bits &= ~INSIG;		/* force off insignificant flag */
	  return(thechar);		/* return the character */
	}
#ifndef CAID
    	/* a ';' has been found, ignore if in stab call */
    	if(bits & INSTAB)goto unstsrc;	/* ignore if on */
#endif
#ifdef MACP
printf("unstby-1: got a %c\n", thechar);
#endif
unstby:
	inpt();				/* get next image */
	macstate |= NOCOMMT;		/* not in a comment */
	inscnt = 0;
	/* scan off blanks from continuation lines */
	while ((inscnt < 72) && ((thechar = in[inscnt++]) == ' '));
	if (inscnt >= 72)goto unstby;	/* get another image */
#ifdef MACP
printf("unstby: unstringing %.72s\n term = %x [%c], inscnt = %d, in[0] = %.2x, thechar = |%.2x|,\n REUNSTF is %s, CALLUS is %s, UNSTFLAG is %s, ESCAPE2 is %s, INSIG is %s\n",
 in, unterm, unterm, inscnt, in[0], thechar, (macstate & REUNSTF) ? "ON" : "OFF",
 (macstate & CALLUS) ? "ON" : "OFF",
 (macstate & UNSTFLAG) ? "ON" : "OFF",
 (bits & ESCAPE2) ? "ON" : "OFF",
 (bits & INSIG) ? "ON" : "OFF");
#endif
	goto unstl;			/* go check out the char */

unstb1:					/* go do next dummy */
	unstck &= ~VALDCK;		/* clear exp macro bit */
	if (macstate & EXPAND) {	/* % found, expanding macro */
	  unstck |= VALDCK;		/* valid terminator found */
	  if (REUNSTF & macstate)	/* middle of char expan */
	    goto unstll;		/* % was just a passed char */
	  macstate |= REUNSTF;		/* set middle of char expan */
	  goto unsts;			/* go get arg number */
	}

	if (!(macstate & DEFMBODY))	/* are we macro body */
	  goto unstll;			/* no, then ignore % */
	mbyt(thechar);			/* copy out to macro storage */
	memset (munsta, ' ', 8);	/* blank dummy name area */
	munstap = 0;			/* no chars yet */
	macstate |= UNSTFLAG;		/* turn on dummy unstringing flag */
	goto scanb;			/* go get next char */

unstb:					/* yes, go finish dummy processing */
	macstate &= ~UNSTFLAG;		/* reset unstring dummy flag */
unstb2:					/* yes, go finish dummy processing */
	if (bits & ESCAPE2) {		/* was preceeding char an escape */
	  bits &= ~ESCAPE2;		/* reset the flag */
	  thechar &= 0x3f;		/* yes, mask it and go on */
	  goto unstb3;			/* put char in the name area */
	}
	if (thechar == ';')		/* if continuation char */
	  goto unstby;			/* go get next line */
	if (thechar == '\"') {		/* is this the escape char */
	  bits |= ESCAPE2;		/* set escape char coming flag */
	  if (!(macstate & CALLUS))	/* are we in macro call */
	    goto scanb;			/* no, go get next char */
	  /* ignore escape char on macro call */
	  bits &= ~INSIG;		/* indicate we have a non space */
	  if (termchk (thechar, terms))	/* see if a terminator */
	    ccset = 1;			/* it was terminator, tell caller */
#ifdef MACP
printf("termchk2 ret ccset = %x, usname = %s, term = %c\n", ccset, usname, thechar);
#endif
	  bits &= ~INSIG;		/* force off insignificant flag */
	  return(thechar);		/* return the character */
	}
	if (!(termchk (thechar, terms))	 &&	/* see if a terminator */
	  (thechar != '%') &&		/* or start of a macro */
	  (thechar != ':')) {		/* or concatination char */
unstb3:					/* put char to name area */
	  if ((int32)munstap < 8)		/* limit name to 8 chars */
	    munsta[munstap] = thechar;  /* save the char */
	  munstap++;			/* bump the count */
	  goto scanb;			/* go get next char */
	}
	/* convert name to positional notation on stack */
	offset = 0;			/* positional counter */
	/* see if name in stack */
	for (tmp = macparam; tmp < macdptr; offset++, tmp += 8) {
#ifdef MACD
printf("unstb3: munsta = %.8s, tmp = %.8s, offset = %d\n", munsta, tmp, offset);
#endif
	  if (!memcmp (munsta, tmp, 8)) /* name in stack */
	    /* name found */
	    goto unstb4;		/* get out of loop */
	}
	/* tmp points to found entry or vacent entry */
	if (tmp >= macdptr) {		/* name found */
	  memcpy (tmp, munsta, 8);	/* no, copy name in */
	  macdptr += 8;			/* bump the stack pointer */
	  defcnt = offset;		/* save param # */
	  defcnt++;			/* make into a count */
	}
unstb4:
#ifdef MACD
printf("unstb4: offset = %d, stackp = %x, stkp = %x, tmp = %x, macdptr = %x, level = %d\n",
  offset, (uint32)stackp, (uint32)stkp, (uint32)tmp, (uint32)macdptr, level);
printf("unstb4: parameter %c%.7s\n", (*tmp == 0xff ? '!' : *tmp), &tmp[1]);
#endif
	mbyt (offset);			/* put offset into prototye storage */
	spmac |= DUMMY;			/* indicate a dummy was unstrung */
	macstate &= ~UNSTFLAG;		/* turn off dummy name unstringing */
	if (thechar == ':')		/* see if concatenation */
	  goto scanb;			/* go get next char */
	if (thechar == '%')		/* see if starting dummy */
	  goto unstb1;			/* go do next dummy */
	mbyt(thechar);			/* put char into prototype storage */
	cc2set = 1;			/* special termination found */
	ccset = 1;			/* it was terminator, tell caller */
	bits &= ~INSIG;			/* force off insignificant flag */
	return(thechar);		/* return the character */
}


/*
 * termchk - check if charecter is terminator
 * input - the character to test
 *         the terminator bitflag list
 * output - 1 = terminator found
 *          0 = no terminator found
 */
 
int	termchk (chr, terms)
char	chr;
unsigned int32 terms;
{

	/* if escape char coming or not a valid termination char, return 0 */
	if ((bits & ESCAPE2) || (chr < ' ') || (chr > '?')) return(0);
#ifdef MACP
printf("doing termcheck char = %c, terms = %x, ret = %x, inscnt = %d, macstate = %x\n",
 chr, terms, ((terms << (chr & 0x1f)) & 0x80000000) ? 1 : 0, inscnt, macstate);
#endif
	if ((terms << (chr & 0x1f)) & 0x80000000) /* check for terminator */
	  return (1);			/* the char matched a terminator */
	return(0);			/* not a terminator */
}

char	argmin[] = {1,1,2,2};	/* MINIMUM NUMBER OF OPERANDS FOR opcodes */
char	argmax[] = {1,2,2,3};	/* MAXIMUM NUMBER OF OPERANDS FOR opcodes */
char	bndws1[] = {2,0,1,0,3,0,1,0};	/* PROGRAM COUNTER STATUS INDICATORS */
char	bndws2[] = {1,3,7};	/*  MODULO 2,4,8 MASKS */
char	grpss2[] = {3,2,0,0,0}; /* OFFSET FOR B,H,W,D,A TYPE ADR RESP. */
/* char	tctg[] = {1,2,4,8}; */

int32	hdtds[2];	/* integer part of constant */
int32	hdtdf[2];	/* fraction part of constant */
int	secnag;		/* SECT NUM OF AUGEND */
int	secnac;		/* SECT NUM OF ACCUMULAND */

#define ARG1	0x08			/* arg 1 bit */
#define	ARG2	0x04			/* arg 2 bit */
#define	ARG3	0x02			/* arg 3 bit */
#define	ARG4	0x01			/* arg 4 bit */
#define UERROR	0x00000400		/* bit for 'U' error */

/*
 * grps - scan expressions from input
 * input - in line of input
 * output - values in expr[?].value
 *          terminators in expt[?].tmp
 */

void	grps()
{
	struct	tval	theval;
	int	i, lval;
	struct symbol FAR *stp;
	int	grpss1;			/* temp save for addressing type */
	int	hwerrfa;
	int	k = 0;			/* parameter counter */
	char	litname[8];		/* literal flags & data as bytes */

	theval.value = 0;		/* zero value */
	theval.type = 0;		/* zero type */
	theval.flags = 0;		/* zero flags */
	theval.tmp = 0;			/* zero terminator */
	for (i=0; i < 5; i++) {		/* zero expression storage */
	  expr[i].value = 0;		/* zero value */
	  expr[i].type = 0;		/* zero type */
	  expr[i].flags = 0;		/* zero flags */
	  expr[i].tmp = 0;		/* zero terminator */
	}
	hwindr = 0;			/* clear indirect addressing flag */
	grpw = -5;			/* set number of expressions */
grps1:
#ifdef MACP
    printf("grps1: calling unst\n");
#endif
	unst(0x81fd0004);		/* unstring something */
#ifdef MACP
    printf("grps: unst called, name = %.8s, unterm = %c,\n", usname, unterm);
#endif
	if (*usname == ' ') {		/* is name spaces */
	  theval.value = 0x20202020;	/* all blanks if we get to grps8 */
	  /* see if * or = */
	  if (unterm == '*' || unterm == '=') {
#ifdef MACP
printf("grps: = or * found, process literal or indirect\n");
	    /* process indirect or literal */
printf("grps1: fac call grpw = %d\n", grpw);
#endif
	    if (fac(grpw))goto grps8;	/* error if not allowed */
	    if (unterm == '*') {	/* is it indirect */
	      /* process indirect */
	      if (BM & option) {	/* is base mode option set */
	        if (yeanay()) {		/* are we assembling */
	          seterr ('S');		/* set indirect error */
	        }
	      } else			/* indirect O.K. */
	      hwindr |= INDFLAG;	/* set bit 11, indirect flag */
	      theval = val (0);		/* unstring another element */
	    } else {
	      /* else process a literal */
#ifdef MACP
printf("grps: = found, process literal\n");
#endif
	      tot = 4;			/* set word len for tdat */
	      hbtttf = 8;		/* set direct data to literal area */
	      grpss1 = hbavar;		/* save addressing type */
	      hwerrfa = hwerrf;		/* save error flags */
	      hwerrf = 0;		/* clear for later testing */
	      inac.value = 0;		/* initial default for adr eval */
	      inac.flags = 0;		/* initial default for adr eval */
	      inac.type = 0;		/* initial default for adr eval */
	      inac.tmp = 0;		/* initial default for adr eval */
	      inacbn = 0;		/* clear common block number */
	      for (i = 0; i < 4; i++)	/* clear terminator stack */
		hbstac[i] = ' ';	/* to blanks */
#ifdef MACP
printf("grps: calling tdat\n");
#endif
	      tdat();			/* evaluate literal */
#ifdef MACP
prtval("val has currpc", &currpc);
prtval("val has theval", &theval);
prtval("val has inac", &inac);
#endif 
	      /* hdtds has the  value */
	      theval.value = hdtds[0];	/* get the value */
	      theval.tmp = inac.tmp;	/* get the terminator */
#ifdef MACP
printf("grps1: literal = %x\n", theval.value);
#endif
	      if (!yeanay())		/* are we not assembling */
	        goto grps8;		/* don't assemble */
	      hwerrfa |= hwerrf;	/* or in the new errors */
	      if (hwerrf & UERROR) {	/* was there an undefined */
	        hwerrf = hwerrfa;	/* restore updated errors */
		if (yeanay())		/* are we assembling */
#ifdef MACP
printf("X error3 inac.type = %x\n", inac.type);
#endif
	 	  seterr ('X');		/* set X error */
	        goto grps8;		/* continue processing */
	      }
	      hwerrf = hwerrfa;		/* restore updated errors */
	      switch (inac.type) {	/* check out data type */
		case TYPCON:		/* a constant */
		case TYPP:		/* program symbol */
		case TYPC:		/* common symbol */
		  break;		/* o.k. */
		default:		/* anything else is error */
		  if (yeanay()) {	/* are we assembling */
#ifdef MACP
printf("X error inac.type = %x\n", inac.type);
#endif
		    seterr ('X');	/* set X error */
		  }
		  goto grps8;		/* continue processing */
	      }
	      /* put block # in byte 0, type of literal in byte 3 */
	      /* put rel info in byte 1 */
	      hdtds[0] = (((int32)inacbn << 24) | ((int32)inac.flags << 16) | inac.type);
	      hdtds[1] = theval.value;	/* the literal constant */
	      /* put literal value into symbol table */
#ifdef MACP
printf("entering literal %x,%x num = %x\n", hdtds[0], hdtds[1], hwltct.value);
#endif
	      i = hwltct.flags;			/* save the flags */
#ifndef TRYIT
	      hwltct.flags = theval.flags;	/* save type */
#else
	      /* literal must be output to current section */
	      hwltct.flags = currpc.flags;	/* save flags */
#endif
#ifdef MACS
prtval("val1 has currpc", &currpc);
prtval("val1 has theval", &theval);
prtval("val1 has inac", &inac);
#endif
#ifndef alpha_fix
	      litname[0] = hdtds[0] >> 24 & 0xff;
	      litname[1] = hdtds[0] >> 16 & 0xff;
	      litname[2] = hdtds[0] >> 8 & 0xff;
	      litname[3] = hdtds[0] & 0xff;
	      litname[4] = hdtds[1] >> 24 & 0xff;
	      litname[5] = hdtds[1] >> 16 & 0xff;
	      litname[6] = hdtds[1] >> 8 & 0xff;
	      litname[7] = hdtds[1] & 0xff;
	      stp = ss (&hwltct, litname);	/* put literal in sym tab */
#else
	      stp = ss (&hwltct, (char *)hdtds); /* put literal in sym tab */
#endif
	      hwltct.flags = i;			/* restore flags */
#ifdef MACS 
printf("lastval = %x, hwltct = %x\n",symval.value, hwltct.value);
#endif
	      if (symval.value == hwltct.value)	/* new literal entered */
		hwltct.value++;		/* no, bump count */
	      i = ((stp->desc.value >> 16) & 0xff); /* get lpool number */
	      lval = (symval.value & 0xffff) << 2;	/* get literal number */
	      lval += litorgs[i].value;		/* add in literal base */
	      theval.type = litorgs[i].type;	/* get the type */
	      theval.flags = litorgs[i].flags;	/* get the flags */
#ifdef MACS 
prtval("val2 has currpc", &currpc);
prtval("val2 has theval", &theval);
prtval("val2 has inac", &inac);
#endif
	      hbavar = grpss1;		/* addressing user wanted */
	      theval.value = lval + grpss2[hbavar];	/* offset in word */
	      hbbn = 0;			/* clear section number */
#ifdef MACS
printf("literal is in %s\n", (symval.flags & CSDS) ? "CSECT" : "DSECT");
#endif
	      if (litorgs[i].flags & CSDS) {	/* is literal in csect */
		hbbn = 1;		/* set literal in csect */
		goto grps8;		/* go store value */
	      }
	      i = ((stp->desc.value >> 16) & 0xff); /* get lpool number */
	      if (litorgs[i].type != TYPC)	/* is type common */
		goto grps8;		/* no, leave as dsect */
	      hbbn = litorgs[i].value >> 16;	/* get block number */
	      goto grps8;		/* go store value */
	    }				/* end of literal processing */
	  } else {			/* process unstrung element */
	    /* process unstrung element */
	    theval = val (1);		/* indicate element unstrung */
	  }
	} else {
	  /* process unstrung element */
	  theval = val (1);		/* indicate element unstrung */
	}
	/* evaluate expression */
#ifdef MACD
prtval("val theval", &theval);
prtval("val inac", &inac);
#endif
    	/* see if auto sectioning on */
    	if (option & ASECT) {
    	  /* see if external reference */
    	  if (theval.type == TYPX)
    	    bacflag |= 4;		/* show external variable */
    	}
	/* is it prog abs */
	if ((theval.type == TYPP) && (!(theval.flags & ABSREL)))
	  goto grps8;			/* theval has inac */
	if (theval.type == TYPC) {	/* is it common */
	  hbbn = inacbn;		/* set common block number */
	} else {
	  hbbn = 0;			/* indicate dsect */
	  if (secnac & 1) 		/* was it csect */
	    hbbn = 1;			/* indicate csect ref */
	}
/* printf("grps8: fac call grpw = %d\n", grpw); */
	fac(grpw);			/* set err if bad */
	/* theval should have inac */
	/* theval has value to store */
grps8:
	expr[k] = theval;		/* store value in list */
/* R5 SET BY CNUM WHEN CALLED BY VAL */
	if (*hbstac != ' ') {		/* test terminator */
	  /* not done yet */
	  k++;				/* next storage location */
	  grpw++;			/* bump max number */
	  if (grpw < 0)			/* at max yet */
	    goto grps1;			/* not finished, do next one */
	}
/*
printf("expr[0].value = %x, expr[1].value = %x\n", expr[1].value, expr[1].value);
printf("opcode = %s, subaug = %x\n", curops->opcode, curops->subaug);
*/
	k = curops->subaug;		/* get sub aug infor */
	if (k & ARG1) {			/* check arg 1 for even */
	  if (expr[0].value & 1) {	/* is arg 1 not even */
	    if (yeanay()) 		/* are we assembling */
	      seterr ('B');		/* set register bound error */
	  }
    }
	if (k & ARG2) {			/* check arg 2 for even */
	  if (expr[1].value & 1) {	/* is arg 2 not even */
	    if (yeanay()) 		/* are we assembling */
	      seterr ('B');		/* set register bound error */
	  }
    }
	k &= 3;				/* just use arg indicator */
	i = grpw + 6;			/* oper cnt converted to 0-5 */
	if ((i > argmax[k]) || 		/* see if # arg */
	  (i < argmin[k])) {		/* out of range */
					/* out of range error */
	  if (yeanay()) {		/* are we assembling */
/*
printf("X error2 inac.type = %x\n", inac.type);
printf("X k = %x, i = %x, argmin = %x, argmax = %x\n",
 k,i,argmin[k],argmax[i]);
*/
	    seterr ('X');		/* set wrong number of args error */
	  }
	}
#ifdef MACD
prtval("val3 has currpc", &currpc);
prtval("val3 has theval", &theval);
prtval("val3 has inac", &inac);
prtval("val3 has expr", &expr[0]);
prtval("val3 has expr", &expr[1]);
prtval("val3 has expr", &expr[2]);
#endif
	return;				/* return */
}

/*
 * fac - see if rel, comm, or extern allowed in this field
 * input - curops points to opcode entry
 *	 - grpw has parameter number
 * output  - return 0 for ok, else 1
 */

int	fac(grpw)
int	grpw;
{
	int	cnt = grpw + 6;		/* convert to 0-5 range */

	/* see if this field number is ok */
/*
printf("fac: field # = %d, cnt = %d\n", curops->fieldnum, cnt);
*/
	if (curops->fieldnum == cnt) return(0);	/* yes, ok */
	if (yeanay()) {			/* are we assembling */
/*
printf("fac: 'R' error, field # = %d, cnt = %d\n", curops->fieldnum, cnt);
*/
	  seterr ('R');			/* set relocation error */
	}
	return(1);			/* return error */
}

char	vdt[] = {
		0,0,		/* null */
		0,1,		/* undefined */
		0,0,		/* literal */
		2,2,		/* common */
		0,1,		/* prog abs, prog rel */
		0,1,		/* multiply defined */
		3,3,		/* external */
		2,2,		/* common */
	/* extensions for set, macro, & form */
		0,1,
		0,0,
		0,0,
		0,0,
		0,0
};
/* general list of terminators */
#ifdef NOTNOW
char	vals[] = {9, ' ', ',', '\'', '(', ')', '+', '-', '*', '/'};
char	vddc[] = {0,0,0,0,0,0,1,2,3};	/*  POINTERS FOR ABOVE LIST */
#endif
		
char	vdc[] = {				/* action operators */
	0x08,0x0c,0x0c,0x04,0x08,0x04,0x04,0x04,	/* + operator */
	0x08,0x04,0x04,0x04,0x18,0x04,0x04,0x04,	/* + operator */
	0x10,0x0c,0x0c,0x04,0x20,0x10,0x04,0x04,	/* - operator */
	0x04,0x04,0x14,0x04,0x04,0x04,0x04,0x04,	/* - operator */
	0x10,0x04,0x04,0x04,0x04,0x04,0x04,0x04,	/* * operator */
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,	/* * operator */
	0x10,0x04,0x04,0x04,0x04,0x04,0x04,0x04,	/* / operator */
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04		/* / operator */
};

char	valundf;			/* set nozero if val undefined */
char	vdap;				/* operation to do */

/*
 * val - evaluate one expression
 * input - 1 = element unstrung already, else not
 * output - inac.flags = csect/dsect and abs/rel flags for variable 
 *	  - inac.type = type of the variable
 *	  - inac.tmp = last terminator found
 *	  - inac = accumulated value
 */

struct	tval	val(unsflag)
int	unsflag;
{
/*
* EVALUATE ONE EXPRESSION---INPUT- R2BIT 31=1 MEANS ELEMENT UNSTRUNG ALR
* OUTPUT- R7 AND HWINAC B0-7 CONTAIN TYPE CODE, B8=1 MEANS REL
*         BITS 9-31 CONTAN THE NUMERIC EQUIVALENT OF THE EXPRESSION
*        R5 CONTAINS THE NUMERIC EQUIV OF THE NON-NUMERIC TERMINATOR
*/
	int	i,j,k,ii,jj;		/* temps */
	int32	result = 0;		/* temp result value */
/*	struct symbol FAR *stp;	*/	/* temp pointer */
	char	augtype;		/* augmend 2 bit type */
	char	acctype;		/* accumuland 2 bit type */
	char	valterm;		/* the terminator for value unstrung */

	inac.value = 0;			/* zero value */
	inac.type = 0;			/* zero type */
	inac.flags = 0;			/* zero flags */
	inac.tmp = 0;			/* zero terminator */
	accum.value = 0;		/* zero value */
	accum.type = 0;			/* zero type */
	accum.flags = 0;		/* zero flags */
	accum.tmp = 0;			/* zero terminator */
	inagbn = 0;			/* zero block # of augned */
	valterm = 0;			/* clear non numberic terminator */
	secnag = 0;			/* clear sect # of augend */
	if(!(bits2 & ALVAL)) {		/* should we eval 1st operand */
					/* yes, do 1st operand */
	  if (!unsflag) {		/* is element unstrung */
	    /* element not unstrung, go unstring it */
	    for (i=0; i<4; i++)		/* blank terminator list */
	     hbstac[i] = ' ';		/* blanks */
	    unst(0x81fd0000);		/* unstring an element */
	  }
	  /* latest terminator in unterm */
val3:
	  /* clear augend storage */
	  inag.value = 0;		/* zero value */
	  inag.type = 0;		/* zero type */
	  inag.flags = 0;		/* zero flags */
	  inag.tmp = unterm;		/* save the terminator */
	  valterm = unterm;		/* save terminator */
#ifdef MACP
printf("val3: usname = %s, unterm = %c\n", usname, unterm);
#endif
	  if ((unterm == '\'') || (unterm == '(')) /* was terminator ' or ( */
	    goto valq;			/* go process */
	  if (!strncmp(usname, "$   ", 4)) {	/* is it a loc ctr ref */
	    				/* it is a pc reference */
	    if (asctflg & ASCTNOD) {	/* is no $ flag set */
	      seterr ('O');		/* yes, set operend error */
	      asctflg &= ~ASCTNOD;	/* clear the flag */
	      inag.tmp = ' ';		/* show blank terminator */
	      return (inag);		/* return null */
		/* what to do here 
         	BU        NEXT         AND BAIL OUT OF INST.
 		*/
	    }
	    inag = currpc;		/* use pc for augument arithmetic */
	    goto vala;			/* go use it */
	  }
	  if ((!strncmp(usname, "    ", 4)) ||	/* is it all spaces or */
	    (!strncmp(usname, "$$  ", 4))) {	/* a special zero name */
	    goto vala;			/* continue processing */
	  }

	  if (!strncmp(usname, "$$$ ", 4)) {	/* is it a loc ctr ref */
	    inag.value = repdone;	/* set iteration count as new aug */
	    goto vala;			/* continue processing */
	  }

	  if (*usname >= '0' && *usname <= '9') {	/* process number */
	    cnum(10);			/* get the number */
	    inag.value = cnumval[0] & 0x7fffff;  /* just get 23 bit number */
	    inag.tmp = cnumterm;	/* save the terminator */
	    valterm = unterm;		/* save the terminator */
	    goto vala;			/* continue processing */
	  }

	  if (yeanay()) {		/* are we assembling */
#ifdef MACS
printf("val found a symbol %s, pcmode = %d\n", usname, pcmode);
prtval("val has currpc", &currpc);
#endif
	    i = currpc.type;		/* save pctype */
	    currpc.type = TYPU;		/* show type as undefined */
/*	    stp = ss (&currpc, usname); */	/* find symbol */
	    ss (&currpc, usname);	/* find symbol */
	    currpc.type = i;		/* restore pctype */
	
	    inag.type = symval.type;	/* save type */
	    inag.flags = symval.flags;	/* save flags */
	    inag.value = symval.value;	/* save the value */
	  }
	}
vala:
#ifdef MACS
printf("vala has a symbol %c%.7s, pcmode = %d\n", ((unsigned char)*usname == 0xff ? '!':*usname), &usname[1], pcmode);
prtval("vala has currpc", &currpc);
prtval("vala has inag", &inag);
prtval("vala has inac", &inac);
#endif
	bits2 &= ~ALVAL; 		/* clear should we eval 1st operand */
	/* process augmend */
	inag.value = inag.value & 0x7fffff;	/* get aug value */
	secnag = 0;			/* clear aug sect num */
	if (inag.flags & CSDS)		/* is aug csect */
	  secnag |= 1;			/* indicate csect section */
	/* is type undefined relocatable */
	if ((inag.type == TYPU) && (inag.flags & ABSREL))
	  valundf = 1;			/* value is undefined */
	/* merge type of value and abs/rel flag */
	i = ((inag.type << 1) | ((inag.flags & ABSREL) >> 1));
	augtype = vdt[i];		/* get 2 bit type code */
#ifdef OLD
	if (augtype != TYPC2)		/* is type common */
	  inag.flags &= ~ABSREL;	/* no, set absolute */
#endif
	/* process accumuland */
	inac.value = inac.value & 0xffffff;	/* get acc value */
	secnac = 0;			/* clear acc sect num */
	if (inac.flags & CSDS)		/* is acc csect */
	  secnac |= 1;			/* indicate csect section */
	/* is type undefined relocatable */
	if ((inac.type == TYPU) && (inac.flags & ABSREL))
	  valundf = 1;			/* value is undefined */
	/* merge type of value and abs/rel flag */
	i = ((inac.type << 1) | ((inac.flags & ABSREL) >>1));
	acctype = vdt[i];		/* get 2 bit type code */
#ifdef OLD
	if (acctype != TYPC2)		/* is type common */
	  inac.flags &= ~ABSREL;	/* no, set absolute */
#endif
	if (augtype == TYPC2) {		/* is 2 bit code common */
					/* processing for common only */
	  inagbn = ((int32)(inag.value & 0xff0000) >> 16);  /* get com blk # */
	  inag.value = inag.value & 0xffff;	/* just use the displacement */
	}

	switch (hbstac[1]) {		/* switch on prev terminator */
	  case ' ':			/* a blank */
	  case ',':			/* a comma */
	  case '\'':			/* an appost */
	  case '(':			/* left parend */
	  case ')':			/* right parend */
	  case '+':			/* a plus */
	    vdap = 0;			/* function to do */
	    break;			/* continue */

	  case '-':			/* minus */
	    vdap = 1;			/* function to do */
	    break;			/* continue */

	  case '*':			/* asterisk */
	    vdap = 2;			/* function to do */
	    break;			/* continue */

	  case '/':			/* slash */
	    vdap = 3;			/* function to do */
	    break;			/* continue */

	  default: 			/* not a valid terminator */
	    if (yeanay()) {		/* are we assembling */
#ifdef MACD
 printf("term hbstac[0] is %x\n", hbstac[0]);
 printf("term hbstac[1] is %x\n", hbstac[1]);
#endif
	      seterr ('E');		/* set element error */
	    }
	    goto vale;			/* finish this element */
	}
	/* generate 6 bit switch value based on 2 bit operator above */
	/* and 2 bit augend type code and 2 bit accumuland type */
	j = ((((vdap << 2) | augtype) << 2) | acctype);
#ifdef MACD
printf("vde: switch on vdc[%d] = %x, vdap = %d, augtype = %d, acctype = %d\n",
	 j, vdc[j], vdap, augtype, acctype);
prtval("vde has currpc", &currpc);
prtval("vde has inag", &inag);
prtval("vde has inac", &inac);
#endif
	switch (vdc[j]) {		/* get action routine value */
	  case 0x00:			/* an error */
	  case 0x04:			/* an error */
	  case 0x1c:			/* an error */
vde:
	    if (yeanay()) {		/* are we assembling */
	      seterr ('V');		/* set VFD error */
	    }
	    goto vale;			/* finish up */

	  case 0x0c:			/* constant */
	    augtype = acctype;		/* set final type code */
	    secnag = secnac;		/* set section number */
	    goto vdag;

	  case 0x08:			/* an operator */
vdag:
	    if (vdap == 0) {		/* plus operator */
    	      /* see if processing rez or res */
    	      if (bacflag & 64) {
    		accum.value += inag.value;	/* add last value */
    	      }
	      if (augtype == TYPREL) {	/* is augend relocatable */
		secnac = secnag;	/* aug sec num to acc sec num */
	      } else {
		if (augtype == TYPC2)	/* is type of aug common */
		  inacbn = inagbn;	/* aug blk # to acc blk # */
	      }
	      result = inac.value + inag.value;	/* add in accumuland */
	      goto valh;		/* continue processing */

	    } else
	    if (vdap == 1) {		/* minus operator */
    	      /* see if processing rez or res */
    	      if (bacflag & 64) {
    		accum.value -= inag.value;	/* subtract last value */
    	      }
	      result = inac.value - inag.value; /* do the substract */
	      goto valh;		/* continue processing */

	    } else
	    if (vdap == 2) {		/* multiply operator */
    	      /* see if processing rez or res */
    	      if (bacflag & 64) {
    	        accum.value *= inag.value;	/* multiply last value */
    	      }
	      result = inac.value * inag.value;	/* do the multiply */
	      goto valh;		/* continue processing */

	    } else
	    if (vdap == 3) {		/* divide operator */
	      result = 0;		/* zero quotient */
	      if (yeanay()) {		/* are we assembling */
/*      if (!inag.value) {	*/	/* is divisor zero */
		if (inag.value == 0) {	/* is divisor zero */
	      	  result = 0;		/* yes, zero quotient */
	  	  seterr ('\\');	/* set divide error */
		} else {		/* ok to divide */
    		  /* see if processing rez or res */
    		  if (bacflag & 64) {
    		    accum.value /= inag.value;	/* divide last value */
    		  }
		  result = inac.value/inag.value;  /* do divide */
		}
	      }
	      goto valh;		/* final updates */
	    } 

	  case 0x10:			/* absolute */
vdaa:
	    augtype = 0;		/* prog abs type */
	    secnag = 0;			/* zero section number */
	    goto vdag;			/* go process */

	  case 0x14:			/* common block */
	    if (inacbn == inagbn)	/* do common blocks match */
	      goto vdaa;		/* yes, make absolute */
	    goto vde;			/* else an error */

	  case 0x18:			/* an external */
	    if (pcmode == PCCOM) {	/* is PC mode common */
	      if (yeanay()) {		/* are we assembling */
	        seterr ('A');		/* set address error */
	      }
	      goto vale;		/* process the value */
	    }
	    if (inac.value)		/* is previous accumuland zero */
	      goto vde;			/* no, external in expression illegal */
	    inac = inag;		/* the external aug is now accumuland */
	    secnac = secnag;		/* update section number */
	    goto vale;			/* process the value */

	  case 0x20:			/* section number */
	    if (secnag == secnac)	/* do section numbers match */
	      goto vdaa;		/* yes, make absolute */
	    goto vde;			/* else an error */

	}				/* end switch */

	/* process the result */
valh:
	inac.value = result & 0x7fffff;	/* just 23 bits */
#ifdef MACD
printf("valh: result %x, cnumterm %x [%c] hbstac [%.2x]\n", result, cnumterm, cnumterm, hbstac[0]);
prtval("valh has inac", &inac);
#endif
	if (augtype == 0) {		/* program absolute */
	  inac.type = TYPP;		/* type program */
	  inac.flags = 0;		/* absolute */
	} else
	if (augtype == 1 ) {		/* program relative */
	  inac.type = TYPP;		/* type program */
	  inac.flags = ABSREL;		/* relative */
	} else
	if (augtype == 2 ) {		/* common */
	  inac.type = TYPC;		/* type common */
	  inac.flags = 0;		/* absolute */
	} else
	if (augtype == 3 ) {		/* external */
	  inac.type = TYPX;		/* type external */
	  inac.flags = 0;		/* absolute */
	}
	if (secnag & 1) {		/* csect expression */
	  inac.flags |= CSDS;		/* set csect flag */
	}
	/* check terminator and leave or continue */
vale:
	if (hbstac[0] == ' ' || hbstac[0] == ',' || hbstac[0] == '\'') {
#ifdef MACD
	  int32 ttt = (uint8)(*usname);
#endif

    	  /* see if processing rez or res */
    	  if (bacflag & 64) {
    	    bacflag &= ~64;		/* clear flag */
    	    /* check for negative size */
    	    if (accum.value < 0) {
	      if (yeanay()) {		/* are we assembling */
#ifdef MACD
      printf("Error N @ 1\n");
#endif
	        seterr ('N');		/* set number error */
	      }
    	      /* clear value */
    	      inag.value = 0;		/* zero value */
    	      inag.type = 0;		/* zero type */
    	      inag.flags = 0;		/* zero flags */
    	      accum.tmp = cnumterm;	/* save the terminator */
    	      valterm = hbstac[0];	/* save the terminator */
    	      return (accum);		/* return the value */
    	    }
    	  }
	  /* if terminator space, comma, or apost, leave */
	  /* valterm has terminator */
	  inac.tmp = cnumterm;		/* save the terminator */
	  valterm = hbstac[0];		/* save the terminator */
#ifdef MACD
      if ((ttt & 0xff) == 0xff) {
printf("val returning, symbol !%.7s pc %x val %x\n", &usname[1], (uint32)&currpc, (uint32)&inac);
      } else {
printf("val returning, symbol %c%.7s, pc=%x, val=%x\n", usname[0], &usname[1], (int32)&currpc, (int32)&inac);
      }
/*printf("val returning, symbol %c%.7s, pc=%x, val=%x\n", */
/* ((uint8)ttt == 0xff ? '!' : (uint8)ttt), &usname[1], (uint32)currpc, (uint32)inac); */
/* (usname[0] == 0xff ? '!' : usname[0]), &usname[1], (uint32)currpc, (uint32)inac); */
prtval("vale returning inac", &inac);
#endif
	  return (inac);		/* return the value */
	}
	if (hbstac[0] != ')') {		/* if not rt parend do next element */
	  unst(0x81fd0000);		/* unstring an element */
	  goto val3;			/* continue */
	}

	/* a right parenthesis found */
#ifdef MACD
printf("vale - rt par: usname[1] = %c,\n", usname[1]);
#endif
	/* add proper f & c bits */
	inac.value = ageq0((int32)inac.value, inac.type) & 0x7fffff;
#ifdef MACD
prtval("vale returning inac", &inac);
#endif
	hbavar = 5;			/* set new address variant */
	runst(0x81fd0000);		/* unstring, term on most anything */
	if (*usname == ' ') {		/* anything in name */
	  if ((hbstac[0] == ' ') ||	/* no, is terminator a space */
	    (hbstac[0] == ',')) {	/* or a comma, return the value */
	    /* valterm has terminator */
	    inag.tmp = valterm;		/* save the terminator */
	    return (inac);		/* return the value */
	  }
	}
	if (yeanay()) {			/* are we assembling */
	  seterr ('V');			/* set value error */
	}
	/* valterm has terminator */
	inag.tmp = valterm;		/* save the terminator */
	return (inac);			/* return the value */

	/* a left parend or appost was found */
valq:
#ifdef MACD
printf("valq: usname[1] = %c,\n", usname[1]);
#endif
	if (usname[1] != ' ') {		/* if not space, an error */
	  if (yeanay()) {		/* are we assembling */
	    seterr ('W');		/* set W error */
	  }
	  goto vale;			/* do it again */
	}
	switch (*usname & ~0x20) {	/* switch u/c char */
	  case 'B':
	    hbavar = 0;
	    goto addra;			/* continue */
	  case 'H':
	    hbavar = 1;
	    goto addra;			/* continue */
	  case 'W':
	    hbavar = 2;
	    goto addra;			/* continue */
	  case 'D':
	    hbavar = 3;
	    goto addra;			/* continue */
	  case 'A':
	    hbavar = 4;
	    goto addra;			/* continue */

	  case 'C':
	    i = 0;			/* tmd value */
	    break;			/* process constant in expression */
	  case 'G':
	    i = 1;			/* tmd value */
	    break;			/* process constant in expression */
	  case 'X':
	    i = 2;			/* tmd value */
	    break;			/* process constant in expression */
	  case 'N':
	    i = 3;			/* tmd value */
	    break;			/* process constant in expression */
	  case 'F':
	    i = 4;			/* tmd value */
	    break;			/* process constant in expression */
	  case 'E':
	    i = 5;			/* tmd value */
	    break;			/* process constant in expression */
	  case 'R':
	    i = 6;			/* tmd value */
	    break;			/* process constant in expression */

addra:
	    if (valterm == '(')	{	/* was terminator a ( */
	      /* an address attribute, get next element */
	      unst(0x81fd0000);	/* unstring an element */
	      goto val3;		/* continue */
	    }
	    /* drop thru for error */

	  case ' ':
	  default:
	    if (yeanay()) {		/* are we assembling */
	      seterr ('W');		/* set W error */
	    }
	    goto vale;			/* do it again */
	}
	    
	/* here to process constant in the expression */
/*valg:*/
#ifdef MACD
printf("valg: valterm [%c], hbtttf %d\n", valterm, hbtttf);
#endif
	if (valterm != '\'') {		/* was latest terminator a ' */
	  if (yeanay()) {		/* are we assembling */
	    seterr ('W');		/* set W error */
	  }
	  goto vale;			/* do next value */
	}
	k = hbstac[1];			/* save previous terminator */
	ii = tot;			/* save tot value */
	jj = hbtttf;			/* save hbtttf value */
	hbtttf = 12;			/* point to value stack */
	tot = 4;			/* number of bytes to go out */
	/* i = 0-6 FOR C,G,X,N,F,E,R RESP */
	tmd(i);				/* translate the constant */
#ifdef MACD
printf("tmd 1: returned %x, %x for type %d\n", hdtds[0], hdtds[1], i);
#endif
	tot = ii;			/* restore tot value */
	hbtttf = jj;			/* restore hbtttf value */
	inag.value = hdtds[0] & 0x7fffff;	/* data computed by tmd */
#ifdef MACD
printf("tmd 1: unstringing %.72s\n term = %x [%c], inscnt = %d, DUMMY is %s\n",
 in, unterm, unterm, inscnt, (spmac & DUMMY) ? "ON" : "OFF");
#endif
	runst(0x81fd0000);		/* unstring without skip leading blks */
#ifdef MACD
printf("tmd 1: unstrung %.72s\n term = %c, inscnt = %d, DUMMY is %s\n",
 in, unterm, inscnt, (spmac & DUMMY) ? "ON" : "OFF");
#endif
	hbstac[1] = k;			/* restore previous terminator */
	goto vala;			/* do next value */
}

/*
 * tdat - process data string
 * input - none
 * output - the value in hdtds and/or hdtdf
 */

void	tdat()
{
	int	i;
	int	tc;
	int	vc = 0;

#ifdef MACD
	printf("entering tdat()\n");
#endif
	hdtds[0] = hdtds[1] = 0;	/* clear integer stack */
	hdtdf[0] = hdtdf[1] = 0;	/* clear fraction stack */
	bits &= ~TGSIGN;		/* assume positive */
	unst (0x81fd0000);		/* unstring descr of constant */
	if ((unterm != '\'') &&		/* was last terminator a ' */
	  (unterm != '('))		/* or is it a ( */
	  goto tdat3;			/* no,  may be implicit numeric */
	/* terminator is ' or (. Evaluate constant type in variable name */
	if (usname[1] != ' ')		/* if 2nd char not blank, error */
	  goto tdater;			/* data error */
	if (islower(tc=usname[0])) 	/* is letter lower case */
	  tc = toupper(usname[0]);	/* upper case */
	switch (tc) {			/* switch on data type */
	  case 'C':
	    i = 0;			/* tmd value */
	    goto tdatcom;		/* process constant in expression */
	  case 'G':
	    i = 1;			/* tmd value */
	    goto tdatcom;		/* process constant in expression */
	  case 'X':
	    i = 2;			/* tmd value */
	    goto tdatcom;		/* process constant in expression */
	  case 'N':
	    i = 3;			/* tmd value */
	    goto tdatcom;		/* process constant in expression */
	  case 'F':
	    i = 4;			/* tmd value */
	    goto tdatcom;		/* process constant in expression */
	  case 'E':
	    i = 5;			/* tmd value */
	    goto tdatcom;		/* process constant in expression */
	  case 'R':
	    i = 6;			/* tmd value */
	    goto tdatcom;		/* process constant in expression */
tdatcom:
#ifdef MACD
printf("tdat: i = %x, term = %c,\n", i, unterm);
#endif
	    if (unterm != '\'')		/* was terminator an ' */
	      goto tdater;		/* no, mark data error */
	    tmd(i);			/* go decode data type */
#ifdef MACD
printf("tdat 2: returned %x, %x for type %d\n", hdtds[0], hdtds[1], i);
printf("tdat 2: hbtttf = %x, usname = %s\n", hbtttf, usname);
#endif
	    if (hbtttf >= 4)		/* processing a gen or data */
	      goto tdat4;		/* no */
	    if (bits2 & ALVAL)		/* do we have an arith expression */
	      goto tdat2b;		/* yes, go process */
	    if ((hbstac[0] != ',') &&	/* if terminator not a comma */
	      (hbstac[0] != ' '))	/* and not a space, N error */
	      goto tdater;		/* mark error */
	    if (*usname != ' ')		/* was there data between ' and , */
	      goto tdater;		/* yes, we have an error */
	    return;			/* no, return */

	  /* translate an address constant string */
	  case 'B':
	    hbavar = 0;
	    goto tdat2a;		/* process an address type string */
	  case 'H':
	    hbavar = 1;
	    goto tdat2a;		/* process an address type string */
	  case 'W':
	    hbavar = 2;
	    goto tdat2a;		/* process an address type string */
	  case 'D':
	    hbavar = 3;
	    goto tdat2a;		/* process an address type string */
	  case 'A':
	    hbavar = 4;
	    goto tdat2a;		/* process an address type string */

	default:
tdater:					/* error if anything else */
	  if (yeanay()) {		/* are we assembling */
	    seterr ('D');		/* set data error */
	  }
#ifdef MACD
printf("tdater 1: unterm = %c, usname = %.8s\n", unterm, usname);
#endif
	  runst(0x80080000);		/* unstring til sp or , */
#ifdef MACD
printf("tdater 2: unterm = %c, usname = %.8s\n", unterm, usname);
#endif
	  if (*usname != ' ')		/* was there data between ' and , */
	    goto tdater;		/* yes, we have an error */
	  return;			/* no, return */
	}

	/* translate an address constant string */
tdat2a:
	if (hbstac[0] != '(')		/* was terminator a '(' */
	  goto tdater;			/* no, error */
	vc = 0;				/* tell unst to not skip blanks */
tdat2b:
#ifdef MACD
printf("tdat2b: unterm = %c, usname = %.8s\n", unterm, usname);
printf("tdat2b: term is [%c]\n", hbstac[0]);
#endif
	bits &= ~TGSIGN;		/* clear negation flag */
	val(vc);			/* call val with correct flag */
	if ((inac.type == TYPC) ||	/* is this a common ref */
	  (inac.type == TYPD)) 		/* or a common def */
	  hbbn = inacbn;		/* get the block # and save */
	else
	  hbbn = secnac;		/* get section # and save */
	hdtds[0] = inac.value;		/* save low order part */
	hdtds[1] = 0;			/* set high order part to zero */
#ifdef MACD
printf("tdat2b: value %x, %x term is [%c]\n", hdtds[0], hdtds[1], hbstac[0]);
printf("tdat2b: hbtttf = %x, usname = %.8s\n", hbtttf, usname);
#endif
	tcy();				/* allow bytes into data stream */
	goto tdat4;			/* go check terminator */

	/* may be implied dec num or unattribuated expression */
tdat3:
#ifdef MACD
printf("tdat3: unterm = %c, usname = %.8s\n", unterm, usname);
#endif
	if (*usname != ' ')		/* anything unstrung */
	  goto tdat3c;			/* yes, then we have something */
	if (spmac & DUMMY) {		/* was a dummy unstrung */
	  spmac &= ~DUMMY;		/* clear the flag */
	  vc = 1;			/* tell val already unstrung */
	  if (hbstac[0] == '+' ||	/* is this an arithmetic operator */
	    hbstac[0] == '-' ||
	    hbstac[0] == '*' ||
	    hbstac[0] == '/')
	    goto tdat2b;		/* yes, go get the value */
	  goto tdat4;			/* go test terminator */
	}				/* not dummy */
	if ((hbstac[0] != ' ') &&	/* see if term space or , */
	  (hbstac[0] != ',')) {	
	  if (hbstac[0] != '+') {	/* is terminator a + */
	    if (hbstac[0] != '-')	/* no, is it - then */
	      goto tdater;		/* no, give out error */
	    bits |= TGSIGN;		/* show it is a - */
	  } 				/* a + or - found */
	  unst(0x81fd0000);		/* unstring something */
	}				/* terminator sp or , */
tdat3c:					/* we have something unstrung */
#ifdef MACD
printf("tdat3c: unterm = %c, usname = %.8s\n", unterm, usname);
printf("tdat3c: term is [%c]\n", hbstac[0]);
#endif
	vc = 1;				/* tell we have something unstrung */
	if (*usname < '0' || *usname > '9')	/* in numeric range */
	  goto tdat2b;			/* no, go evaluate it */
	/* we have a numeric value */
	if (hbstac[0] == '+' ||		/* is there an arithmetic operator */
	  hbstac[0] == '-' ||
	  hbstac[0] == '*' ||
	  hbstac[0] == '/')
	  goto tdat2b;			/* yes, go get the value */
	/* no, go convert the number, base 10 */
	cnum(10);			/* get the number */
	hdtds[0] = cnumval[0];		/* save low order part */
	hdtds[1] = cnumval[1];		/* save high order part */
	if (bits & TGSIGN) {		/* is sign negative */
	  /* call negate to get negative value */
	  negate (hdtds);		/* negate the value */
	}
	tcy();				/* allow bytes into data stream */
	/* check terminators */
tdat4:					/* check terminator */
	if ((hbstac[0] == ',') ||	/* was term , */
	  (hbstac[0] == ' ')) {		/* or space */
#ifdef MACD
printf("tdat4: returning %x, %x term is [%c]\n", hdtds[0], hdtds[1], hbstac[0]);
printf("tdat4: hbtttf = %x, usname = %.8s\n", hbtttf, usname);
#endif
	  return;			/* yes, return */
	}
	runst(0x80080000);		/* no, unstring til sp or , */
#ifdef MACD
printf("tdat4: unterm = %c, usname = %.8s\n", unterm, usname);
#endif
	if (*usname != ' ')		/* was there data between ' and , */
	  goto tdater;			/* yes, we have an error */
	return;				/* no, return */
}

short	hhtdb;				/* entered binary exponent */
short	hhtdbn;				/* entered binary exponent */
int	dblorsgl = 0;			/* double or single flag */

/*
 * tmd - translate constant type
 * input - typ = 0-6 for c,g,x,n,f,e or r
 */

void	tmd(typ)
int	typ;
{
	int	chr;
	int	tmp;
	int	cnt = 0;

	if (typ == 5)			/* is it e type */
    	  dblorsgl = 1;			/* show single precision */
	hdtds[0] = hdtds[1] = 0;	/* clear integer stack */
	hdtdf[0] = hdtdf[1] = 0;	/* clear fraction stack */

#ifdef MACD
printf("tmd called typ = %x, tot = %d\n", typ, tot);
#endif
	if (typ == 0) {			/* process C type constant */
/* process C type constant */
	  ccset = 0;
	  while (!ccset) {		/* terminate on ' or error */
	    chr = gbyt(0x01000000);	/* get a char, term on ' */
	    if (ccset)			/* apostrophe or error */
	      break;			/* terminate on ' or error */
	    tdg((int32)chr, 1, 0);	/* put out left just char */
	  }
	  if (!yeanay())		/* are we assembling */
	    goto tgd30;			/* no, skip boundry check */
	  while (1) {			/* do until boundry reached */
#ifdef MACD
printf("tmd C - bounding pc tot = %d, pcmode = %d\n", tot, pcmode);
prtval("tmd C - currpc", &currpc);
prtval("tmd C - sectpc[pcmode]", &sectpc[pcmode]);
#endif
	    if (!tbou(tot))		/* are we on correct boundry yet */
	      break;			/* yes, exit loop */
	    if (hbtttf)			/* is this data statement */
	      break;			/* get out if not */
	    tdg((int32)' ', 1, 0);	/* no, feed a blank */
	  }
tgd30:
	  tmp = inscnt;			/* save byte reading ptr */
#ifdef MACD
printf("at tgd30 - tmp = %d\n", tmp);
#endif
	  if (hbtttf <= 4)		/* processing gen or data */
	    runst(0x80080000);		/* yes, term on space or comma */
	  goto tgd3;			/* get out without storing value */
	} 

	if (typ == 1) {			/* process G type constant */
/* process G type constant */
	  ccset = 0;
	  while (!ccset) {		/* terminate on ' or error */
	    chr = gbyt(0x01000000);	/* get a char, term on ' */
	    if (ccset)			/* apostrophe or error */
	      break;			/* terminate on ' or error */
	    lefts(hdtds, 8);		/* make room for new char */
	    hdtds[0] |= chr;		/* put in the char */
	  }
tgd2:					/* cycle out the data */
	  tmp = inscnt;			/* save byte reading ptr */
#ifdef MACD
printf("at tgd2 - tmp = %d hbtttf = %d\n", tmp, hbtttf);
#endif
	  if (hbtttf <= 4) {		/* processing gen or data */
	    runst(0x81fd0000);		/* yes, term on almost anything */
	    if (unterm == '+' || unterm == '-' ||
	      unterm == '*' || unterm == '/') {	/* see if arith term */
	      inag.value = hdtds[0] & 0x7fffff;  /* yes, just leave address */
	      hbstac[1] = ' ';		/* show space as prev terminator */
	      bits2 |= ALVAL;		/* tell val to skip evaluation */
#ifdef MACD
printf("tgd2 returning inag, term = %c, inscnt = %d\n", unterm, inscnt);
#endif
	      goto tgd3;		/* get out without storing value */
	    }
	  }
	  tcy();			/* allow bytes into data stream */
tgd3:
	  if (tmp < 73)			/* within good part of line */
	    return;			/* yes, exit */
#ifdef MACD
printf("at tgd3 - tmp = %d\n", tmp);
#endif
	  if (yeanay())			/* are we assembling */
	    seterr ('C');		/* set no termination error */
	  return;			/* exit */
	} 

	if (typ == 2) {			/* process X type constant */
/* process X type constant */
	  cnt = unst(0x01000000);	/* unstring hex number */
#ifdef MACD
printf("tgd hex conv entered, usname = %.8s term = %c\n", usname, unterm);
#endif
	  /* is this a dummy parameter or are we in cond scan */
	  if ((spmac & DUMMY) || (macstate & CONDSCAN)) {
	    spmac &= ~DUMMY;		/* yes, reset flag */
	    hdtds[0] = hdtds[1] = 0;	/* zero output area */
	    goto tgd2;			/* go cycle out the data */
	  }
#ifdef MACD
printf("tgd term = %c\n", unterm);
#endif
	  if (unterm != '\'')		/* was term an ' */
	    goto txd17;			/* no, error, let cnum give error */
	  if (cnt > 17)			/* more than 17 chars, error */
	    goto txd16;			/* yes, error */
	  if (cnt == 17)		/* exactly 17 */
	    if (*usname != '+')		/* 1st char a + */
	      if (*usname != '-')	/* or a - sign */
	        goto txd16;		/* no, than it is an error */
	  /* we have what we think is a number, check for h or w in string */
	  for (cnt = 0; cnt < unstnp; cnt ++) {	/* loop for all the chars */
	    if (usname[cnt] == ' ' ||
	      usname[cnt] == 'H' || usname[cnt] == 'h' ||
	      usname[cnt] == 'W' || usname[cnt] == 'w') {
txd16:
	      if (yeanay()) {			/* are we assembling */
#ifdef MACD
      printf("Error N @ 2\n");
#endif
	        seterr ('N');			/* set number error */
	      }
	      goto tgd2;			/* cycle out data */
	    }
	  }
txd17:
	  cnum(16);			/* get the number */
	  hdtds[0] = cnumval[0];	/* save low order part */
	  hdtds[1] = cnumval[1];	/* save high order part */
	  goto tgd2;			/* go dump the number */
	}
/* typ is > 2 */
/* printf("tgd n, f, e or r conversion entered, usname = %.8s\n", usname); */
/* process n or f or e or r type constants */
	if (typ == 3)			/* n type */
	  cnt = 31;			/* bit scaling is 31 */
	else if (typ == 4)		/* f type */
	  cnt = 63;			/* bit scaling is 63 */
	else if (typ == 5)		/* e type */
	  cnt = 8;			/* bit scaling is 8 */
	else if (typ == 6)		/* r type */
	  cnt = 31;			/* bit scaling is 40 */
	hhtdb = hhtdbn = cnt;		/* set default for B and scaling */
	tfn(typ);			/* translate field string to bytes */
	goto tgd2;			/* go output the data */
}

int32	tdmp[] = {			/* 0x16 in digit dec inverted form */
	0x00000000,			/* 0 x 16 */
	0x06010000,			/* 1 x 16 */
	0x02030000,			/* 2 x 16 */
	0x08040000,			/* 3 x 16 */
	0x04060000,			/* 4 x 16 */
	0x00080000,			/* 5 x 16 */
	0x06090000,			/* 6 x 16 */
	0x02010100,			/* 7 x 16 */
	0x08020100,			/* 8 x 16 */
	0x04040100,			/* 9 x 16 */
};

int32	base[] = {
	0x00000000,	0x41a00000,	/* 10.**1 */
	0x00000000,	0x42640000,	/* 10.**2 */
	0x00000000,	0x44271000,	/* 10.**4 */
	0x00000000,	0x475f5e10,	/* 10.**8 */
	0x6fc10000,	0x4e2386f2,	/* 10.**16 */
	0xd415b85a,	0x5b4ee2d6,	/* 10.**32 */
	0xe93ff9f4,	0x76184f03,	/* 10.**64 */
};

int32	one[] = {
	0x00000000,	0x41100000	/* 1 */
};

short	hhtde;				/* entered decimal exponent */
int32	hbtdfn;				/* floating pt digit count */
#ifdef MYATOF
#include "float.h"
extern FPN ifpn;
extern FPN* myatof();
extern void flconv();
#endif

/* tfn - translate field in usname to bytes
 * input in usname
 * output in hdtdf or hdtds
 */

void	tfn(typ)
int	typ;				/* exponent type */
{
	int	cnt;
	int32	tmp;
	int32	chr, dig;
	int32   hbtfn1 = 0;		/* previous terminator - assume int */
	int32   hbtfn2 = 0;		/* latest terminator - assume int */
	int32	hbtfn3 = 0;		/* store counter */
	int32	tmpf[2];		/* temp floating number */
	int	prop = 0;		/* ???? */
	int32	*nump;
	int32	bn, mask;

	hhtde = 0;			/* zero the user entered exponent */
	bits &= ~XPONENT;		/* clear user entered exp flag */
#ifdef MYATOF
#ifdef FPBUG
 printf("tfn: typ = %d\n", typ);
#endif
    	if(typ >= 5) {			/* see if e or r type */
	  /* convert number to floating point */
	  int cc, gdot, gote, ieee;
	  cc = gdot = gote = 0;
	  ieee = 0;			/* assume encore floating point */
	  memset (usname, '\0', MAXCHARS);	/* blank receiving area */
	  if (bits & TFSIGN)		/* do we have a neg dec constant */
	    usname[cc++] = '-';		/* set minus sign */
stn:
	  chr = gbyte(0x01000000);	/* get a byte, term on ' */
	  if (ccset) {			/* was terminator found */
	    hbtfn2 = 5;			/* set latest terminator */
	    goto stndone;		/* yes, make way out */
	  }
	  if (chr == ' ')		/* is char a space */
	    goto stn;			/* ignore spaces */
	  /* see if char is a valid terminator of . E B , or ' */
	  if (islower(tmp=chr)) 	/* is letter lower case */
	    tmp = toupper(chr);		/* make u/c */
#ifdef FPBUG
 printf("stn: switching on %c\n", tmp);
#endif
	  switch ((int32)tmp) {		/* switch on the u/c chr */
	    case '.':			/* dec point */
	      if (gdot++)
		goto nerrx;		/* we have number error */
	      goto addnx;		/* ok, process number */
	    case 'E':			/* exponent */
	    case 'e':			/* exponent */
	      if (gote++)
		goto nerrx;		/* we have number error */
	      goto addnx;		/* ok, process number */
	    case '+':			/* plus */
	    case '-':			/* minus */
	    case '0':			/* dec 0 */
	    case '1':			/* dec 1 */
	    case '2':			/* dec 2 */
	    case '3':			/* dec 3 */
	    case '4':			/* dec 4 */
	    case '5':			/* dec 5 */
	    case '6':			/* dec 6 */
	    case '7':			/* dec 7 */
	    case '8':			/* dec 8 */
	    case '9':			/* dec 9 */
addnx:
	      usname[cc++] = chr;	/* store the value */
	      if(cc < MAXCHARS)
		goto stn;		/* get next char */

	  default:
nerrx:
	    if (yeanay()) {		/* yes, are we assembling */
#ifdef MACD
      printf("Error N @ 3\n");
#endif
	      seterr ('N');		/* set number error */
	    }
	  }
stndone:
	  usname[cc++] = '\0';		/* terminate input */
#ifdef FPBUG
printf("input %s\n", usname);
#endif
	  myatof(usname);		/* convert to internal float */
#ifdef FPBUG
printf("after myatof input %s\n", usname);
#endif
    	  if (option & OPT55)		/* option 55 set? */
	    ieee=1;			/* return ieee format */
#ifdef FPBUG
printf("calling flconv typ %x\n", typ);
#endif
	  flconv(typ, ifpn.ne, ifpn.nf, hdtds, ieee);
#ifdef FPBUG
printf("tfn: got val %x,%x\n", hdtds[0], hdtds[1]);
#endif
    	  return;			/* return number */
	}
#endif /* MYATOF */
    	if (option & OPT55) {		/* option 55 set? */
    	  if(typ > 5) {			/* see if e or r type */
#ifdef NOT4NOW
    	    Eatof();			/* conver to IEEE-754 format */
#else
    	    hdtds[0] = 0;		/* zero low order part */
	    hdtds[1] = 0;		/* zero high order part */
#endif
    	    return;			/* return IEEE number */
    	  }
    	}
tfm1:
	hbtfn1 = hbtfn2;		/* save terminator */
	hbtfn3 = 0;			/* clear store counter */
	memset (usname, ' ', MAXCHARS);	/* blank receiving area */
tfm2:
	chr = gbyte(0x01000000);	/* get a byte, term on ' */
	if (ccset) {			/* was terminator found */
	  hbtfn2 = 5;			/* set latest terminator */
	  goto tfm6;			/* yes, make way out */
	}
	if (chr == ' ')			/* is char a space */
	  goto tfm2;			/* ignore spaces */
	/* see if char is a valid terminator of . E B , or ' */
	if (islower(tmp=chr))	 	/* is letter lower case */
	  tmp = toupper(chr);		/* make u/c */
#ifdef FPBUG
 printf("tfm2: switching on %c\n", tmp);
#endif
	switch ((int)tmp) {		/* switch on the u/c chr */
	  case '.':			/* dec point */
	    hbtfn2 = 1;			/* set latest terminator */
	    goto tfm6;			/* go process */
	  case 'E':			/* exponent */
	  case 'e':			/* exponent */
	    hbtfn2 = 2;			/* set latest terminator */
	    goto tfm6;			/* go process */
	  case 'B':			/* binary exponent */
	  case 'b':			/* binary exponent */
	    hbtfn2 = 3;			/* set latest terminator */
	    goto tfm6;			/* go process */
	  case ',':			/* comma, done */
	    hbtfn2 = 4;			/* set latest terminator */
	    goto tfm6;			/* go process */
	  case '\'':			/* apost, done */
	    hbtfn2 = 5;			/* set latest terminator */
	    goto tfm6;			/* go process */

	default:
#ifdef MYATOF
	  if ((int32)hbtfn3 >= 20) {		/* see if too many digits */
#else
	  if ((int32)hbtfn3 >= 16) {		/* see if too many digits */
#endif
#ifdef FPBUG
 printf("tfm2 default: too many digits in usname |%.8s|, hbtfn3=%d\n", usname, hbtfn3);
#endif
	    if (yeanay()) {		/* yes, are we assembling */
#ifdef MACD
      printf("Error N @ 4\n");
#endif
	      seterr ('N');		/* set number error */
	    }
	  } else {
	    usname[hbtfn3++] = chr;	/* store the digit */
#ifdef FPBUG
 printf("tfm2-d: storing in usname |%s|, hbtfn3=%d\n", usname, hbtfn3);
#endif
	  }
	  goto tfm2;			/* get next digit */
	}
tfm6:
#ifdef FPBUG
 printf("tfm6: switch on %x\n", hbtfn1); 
#endif
	switch (hbtfn1) {		/* do processing on previous term */
	  case 0:			/* space or null, integer */
	    goto tfi; 
	  case 1:			/* period, float */
	    goto tff; 
	  case 2:			/* 'E', exponent */
	    goto tfx; 
	  case 3:			/* 'B', binary exponent */
	    goto tfb; 
	  case 4:			/* comma, all done */
	  case 5:			/* apost, all done */
	    goto tfo; 
	}

tfi:					/* do integer */
#ifdef FPBUG
 printf("tfi: process usname %s\n", usname); 
#endif
	cnum(10);			/* get the number */
	hdtds[0] = cnumval[0];		/* save low order part */
	hdtds[1] = cnumval[1];		/* save high order part */
	bits &= ~TFSIGN;		/* 0 = +, 1 = - */
	if (hbcnul) 			/* was sign negative */
	  bits |= TFSIGN;		/* set neg flag, 0 = +, 1 = - */
#ifdef FPBUG
 printf("tfi: got val hdtds %x,%x\n", hdtds[0], hdtds[1]); 
#endif
	goto tfm8;			/* continue */

tfx:					/* decimal radix */
	cnum(10);			/* get the number */
	prop = 0;			/* no propagated digits */
	hhtde = cnumval[0];		/* save low order part */
	if (hhtde)			/* if not zero */
	  bits |= XPONENT;		/* show user entered exponent */
#ifdef FPBUG
 printf("tfx: got exp val hhtde = %x\n", hhtde); 
#endif
	goto tfm8;			/* continue */

tfb:					/* binary radix */
	cnum(10);			/* get the number */
	hhtdb = cnumval[0];		/* save low order part */
#ifdef FPBUG
 printf("tfb: got bin exp val hhtdb = %x\n", hhtdb);
#endif
	goto tfm8;			/* continue */

tff:					/* floating pointer number */
	tmpf[0] = tmpf[1] = 0;		/* clear fraction stack */
	for (cnt=0; cnt<16; cnt++) {	/* 16 fractional hex digits wanted */
	  tmp = 0;			/* no carry at start */
	  dig = 15;			/* 16 digits are here */
#ifdef FPBUG
 printf("ttf4: got dig %x tmp %x cnt %x chr %.2x\n", dig, tmp, cnt, usname[dig]);
#endif
tff4:
	  chr = usname[dig];		/* get a digit */
	  if (cnt == 0) 		/* 1st time through */
	    if (chr != ' ')		/* is char a blank */
	      if (chr < '0' || chr > '9')  /* no, is it dec number */
	        goto tfe;		/* no, got an error here */
	  /* we have blank or num 1st time, or ? after first */
	  chr &= 0xf;			/* convert from ascii to hex */
	  tmp += tdmp[chr];		/* get digit times 16 */
	  chr = (uint32)tmp >> 24;	/* get l.s.d. of product */
	  tmp <<= 8;			/* shift up the carry */
	  while (chr >= 10) {		/* check for dec carry */
        chr -= 10;	   	    /* +10 to 0 */
/*	    chr = ((int32)chr - 10);	*/	/* +10 to 0 */
	    tmp += 0x01000000;		/* add in the carry */
	  }
	  usname[dig] = chr;		/* sto back 1 multiplied digit */
#ifdef FPBUG
/* printf("ttf3: got dig %x tmp %x cnt %x chr %.2x\n", dig, tmp, cnt, chr); */
#endif
/*      --dig;     */           /* ms to ls bit */
/*    dig = ((int32)dig - 1); */             /* ms to ls bit */
/*    if ((int32)dig >= 0) */ /* go from ls to ms, done yet */
      if ((int32)(--dig) >= 0)	/* go from ls to ms, done yet */
	    goto tff4;			/* not all digits done */
	  chr = (uint32)tmp >> 24;	/* get l.s.d. of product */
	  tmp <<= 8;			/* shift up the carry */
	  if (tmp & 0x01000000)	/* check for over 10 */
	    chr +=10;			/* yes, make into 1 hex digit */
	  lefts(tmpf, 4);		/* makeroom in fraction stack */
	  tmpf[0] |= chr;		/* put in new digit */
#ifdef FPBUG
 printf("ttf2: got dig %x tmp %x cnt %x chr %.2x\n", dig, tmp, cnt, chr);
#endif
	}
	prop = chr;			/* save last propagation */
	hdtdf[0] = tmpf[0];		/* save lower part */
	hdtdf[1] = tmpf[1];		/* save upper part */
#ifdef FPBUG
 printf("tff: got val %x,%x\n", hdtdf[0], hdtdf[1]); 
#endif
	/* drop throught to tfm8 */

tfm8:
#ifdef FPBUG
 printf("tfm8: hbtfn2 = %x, hntfn1 = %x\n", hbtfn2, hbtfn1);
#endif
	if ((int32)hbtfn2 <= (int32)hbtfn1) {		/* is new ptr gtr than old ptr */
tfe:					/* no, we have element sequence error */
	  if (yeanay())	{		/* are we assembling */
#ifdef MACD
      printf("Error N @ 5\n");
#endif
	    seterr ('N');		/* set number error */
      }
	  return;			/* exit after error */
	}
	if ((int32)hbtfn2 < 4)		/* was last terminator final */
	  goto tfm1;			/* no, get next item */

	/* got a final terminator, finish up */
tfo:
#ifdef FPBUG
 printf("tfo: hdtdf %x,%x hdtds %x,%x hhtde %x\n",
 hdtdf[0], hdtdf[1], hdtds[0], hdtds[1], hhtde);
#endif
	if (bits & TFSIGN) {		/* do we have a neg dec constant */
	  if (hdtdf[0] != 0 || hdtdf[1] != 0) {	/* yes, is fraction zero */
	    /* call negate to get negative value */
	    negate (hdtdf);		/* no, negate the fraction value */
	    tmpf[0] = tmpf[1] = -1;	/* get -1 to adjust integer part */
	    add64 (tmpf, hdtds);	/* adj integer part by -1 */
	  }
	}
#ifdef FPBUG
 printf("tfo4: hhtde = %x hhtdbn %x\n", hhtde, hhtdbn);
#endif
 /* tfo4 */
	if (hhtde == 0) {			/* do we have an exponent */
	  /* make 31 into 63 and 63 into 63. if 63, fixed point const */
	  if ((hhtdbn | 0x20) == 63) {	/* no, norminal binary scaling */
 /* tfo8 */
	    tsh(hhtdbn - hhtdb);	/* shift stack - rt, + left */
	    goto tfo9;			/* exit this thing */
	  }
	}
#ifdef FPBUG
 printf("tfoat1: hhtde = %x hhtdbn %x\n", hhtde, hhtdbn);
#endif
/* tfoat1 */
	/* we have an exponent */
/*??	dig = 20;	*/		/* i don't know why */
	dig = hbtfn1;           /* term of 4W or 5W */
	mask = 0xf0;			/* nibble mask */
	chr = (uint32)hdtds[1] >> 24;   /* get most sig byte */
	tmp = chr & mask;		/* get the nibble */
	if (tmp != 0) {			/* pos and not normalized */
	  if (tmp != 0xf0)		/* no, is it normalized */
	    goto tfoat8;		/* yes, continue */
	  tmp = 0xff;			/* neg and not normalized */
	}
/* tfoat6 */
	/* + or - unnormalized, tmp has 00 or ff for pos and neg */
	dig = -16;
	bn = 0;				/* start at first digit */
	nump = hdtds;			/* start with integer part */
#ifdef FPBUG
 printf("tfoat6:a hdtdf %x,%x hdtds %x,%x hhtde %x\n",
 hdtdf[0], hdtdf[1], hdtds[0], hdtds[1], hhtde);
#endif
tfoat7:
	if (bn == 8) {
	  nump = hdtdf;			/* point to fraction */
	  bn -= 8;			/* byte offset in double word */
	}
/*	i =  1 - bn/4;		*/	/* int offset */
/*	j = bn%4;	*/		/* byte offset */
	
	chr = ((int32)((uint32)nump[1 - bn/4] & (int32)(0xff000000 >>
	  ((bn%4)*8))) >> ((3 - (bn%4))*8));
	mask = 0xf0;			/* digit 1 mask */
	if (((tmp ^ chr) & mask) != 0)	/* check digit 1 of byte */
	  goto tfoat8;			/* now normalized */
	mask = 0x0f;			/* digit 2 mask */
	if (((tmp ^ chr) & mask) != 0)	/* check digit 2 of byte */
	  goto tfoat8;			/* now normalized */
	bn++;				/* next byte */
	if (++dig != 0)			/* done yet */
	  goto tfoat7;			/* no, do next digit */
	/* all zeros */
	hdtds[0] = 0;			/* set number to zero */
	hdtds[1] = 0;			/* set number to zero */
	goto tfo9;			/* all done now */
	
tfoat8:
#ifdef FPBUG
 printf("tfoat8: dig %x mask %x hdtds %x,%x hhtde %x\n",
 dig, mask, hdtds[0], hdtds[1], hhtde);
#endif
	dig = (dig + 15) << 1;		/* make positive and a digit count */
	if (mask == 0x0f)		/* were we in digit 2 */
	  dig++;			/* yes, add a count */
	if (tmp == 0)			/* was number positive */
	  goto tfoat9;			/* yes, go on */
	if ((chr & mask) != 0)		/* neg num */
	  goto tfoat9;			/* neg and digit was not zero */
	/* neg and digit was zero */
	if (prop == 0)			/* were there any propagated digits */
	  goto tfoat83;			/* if zero, then a fraction entered */
/* prop from tff has what was in r2 last */
	if (hdtdf[1])			/* 1st 1/2 of fraction */
	  goto tfoat83;			/* go if we have fraction */
	if (hdtdf[0])			/* 2nd 1/2 of fraction */
	  goto tfoat83;			/* go if we have fraction */
	dig--;				/* adj bit shift value */
tfoat83:
#ifdef FPBUG
 printf("tfoat83: prop %x hhtde %x hdtds %x,%x dig %x\n",
 prop, hhtde, hdtds[0], hdtds[1], dig); 
#endif
	if (prop)			/* any propagated digits */
	  goto tfoat9;			/* if so, done */
	if (mask == 0x0f)		/* check normalization mask */
	  goto tfoat9a;			/* go if equal */
	dig--;				/* adj bit shift value */
	goto tfoat9;			/* and continue */
tfoat9a:
#ifdef FPBUG
 printf("tfoat9a: tmp %x hhtde %x hdtds %x,%x dig %x\n",
 tmp, hhtde, hdtds[0], hdtds[1], dig); 
#endif
	if (!(dig & 1))			/* odd numeric value */
	  goto tfoat9;			/* even is o.k. */
	if (hbtdfn == 0x15)		/* check exp shift value */
	  goto tfoat9b;			/* cont if max */
	dig--;				/* adj bit shift count */
	goto tfoat9;			/* and continue */
tfoat9b:
#ifdef FPBUG
 printf("tfoat9b: tmp %x hhtde %x hdtds %x,%x dig %x\n",
 tmp, hhtde, hdtds[0], hdtds[1], dig); 
#endif
	if (hdtds[0] & 0xfff)		/* check fraction portion */
	  goto tfoat9;			/* go on if not zero */
	dig--;				/* adjust bit shift value */
tfoat9:
#ifdef FPBUG
 printf("tfoat9: tmp %x hhtde %x hdtds %x,%x dig %x\n",
 tmp, hhtde, hdtds[0], hdtds[1], dig); 
#endif
	if (hhtde)			/* did user enter exponent */
	  goto tfoat9d;			/* yes, go */
	if (!(bits & XPONENT))		/* is there an exponent */
	  goto tfoat9c;			/* zero means no - just go */
tfoat9d:
	if (tmp != 0) {			/* is number neg */
	  bits &= ~XPONENT;		/* yes, clear exponent flag */
	  dig--;			/* and adjust bit count */
	}
tfoat9c:
#ifdef FPBUG
 printf("tfoat9c: hdtdf %x,%x hdtds %x,%x dig %x\n",
 hdtdf[0], hdtdf[1], hdtds[0], hdtds[1], dig); 
#endif
	hbtdfn = dig;			/* save bit count */
	tsh(dig << 2);			/* shifts are 4x of digits */
	tmp = -hbtdfn + 14 + 0x40;	/* neg digs + stack bias + fp bias */
	tmp &= 0x7f;			/* limit to 7 bits */
	if (bits & TFSIGN)		/* 0 = +, 1 = - */
	  tmp = ~tmp;			/* neg comp diased exponent */
	/* set finished val */
	hdtds[1] = (hdtds[1] & 0x00ffffff) | (tmp << 24);
	if (hhtde == 0)			/* any exponent */
	  goto tfo7;			/* no, skip tests */
	if (hhtde < -77 || hhtde > 77)	/* is exponent in range */
	  goto tfe;			/* error if not */

#ifdef FPBUG
 printf("tfo9ca: hdtdf %x,%x hdtds %x,%x hhtde %x\n",
 hdtdf[0], hdtdf[1], hdtds[0], hdtds[1], hhtde); 
#endif
	/* compute 10.D0 ** I, I is integral (pos or neg) */
	tmpf[0] = one[0];		/* set 1 as initial pp */
	tmpf[1] = one[1];		/* upper bits too */
	if (hhtde < 0)			/* is exponent neg */
	  tmp = -hhtde;			/* yes, make neg */
	else if (hhtde > 0)		/* is exponent pos */
	  tmp = hhtde;			/* yes, get exp */
	else goto tftx;			/* if 0, exit with one as pp */
	bn = 0;				/* zero bit counter */
	while(tmp) {			/* while we have an exp */
#ifdef FPBUG
 printf("tfo9cx: tmp loop = %x tmpf %x,%x\n", tmp, tmpf[0], tmpf[1]); 
#endif
	  if (tmp & 1)			/* low order bit on */
	    mulfp64(&base[bn*2], tmpf);	/* pp = pp*10.D0**(2**32-n)) */
					/* where n is bit position of one bit */
	  tmp = (unsigned int32)tmp >> 1;	/* shift to next bit */
	  bn++;				/* next bit number */
	}
#ifdef FPBUG
 printf("tfo9cb: hdtdf %x,%x hdtds %x,%x hhtde %x\n",
 hdtdf[0], hdtdf[1], hdtds[0], hdtds[1], hhtde); 
#endif
	if (hhtde > 0) {		/* is exponent neg */
	  /* exponent is positive, see if adj required */
	  if (hdtds[0] == (int32)0xffffffff)	/* get low 1/2 of val, can adj */
	    hdtds[0]++;			/* make adj for accuracy */
	  tmpf[0] = 0;			/* make l/o 1/2 of value zero */
	} else {
	  /* exponent is negative, answer is 1.D0/pp */
	  int32	temp[2];		/* a temp */

	  temp[0] = tmpf[0];		/* save l/o part */
	  temp[1] = tmpf[1];		/* save h/o part */
	  tmpf[0] = one[0];		/* get l/o of a one */
	  tmpf[1] = one[1];		/* get h/o of a one */
	  divfp64(temp, tmpf);		/* div, answer in tmpf */
	  if (hdtds[1] >= 0) {		/* is orig number neg */
	    if (hhtde & 1)		/* is exp odd */
	      tmpf[0] += 17;		/* inject fudge factor (odd) */
	    else
	      tmpf[0] += 6;		/* even, fudge factor (even) */
	  }
	}
	/* tmpf has the value, mult 10**E by non neg part of constant */
tftx:
#ifdef FPBUG
 printf("tft: tmpf %x,%x hdtds %x,%x hhtde %x hhtdbn %x %x\n",
 tmpf[0], tmpf[1], hdtds[0], hdtds[1], hhtde, hhtdbn, hhtdbn|0x20); 
#endif
	mulfp64(tmpf, hdtds);		/* do the multiply, answer in hdtds */
tfo7:
#ifdef FPBUG
 printf("tfo7: hdtdf %x,%x hdtds %x,%x hhtde %x hhtdbn %x %x\n",
 hdtdf[0], hdtdf[1], hdtds[0], hdtds[1], hhtde, hhtdbn, hhtdbn|0x20); 
#endif

	if ((hhtdbn | 0x20) != 63)	/* not fixed point, no unfloat */
	  goto tfo9;			/* exit this thing */
	/* unfloat the number */
#ifdef FPBUG
 printf("tfo7a: hdtdf %x,%x hdtds %x,%x hhtde %x hhtdbn %x\n",
 hdtdf[0], hdtdf[1], hdtds[0], hdtds[1], hhtde, hhtdbn); 
#endif
	if (hdtds[1] < 0) {		/* if sign neg, set byte to all 1's */
	  tmp = (unsigned int32)hdtds[1] >> 24;  /* get sign/ exponent */
	  tmp = ~tmp;			/* complement value */
	  hdtds[1] |= 0xff000000;	/* set all the bits */
	} else {
	  hdtds[1] &= 0x00ffffff;	/* pos, clear all the bits */
	  tmp = (unsigned int32)hdtds[1] >> 24;  /* get sign, exponent */
	}
	tmp = tmp - 0x40 + 14;		/* remove exponent and stack bias */
	tmp <<= 2;			/* digit to bit count */
#ifdef FPBUG
 printf("tfo7b: tmp %x hdtds %x,%x hhtde %x hhtdbn %x\n",
 tmp, hdtds[0], hdtds[1], hhtde, hhtdbn); 
#endif
	tsh(tmp);			/* shift stack to unfloat number */
	goto tfo9;			/* number is ready */
tfo9:
#ifdef FPBUG
 printf("tfo9: hdtdf %x,%x hdtds %x,%x hhtde %x hhtdbn %x\n",
 hdtdf[0], hdtdf[1], hdtds[0], hdtds[1], hhtde, hhtdbn); 
#endif
	if (hhtdbn == 8) {		/* was the num an e type */
	  /* num was e type, make single precision number */
	  hdtds[0] = hdtds[1];		/* move sign, exp, and mantissa */
	  /* normalize number by adding to zero */
      /* FIXME */
	  hdtds[0] += 0;
	  hdtds[1] = 0;			/* into proper place for single prec */
#ifdef FPBUG
 printf("tfo9a Normalize needed hdtds %x,%x hhtde %x\n",
 hdtds[0], hdtds[1], hhtde); 
#endif
	}
#ifdef FPBUG
 printf("tfo9 ret: hdtdf %x,%x hdtds %x,%x hhtde %x\n",
 hdtdf[0], hdtdf[1], hdtds[0], hdtds[1], hhtde); 
#endif
	return;				/* return */
}

/*
 * tcy - release proper # of data bytes
 * input - data in hdtds
 *	 - tot has count
 */

void	tcy()
{
	int	ncnt = -tot;		/* neg number of bytes */
	int	i = 0;
	uint32 data = hdtds[0];	/* 1st word of data to go out */

	if (tot == 8) data = hdtds[1];	/* send out hi order first */
	if (tot == 2) data <<= 16;	/* position it */
	if (tot == 1) data <<= 24;	/* position it */
#ifdef MACD
printf("tcy: data %x, tot %d\n", data, tot);
#endif
	while (i < tot) {		/* do all the bytes requested */
	  if (i++ == 4)			/* 2nd word to go */
	    data = hdtds[0];		/* point to second word */
	  /* output the data rt justified, byte 0 first */
	  tdg((uint32)(data & 0xff000000) >> 24, 0, ncnt++);
	   /* output the data rt just */
	  data <<= 8;			/* next byte */
	}
}

/*
 * tsh - shift double value left or right n places
 * input - count = number of shifts
	 - if count neg, sign extend right shift
	 - if count pos, zero fill left shift
 *	 - hdtds and hdtdf are pointer to 64 bit number
 * output - hdtds and hdtdf shifted n places
 */

void	tsh(count)
int	count;
{
	if (count > 0) {		/* see if left shift */
	  lefts (hdtds, count);		/* shift hdtds */
	  lefts (hdtdf, count);		/* shift hdtdf */
	}
	else
	if (count < 0) {		/* see if right shift */
	  rights (hdtds, -count);	/* shift hdtds */
	  rights (hdtdf, -count);	/* shift hdtdf */
	}
	return;
}

/*
 * tdg - transfer data byte to proper sequencing
 * input - data = the data byte
 *	 - ljust = left justify the field, else right justify
 * 	 - cnt = the neg num of byte being emitted
 *	 - hbtttf - destination 0, 4, 8, c for data,gen,lit,val
 * output - hdtds has proper byte
 */

void	tdg(data, ljust, cnt)
int32	data;
int	ljust, cnt;
{
#ifdef MACD
printf("tdg called hbtttf %d, data %x, cnt %d\n", hbtttf, data, cnt);
#endif
	if (hbtttf == 0) {		/* data going out */
	  /* process data, datab, datah, dataw, datad */
	  if (++cnt > 0)goto tdg9;	/* go if not last byte */
	  /* this is the last byte to go out */
	  /* if type of inac null and abs, o.k. */
	  if ((inac.type == 0) && !(inac.flags & ABSREL))
	    goto tdg9;			/* o.k. for all data types */
	  /* if type of inac prog and abs, o.k. */
	  if ((inac.type == TYPP) && !(inac.flags & ABSREL))
	    goto tdg9;			/* o.k. for all data types */
	  if (tot != 4)	{		/* if 4 bytes, data statement */
	    if (yeanay())		/* it's not, are we assembling */
	      seterr ('R');		/* set relocation error */
	    hweval.value = 0;		/* set data to zero */
	    hweval.type = 0;		/* and null type */
	    hweval.flags = inac.flags & ~ABSREL;  /* force absolute */
	  } else {
	    hweval = inac;		/* set data value, val, and flags */
	  }
tdg9:					/* output byte */
	  igen((int)data);		/* output the byte */
	  return;			/* return */
	}
	else
	if (hbtttf == 4) {		/* process gen */
#ifdef MACD
printf("tdg: process gen hhvfgb = %d, hhvfs = %d, hhvff = %d\n",
hhvfgb, hhvfs, hhvff);
#endif
	  if (ljust) {			/* do left justified data */
	    int	numbits = 8;		/* default # bits out */

	    if (hhvfgb == 0) {		/* has any bits been output */
	      if (hhvfs & 7) 		/* no, get last 3 bits of field size */
					/* truncation is required if non 0 */
	 	numbits = hhvfs & 7;	/* set truncated size */
	    }
	    if (hhvfgb >= hhvfs)	/* # bits allowed against field size */
	      return;			/* already enough released, ignore */
	    vfdo (data, numbits);	/* generate field */
	    return;			/* get out */
	  } else {			/* do rt justified data */
	    /* issue rt justified data */
	    int	numbits = 8;		/* default to full byte */
	    int	i;
#ifdef MACD
printf("tdg rt just: hhvff %d, hhvfs %d, i = %d\n", hhvff, hhvfs, (64-hhvfs));
#endif
	    if (hhvff)			/* any bits out yet */
	      goto tdg5;		/* yes, go do it */
	    if ((i = (64 - hhvfs)) >= 0)  /* max size of usable data */
	      goto tdg5;		/* yes, don't need padding */
	    numbits = 8 - (i & 7);	/* get number of bits */
	    i /= 8;			/* convert from bit cnt to byte cnt */
	    if (numbits != 8) {		/* extra bits */
#ifdef MACD
printf("tgd rt2: i %d, numbits %d\n", i, numbits);
#endif
	      vfdo((int32)0, numbits);	/* output the bits */
	      numbits = 8;		/* all the rest are full bytes */
	    }
#ifdef MACD
printf("tgd rt2: i %d, numbits %d\n", i, numbits);
#endif
	    while (i < 0) {		/* pad fields with zeros */
	      vfdo((int32)0, numbits);	/* output the bits */
	      i++;			/* next byte */
	    }
tdg5:
#ifdef MACD
printf("tdg5 rt just: hhvfs = %d, hhvff = %d, i = %d\n", hhvfs, hhvff,
(64 - hhvfs - hhvff));
#endif
	    numbits = 8;		/* default to 8 bits out */
	    if ((i = (64 - hhvfs - hhvff)) < 0) { /* are we into a field */
	      vfdo(data, numbits);	/* yes, emit the byte */
	      return;			/* return */
	    }
	    if (i < 8) {		/* beginning of field */
	      vfdo(data, (8 - i));	/* yes, emit num bits */
	      return;
	    }
	    /* not at field yet */
	    hhvff += 8;			/* move to next data */
	    return;			/* return */
	  }
	}
	else {
	/* process literal or value expression */
	  if (ljust == 0)		/* is data to be right justified */
	    return;			/* yes, its o.k. where it is */
	  if (tot == 4)			/* 1st time thru */
	    hdtds[0] = 0x20202020;	/* blank the buffer */
	  if (tot >= 8)			/* are we at end */
	    return;			/* max reached, return */
	  /* clear byte position where byte is to go */
	  hdtds[0] &= ~(0xff << ((7 - tot) << 3));
	  /* put the data in */
	  hdtds[0] |= (data << ((7 - tot) << 3)); /* put in the data */
	  tot++;			/* bump the count */
	  return;			/* get out */
	}
}

/*
 * cnum - generate an integer number from ascii input
 * input - radix = 10 or 16 for decimal or hex conversion
 * output - 64 bit integer in cnumval
 *	  - terminator in cnumterm
 *	  - pointer to cnumval returned 
 */

int32	*cnum(radix)
int	radix;
{

/*
*        RADIX NUMBER TO BE ENTERED IN R2.  IT MAY RANGE FROM N'2' TO
*        N'16' WHERE INPUT CHARACTERS WILL BE ASCII ALPHABET FROM
*        0-9 AND THEN A-F.
*        OUTPUT IS THE DOUBLE PRECISION INTEGER IN R6 AND R7
*        AND THE NON-NUMERIC EQUIVALENT TERMINATOR IN R5
*/
	int	bcnt = 0;		/* input byte counter */
	char	nsign = 0;		/* set to sign of number */
	int32	*cval = cnumval;	/* point to output area */
	int	num;			/* temp loc */

	cnumval[0]=cnumval[1]=0;	/* initialize */
	cnumterm = 0;			/* no valid terminator found */
	if ((spmac & DUMMY) ||		/* is this a dummy parameter */
	  (macstate & CONDSCAN) ||	/* is this conditional scan */
	  (macstate & RSCAN) ||		/* is this rept scan */
	  (macstate & DEFMBODY)) {	/* are we in macro prototype */
	  spmac &= ~DUMMY;		/* clear the flag */
	  return(cval);			/* yes, return pointer to number */
	}
	if (usname[bcnt] == '+') {	/* is this a positive number */
	  bcnt++;			/* skip over '+' sign */
	  nsign = 0;			/* set number as positive */
	} else
	if (usname[bcnt] == '-') {	/* is this a negative number */
	  bcnt++;			/* skip over '-' sign */
	  nsign = 1;			/* set number as negative */
	}

loop:
	num = usname[bcnt++];		/* get an input char */
	if (islower(num)) 		/* is letter lower case */
	  num = toupper(num); 		/* make upper case */
	if (num != ' ') {		/* has space terminator been found */
	  /* see if totally invalid character */
	  if ((num < '0') || (num > '9' && num < 'A')) {  /* is it a number */
	    /* can not be a number, set number error and get out */
#ifdef MACD
      printf("Error N @ 6\n");
#endif
	    seterr('N');		/* yes, error */
	    goto cnuu;			/* get out */
	  }
	  if (num <= 'F') {		/* no, is it dec or hex number */
	    /* we have a dec or hex number, it it greater than radix */
	    int tmp = 0;
	    if (num >= '0' && num <= '9')tmp=num- '0';  /* make a number */
	    else
	    if (num >= 'A' && num <= 'F')tmp=num- 'A' + 10;  /* make a num */
	    if (tmp <= radix) {		/* is num > radix */
	      /* start the conversion, technique is multiplication by */
	      /* successive addition and shifting of 64 bit accumuland */
	      int32 dtemp[2];		/* double length temp */
	      int32 result[2];		/* double length result temp */
	      int	i=radix;	/* radix temp */
	      int	j;		/* a temp */

	      result[0] = 0;		/* clear lower 32 bits */
	      result[1] = 0;		/* clear upper 32 bits */
	      dtemp[1] = 0;		/* clear upper 32 bits */
	      dtemp[0] = tmp;		/* the number to add */
	      for (j = 0; j<6; j++) {	/* maximum of 6 bit multplier */
		lefts(result, 1);	/* shift result 1 left */
		i <<= 1;		/* multiplier to next position */
		if (i & 0x40)		/* check bit of multiplier */
		  add64 (cval, result);	/* bit is on, add multiplicand */
	      }
	      add64 (dtemp, result);	/* add in new digit */
	      cval[0] = result[0];	/* copy result to return storage */
	      cval[1] = result[1];	/* copy result to return storage */
	      goto loop;		/* loop for all characters */
	    }
	  }
	  /* not a valid number, is next char a ' ' terminator */
	  if (usname[bcnt] != ' ') {	/* is terminator a ' ' */
#ifdef MACD
      printf("Error N @ 7\n");
#endif
	    seterr ('N');		/* no, go number error */
	    goto cnuu;			/* get out */
	  }
	  /* we have a space terminator, see if b, h, w, d multiplier */
	} 				/* we have space terminator */
	switch (num) {			/* see if valid multiplier */
	  case ' ':
	  case 'B':
	    cnumterm = 1;		/* terminator to return */
	    break;			/* no conversion */
	  case 'H':
	    cnumterm = 2;		/* terminator to return */
	    lefts(cval, 1);		/* mult by 2 */
	    break;
	  case 'W':
	    cnumterm = 4;		/* terminator to return */
	    lefts(cval, 2);		/* mult by 4 */
	    break;
	  case 'D':
	    cnumterm = 8;		/* terminator to return */
	    lefts(cval, 3);		/* mult by 8 */
	    break;
	  case 'F':
	    cnumterm = 32;		/* terminator to return */
	    lefts(cval, 5);		/* mult by 32 */
	    break;

	  default:			/* not a valid multiplier */
#ifdef MACD
      printf("Error N @ 8\n");
#endif
	    seterr ('N');		/* no, go number error */
	    goto cnuu;			/* get out */
	}

	/* done processing, make value proper sign */
cnuu:
	if (nsign) {			/* is sign negative */
	  /* call negate to get negative value */
	  negate (cval);		/* negate the value */
	}
	hbcnul = nsign;			/* return the sign also */
	return(cval);			/* return pointer to 64 bit number */
}

/*
 * negate - make 64 bit value negative
 * input - num is pointer to number
 * output - the number is negated
 */

void	negate(num)
int32	*num;
{
	  /* use 2's complement to get negative value */
	  int32	dtemp[2];		/* a temp 64 bit value */

	  dtemp[0] = 1;			/* the 1 to add */
	  dtemp[1] = 0;			/* clear upper 32 bits */
	  num[0] = ~num[0];		/* complement lower 32 bits */
	  num[1] = ~num[1];		/* complement upper 32 bits */
	  add64(dtemp, num);		/* add one to get neg number */
}

/*
 * lefts - shift double value left n places
 * input - count = number of shifts
 *	 - nump = pointer to 64 bit number
 * output - nump shifted n places
 */

void	lefts(nump, count)
uint32	*nump;
int	count;
{
	while (count--) {		/* for number of bits to shift */
	  nump[1] <<= 1;		/* shift upper 32 bits */
	  if (nump[0] & 0x80000000)	/* is lower 32 bits sign bit on */
	    nump[1] |= 1;		/* propagate to upper 32 bits */
	  nump[0] <<= 1;		/* shift lower 32 bits */
	}
}

/*
 * rights - shift double value right n places
 *	    shift is arithmetic shift, with sign bit propagated
 * input - count = number of shifts
 *	 - nump = pointer to 64 bit number
 * output - nump shifted n places
 */

void	rights(nump, count)
uint32	*nump;
int	count;
{
	int32	sign = nump[1] & 0x80000000;	/* get sign bit */

	while (count--) {		/* for number of bits to shift */
	  nump[0] >>= 1;		/* shift lower 32 bits */
	  if (nump[1] & 1)		/* is low order bit on */
	    nump[0] |= 0x80000000;	/* propagate to lower 32 bits */
	  nump[1] >>= 1;		/* shift upper 32 bits */
	  nump[1] |= sign;		/* propagate the sign bit */
	}
}

/*
 * add64 - add two 64 bit numbers
 * input - val = pointer to number to be added to result
 *	 - result = pointer to results 
 * output - val added to result
 */

void	add64(val, result)
int32	*val;
int32	*result;
{
	int32	temp[2];		/* temp results */
	int32	i,ssum,a1,a2,carry;	/* more temps */

	/* perform addition of 32 bit numbers by first stripping off
	 * the sign bits of each 32 bit number, adding the numbers,
	 * manually appending the sign bit, and then generating a
 	 * carry if necessary.
	 */

	carry = 0;			/* no carry yet */
	for (i=0; i<2; i++) {		/* for both 32 bit words */
	  a1 = val[i] & 0x7fffffff;	/* strip sign bit */
	  a2 = result[i] & 0x7fffffff;	/* strip sign bit */
	  temp[i] = a1 + a2 + carry;	/* add the unsigned numbers */
	  ssum = 0;			/* init sign sum */
	  if (val[i] & 0x80000000)	/* test sign of 1st number */
	    ssum++;			/* got a sign */
	  if (result[i] & 0x80000000)	/* test sign of 1st number */
	    ssum++;			/* got a sign */
	  if (temp[i] & 0x80000000)	/* test sign of 1st number */
	    ssum++;			/* got a sign */
	  if (ssum == 0)		/* check sign sum */
	    carry = 0;			/* no carry */
	  else if (ssum == 1) {		/* check sign sum */
	    carry = 0;			/* no carry */
	    temp[i] |= 0x80000000;	/* but we need a sign bit */
	  } else if (ssum == 2) {	/* check sign sum */
	    carry = 1;			/* we have a carry */
	    temp[i] &= 0x7fffffff;	/* turn it off in number */
	  } else 			/* ssum == 3 */
	    carry = 1;			/* we have carry */
	}
	/* we ignore any overflow */
	result[0] = temp[0];
	result[1] = temp[1];		/* copy returned sum to output */
	return;				/* return */
}

/* the multiply and divide routines use 2 32 bit integers as pseudo
 * registers to do the operation.  val[0] is the low order part of
 * the 64 bit result and val[1] is the high order part.  On most systems
 * the bytes are right to left, while on the gould the bytes are left to
 * right.  This causes a lot of confusion.  The single precision number
 * is in val[0], the double precision number is in val[1] and val[0].
 */

/*
 * mulfp64 - multiply 2 floating point numbers
 * input - val1 - 1st multiplier
 *	 - val2 - 2nd multiplier and results location
 * output - val2 has results
 */

void	mulfp64(val1, val2)
int32	*val1;
int32	*val2;
{
#ifdef FPBUG
 printf("FLT: mulfp64 called %x %x\n", *val1, *val2);
#endif
}

/*
 * divfp64 - divide 2 floating point numbers
 * input - val1 - 1st divisor
 *	 - val2 - 2nd dividend and results location
 * output - val2 has results
 */

void	divfp64(val1, val2)
int32	*val1;
int32	*val2;
{
#ifdef FPBUG
 printf("FLT: divfp64 called %x %x\n", *val1, *val2);
#endif
}

/* Use internal floating point code, not machine code */
#ifdef MYATOF

#include "float.h"
extern void fcvtf();
extern int div10();
extern int mul10();
extern void incf();
extern void fdump();
extern void pfrsh8();
extern void pflsh();
extern void pfrsh();
extern void pnorm();
extern void iftodbl();
extern void fdump();
extern void cntofp();

/* floating point service */
static short	fexp;			/* floating exponent		*/
static short	fr[NF];			/* floating fraction		*/
static int32	fvhigh,fvlow;	/* floating final form		*/
static short	binexp;

/*	floating point  conversions	*/

void cntofp(num)
int *num;	/* the number */
{
#ifdef FPBUG
 printf("FLT: cntofp called %x\n", *num);
#endif
}

#ifdef DEBUG_FP
void flconv(typ, fe, f, rnum, ieee)
int typ;
short fe;
unsigned char *f;
int32 *rnum;
int ieee;
{
	register int i,j;
	printf("ieee conversion %s\n", ieee == 0 ? "no" : "yes");
	printf("flconv: typ[%x] exp[%x] frac[",typ,fe);
	for(i=0; i<NF; i++) {
		printf("%x ",f[i]&0xff);
	}
	printf("]\n");
	xflconv(typ, fe, f, rnum, ieee);
	printf("flconv returns %x %x\n",rnum[0],rnum[1]);
}

void xflconv(typ, fe, f, rnum, ieee)
#else
void flconv(typ, fe, f, rnum, ieee)
#endif
int typ;
short fe;
unsigned char *f;
int32 *rnum;
int ieee;
{
	/* pack up a floating point number */
	register int	i,j;
	register int	sign;

	binexp = 0;

	for( i=0; i<NF; i++ ) fr[i] = f[i] & 0xff;
	fexp = fe;
	rnum[0] = rnum[1] = 0;
	fvhigh = fvlow = 0;
	sign = 0;
	if( fr[NF-1] & 0x80 ){
		sign = j = 1;
		for( i=0; i<NF; i++ ){
			j += ~fr[i] & 0xff;
			fr[i] = j & 0xff;
			j >>= 8;
		}
	}
	for( i=0; i<NF; i++ ) if( fr[i] ) break;
	if( i == NF ) return;			/* true zero */
	pnorm();
	j = 0;
	while( fexp < 0 ) {
		 j = div10();
		 fexp++;
		 pnorm();
	}			 /* reduce dec exp */
	if( j >= 5 ) {
		 incf();
		 pnorm();
	}
	while( fexp > 0 ) {
		j = mul10();
		fexp--;
		if ( j ) pfrsh8(), fr[NF-1] = j, binexp += 8;
		pnorm();
	}
	iftodbl(ieee);
	if (ieee) {
		if( sign ) fvhigh |= 0x80000000L;
	} else {
		if( sign ){
			fvhigh = ~fvhigh;
			fvlow = -fvlow;
			if( fvlow == 0 ) fvhigh++;
		}
	}
	rnum[0] = fvhigh;
	rnum[1] = fvlow;
	if (typ == 5) {			/* if float, truncate */
		fcvtf(rnum, ieee);
		return;
	}
	/* swap for linux & mpx */
	i = rnum[1];
	rnum[1] = rnum[0];
	rnum[0] = i;
}

void iftodbl(ieee)		/* internal format to 64 bit floating point */
int ieee;
{
	register int	i;
	int	tmpexp;

	if (ieee) {
		for( i=0; i<9; i++ )pfrsh();
		incf();		/* round it up */
		pfrsh();	/* and truncate bit */
	} else {
#ifdef ENCORE
		for( i=0; i<5; i++ )pfrsh();
#else
		for( i=0; i<6; i++ )pfrsh();
#ifdef BADBAD
		while ((binexp+63) & 3)pfrsh(), binexp++;
#else
		while ((binexp+NF*8-1) & 3)pfrsh(), binexp++;
#endif
		incf();		/* round it up */
		pfrsh();	/* and truncate bit */
		binexp++;
#endif
	}
#ifdef BADBAD
	for( i=3; i>=0; i-- ) fvlow = (fvlow << 8) | fr[i];
	for( i=7; i>=4; i-- ) fvhigh = (fvhigh << 8) | fr[i];
#else
	/* just use 64 bits worth */
	for( i=NF-5; i>=NF-8; i-- ) fvlow = (fvlow << 8) | fr[i];
	for( i=NF-1; i>=NF-4; i-- ) fvhigh = (fvhigh << 8) | fr[i];
#endif
	if (ieee) {
		fvhigh &= 0x000fffff;		/* clear out 12 bits */
		fvhigh |= (int32)((binexp + 1085) & 0x7ff) << 20;
	} else {
		fvhigh &= 0x00ffffff;		/* clear out 8 bits */
#ifdef ENCORE
		fvhigh |= (int32)((binexp + 126) & 0x7f) << 24;
#else
#ifdef BADBAD
		tmpexp = ((62 + binexp) >> 2) + 64;
#else
		tmpexp = ((NF*8-2 + binexp) >> 2) + 64;
#endif
#ifdef JUNK
		if (tmpexp > 77) {
			/* number too big, use max */
			fvhigh = 0x7fffffff;
			fvlow = 0xffffffff;
		} else if (tmpexp < -77) {
			/* number too small, use zero */
			fvhigh = 0;
			fvlow = 0;
		} else
#endif
 			fvhigh |= (tmpexp & 0x7f) << 24;
#endif
	}
}

void pnorm(){
	while( fr[NF-1] <= 63 ){ pflsh(); binexp--; }
	while( fr[NF-1] > 127 ){ pfrsh(); binexp++; }
}

void pflsh()
{
	register int	i,j;

	j = 0;
	for( i=0; i<NF; i++ ){
		j |= fr[i] << 1;
		fr[i] = j & 0xff;
		j >>= 8;
	}
}

void pfrsh8()
{
	int	i;

	for( i=0; i<NF-1; i++ )
		fr[i] = fr[i+1];
	fr[NF-1] = 0;
}

void pfrsh()
{
	register int	i,j;

	j = 0;
	for( i=NF-1; i>= 0; i-- ){
		j |= fr[i];
		fr[i] = j >> 1;
		j = (j & 1) << 8;
	}
}

int mul10()
{
	register int	i,j;

	j = 0;
	for( i=0; i<NF; i++ ){
		j += fr[i] * 10; 
		fr[i] = j & 0xff;
		j >>= 8;
	}
	return (j);
}

int div10()
{
	register int	i,j;

	j = 0;
	for( i=NF-1; i>=0; i-- ){
		j <<= 8;
		j |= fr[i];
		fr[i] = j/10;
		j %= 10;
	}
	return j;
}

void incf()
{		/* increment */
	register int	i;

	for( i=0; i<NF; i++ ){
		fr[i]++;
		if( (fr[i] &= 0xff) ) return;
	}
}

void fcvtf(rnum, ieee)
int32 *rnum;
int ieee;
{			/* convert to single */
	register int	i;
	int32	sign;

	if (ieee) {
		sign = rnum[0] & 0x80000000;	/* save sign */
		i = (unsigned int)rnum[1] >> 29;	/* get three bits */
		i &= 7;
		rnum[0] -= 0x40000000;	/* remove exponent bias	*/
		rnum[0] <<= 3;		/* make room for three bits */
		rnum[0] += i;		/* put in bottom three bits */
		rnum[1] = 0;
		rnum[0] += 0x40000000L;	/* restore exponent bias */
		rnum[0] &= 0x7fffffff;	/* turn off sign	 */
		rnum[0] |= sign;	/* restore sign */
	} else {
		rnum[1] = 0;		/* simply truncate	*/
	}
}

#ifdef NOTNOW
fcvtd(rnum, ieee)
int32 *rnum;
int ieee;
{			/* convert to double */
	register int	i;
	int32	sign;

	if (ieee) {
		sign = rnum[0] & 0x80000000;
		i = rnum[0];
		i &= 7;
		rnum[1] = (int32)i << 29;
		rnum[0] -= 0x40000000;	/* remove exponent bias	*/
		rnum[0] <<= 1;		/* exponent sign to sign position */
		rnum[0] >>= 4;		/* extend it */
		rnum[0] &= 0x7fffffff;	/* and clear sign bit */
		rnum[0] += 0x40000000;	/* restore exponent bias*/
		rnum[0] |= sign;	/* restore sign */
	} else {
		rnum[1] = 0;		/* simply guarantee zero */
	}
}

cvitof( p )reg NODE *p;{		/* convert to float		*/

	reg int	i;
	reg int	signl;
	int32	sign;

	sign = 0;
	if( p->nd_fval == 0 ){
		p->nd_fvl2 = 0;
		goto pret;
	}
	if( p->nd_fval < 0 ){
		sign++;
		p->nd_fval = -p->nd_fval;
	}
	for( i=0; i<4; i++ ){
		fr[i] = p->nd_fval & 0xff;
		p->nd_fval >>= 8;
	}
	for( ; i<8; i++ ) fr[i] = 0;
	fexp = binexp = 0;
	pnorm();
	iftodbl(ieee);
	p->nd_fval = fvhigh;
	p->nd_fvl2 = fvlow;
pret:	p->nd_type = TYREAL|(8<<5);
	if( sign ) p->nd_fval |= 0x80000000;
}

cvftoi( p ) reg NODE *p; {		/* float to int */

	reg int	i;
	reg int	sign;

	if( p->nd_fval == 0 ){
		p->nd_fvl2 = 0;
		p->nd_type = deflong;
		return;
	}
	if( p->nd_fval < 0 ) sign++;
#ifdef IEEE
	i = p->nd_fval >> 20;
	if( varlen( p->nd_type ) == 8 ){	/* from double */
		i &= 0x7ff;			/* exponent is 11 bits */
		i -= 1027;			/* remove bias */
		p->nd_fvl2 >>= 20;
		p->nd_fvl2 &= 0xfff;
		p->nd_fval = (p->nd_fval << 12) | p->nd_fvl2 | 0x80000000;
		p->nd_fvl2 = 0;
	} else {
		i = (i >> 3) & 0xff;		/* exponent is 8 bits */
		i -= 127;			/* remove bias */
		p->nd_fval = (p->nd_fval << 23 ) | 0x80000000;
	}
#else		/* use the UNIFORM format	*/
	if( sign ) fneg( p );
	i = p->nd_fval >> 24;
	i &= 0x7f;				/* get exponent	*/
	i -= 64;				/* remove bias	*/
	p->nd_fvl2 >>= 24;
	p->nd_fvl2 &= 0xff;
	p->nd_fval = (p->nd_fval << 8) | p->nd_fvl2;
	p->nd_fvl2 = 0;
#endif
	if( i < -1 ){				/* no significance at all */
		p->nd_fval = 0;
		i = 31;
	}
	while( i < 31 ){
		p->nd_fval >>= 1;
		p->nd_fval &= 0x7fffffff;
		i++;
	}
	if( sign ) p->nd_fval = -p->nd_fval;
	p->nd_type = deflong;
}

fneg( p ) reg NODE *p; {
#ifdef IEEE
	p->nd_fval ^= 0x80000000L;
#else
	p->nd_fval = ~p->nd_fval;
	if( (p->nd_fvl2 = -p->nd_fvl2) == 0 ) p->nd_fval++;
#endif
}
#endif /* NOTNOW */

void fdump(s)
char *s;
{
	register int	i;
	printf("fd(%s)fexp = %d binexp = %d ",s,fexp,binexp);
	printf(" %4x %4x [",fvhigh,fvlow);
	for( i=NF-1; i>= 0; i-- ) printf(" %2x",fr[i] );
	printf("]\n");
}

#endif /* MYATOF */
