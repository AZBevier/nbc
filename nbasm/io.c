/* io.c */

/* this module does all i/o for gasm */

#include <ctype.h>
#include "defs.h"
#include <string.h>

#ifdef DOS
void	str2upr(char *);
void	ejct(char *);
void	ejct2(char *);
void	pb(unsigned char *, int, int);
void	pbp(int);
void	mpxbb(unsigned char *, int);
int	inpt();
void	igen(int);
void	releas();
void	pout();
void	loch(struct tval *, int, char *);
int	ppp(int, char *, int);
int32	iread(int, char *);
void	pbyt(char);
#endif

#ifndef CAID
extern	int	sudo;	/* processing pseudo-op */
#endif
uint8	inscnt;		/* input scanner count */
uint8	ppt;		/* binary record length (120) */

short	pbsq;		/* current sequence number */
/* short	xdummy; */		/* bound buffer in 16 bit boundry */
unsigned char	PBL[BRL];	/* binary buffer */
/* unsigned char	*PBBA; */		/* saved pointer address to buffer */
short	*pblc = (short *)&PBL[2];  /* 16 bit checksum */
short	*pbls = (short *)&PBL[4];  /* 16 bit sequence */
unsigned char	*pblp = (&PBL[6]);  /* start of data in binary buffer */

extern	FILE	*outfd;	/* output file descriptor */
int32	lice;		/* line count */
struct	tval	max;	/* maximum program size */
/* char	imip; */		/* image in progress flag */

char	*ahdr;		/* header address for tof printing */
char	nlpr = 0;	/* number of lines printed on page */
unsigned char dpnum;	/* sumbol's dpnum */

char	tcwd[TCWSIZE];	/* the title buffer */

/*
 * str2upr - set string to upper case
 * str2upr(str)
 * input - pointer to string
 * output - string set to uppercase
 */

void	str2upr(str)
char *str;
{
	while (*str) {
	  if (islower(*str))*str = toupper(*str);
	  str++;
	}
	return;
}

/*
 * ejct - page eject for listing output
 * ejct will set up for page eject on next print request
 * only if lo is enabled
 * input - pointer to new header
 */

void	ejct (header)
char	*header;
{
	if (!(LO & option)) return;	/* return if not listing */
	ahdr = header;			/* save new header infor */
	nlpr = 0;			/* zero num of lines printed */
	return;
}

/*
 * ejct2 - page eject for listing output
 * ejcti2 will unconditionally set up for page eject on next print request
 * only if lo is enabled
 * input - pointer to new header
 */

void	ejct2 (header)
char	*header;
{
	ahdr = header;		/* save new header infor */
	nlpr = 0;		/* zero num of lines printed */
	return;
}

/*
 * pb - publish binary routine
 * input - buffer addr
 *	   expanded function code
 *	   sub code
 */

void	pb(buff, expfc, subc)
unsigned char 	*buff;
int	expfc;
int	subc;
{
	int32	tmp;
	int	PBCNT;		/* bytes to go out this call */
	int32	tsum;

#ifdef BIN
printf("pb entry: buff = %x, cnt = %x, expfc = %x, subc = %x\n", buff, *buff, expfc, subc);
#endif
	if (!(BO & option)) return;	/* return if no bo req'd */
	if (expfc != 0xd) {	/* is this expanded loader funct code */
	  tmp = *buff;		/* get byte cnt (HBBS) */
	  PBCNT = tmp;		/* save # bytes being passed out */
	  PBCNT++;		/* incr byte count to inc funct code byte */
	  expfc <<= 4;		/* shift function code */
	  expfc |= tmp;		/* concatenate func code and byte cnt */
	} else {
	  /* this is an expanded loader function code */
	  tmp = *buff;		/* get byte cnt (HBBS) */
	  tmp++;		/* incr by 1 for code */
	  buff[2] = tmp;	/* save as byte count in ldr data */
	  PBCNT = tmp;		/* save # bytes being passed out */
	  expfc <<= 4;		/* shift function code */
	  if (buff[1] == 12) {	/* is subcode date/time or prod id */
	    PBCNT += 3;		/* add in 3 bytes for control info */
				/* 1 byte for code was added above */
	    buff[2] = PBCNT;	/* save as byte count in ldr data */
	    expfc |= subc;	/* put sub code in record */
	  } else {
	  if (buff[1] != 11)	/* is subcode a debug item */
	    if (buff[4])	/* is sect num dsect (zero) */
#ifdef FIX_EBAC33B
	      expfc |= 4;	/* no, set csect flag */
#else
    		;
#endif
	  }
	}
	*buff = expfc;		/* put in first byte */
	if (!ppt) return;	/* return if device unusable for bo */
#ifdef BIN
printf("pb: outputing ppt, rec len = %d\n", (ppt-6-(int)PBLB-(int)PBCNT));
printf("pb: ppt = %x, PBLP = %x, PBLB = %x, PBCNT = %x\n", ppt, PBLP, PBLB, PBCNT);
#endif
	/* rec length - control cnt - # in buf now - new cnt */
	if ((6 + (int)PBLB + (int)PBCNT) > ppt) {
	  /* no room in buffer for current record */
	  /* dump buffer stack on bo device */
#ifdef BIN
printf("pb: DUMPING buffer, PBLB = %x\n", PBLB);
#endif
	  pbp (0xff);		/* binary output function code */
	}
#ifdef BIN
printf("pb: moving record PBLC = %x, PBLB = %d, PBCNT = %x\n", PBLC, PBLB, PBCNT);
#endif
	/* get the old checksum */
	tsum = ((PBL[2] << 8) & 0xff00) | (PBL[3] & 0xff);
	/* pack current record into stack */
	for ( tmp = tsum; PBCNT; PBCNT-- ) {
	  PBLP[PBLB++] = *buff;		/* put byte in stack */
	  tmp = (tmp + *buff++) & 0xffff; /* checksum it */
	}
	/* put back the checksum */
	PBL[2] = (tmp & 0xff00) >> 8;
	PBL[3] = (tmp & 0xff);
	return;
}

/*
 * pbp (fc)
 * finish buffer computations and
 * output current buffer to bo
 * input - binary output function code 
 */

void	pbp(fc)
int	fc;
{
	if (!(BO & option)) return;	/* return if no bo wanted */
	PBLF = fc;			/* put funct code into buffer */
	if (!ppt) return;		/* if no bo device, return */
	/* update the sequence number */
	pbsq++;				/* incr sequence number */
	PBL[4] = (pbsq & 0xff00) >> 8;	/* set seq number in buffer */
	PBL[5] = (pbsq & 0xff);
#ifdef MPXBB
	if ((fwrite(PBL, 1, BRL, outfd)) < 0)
	  boer();			/* EOF on bo */
#else
	mpxbb(PBL, BRL);		/* output mpx blocked file */
#endif
	memset(PBL, '\0', BRL);		/* initialize BO buffer */
	PBLC = 0;			/* clear checksum */
	PBLB = 0;			/* clear byte count */
	return;
}

static	unsigned  char	bb[768];	/* blocking buffer */
/* static	char	*bhc = 0; */		/* buffer head cell */
static	char	first = 0;		/* 1st time thru flag */

/*
 * mpxbb - make up mpx block file output
 * input - buffer address
 *	 - byte count
 */

void	mpxbb(buf, cnt)
unsigned char	*buf;
int	cnt;
{
	int	boff;			/* next write address offset */

	if (!first) {			/* is this 1st time thru */
	  first = 1;			/* set the flag */
	  memset (bb, '\0', 768);	/* zero the buffer */
	  bb[3] = 4;			/* next write byte offset */
	  bb[4] = 0x60;			/* set beg/end of block */
/*	  bb[5] = 8; */			/* 1st block count is 8 bytes */
	  bb[5] = 0;			/* 1st block count is 0 bytes */
	}
	boff = (bb[2] << 8) | (bb[3]);	/* get next write address offset */
	/* see if enough room in buffer for this record */
	/* add current offset + 2 (for last record info) plus new */
	/* record size plus 4 (2 for this rec, 2 for last) */
	if ((boff + 2 + cnt + 4) >= 768) {
	  /* not enough space, write out this record */
	  if ((fwrite(bb, 1, 768, outfd)) < 0)
	    boer();			/* EOF on bo */
	  memset (bb, '\0', 768);	/* zero the buffer */
	  bb[4] = 0x60;			/* set beg/end of block */
	  bb[5] = 0;			/* 1st block count is 0 bytes */
					/* after 1st write */
	  boff = 4;			/* init count at 4 bytes */
	}
	/* we have enough room, move in the record */
	/* clear last record end of block flag, set up this record */
	/* info and last rec info at end of data, and update cnt */
	bb[boff] &= ~0x20;		/* clear end of block flag */
	bb[boff+2] = 0x00;		/* clear this blocks flags */
	bb[boff+3] = cnt;		/* set this record count */
	memcpy(&bb[boff+4], buf, cnt);	/* copy in the data */
	boff += (cnt+4);		/* update count */
	bb[boff] = 0x20;		/* set eob status flag */
	bb[boff+1] = cnt;		/* set last rec byte count */
	bb[2] = (boff & 0xff00) >> 8;	/* set hi byte of count */
	bb[3] = (boff & 0xff);		/* set lo byte of count */
	if (*buf != 0xdf)		/* was this the last rec */
	  return;			/* no, done */
	/* that was the last record, set eof flag in bb, write it and exit */
	/* see if enough room in buffer for EOM record */
	/* add current offset + 2 (for last record info) plus new */
	/* EOF record size of 4 (2 for this rec, 2 for last) */
	if ((boff + 2 + 4) >= 768) {
	  /* not enough space, write out this record */
	  if ((fwrite(bb, 1, 768, outfd)) < 0)
	    boer();			/* EOF on bo */
	  memset (bb, '\0', 768);	/* zero the buffer */
	  bb[4] = 0x60;			/* set beg/end of block */
	  bb[5] = 0;			/* 1st block count is 0 bytes */
					/* after 1st write */
	  boff = 4;			/* init count at 4 bytes */
	}
	bb[boff] &= ~0x20;		/* clear end of block flag */
	bb[boff+2] = 0x80;		/* clear this blocks flags */
	bb[boff+3] = 0;			/* set record count of 0 */
	bb[boff+4] = 0xa0;		/* set EOF/EOB flags */
	boff += 4;			/* 4 more bytes */
	bb[2] = (boff & 0xff00) >> 8;	/* set hi byte of count */
	bb[3] = (boff & 0xff);		/* set lo byte of count */
	/* write out EOF record */
	if ((fwrite(bb, 1, 768, outfd)) < 0)
	  boer();			/* EOF on bo */
	first = 0;			/* reset 1st time flag */
	return;				/* get out, done */
}

/*
 * inpt - release image and get next one
 * returns 0xff on EOF
 */

int	inpt()
{
	uchrfp	tcp;			/* where input is from */
	uchrfpp	place=NULL;		/* which pointer to use */
	int	cnt;			/* number of chars processed */

    	if (macstate & BLANKLN) {	/* do we have a blank line */
    	  macstate &= ~BLANKLN;		/* clear flag */
    	  goto doblank;			/* skip other stuff */
    	}
	if (macstate & NOCOMMT) {	/* is it a non comment line */
	  macstate &= ~NOCOMMT;		/* yes, clear flag */
	  if ((inptstat & DEFMBODY) 	/* are we scanning a prototype */
	    || (inptstat & RSCAN)) {	/* or looking for end of rept */
	    mbyt((unsigned char)0xff);	/* send end of input record */
	  } 
	}				/* just process input */

	releas();			/* release the printed output */
	while (hwerrf) {		/* any unprinted errors */
	  bits &= ~IMIN;		/* no image ready, just print errors */
	  releas();			/* print the errors */
	}

doblank:
	inptstat = macstate;		/* get the latest macro state */
	/* if we are not doing anything special, get a line of input */
	if (!(macstate & (MACREP | EXPAND | RPTGEN))) {
	  lict = iread(80, in);		/* get 80 bytes to input buffer */
	  inscnt = 0;			/* init line unstrung counter */
	  bits |= IMIN;			/* indicate buffer image ready */
	  currpc = sectpc[pcmode];	/* get section PC and save */
	  return(lict);			/* return line cnt or EOF */
	}
	if (macstate & MACREP) {	/* is it repeat within an expansion */
	  if (level == 0) {		/* is this still at the repeat level */
	    if (macstate & RPTGEN) {	/* are we repeating */
	      place = &hwrepsp;		/* point to repeat space */
	      goto getin;		/* go copy input */
	    }
	  }
	}
	if (macstate & EXPAND) {	/* are we expanding a macro */
	  place = &mpp->maca;		/* point to prototype */
	  goto getin;			/* go copy input */
	} 
	if (macstate & RPTGEN) {	/* are we repeating */
	  place = &hwrepsp;		/* point to repeat space */
	  goto getin;			/* go copy input */
	}
getin:
	for (cnt = 0; cnt < 72; cnt++) {
	  tcp = *place;			/* get the pointer */
	  (*place)++;			/* incr the pointer */
	  if (*tcp == 0xff) {		/* check for end of line */
	    /* blank out rest of input buffer */
	    memset(&in[cnt], ' ', 80-cnt);
	    break;			/* get out of loop */
	  }
	  in[cnt] = *tcp;
	}  
#ifdef MACD
{
#ifdef OLDWAY_022521
	int	i;
printf("getin: count = %d\n", cnt);
	for (i=0; i<80; i++) {
	if (i==40)
	  printf("\n");
	if (isprint(in[i]))
	  printf("%c", in[i]);
	else
	  printf("%.2x",in[i]);
	if (in[i] == 0xff) break;
	}
	printf("\n");
#else
printf("getin: count = %d\n", cnt);
    printf("getin: %.72s\n", in);
#endif
/* printf("getin: %.72s\n", in); */
/* printf("",in); */
}
#endif
	if (cnt == 72) {		/* check next char for eol */
	  if (tcp[1] == 0xff) {		/* next char end of line */
printf("getin: long line, adv by 3\n");
	    *place += 3;		/* adv pointer past long record */
	  }
	}
	memset(mpbuf, ' ', 80);		/* blank aux print buffer */
	inscnt = 0;			/* init line unstrung counter */
	bits |= IMIN;			/* indicate buffer image ready */
	currpc = sectpc[pcmode];	/* get section PC and save */
	return(lict);			/* return line cnt */
}

/*
 * igen (byte) - byte generation routine
 * place at next available location at PC
 */

void	igen (byte)
int	byte;
{
	int32	tmp;

	if (CONDSCAN & macstate) return; /* return if no assembly flag */
	if (DEFMBODY & macstate) return; /* return if in mac prototype */
	if (RSCAN & macstate) return;	/* return if in repeat scan */
	bits |= CVFL;			/* signal to print program counter */
	hbbbct++;			/* increment gen byte count */
	tmp = sectpc[pcmode].value & 3;	/* get last 2 bits of pc */
	hwbyte[tmp] = byte;		/* store the byte into corr byte loc */
	hwbytf[tmp] = 1;		/* flag byte as being generated */
	sectpc[pcmode].value++;		/* increment the pc */
    	pcchk();			/* check for pc overflow */
	if (!(sectpc[pcmode].value & 3)) {	/* see if on wd boundry */
	  /* on word boundry, print it out */
#ifdef BIN
printf("igen: hwbytf = %x %x %x %x\n", hwbytf[0], hwbytf[1], hwbytf[2], hwbytf[3]);
printf("igen: hwbyte = %x %x %x %x\n", hwbyte[0], hwbyte[1], hwbyte[2], hwbyte[3]);
#endif
	  releas();			/* print it out */
	  currpc = sectpc[pcmode];	/* staticize the prog counter */
	}
	return;				/* done, return */
}

extern struct	tval	hwbbls;		/* last pc address */
char	dpbuf[18];

/*
 * releas - image and object output control routine
 */

void	releas ()
{
	int	i, j, tmp;

	/* do binary output first */
	if ((PASS & 1) || !hbbbct) {	/* if pass 1 or no bo, return */
#ifdef BIN
printf("releas: hbbbct = %d\n", hbbbct);
#endif
    	  goto bbxit;			/* get out of here */
	}
#ifdef BIN
printf("releas: hwbytf = %x %x %x %x\n", hwbytf[0], hwbytf[1], hwbytf[2], hwbytf[3]);
printf("releas: hwbyte = %x %x %x %x\n", hwbyte[0], hwbyte[1], hwbyte[2], hwbyte[3]);
#endif
	hbbbfb |= 1;			/* show that a byte has been gen'd */
	*hbbs = 0;			/* reset binary stack count */
	if ((currpc.value != hwbbls.value) || (currpc.flags != hwbbls.flags) ||
	  (currpc.type != hwbbls.type))
	  goto neworg;			/* go do new origin */
	if (!(bits3 & EXPLFC))		/* expanded lfc's */
	  goto bb2;			/* no, no need for new origin */
	/* is this location zero in the dsect */
	if (!(currpc.flags == ABSREL && currpc.value == 0 && 
	  currpc.type == TYPP))
	  goto bb2;			/* no, no need for a new origin */
neworg:
	if (currpc.type == TYPC) {	/* pc in common */
	  /* a common origin is needed */
	  bfa(currpc.value);		/* output block # and offset */
	  pb (hbbs, PTCO, 0);		/* publish common origin */
	  goto bb2;			/* go output other bytes */
	}
#ifdef BIN
prtval("neworg", &currpc);
#endif
	if (!(bits3 & EXPLFC)) {	/* using expanded lfc's */
	  /* no, use std lfc's */
	  bfa(currpc.value | (currpc.flags & ABSREL ? 0x800000L : 0L));
	  pb (hbbs, PTO, 0);		/* publish the stack */
	} else {			/* using exp loader funct codes */
	  bfb(LFSORIG);			/* set loader subcode */
	  bfb(0);			/* dummy byte */
	  bfb(0);			/* zero unused byte */
	  bfb(currpc.flags & CSDS ? 1 : 0);	/* section number */
	  bfa0(currpc.value);		/* output address */
	  pb (hbbs, EXPFUNC, 0);	/* publish the stack */
	}
bb2:
#ifdef BIN
printf("bb20: hwbytf = %x %x %x %x\n", hwbytf[0], hwbytf[1], hwbytf[2], hwbytf[3]);
printf("bb20: hwbyte = %x %x %x %x\n", hwbyte[0], hwbyte[1], hwbyte[2], hwbyte[3]);
#endif
	*hbbs = 0;			/* reset stack counter */
	tmp = hweval.type;		/* set type */
	if (hweval.type == TYPC) {	/* ref to common */
	  bfb(hbbn);			/* yes, output common block # */
	  tmp = hbbn;			/* set common block # */
	}
	/* continue with normal type */
	if (!(bits3 & EXPLFC))		/* use exp lfc's */
	  goto bb3;			/* not set, gen std codes */
	switch (tmp) {
	  case TYPU:
	  case TYPL:
	  case TYPP:
	  case TYPM:
	  case TYPX:
	  case TYSETSYM:
	    if (!(hweval.flags & ABSREL))	/* is type relocatable */
	      goto bb3;			/* no, gen old code */
	    if (DPFLG & dpflags)	/* datapool reference */
	      goto bb3;			/* yes, gen old code */
	    /* output exp loader function code for rel's */
    	    if (bacflag & 1) {		/* see if bacw or bach */
	      bfb(LFCBAC);		/* output loader subcode */
    	      bfb(hbbbct);		/* output data byte count */
    	      bfb(0);			/* output unused byte */
    	      if (bacflag & 2)		/* addr in csect */
    		bfb(1);			/* show csect address */
    	      else
    		bfb(0);			/* show dsect addr */
	      bfb(hwbyte[1]);		/* output the byte */
	      bfb(hwbyte[2]);		/* output the byte */
	      bfb(hwbyte[3]);		/* output the byte */
	      tmp = EXPFUNC;		/* type is expanded */
    	      goto bb5;
    	    }
	    bfb(LFSREL);		/* output loader subcode */
	    bfb(hbbbct);		/* output data byte count */
	    bfb(0);			/* output unused byte */
	    bfb(hbbn);			/* section number */
	    bfb(0);			/* repeat count of 0 */
	    tmp = EXPFUNC;		/* type is expanded */
#ifdef BIN
printf("bb2: hwbytf = %x %x %x %x\n", hwbytf[0], hwbytf[1], hwbytf[2], hwbytf[3]);
printf("bb2: hwbyte = %x %x %x %x\n", hwbyte[0], hwbyte[1], hwbyte[2], hwbyte[3]);
#endif
	    for (i=0; i<4; i++)		/* look at 4 bytes */
	      if (hwbytf[i])		/* this byte to go out */
	        bfb(hwbyte[i]);		/* output the byte */
bb5:
	    pb (hbbs, tmp, 0);		/* publish binary output */
bb6:
	    hwbbls = sectpc[pcmode];	/* save program ctr for this section */
bbxit:
	    if (!(PASS & 1)) {		/* if pass 2 */
    	      if(extflg & 1)		/* non stringback entry */
    		if(option & ASECT)	/* autosectioning on */
    		  if(option & OPT11) {	/* option 11 */
    		    extflg &= ~1;	/* clear flag */
    		    *hbbs = 0;		/* reset stack counter */
    		    bfb(LFEXTRF);	/* ext ref loader funct code */
    		    bfb(0);		/* dummy byte */
    		    bfb(0);		/* unused byte */
    		    bfb(extwrd.flags & CSDS ? 1 : 0);	/* section number */
    		    /* output address */
    		    bfa(currpc.value|(extwrd.flags & ABSREL?0x800000L:0L));
    		    memcpy (usname, extnam, 8);	/* move 8 bytes of ext name */
    		    bfn0 ();		/* output 8 bytes from usname */
    		    pb(hbbs, EXPFUNC, 0); /* publish the stack */
    		  }
    	    }
	    pout();			/* make up listing output */
	    cext();			/* clear ouput buffer and flags */
    	    bacflag &= ~1;		/* clear bacw, bach flag */
    	    bacflag &= ~2;		/* clear CSECT address flag */
	    return;			/* exit */

	  default: 			/* not a section type */
	    goto bb3;			/* yes, gen old code */
	}
bb3:
#ifdef BIN
printf("bb3: hwbytf = %x %x %x %x\n", hwbytf[0], hwbytf[1], hwbytf[2], hwbytf[3]);
printf("bb3: hwbyte = %x %x %x %x\n", hwbyte[0], hwbyte[1], hwbyte[2], hwbyte[3]);
#endif
	for (i=0; i<4; i++)		/* look at 4 bytes */
	  if (hwbytf[i])		/* this byte to go out */
	    bfb(hwbyte[i]);		/* output the byte */
	tmp = PTCR;			/* default to common funct code */
	if (hweval.type == TYPC)	/* is type common */
	  goto bb5;			/* yes, go output */
	tmp = PTA;			/* set default to abs funct code */
	if (!(hweval.flags & ABSREL))	/* it it absolute */
	  goto bb5;			/* yes, go output */
	tmp = PTR;			/* set default to rel funct code */
	if (!(DPFLG & dpflags))		/* is it a datapool reference */
	  goto bb5;			/* no, rel, go output */
	tmp = PTA;			/* set default to abs funct code */
 	/* datapool reference is needed */ 
	for (i=0; i<16; i++)		/* clear datapool buffer */
	  dpbuf[i] = 0;			/* set to zero */
	if (*hbbs != 4) {		/* have 4 bytes been gen'd */
	  seterr ('A');			/* no, set address error */
	  goto bb5;			/* output buffer */
	}
#ifdef BIN
printf("bb3: processing datapool\n");
#endif
	i = 0;				/* clear the counter */
	if (dpnum != 100)		/* is this "datapool" */
	  i = 3;			/* set buffer for ext output */
	for (j=0; j<8; j++) {		/* 8 chars max */
	  if (dpitem[j] == ' ')		/* are we at end of name */
	    break;			/* yes, exit loop */
	  hbbs[0]++;			/* bump std buffer count */
	  dpbuf[i+1] = dpitem[j];	/* store the char */
	  i++;				/* next store loc */
	}
	for (j=0; j<4; j++) {		/* move gen'd data to dpbuf */
	  dpbuf[i+1] = hbbs[j+1];	/* get a byte */
	  i++;				/* next loc in hbbs */
	}
	if (dpnum != 100) {		/* is this "datapool" */
	  dpbuf[i+1] = dpnum;		/* no, save datapool # */
	  dpbuf[1] = LFMULDP;		/* set subtype in dpbuf */
	  dpbuf[0] = hbbs[0] + 4;	/* set count */
	  dpbuf[3] = 0;			/* clear unused byte */
	  pb (dpbuf, EXPFUNC, 0);	/* publish binary output */
	  goto bb6;			/* finish up */
	}
	dpbuf[0] = hbbs[0];		/* set the byte count */
	pb (dpbuf, PTDP, 0);		/* publish binary output */
	goto bb6;			/* finish up */
}

/*
 * pout - print output
 * prnt is print buffer
 * in has input line
 */

void	pout()
{
/*
*--------SYSTEM FLAGS CONTROLLING FORMAT AND OUTPUT DETERMINATION IN
*--------THIS ROUTINE ARE AS FOLLOWS
*                  HBAPON=0=ALLOW LISTING,1=NO LISTING
*                  HBAPEX=0'ALLOW LISTING OF EXTENSION,1=NO EXT LISTING
*                  PASS=0=PASS 2,ELSE PASS1
*                  HWERRF=IND ERROR TYPES SINCE LAST PRINTED
*                  HBCVFL=0=DONT PRINT PROG COUNTER, 1 MEANS PRINT IT
*                  HBIMIN=0=IMAGE ALREADY PRINTED,1 MEANS NOT PRINTED
*/
	int	line = 0;
	int	maxerr;
	char	xx[20];

	memset(prnt, ' ', 40);		/* blank buffer */
	spmac &= ~MBUFSW;		/* clear prnt buf switch */
	if (PASS & 1) {			/* is this pass 2 */
	  /* no, do special error handling */
	  /* ignore b, r, u, v, and \ errors in pass 1 */
	  clrerr('B');			/* ignore B error */
	  clrerr('R');			/* ignore R error */
	  clrerr('U');			/* ignore U error */
	  clrerr('V');			/* ignore V error */
	  clrerr('\\');			/* ignore \ error */
	  if (hwerrf == 0)		/* see if any errors */
	    goto pouw;			/* no, don't print line */
	  else
	    goto pouu;			/* print short errors and long image */
	}
	/* pass2 error processing */
	if (hwerrf != 0)		/* see if any errors */
	  goto pouy;			/* yes, print line */
	if (bits & NGPRINT) {		/* listing non-gen source */
	  if (yeanay()) {		/* are we assembling */
	    if (bits2 & NONGITEM)	/* yes, list non suppressable op */
	      bits &= ~IMIN;		/* yes, mark no image ready */
	  } else
	      bits &= ~IMIN;		/* not assem, mark no image ready */
	}
	if (bits & APON)		/* is list on? */
	  goto pouw;			/* no, skip printout */
	if (spmac & NOPGEN) {		/* generating a nop? */
	  if (!(bits & BNDWS4))		/* expanding while gen'ing a nop */
	    if (bits2 & MACPRINT)	/* yes, expansion list allowed */
	      goto pouw;		/* no, skip printout */
	} else {			/* not gening a nop */
	  if (inptstat & EXPAND)	/* expanding */
	    if (bits2 & MACPRINT)	/* yes, expansion list allowed */
	      goto pouw;		/* no, skip printout */
	}
	if (inptstat & RPTGEN)		/* gen'ing repeat code */
	  if(bits2 & REPPRINT)		/* repeat expansion allowed */
	    goto pouw;			/* no, skip printout */
	if (bits & IMIN)		/* is listing suppressed */
	  goto pouy;			/* no, go print line */
	if (!(bits & CVFL))		/* is print pc flag set */
	  goto pouw;			/* no, skip printout */
	if (bits & APEX)		/* do we allow extension listing */
	  goto pouw;			/* no skip printout */
pouy:
	/* an image is ready for printing or we have bytes generated and */
	/* ready for printing in the extension image case or we have errors */
	/* on pass 2 */

	if (bits & CVFL) {		/* print prog counter */
	  /* yes, print the program counter */
	  loch(&currpc, 0, &prnt[9]);
	  /* is there an evaluated expression */
	  if (hweval.value || hweval.type || hweval.flags) {
	    /* yes, print it then */
	    if (hweval.type == TYPC) {	/* is type common */
	      /* or in block # */
	      hweval.value = ((hweval.value & 0xffffL) | ((int32)hbbn << 16));
	    }
	    loch(&hweval, 1, &prnt[28]);
	    if (dpflags & DPFLG) {	/* it it datapool */
	      prnt[30] = 'A';		/* indicate in print buffer */
	      if (dpnum == 0xff)	/* is it sext */
		prnt[30] = 'X';		/* indicate sext in print buffer */
	    }
	  }
	  /* format those flagged bytes of generated code for printout */
	  if (hwbytf[0]) {		/* this byte to be printed */
	    sprintf(xx, "%02X", hwbyte[0]);
	    memcpy(&prnt[19], xx, 2);	/* copy in 2 chars */
	  }
	  if (hwbytf[1]) {		/* this byte to be printed */
	    sprintf(xx, "%02X", hwbyte[1]);
	    memcpy(&prnt[21], xx, 2);	/* copy in 2 chars */
	  }
	  if (hwbytf[2]) {		/* this byte to be printed */
	    sprintf(xx, "%02X", hwbyte[2]);
	    memcpy(&prnt[23], xx, 2);	/* copy in 2 chars */
	  }
	  if (hwbytf[3]) {		/* this byte to be printed */
	    sprintf(xx, "%02X", hwbyte[3]);
	    memcpy(&prnt[25], xx, 2);	/* copy in 2 chars */
	  }
	}				/* don't print pc */

	memset (&prnt[4], ' ', 4);	/* blank line number location */
	line = 0;			/* default to short line if no image */
	if (bits & IMIN)		/* is buffer ready to print */
	  goto pouu;			/* yes, go print it */
	if (!(inptstat & EXPAND))	/* are we in an expansion */
	  goto poux;			/* not in expansion */
	if (hwmspbuf == 0)		/* any macro bytes read */
	  goto poux;			/* there are none */
pouu:
	/* print a short number of errors and a long image line */
	bits &= ~IMIN;			/* clear image ready flag */
	if (inptstat & EXPAND) {	/* are we expanding a macro */
	  /* expanding, switch buffers */
	  int	i;
	  int	t;

	  spmac |= MBUFSW;		/* flag print buffers were switched */
	  for (i=0; i < 80; i++) {	/* exchange the buffers */
	    t = mpbuf[i];		/* get a char */
	    mpbuf[i] = in[i];		/* move the char */
	    in[i] = t;			/* switch them */
	  }
	}
	hwmspbuf = 0;			/* clear store pointer for macro prnt */
	/* if expanding a macro or in rept gen, don't print line number */
	if (!(inptstat & (EXPAND | RPTGEN))) {
	  sprintf(xx, "%05d", lict);	/* print line number */
	  memcpy(&prnt[3], xx, 5);	/* copy in 5 chars */
	}
	line = 4;			/* indicate a full line to print */
	maxerr = 2;			/* maximum of 2 errors */

pouv:
	/* finish up the line and print it.  line has length, maxerr has
	 * number of errors that can be printed on the line
	 */
	if (hwerrf != 0) {		/* all possible error flags */
	  unsigned char	pos = 1;		/* starting print position */
	  int	i;

	  for (i = 0; i < 32; i++) {	/* check all 32 bits */
	    if (hwerrf & (1L << i)) {	/* see if flag on */
	      prnt[pos] = 0x40 + i;	/* output the code */
	      hwerrf &= ~(1 << i);	/* turn off the flag */
	      if (maxerr <= pos++)	/* max errors processed */
		break;			/* yes, quit */
	    }
	  }
	}
	if (line) {			/* long or short line to be printed */
	  char tmpbuf[121];

	  memcpy(tmpbuf, prnt, 40);	/* the short one first */
	  memcpy(&tmpbuf[40], in, 80);	/* then the image */
	  ppp(120, &tmpbuf[0], prnt[1]-' ');  /* print the long line */
	} else {
	  ppp(40, &prnt[0], prnt[1]-' ');  /* print the short line */
	}
	
	/* done printing or no printout required */
pouw:
	if (spmac & LPOOLM)		/* are we processing an lpool */
					/* in a macro expansion */
	  goto pouj;			/* yes, don't touch mpbuf */
	if (spmac & NOPGEN)		/* is nop being generated */
	  goto pouj;			/* yes don't touch mpbuf */
	if (spmac & MBUFSW) {		/* were print buffs switched */
	  int 	i;
	  for (i=0; i<80; i++) {		/* yes, switch back */
	    in[i] = mpbuf[i];		/* restore input buffer */
	    mpbuf[i] = ' ';		/* blank buffer */
      }
	} else {			/* no, just blank buffer */
	  int 	i;
	  for (i=0; i<80; i++)		/* yes, switch back */
	    mpbuf[i] = ' ';		/* blank buffer */
	}
	hwmspbuf = 0;			/* clear store ptr for macro print */
pouj:
	spmac &= ~MBUFSW;		/* clear prnt buf switch flag */
	return;				/* return, all done */
	
poux:
	maxerr = 20;			/* num of errors we can print */
	if (bits & CVFL)		/* prog cntr to be printed */
	  maxerr = 8;			/* yes, output 8 flags */
	goto pouv;			/* finish up short line */
}

/* list of symbol types for printing use.  This list is laid
 * out for look-up from symbol type and abs/rel bit
 */

char	sstb[] = "NNUULLCC PMMXYDDJKBBFF  ";

/* null, undef, literal, common, prog, mult, extern, and block
 * in that order by two's.  Also macro type items.
 */

/*
 * loch - format location counter type expression for printout
 * input - struct tval pointer containing following:
 *	 -	value = value to convert
 *	 -	type = type of the value
 *	 -	flags = cs/ds and abs/rel flags
 *	 - exts = flag to process enhanced inst set
 *	 - buff = pointer to output buffer
 */

void	loch(lcd, exts, buff)
struct	tval	*lcd;
int	exts;
char	*buff;
{
	int32	tmp;
	char	xx[10];

/*
prtval("loch", lcd);
*/

	switch (lcd->type) {			/* switch on section type */
	  case TYPU:
	  case TYPL:
	  case TYPP:
	  case TYPM:
	  case TYPX:
	  case TYSETSYM:
	    if (lcd->flags & CSDS)		/* is csect flag set */
	      buff[1] = '*';			/* csect indicator */
	}
	/* concatenate type code and abs/rel flag */
	tmp = ((lcd->type << 1) | ((lcd->flags & ABSREL) ? 1 : 0));
	buff[2] = sstb[tmp];			/* get the type char */
	if (buff[2] == 'C') {			/* is type common */
	  tmp = ((int32)(lcd->value & 0xff0000) >> 16);  /* get common blk # */
	  if (hwcmsize[tmp] & 0x80000000)	/* is it ssect */
	    buff[2] = 'S';			/* show as ssect */
	}
	if (exts)			/* are we processing oprnd data */
	  if (eisflg & EISOPC)		/* is this a context instr */
	    buff[2] = '#';		/* store # in output line */
	eisflg &= ~EISOPC;		/* clear context flag */
	sprintf(xx, "%05X", lcd->value & 0xfffff);	/* store 5 hex chars */
	memcpy(&buff[3], xx, 5);	/* copy in 5 hex chars */
	return;				/* return */
}

#ifdef OLDWAY
static char my_buffer[132];
#else
#define my_buffer buffer
#endif

/* 
 * ppp - output data to list output
 * intput 	byte count
 *		buffer address 
 *		error line flag 0=none, else print to stderr
 * output	0 line on same page, 1 new page started
 */

int	ppp(count, buffer, eflag)
int	count;
char 	*buffer;
int	eflag;
{
	int i = count;
#ifdef DPPP
printf("ppp entry\n");
#endif
	while (my_buffer[--i] == ' ' && i >1)
	  ;
	my_buffer[++i] = 0;

/* NOTE - somewhere here abouts, we should check line count and
 *	  output header line for top of forms processing.  We
 *	  should also check for EOF on output and abort if at EOF.
 */
	if (eflag) 			/* print line to stderr? */
	  fprintf(stderr, "%s\n", my_buffer);  /* print the line */
	if (option & LO) {		/* is lo option set? */
#ifdef NO_HEADER
	  if (nlpr == 0) {		/* new page print header */
	    i = TCWSIZE;
	    while (ahdr[--i] == ' ' && i >1) ;
	    ahdr[++i] = 0;
	    printf("%s\n", ahdr);	/* print header to stdout */
	    ahdr[i] = ' ';
	  }
	  nlpr++;			/* bump line count */
#endif
	  printf("%s\n", my_buffer);	/* print line to stdout */
	}
#ifdef DPPP
printf("ppp exit\n");
#endif
	return(0);		/* not top of form yet */
}

/*
 * iread - read input file
 * input	num - number of bytes requested
 *		buff - buffer address
 * output	line number or 0 for EOF
 */

int32	iread(num, buff)
int	num;
char	*buff;
{

	int	i, val, j;

	memset(buff, ' ', num);		/* blank the input buffer */
	if (!(PASS & 1)) {		/* is this pass 1 */
	  /* pass 2, read the temp file */
	  for (i = 0; i < num+1; i++) {
	    if((val = getc(tempfd)) == EOF) return (0);	/* exit on EOF */
	    if (val == '\n')break;	/* stop reading on newline */
	    buff[i] = val;		/* put char in buffer */
	  }
	  return (++lice);		/* return line count */
	}
	/* pass 1, read std input */
again:
	for (i = 0; i < num; i++) {
	  if((val = getchar()) == EOF) break; /* exit loop on EOF */
	  if (val == '\t') {		/* if tab, special processing */
	    val = ' ';			/* replace tab with space */
	    while (i < num - 1) {	/* feed blanks for spaces */
#ifndef CAID
	      /* if comment use mod 4 tabs */
	      if (*buff == '*' || sudo || (*buff == ' ' && buff[1] == '.')) {
		if (i==7 || i==15 || i==23 || i==31 || i==39 || i==47 ||
		  i==55 || i==63 || i==71 ||
		  i==3 || i==11 || i==19 || i==27 || i==35 || i==43 ||
		  i==51 || i==59 || i==67)
#else
	      /* if comment use mod 8 tabs */
	      if (*buff == '*') {
		if (i==7 || i==15 || i==23 || i==31 || i==39 || i==47 ||
		  i==55 || i==63 || i==71)
#endif
		  break;		/* we are there */
	      } else {			/* else use mpx tabs */
		if (i==9 || i==19 || i==35 || i==47 || i==71)
		  break;		/* we are there */
	      }
	      buff[i++] = ' ';		/* put in blank */
	    }
	  }
	  if (val == '\n')break;	/* stop reading on newline */
	  buff[i] = val;		/* put char in buffer */
	}
	if (val != '\n' && val != EOF) {
	  while ((j = getchar()) != EOF && j != '\n');	/* loop till '\n' */
	  buff[80] = '\n';		/* put newline at end of line */
	  val = j;			/* save terminator */
	}
	/* put input out to temp file if not EOF */
	if (val != EOF) {
	  for (j=0; j < i; j++) {
	    if(fputc(buff[j], tempfd) == EOF) {
	      perror(tempfile);
	      error ("Fatal assembler error (tempfile %s)", tempfile);
	      abortm(0);		/* abort the assembler */
	      /* no return */
	    }
	  }
	  if(fputc('\n', tempfd) == EOF) {
	    perror(tempfile);
	    error ("Fatal assembler error (tempfile %s)", tempfile);
	    abortm(0);		/* abort the assembler */
	    /* no return */
	  }
fflush(tempfd);
	}
	if (val != EOF)return (++lice);		/* return line count */
	/* we have an EOF on the input, get next file */

	/* assemble all the files given */
	if ((infile = inputf[numfproc++])) {	/* get file to process */

	  if (freopen(infile,"r",stdin)==(FILE *)NULL) {
	    perror(infile);
	    error ("Fatal assembler error (input file %s)", infile);
	    abortm(0);			/* abort the assembler */
	    /* no return */
      }
	  curfile = infile;		/* set current file */
	} else return(0);		/* return EOF */
	goto again;			/* read next file */
	
}

/*
 * pbyt - put byte in output buffer
 * input - byte to output
 * output - none
 */

void	pbyt(chr)
char	chr;
{
	if (hwmspbuf < 80)		/* limit output to 80 chars */
	  mpbuf[hwmspbuf++] = chr;	/* put char in print buffer */
	return;
}

