/* macro.c */

#include "defs.h"
#include <stdio.h>

/* #define DBUGM0 */
/* #define DBUGM1 */
/* #define DBUGM1X */
/* #define DBUGM2 */
/* #define DBUGIF */
/* #define SETD */
/* #define DEBUG */

#ifdef DOS
#include <io.h>
#include <string.h>
#include <malloc.h>

void	macinit();
void	macer();
struct	symbol	FAR *libsch(char *);
int	readrec();
int	prim();
void	defmpro();
void	endmpro();
void	exitmp();
void	formp();
void	formexp();
void	gotop();
void	ifpro();
void	macexp();
void	mbyt(unsigned char);
void	reptp();
void	endrp();
void	setpro();
#endif

extern	char	*macfile;		/* default of m.mpxmac */
int	macopen = 0;			/* non zero when mac fileopen */
FILE	*macfd;

/*
 * macinit - open m.mpxmac file for unblocked read
 */

void	macinit()
{
	/* open macro library file */
	if (macfile) {			/* is there a macro file */
#ifdef DOS
	  if ((macfd = fopen(macfile,"rb")) <= 0) {
#else
#ifdef mpx
	  if ((macfd = fopen(macfile,"ru")) <= 0) {
#else
	  if ((macfd = fopen(macfile,"r")) == 0) {
#endif
#endif
	    perror(macfile);
	    error ("Fatal assembler error (macfile file %s)", macfile);
	    macer();
   	  }
	  macopen++;			/* show mac open */
	  fseek (macfd, (int32)0, 0);	/* rewind mac file */
	  return;			/* return */
	}

}

/* abort routines */

/* error on mac file */
void	macer()
{
	abrtm1("AS29");			/* abort with AS29 error */
	/* no return */
}

static unsigned char	*libbuf;	/* buffer pointer to 48w record */
static	struct	tval	macd = {	/* macro definition entry */
		TYMACDEF,	/* type is macro definition */
		0,		/* dsect/abs */
		0,		/* not used */
		0		/* no value yet */
};

/*
 * libsrch - search macro library
 * input - name of macro to search for
 * output - macss symbol table pointer
 */

struct	symbol	FAR *libsch(name)
char	*name;
{
	char	ucname[24];		/* storage for u/c macro name */
	uchrfp	macp;			/* macro storage pointer */
	uchrfp	chrp;			/* malloc storage pointer */
	int	rcnt;			/* current record count */
	unsigned int chrcnt;		/* number of chars allocated */
	unsigned int maccnt;		/* number of chars in macro */
	char	protoflg;		/* into prototype flag */
	char	parflg;			/* parameter coming flag */
	int	i;
	unsigned char	libcnt=0;	/* max lib count */
	unsigned char	*tpt;		/* temp prototype pointer */

	if (!macopen)			/* is file open */
	  return((struct symbol FAR *)0);	/* no return not found */
	memcpy(ucname, name, 8);	/* copyin macro name */
	ucname[8] = '\0';		/* null terminate string */
	str2upr(ucname);		/* make uppercase */
	fseek (macfd, (int32)0, 0);	/* rewind mac file */
#ifdef DBUGM1X
printf("looking for macro %0.8s\n", ucname);
#endif
	/* prime the input buffer */
	if (prim() == EOF)		/* error if EOF here */
 	  abortm("** UNEXPECTED EOF ON MACRO LIBRARY FILE **");
#ifdef DBUGM1
printf("buffer primed\n");
#endif
#ifdef DOS
	chrp = (uchrfp)_fmalloc(256);	/* get some memory */
#else
	chrp = (uchrfp)malloc(256);	/* get some memory */
#endif
	if (!chrp)			/* did we get it */
 	  abortm("** UNABLE TO ALLOCATE MEMORY FOR MACRO STORAGE **");
	macp = (uchrfp)chrp;		/* point to macro storage */
	chrcnt = 256;			/* chars allocated */
	protoflg = 0;			/* not in prototype yet */
	maccnt = 0;			/* macro chars processed */
reread:
	while (readrec() != EOF) {	/* read a record,search till EOF */
	  if (*libbuf == 0xef)		/* 1st byte of a record */
	    goto libsc3;		/* either 1st or middle record */
	  if (*libbuf != 0xcf)		/* last record of protype */
	    continue;			/* no, ignore this record */
	  if (protoflg) {		/* 1st or last record */
	    protoflg = 0;		/* it was the last record */
	    continue;			/* done with prototype, get next rec */
	  }
	  goto libsc4;			/* same record is 1st and last record */
libsc3:
	  if (protoflg)			/* in a prototype */
	    continue;			/* no, a middle record */
	  protoflg++;			/* indicate we started a prototype */
	  /* come here when we are starting a protype */
libsc4:
	  if (memcmp(&libbuf[8], ucname, 8))	/* is this our macro */
	    continue;			/* no, try again */
#ifdef DBUGM1
printf("found macro %0.8s\n", &libbuf[8]);
#endif
	  /* come here on 1st record of the found protype */
	  if ((rcnt = libbuf[1]) == 0)	/* get record byte count */
	    /* abort if zero count */
	    abortm("** BAD MACRO ENCOUNTERED DURING MACRO SEARCH **");
	  parflg = 0;			/* no parameters yet */
	  rcnt -= 10;			/* cnt less id portion */
	  tpt = libbuf;			/* temp pointer to buffer */
	  tpt += 16;			/* where data starts */
libmv2:
#ifdef DBUGM1X
printf("about to move %x bytes\n", rcnt);
#endif
	  if ((rcnt+maccnt) > chrcnt) {	/* will we overrun the storage */
	    /* yes, we need to get 256 bytes more macro storage */
#ifdef DOS
	    {
	    uchrfp work;		/* work pointer */
	    work = (uchrfp)_fmalloc(chrcnt+256);
	    if (!work)			/* did we get it */
 	      abortm("** UNABLE TO ALLOCATE MEMORY FOR MACRO STORAGE **");
	    for (i = 0; i < chrcnt; i++) 
	      work[i] = chrp[i];	/* copy the char */
	    _ffree((uchrfp)chrp);	/* deallocate the old */
	    chrp = work;		/* set the new address */
	    }
#else
	    chrp = (uchrfp)realloc((uchrfp)chrp, chrcnt+256);
	    if (!chrp)			/* did we get it */
 	      abortm("** UNABLE TO ALLOCATE MEMORY FOR MACRO STORAGE **");
#endif
	    chrcnt += 256;		/* new amount of storage */
	    macp = chrp+maccnt;		/* new storage address */
	  }
	  maccnt += rcnt;		/* add in new byte count */
	  for (i=0; i<rcnt; i++) {	/* copy in the record */
	    if (parflg) {		/* is next char a paramter */
	      parflg = 0;		/* yes, see if we have a new high */
	      if (*tpt >= libcnt) {	/* new gtr than old */
	        libcnt = *tpt;		/* set new value */
	        libcnt++;		/* make it a count */
	      }
	    } else
	    if (*tpt == '%')		/* is parameter coming */
	      parflg++;			/* flag that it is coming */
	    *macp++ = *tpt++;		/* save the character */
	  }

	  if (*libbuf == 0xcf) {	/* was this final record */
	    /* resize storage area */
#ifdef DOS
	    {
	    int	i;
	    uchrfp work;		/* work pointer */
	    work = (uchrfp)_fmalloc(maccnt);
	    if (!work)			/* did we get it */
 	      abortm("** UNABLE TO ALLOCATE MEMORY FOR MACRO STORAGE **");
	    for (i = 0; i < maccnt; i++) 
	      work[i] = chrp[i];	/* copy the char */
	    _ffree((uchrfp)chrp);	/* deallocate the old */
	    chrp = work;		/* set the new address */
	    }
#else
	    chrp = (uchrfp)realloc((uchrfp)chrp, maccnt);
#endif
	    macd.tmp = maccnt;		/* set macro byte count */
	    macd.flags = libcnt;	/* set parameter count */
	    macd.value = (unsigned int32)chrp;	/* set prototype address */
	    /* put new macro definition if macro symbol table */
#ifdef DBUGM1X
printf("macro %0.8s defined with %d params, %x chars read into %x\n",
  ucname, libcnt, maccnt, chrp);
#endif
	    return(macss(&macd, ucname, MACADD)); /* return macss pointer */
	  }
	  if (readrec() == EOF)		/* read a record, error if EOF */
 	    abortm("** UNEXPECTED EOF ON MACRO LIBRARY FILE **");
	  if ((rcnt = libbuf[1]) == 0)	/* get record byte count */
	    /* abort if zero count */
	    abortm("** BAD MACRO ENCOUNTERED DURING MACRO SEARCH **");
	  tpt = libbuf;			/* temp pointer to buffer */
	  tpt += 6;			/* where data starts */
	  goto libmv2;			/* copyin new record */
	}
	return((struct symbol FAR *)0);	/* no return not found */
}

static	unsigned char	sysbuf[7680];	/* read buffer */
static	int	recnum = 0;		/* record number */
static	int	currec;			/* current record # (1-40) */

/*
 * readrec - read a 48w macro record
 */

int	readrec()
{
	/* see if at EOF record */
	if ((sysbuf[currec*192] == 0x0f) && (sysbuf[(currec*192) + 1] == 0))
	  return(EOF);			/* return EOF */
	if (!recnum)			/* reprime the input if no records */
	  if (prim() == EOF)		/* prime the input buffer */
	    return(EOF);		/* return EOF */
	libbuf = &sysbuf[currec * 192];	/* where this input is */
	currec++;			/* next record */
	recnum--;			/* decr record count */
	return(192);			/* 192 bytes in libbuf */
}

/*
 * prim - prim the input record
 */

int	prim()
{
	int	rv;

	if((rv = fread(sysbuf, 1, 7680, macfd) == EOF))
	  return(EOF);			/* return EOF */
	currec = 0;			/* clear record counter */
	recnum = 40;			/* 40 records @ 48w (192b) per record */
#ifdef DBUGM1
printf("prime read %x chars, %d records\n", rv, recnum);
#endif
	return(rv);			/* return the count */
}

/*****************************/
/* macro processing routines */
/*****************************/

extern char	dpflags;	/* datapool flags */
unsigned char	hwdpnum;	/* datapool number */
int	level;			/* number of levels below repeat */

/* stack is the current macro level definition pointer */
/* stackp points to the next level.  stackp is type macxe */
/* mpp points to the current level.  mpp is type macxe */
/* stackp->pcnt has the parameter count for the macro */
/* stackp->clev has pointer to base of 6w * #parameters storage in stk */
/* 		this area is for parameter substitution generation */
/* stackp->maca has pointer to the macro prototype (hwcma->desc.value) */

struct	macxe	stack[256];	/* stack for upto 256 parameters */
struct	macxe	*stackp = stack; /* pointer to stack */
struct	macxe	*mpp;		/* macro prototype pointer in stack */
uchrfp	hwrepsp;		/* repeat prototype storage pointer */

/* dmstp points to the macro symbol table entry defined by macss */
/* this is also the address stored in the symbol table entry for this macro */
/* dmstp->desc.value then points to the actual macro storage */
/* dmstp->desc.tmp has the size of the macro in bytes */
/* dmstp->desc.flags has the number of parameters */
/* dmstp->sym has the macro name */

uchrfp	hwcmac; 		 /* holds ptr to body of latest form/macro */
uchrfp	hwcmacp;  		/* holds a chaining pointer to form list */
/* struct macro *macp;		/* address of macros */
char	*stkp;			/* pointer to parameter expansion area in stk */
char	stk[8000];		/* macro parameter substitution area */
/* stk contains multiple 24 char parameter names used during expansion */
/* it is pointed to by the level pointers in stackp->clev */

struct	symbol	FAR *dmstp;		/* pointer to macro symbol entry */
unsigned char	macparam[8*384];	/* storage for dummy macro parameters */
unsigned char	*macdptr;		/* pointer to dummy parameter storage */
uchrfp	macsp;				/* pointer for macro body storage */
unsigned char 	defcnt;			/* macro parameter count */
int16	maccnt;				/* number of chars in macro */
int16	high;				/* count of char in macro storage */
struct	symbol	FAR *head;		/* current macro definition */

static	struct	tval	macx = {	/* macro definition entry */
		TYMACDEF,	/* type is macro definition */
		0,		/* dsect/abs */
		0,		/* not used */
		0		/* no value */
};

/*
 * defmpro - process macro definition
 */

void	defmpro()
{
#ifdef MACD
printf("enter defmpro: \n");
#endif
	if (macstate & CONDSCAN)	/* are we skipping source */
	  goto defmproe;		/* yes */
	if (macstate & RSCAN)		/* are we in a rept scan */
	  goto defmproe;		/* yes */
	if (macstate & EXPAND)		/* are we expanding */
	  goto defmprob;		/* yes */
	if (!(macstate & DEFMBODY))	/* are we in a prototype body */
	  goto defmpro1;		/* no */
defmprob:
	seterr ('A');			/* set addressing error */
defmproe:
	/* unstring all the parameters */
	do {				/* unstring till space term */
	  unst(0x80080000L);		/* term on space or comma */
	} while (hbstac[0] != ' ');	/* terminator a space */
	return;				/* they are unstrung, exit */

defmpro1:				/* process the macro definition */
	if (!(PASS & 1)) {		/* are we in pass 1 */
	  spmac |= DEFFRM2;		/* no, set pass 2 defm-form bit */
	  goto defmpro3;		/* don't reenter macro in sym tab */
	}
	/* pass 1 processing */
	macdptr = macparam;		/* reset dummy parameter pointer */
	/* define macro in symbol table */
	macx.value = macx.tmp = macx.flags = 0;	/* insure zero description */
#ifdef MACD
printf("defmpro1: calling ss label = %0.8s\n", label);
#endif
	dmstp = ss (&macx, csnegate(label));  /* enter macro name */
#ifdef MACD
printf("defmpro1: ss return dmstp = %x\n", dmstp);
#endif
	macx.value = macx.tmp = macx.flags = 0;	/* insure zero description */
#ifdef MACD
printf("defmpro1: calling macss\n");
#endif
	head = macss (&macx, label, MACADD);	/* enter in macro storage */
				/* and get 256 bytes of initial storage */
#ifdef MACD
printf("defmpro1: macss return head = %x\n", head);
prtval("defmpro1 head", &head->desc);
#endif
	defcnt = 0;			/* zero number of arguments */
	macsp = (uchrfp)head->desc.value;	/* where storage is */
	high = head->desc.tmp;		/* count of chars allocated */

defmpro3:				/* pass 2 merge point */
	do {				/* scan off all the parameters */
	  unst(0x80080000L);		/* term on sp or comma */
	  if (*usname == ' ')		/* any name */
	    break;			/* no, exit loop */
	  if (spmac & DEFFRM2)		/* in pass 2 defm-form scan */
	    continue;			/* yes, don't save args */
#ifdef MACD
printf("defmpro3 entry unstrung usname = %0.8s\n", usname);
#endif
	  memcpy(macdptr, usname, 8);	/* copy into stack */
	  macdptr += 8;			/* bump to next save loc */
	  defcnt++;			/* bump the count too */
	} while (hbstac[0] == ',');	/* loop on comma, more parameters */
	if (!(spmac & DEFFRM2)) {	/* in pass 2 defm-form scan */
	  /* now update macro symbol entry for number of parameters */
	  head->desc.flags = defcnt;	/* set the count */
	  /* and update symbol table entry with macro symbol table address */
	  dmstp->desc.value = (unsigned int32)head; /* macro def entry addr */
	  maccnt = 0;			/* zero number of chars in macro */
#ifdef MACD
printf("defmpro3: dmstp = %x, head = %x\n", dmstp, head);
prtval("defmpro3 dmstp", &dmstp->desc);
prtval("defmpro3 head", &head->desc);
#endif
	}
#ifdef DEBUG
printf("defmpro: exiting\n");
{
char *p = (char *)head->desc.value;
printf("defining macro %0.8s, addr = %x, count = %x, hcnt = %x\n",
 head->sym, p, maccnt, head->desc.tmp);
prtsymt();				/* dump the symbol table */
}
#endif
#ifdef MACD
printf("defpro - setting DEFMBODY\n");
#endif
	macstate |= DEFMBODY;		/* we are going into a macro body */
	return;				/* let it come in */
}

/*
 * endmpro - process endm directive
 */

void	endmpro()
{
#ifdef MACP
printf("endmpro: entry\n");
#endif
	if (macstate & EXPAND)		/* expanding a macro */
	  goto endm6;			/* yes, we are expanding a macro */
	if (macstate & DEFMBODY)	/* are we in the body */
	  goto endm11;			/* yes, no error */
	if (macstate & (CONDSCAN | RSCAN))	/* skipping src or rept scan */
	  return;			/* yes, just return */
endm5:					/* addressing error */
	seterr ('A');			/* set addressing error */
	goto endm10;			/* reset flags, and exit */

endm6:					/* we are expanding a macro */
	stackp--;			/* dump last macro def in param stack */
	if (stackp == stack)		/* are we at bottom of stack */
	  goto endm63;			/* yes */
	if (level == 0)			/* is macro depth lev in rept zero */
	  goto endm8;			/* yes */
	level--;			/* decr the depth level in rept */
	goto endm8;			/* keep looking for prototype ptr */

endm63:					/* we are at bottom of stack */
	level = 0;			/* clear the rept level */
	stkp = stk;			/* reset parameter stack pointer */
	stackp = stack;			/* reset macro level stack */
	mpp = stackp;			/* show base as this level */
#ifdef MACP
printf("endm63: stackp = %x, stack = %x level = %d\n",stackp, stack, level);
printf("endm63: stkp = %x, stk = %x mpp = %x\n",stkp, stk, mpp);
#endif
	/* reset macro status flags */
/* printf("endm63 - resetting all flags\n"); */
	macstate &= ~((int16)(MACREP|FORMGET|CALLUS|EXPAND|
	   UNSTFLAG|REUNSTF|DEFMBODY));
	goto endm10;			/* all done with macro expansion */

endm8:
#ifdef MACP
printf("endm8: stackp = %x, stack = %x level = %d\n",stackp, stack, level);
#endif
	stackp--;			/* previous level */
	/* set new expansion pointer, allowing 24 chars for each parameter */
 	stkp = (char *)(stackp->clev + (stackp->pcnt * 24));
	mpp = stackp;			/* stack ptr for this level */
	hwcmac = stackp->maca;		/* prototype storage pointer */
	stackp++;			/* next available level */
#ifdef MACD
printf("endm8-2: stackp = %x, stack = %x level = %d\n",stackp, stack, level);
printf("endm8-3: stkp = %x, stk = %x mpp = %x\n",stkp, stk, mpp);
#endif
endm10:
#ifdef MACP
printf("endm10 - resetting DEFMBODY flag\n");
#endif
	macstate &= ~DEFMBODY;		/* clear in defm body flag */
	inptstat &= ~DEFMBODY;		/* clear in defm body flag */
	spmac &= ~DEFFRM2;		/* clear pass2 defm-form flag */
	return;				/* done with pass 2 defm */

/* done with macro prototype definition */
endm11:
	macdptr = macparam;		/* reset param pointer to start */
	if (spmac & DEFFRM2)		/* in pass 2 def body */
	  goto endm10;			/* clear flags and exit */

	mbyt((unsigned char)0xff);	/* copy out the terminator */
	/* now update macro byte count in mac symbol entry */
	head->desc.tmp = maccnt;	/* bytes read in for macro */
	/* update the macro parameter count */
	head->desc.flags = defcnt;	/* set the count */
	/* now realloc macro storage to delete unused bytes */
	/* also reset address of macro in macro symbol entry */
#ifdef DEBUG
{
char *p = (char *)head->desc.value;
printf("pass 1 stored macro %0.8s, addr = %x, count = %x, hcnt = %x\n",
 head->sym, p, maccnt, head->desc.tmp);
prtsymt();				/* dump the symbol table */
}
#endif
#ifdef DOS
	    {
	    int	i;
	    uchrfp work;		/* work pointer */
	    uchrfp work1;		/* work pointer */
	    work = (uchrfp)_fmalloc(maccnt);
	    if (!work)			/* did we get it */
 	      abortm("** UNABLE TO ALLOCATE MEMORY FOR MACRO STORAGE **");
	    work1 = (uchrfp)head->desc.value;	/* get old pointer */
	    for (i = 0; i < maccnt; i++) 
	      work[i] = work1[i];	/* copy the char */
	    _ffree((uchrfp)work1);	/* deallocate the old */
	    head->desc.value = (unsigned int32)work;	/* set the new addr */
	    }
#else
	head->desc.value = 
	  (unsigned int32)realloc((uchrfp)head->desc.value, maccnt);
#endif
#ifdef DEBUG
{
char *p = (char *)head->desc.value;
printf("stored macro %0.8s, addr = %x, count = %x, hcnt = %x\n",
 head->sym, p, maccnt, head->desc.tmp);
}
prtsymt();				/* dump the symbol table */
#endif
#ifdef JUNK
	maccnt = 0;			/* reset the count */
	macsp = (uchrfp)head->desc.value;
#endif
	goto endm10;			/* clear flags and exit */
}

/*
 * exitmp - exit macro processing
 */

void	exitmp()
{
	if (!yeanay())			/* are we assembling */
	  return;			/* no, don't process this exitm */
	if (macstate & EXPAND) {	/* are we expanding macro */
	  endmpro();			/* yes, terminate it early */
	  return;			/* return after ending macro */
	}
	/* not expanding, we have an error */
	seterr ('A');			/* set addressing error */
/* printf("exitmp - resetting DEFMBODY flag\n"); */
	macstate &= ~DEFMBODY;		/* clear in defm body flag */
	inptstat &= ~DEFMBODY;		/* clear in defm body flag */
	spmac &= ~DEFFRM2;		/* clear pass2 defm-form flag */
	return;				/* done with pass 2 defm */
}

static	struct	tval	formx = {	/* form definition entry */
		TYFRM,		/* type is form definition */
		0,		/* dsect/abs */
		0,		/* not used */
		0		/* no value */
};

/*
 * formp - form processing
 */

void	formp()
{
	int32	bitv;

	if (yeanay()) {			/* are we assembling */
	  /* we are assembling */
	  /* if we are expanding a macro or generating rept code, error */
	  if (macstate & (EXPAND|RPTGEN)) {	/* are we expanding */
	    seterr ('A');		/* set addressing error */
	    /* unstring all the parameters */
	    do {			/* unstring while comma term */
	      unst(0x80080000L);		/* term on space or comma */
	    } while (hbstac[0] == ',');	/* terminator on non comma */
	    return;			/* they are unstrung, exit */
	  }
					/* process the form definition */
	  if (!(PASS & 1)) {		/* are we in pass 1 */
	    spmac |= DEFFRM2;		/* no, set pass 2 defm-form bit */
	    goto formp3;		/* don't reenter name in sym tab */
	  }
	  /* pass 1 processing */
	  macdptr = macparam;		/* reset dummy parameter pointer */
	  /* define form in symbol table */
	  /* insure zero description */
	  formx.value = formx.tmp = formx.flags = 0;
	  dmstp = ss (&formx, csnegate(label));  /* enter macro name */
	  /* insure zero description */
	  formx.value = formx.tmp = formx.flags = 0;
	  head = macss (&formx, label, MACADD);	/* enter in macro storage */
				/* and get 256 bytes of initial storage */
	  defcnt = 0;			/* zero number of arguments */
	  macsp = (uchrfp)head->desc.value;	/* where storage is */
	  maccnt = 0;			/* number of chars stored */
	  high = head->desc.tmp;	/* count of chars allocated */
	}
formp3:					/* pass 2 merge point */
	/* get the bit length */
	val(0);				/* nothing unstrung yet */
	bitv = inac.value & 0xfffffL;	/* the value */
	if (bitv > 254) {		/* no more than 254 bits allowed */
	  if (yeanay())			/* are we assembling */
	    seterr ('H');		/* set defm/form error */
	  spmac &= ~DEFFRM2;		/* clear pass 2 defm-form bit */
	  return;			/* can't do anything with it */
	}
	inptstat |= FORMSCAN;		/* set form scan flag */
	if (yeanay())			/* are we assembling */
	  mbyt((unsigned char)bitv);	/* yes, copy out the value */
	inptstat &= ~FORMSCAN;		/* clear in form body flag */
	if (hbstac[0] == ',')		/* more terms to get */
	  goto formp3;			/* yes, get next one */
	inptstat |= FORMSCAN;		/* set form scan flag */
	if (yeanay())			/* are we assembling */
	  mbyt((unsigned char)0xff);	/* copy out the terminator */
	inptstat &= ~FORMSCAN;		/* clear in form body flag */
	spmac &= ~DEFFRM2;		/* clear pass2 defm-form flag */
	/* now update macro byte count in mac symbol entry */
	head->desc.tmp = maccnt;	/* bytes read in for macro */
	/* now realloc macro storage to delete unused bytes */
	/* also reset address of macro in macro symbol entry */
#ifdef DOS
	    {
	    int	i;
	    uchrfp work;		/* work pointer */
	    uchrfp work1;		/* work pointer */
	    work = (uchrfp)_fmalloc(maccnt);
	    if (!work)			/* did we get it */
 	      abortm("** UNABLE TO ALLOCATE MEMORY FOR MACRO STORAGE **");
	    work1 = (uchrfp)head->desc.value;	/* old buffer address */
	    for (i = 0; i < maccnt; i++) 
	      work[i] = work1[i];	/* copy the char */
	    _ffree((uchrfp)work1);	/* deallocate the old */
	    head->desc.value = (unsigned int32)work;	/* set the new addr */
	    }
#else
	head->desc.value =
	  (unsigned int32)realloc((uchrfp)head->desc.value, maccnt);
#endif
	return;				/* done with form */
}

/*
 * formexp - form expansion processing
 */

void	formexp()
{
	inptstat |= FORMGET;		/* indicate stripping down a form */
	/* get where it is stored */
	hwcmac = (uchrfp)dmstp->desc.value;
	hwcmacp = hwcmac;		/* save pointer for form prototype */
	if (yeanay()) {			/* are we assembling */
#ifdef REPTR
         LW        1,TALLS1        INDICATE A REQUEST WAS PERFORMED
         LW        3,lict        FOR A FORM  FROM THIS LINE NUMBER
         ZMW       REPTYPE         INDICATE SYMBOL REPORT TO XREF
         BL        REPTR          SO IT WILL SHOW UP IN THE XREF
#endif
	  tall();			/* allocate current form label */
	}
	vfd();				/* have vfd do the processing */
}

static	int	gotoc;			/* holds count during goto list scan */
static	char	gotocb;			/* flag for goto list find/nofind */
static	char	hwscnhp[16];		/* prospective name for cond scan */

/*
 * goto processor
 * input - normal
 *
 */

void	gotop()
{
	struct	tval	theval;

	unst(0x80080000L);		/* get item, terminate by sp or , */
	memcpy (hwscnhp, usname, 8);	/* move 8 bytes of label */
	if (hbstac[0] == ' ')		/* test for unconditional goto */
	  goto gotope;			/* space means all done */
	theval = val (1);		/* tell val already unstrung */
	gotoc = -((int)(theval.value & 0xffffffL));	/* use as counter */
	gotocb = 0;			/* clear found flag */
	while (hbstac[0] == ',') {	/* loop till no more elements */
	  unst(0x80080000L);		/* get item, terminate by sp or , */
	  if (++gotoc == 0) {		/* bumpcnt, are we there yet */
	    /* save name to goto */
	    memcpy (hwscnhp, usname, 8);  /* move 8 bytes of label */
	    gotocb++;			/* set found flag */
	  }
	}
	if (!gotocb)			/* was the place in list found */
	  return;			/* return, goto not to be done then */
gotope:
	if (!yeanay()) return;		/* if not assembling return */
	memcpy (lablscan, hwscnhp, 8);	/* save label to scan for */
	macstate |= CONDSCAN;		/* show we are in a conditional scan */
	return;				/* do next input line */
}

static	int	prevrelo;		/* holds previous if relation op */
static	int	ifet;			/* holds temp true/false */
static	char	unstk = 0;		/* invalid parameter check flag */
static	char	ifflg = 0;		/* symbol defined/undefined flag */

/*
 * ifpro - conditional if processor
 */

void	ifpro()
{
	int	temp;
	int	i = 0;
	char	dummy[16];
	struct	symbol	FAR *stp;

#ifdef DBUGIF
printf("ifpro: label = %0.8s, usname = %0.8s binop = %x\n",
 label, usname, curops->binop);
#endif
	prevrelo = 0;			/* clear out pointer to prev rel op */
	if (curops->binop > 3) {	/* is it ifp/ifa */
	  /* it is an ifp/ifa pseudo op */
	  unst(0x00080000L);		/* terminate on comma only */
	  if (!(PASS & 1))		/* in pass 2 */
	    /* we are in pass 2, check delim flag */
	    if (unstk) {		/* should end in param, not delim */
	      seterr ('E');		/* set faulty parm list error */
/* printf("1E\n"); */
	      unstk = 0;		/* clear the flag */
	    }
	  unstk = 0;			/* clear the flag */
	  if (inscnt >= 73)		/* was comma found */
	    goto iferr;			/* no, go mark error */
	  goto ifprod;			/* yes, go get place to go to */
	}
	if (curops->binop < 2) {	/* is it ift/iff */
	  /* it is ift/iff op */
ifpro2:
	  unst(0x81fd0000L);		/* unstring a term */
#ifdef DBUGIF
printf("ifpro2: label = %0.8s, usname = %0.8s\n", label, usname);
#endif
	  if (!(PASS & 1)) {		/* are we pass 2 */
	    if (unstk) {		/* should end in param, not delim */
	      seterr ('E');		/* set faulty parm list error */
/* printf("2E\n"); */
	      unstk = 0;		/* clear the flag */
	    }
	  }
	  i = 0;			/* clear type */
	  unstk = 0;			/* clear the flag */
	  if (*usname == ' ')		/* is token blank */
	    goto ifpro9;		/* yes, skip blanks and continue */
	  memcpy(dummy, usname, 8);	/* copy to a dummy loc */
	  str2upr(dummy);		/* make upper case */
	  if (!(memcmp(".AND.", dummy, 4))) {	/* is this an and */
	    i = 1;			/* set type flag */
	    goto find;			/* go get the next element */
	  }
	  if (!(memcmp(".OR.", dummy, 4))) {	/* is this an or */
	    i = 2;			/* set type flag */
	    goto find;			/* go get the next element */
	  }
	  if (!(memcmp(".LT.", dummy, 4))) {	/* is this a lt */
	    i = 3;			/* set type flag */
	    goto find;			/* go get the next element */
	  }
	  if (!(memcmp(".GT.", dummy, 4))) {	/* is this a gt */
	    i = 4;			/* set type flag */
	    goto find;			/* go get the next element */
	  }
	  if (!(memcmp(".GE.", dummy, 4))) {	/* is this a ge */
	    i = 5;			/* set type flag */
	    goto find;			/* go get the next element */
	  }
	  if (!(memcmp(".LE.", dummy, 4))) {	/* is this a le */
	    i = 6;			/* set type flag */
	    goto find;			/* go get the next element */
	  }
	  if (!(memcmp(".EQ.", dummy, 4))) {	/* is this a eq */
	    i = 7;			/* set type flag */
	    goto find;			/* go get the next element */
	  }
	  if (!(memcmp(".NE.", dummy, 4))) {	/* is this a ne */
	    i = 8;			/* set type flag */
	    goto find;			/* go get the next element */
	  }
	  /* no logical op, process the old one */
	  /* inac has value */
	  val(1);			/* evaluate unstrung element */
	  temp = (int)inac.value;	/* get the value */
#ifdef DBUGIF
printf("ifpro: prevrelo = %d, ifet = %d i = %d\n", prevrelo, ifet, i);
prtval("ifpro val", &inac);
#endif
	  switch (prevrelo) {		/* switch on condition */
	    case 0:			/* nothing found */
	      ifet = (int)temp;		/* save the value */
	      goto ifpro9;		/* get next element */
	    case 1:			/* and operator */
	      ifet &= temp;		/* and it with temp */
	      goto ifpro9;		/* get next element */
	    case 2:			/* or operator */
	      ifet |= temp;		/* or it with temp */
	      goto ifpro9;		/* get next element */
	    case 3:			/* or operator */
	      if (ifet < temp)		/* lt op */
	        goto ifpro5;		/* true cond */
	      break;			/* false cond */
	    case 4:			/* gt operator */
	      if (ifet > temp)		/* gt op */
	        goto ifpro5;		/* true cond */
	      break;			/* false cond */
	    case 5:			/* ge operator */
	      if (ifet >= temp)		/* ge op */
	        goto ifpro5;		/* true cond */
	      break;			/* false cond */
	    case 6:			/* le operator */
	      if (ifet <= temp)		/* le op */
	        goto ifpro5;		/* true cond */
	      break;			/* false cond */
	    case 7:			/* eq operator */
	      if (ifet == temp)		/* eq op */
	        goto ifpro5;		/* true cond */
	      break;			/* false cond */
	    case 8:			/* ne operator */
	      if (ifet != temp)		/* ne op */
	        goto ifpro5;		/* true cond */
	      break;			/* false cond */
	  }	/* end of switch */
	  ifet = 0;			/* set false condition */
	  goto ifpro9;			/* go get next element */
ifpro5:
	  ifet = 1;			/* set true */
	  goto ifpro9;			/* go get next element */

find:
#ifdef DBUGIF
printf("find: label = %0.8s, usname = %0.8s i = %d\n", label, usname, i);
#endif
	  prevrelo = i;			/* save the cond operator */
ifpro9:
	  if (hbstac[0] == ',')		/* was term a comma */
	    goto ifprod;		/* yes, no more terms to check */
	  if (inscnt < 73)		/* did we go beyond col 72 */
	    goto ifpro2;		/* no, check more terms */

iferr:
	  if (yeanay()) {			/* are we assembling */
	    seterr ('E');		/* set faulty parm list error */
/* printf("3E\n"); */
	  }
	  return;			/* exit */

ifprod:
#ifdef DBUGIF
printf("ifprod: prevrelo = %d, ifet = %d i = %d\n", prevrelo, ifet, i);
#endif
	  macstate &= ~INTGEN2;		/* clear flag initially */
	  if (macstate & INTGEN)	/* internal label in exp */
	    macstate |= INTGEN2;	/* yes, copy the flag */
#ifdef DBUGIF
printf("ifprod:a prevrelo = %d, ifet = %d i = %d\n", prevrelo, ifet, i);
#endif
#ifdef FIX_LINUX
{ int dummy[5];		/* this fixes a stack overwrite problem */
#endif
	  unst(0x80080000L);		/* unstring a term, term on sp or , */
#ifdef FIX_LINUX
}
#endif
#ifdef DBUGIF
printf("ifprod:b prevrelo = %d, ifet = %d i = %d\n", prevrelo, ifet, i);
#endif
	  if (!(PASS & 1)) {		/* are we pass 2 */
	    if (unstk) {		/* should end in param, not delim */
	      seterr ('E');		/* set faulty parm list error */
/* printf("4E\n"); */
	      unstk = 0;		/* clear the flag */
	    }
	  }
	  unstk = 0;			/* clear the flag */
#ifdef DBUGIF
printf("ifprod1: INTGEN2 is %s, binop = %x\n",
 (macstate&INTGEN2) ? "ON" : "OFF",curops->binop);
#endif
	  if (curops->binop == 0x14) {	/* is it ifp */
	    if (!(macstate & INTGEN2))	/* any int syms present */
	      return;			/* no, skip cond scan */
	  } else
	  if (curops->binop == 0x15) {	/* is it ifa */
	    if (macstate & INTGEN2)	/* any int syms present */
	      return;			/* yes, skip cond scan */
	  } else
	  if (curops->binop ^ (ifet & 0xff)) { /* comp to t/f case of expr */
#ifdef DBUGIF
printf("nomatch, return\n");
#endif
	    return;			/* no match, get next statement */
	  }
ifpro8:
#ifdef DBUGIF
printf("ifpro8: usname = %0.8s, ifet = %d, binop = %d\n",
 usname, ifet, curops->binop);
#endif
	  /* save name where we can resume assemble */
	  memcpy (hwscnhp, usname, 8);	/* move 8 bytes of label */
	  if (!yeanay()) return;	/* if not assembling return */
	  memcpy (lablscan, hwscnhp, 8); /* save label to scan for */
	  macstate |= CONDSCAN;		/* show we are in a conditional scan */
	  return;			/* do next input line */
	}		/* must be iftdef/iffdef ops */
	ifflg = 0;			/* clear symbol found flag */
	unst(0x00080000L);		/* terminate on comma */
	stp = symtab;			/* get address of symbol table */
	while (stp) {
	  if (memCmp(usname, stp->sym, 8)) {	/* see if the symbol */
	    ifflg = 1;			/* show symbol found */
	    break;			/* exit loop */
	  }
	  stp = stp->flink;		/* get next entry */
	}
	unst(0x80080000L);		/* terminate on sp or comma */
	if (curops->binop == 2) {	/* is it iftdef */
	  if (ifflg)			/* was symbol defined */
	    return;			/* next instruction if defined */
	   goto ifpro8;			/* else, go set jump name */
	}				/* no, must be iffdef */
	if (!ifflg)			/* was symbol defined */
	  return;			/* next instr if not defined */
	goto ifpro8;			/* save jump name */
}

static	char	*mact;			/* end of parameter storage in stk */

/*
 * macexp - process a macro expansion
 * input - dmstp points to macro definition entry
 */

void	macexp()
{
	struct	symbol	FAR *mstp;	/* temp macro symbol entry pointer */
	unsigned	i, j;

	if (yeanay()) {			/* are we assembling */
	/* yes */
#ifdef REPTR
         LW        1,TALLS1        INDICATE A REQUEST WAS PERFORMED
         LW        3,lict        FOR A MACRO FROM THIS LINE NUMBER
         ZMW       REPTYPE         INDICATE SYMBOL REPORT TO XREF
         BL        REPTR          SO IT WILL SHOW UP IN THE XREF
#endif
#ifdef MACD
printf("macexp: expanding %0.8s\n", dmstp->sym);
#endif
	  tall();			/* allocate current macro label */
	  level++;			/* indicate a level of expansion */
	  macstate |= CALLUS;		/* set current macro call ind */
	  if (!(macstate & EXPAND))	/* are we expanding a macro now */
	    stkp = stk;			/* no, set start of expansion stack */

#ifdef DBUGM0
if (macstate & EXPAND)
printf("macexp: EXPAND set 1\n");
#endif
	  j = stackp->pcnt = dmstp->desc.flags;	/* get parameter count */
	  stackp->clev = (unsigned char *)stkp;	/* expansion stack address */
	  mact = (char *)stackp->clev;	/* parameter expansion stack address */
	  /* get macro prototype address */
	  stackp->maca = (uchrfp)dmstp->desc.value;
/*XXX	  mpp = stackp;			/* macro expans entry for this level */
#ifdef MACD
printf("macexp: %d parameters found, stkp = %x, level = %x\n",stackp->pcnt, stkp, level);
#endif
	  for (i=0; i<j; i++) {		/* loop for requested param cnt */
	    memset(mact, ' ', 24);	/* preblank parameter storage */
	    mact += 24;			/* next parameter pointer */
#ifdef MACD
printf("macexp: clearing param %d, stkp = %x, mact = %x\n",i, stkp,mact);
#endif
	  }				/* mact points past end of parameters */
	}
	do {				/* get all the parameters, term on , */
	  unsigned char theff = 0xff;
	  unsigned char ttt;

	  unst(0x80080000L);		/* unstring param, term on sp & comma */
	  ttt = *usname;
#ifdef MACD
printf("macexp: unstrung |%c%0.11s| stkp = %x, mact = %x\n",
(ttt == 0xff ? '!' : ttt), &usname[1], stkp, mact);
#endif
	  if (!yeanay())		/* are we assembling */
	    continue;			/* no, just unstring them */
	  if (macstate & INTGEN) {	/* was arg an internal symbol */
	    macstate &= ~INTGEN;	/* yes, reset the flag */
	    *usname = theff;		/* put internal sym xref char in sym */
	  } else 
	  if (*usname == ' ') {		/* generate an internal symbol */
	    char intsym[16];		/* new internal symbol */
	    /* get symbol num of 5 digits with leading 0 and trailing blnks */
	    sprintf(intsym, "%.5X   ", (inttag++ & 0xffff));
	    memcpy(usname, intsym, 8);	/* copy into unstrung location */
	    *usname = theff;		/* int sym lead char to stack */
#ifdef MACD
printf("macexp: dummy made %0.8s\n", intsym);
#endif
	  }
	  if (stkp > mact) {		/* too many parameters specified */
#ifdef DBUGM2
printf("macexp: X error stkp = %x, mact = %x\n", stkp, mact);
#endif
	    seterr ('X');		/* set parameter error */
	    continue;			/* don't store the parameter */
	  }
	  memcpy(stkp, usname, 24);	/* copy into stack location */
	  stkp += 24;			/* next parameter storage location */
	} while (hbstac[0] == ',');	/* terminate on non comma terminator */
	if (yeanay()) {			/* are we assembling */
	  stkp = mact;			/* yes, set start of new stack */
	  mpp = stackp;			/* macro expans entry for this level */
	  stackp++;			/* set for next level */
#ifdef DBUGM2
printf("macexp: EXPAND set 2\n");
#endif
	  macstate |= EXPAND;		/* show we are expanding */
#ifdef DBUGM2
printf("macexp: EXPAND set 2a\n");
#endif
	  bits |= CVFL;			/* indicate print prog counter */
#ifdef DBUGM2
printf("macexp: EXPAND set 2b\n");
#endif
	}
#ifdef MACD
printf("macexp: stackp = %x, stack = %x level = %d\n",stackp, stack, level);
printf("macexp: stkp = %x, stk = %x mpp = %x\n",stkp, stk, mpp);
#endif
	macstate &= ~CALLUS;		/* clear current macro call ind */
#ifdef DBUGM2
printf("macexp: Clear CALLUS\n");
#endif
	return;				/* expand the macro */
}

/*
 * mbyt - copy byte into macro storage
 */

void	mbyt(byte)
unsigned char	byte;
{
	if (inptstat & RSCAN)		/* in repeat scan */
	  goto mbyt1;			/* yes, go store it */
	if (spmac & DEFFRM2)		/* in pass 2 defm-form */
	  return;			/* yes, no need to store byte */
	if (inptstat & DEFMBODY)	/* in defm body */
	  goto mbyt1;			/* yes, go store it */
	if (!(inptstat & FORMSCAN))	/* in form def */
	  return;			/* no, no need to store byte */
mbyt1:
	maccnt++;			/* bump num of chars in macro */
#ifdef MACS
printf("mbyt1: maccnt=%x\n",maccnt);
#endif
	if (maccnt > high) {		/* will this char overflow buffer */
#ifdef MACS
printf("mbyt1: head = %x, maccnt = %x, high = %x\n", head, maccnt,high);
prtval("mbyt1head", &head->desc);
#endif
	  /* yes, realloc the buffer adding 256 more chars for storage */
#ifdef DOS
	    {
	    int	i;
	    uchrfp work;		/* work pointer */
	    uchrfp work1;		/* work pointer */
	    work = (uchrfp)_fmalloc(high+256);
	    if (!work)			/* did we get it */
 	      abortm("** UNABLE TO ALLOCATE MEMORY FOR MACRO STORAGE **");
	    work1 = (uchrfp)head->desc.value;	/* old buffer address */
	    for (i = 0; i < high; i++) 
	      work[i] = work1[i];	/* copy the char */
	    _ffree((uchrfp)work1);	/* deallocate the old */
	    head->desc.value = (unsigned int32)work;	/* set the new addr */
	    }
#else
	  head->desc.value =
	    (unsigned int32)realloc((uchrfp)head->desc.value, high + 256);
#endif
	  macsp = (uchrfp)head->desc.value;	/* new buffer address */
	  macsp += high;		/* where to start storing */
	  high += 256;			/* new char count */
	  head->desc.tmp = high;	/* set new size */
#ifdef DEBUG
{
char *p = (char *)head->desc.value;
printf("realloc macro %0.8s, addr = %x, count = %x, hcnt = %x\n",
 head->sym, p, maccnt, head->desc.tmp);
}
prtsymt();				/* dump the symbol table */
#endif
#ifdef MACS
printf("mbyt1: head = %x, maccnt = %x, high = %x\n", head, maccnt,high);
prtval("mbyt1head", &head->desc);
#endif
	}
	*macsp++ = byte;		/* stor the byte */
	return;				/* return */
}

static	int32	repcnt;			/* repeat count */
int32	repdone;			/* repeat done count */
static	uchrfp	hwrepss;		/* rept storage save address */
#ifdef JUNK
struct	symbol	dumrept = {		/* dummy repeat header */
	(struct symbol FAR *)0,
	(struct symbol FAR *)0,
	(struct symbol FAR *)0,		/* zero llink, rlink, flink */
	"REP",				/* no symbol */
	0,0,0,				/* zero type, flags, tmp & value */
	(unsigned int32)0
};
#else
static	struct	symbol	FAR * dumrept;
#endif

/*
 * reptp - process repeat
 */

void	reptp()
{

	if (macstate & RSCAN) {		/* are we already in a rept scan */
	  macstate &= ~RSCAN;		/* clear the rept flag */
	  seterr ('Y');			/* set rept error */
	  return;			/* we are done */
	}
	tall();				/* allocate current label */
	valundf = 0;			/* clear undefined flag from val */
	val(0);				/* unstring repeat count */
	repcnt = inac.value & 0xfffffL;	/* the value */
	if (valundf) {			/* was value undefined */
	  repcnt = 0;			/* yes, set count to zero */
	  valundf = 0;			/* clear undefined flag from val */
	}
	if (macstate & (DEFMBODY | CONDSCAN))	/* in def or cond scan */
	  return;			/* yes, return */
	repdone = 0;			/* zero times through counter */
	macstate |= RSCAN;		/* indicate we are in rep scan */
	/* get memory for rept storage, default to 256 bytes */
#ifdef DOS
	dumrept = (struct symbol FAR *)_fmalloc(sizeof(struct symbol));
#else
	dumrept = (struct symbol FAR *)malloc(sizeof(struct symbol));
#endif
	if (!dumrept)			/* if no memory terminate assemble */
 	  abortm("** UNABLE TO ALLOCATE MEMORY FOR REPT STORAGE **");
#ifdef DOS
	dumrept->desc.value = (unsigned int32)_fmalloc(256);
#else
	dumrept->desc.value = (unsigned int32)malloc(256);
#endif
	if (!dumrept->desc.value)	/* if no memory terminate assemble */
 	  abortm("** UNABLE TO ALLOCATE MEMORY FOR REPT STORAGE **");
	dumrept->desc.tmp = 256;	/* initial storage size */
	head = dumrept;			/* address of dummy header */
	high = dumrept->desc.tmp;	/* set number of bytes malloced */
	defcnt = 0;			/* zero number of chars read in */
	maccnt = 0;			/* number of chars stored */
	macsp = (uchrfp)dumrept->desc.value;
	hwrepss = (uchrfp)macsp;	/* save pointer for rept prototype */
	return;				/* get the repeat code */
}

/*
 * endrp - endr processing
 */

void	endrp()
{
	if (macstate & DEFMBODY)	/* check for being in defm */
	  return;			/* we are in dummy macro, exit */
	if (macstate & CONDSCAN) {	/* conditional assembly */
	  if (!(macstate & RPTGEN))	/* are we in repeat generation */
	    return;			/* no return */
	  macstate &= ~RPTGEN;		/* yes, clear the flag */
	  goto endrf;			/* go terminate repeat gen */
	}
	if ((macstate & RPTGEN)) {	/* are we in repeat generation */
	  macstate &= ~RPTGEN;		/* yes, clear the flag */
	  goto endrpr;			/* yes, a new pass, fiddle cnts */
	}
	if (!(macstate & RSCAN)) {	/* in a previous repeat */
	  seterr ('Y');			/* set rept error */
	  return;			/* we are done */
	}
	mbyt((unsigned char)0xff);	/* copy out the terminator */
	macstate &= ~RSCAN;		/* clear the rept flag */
	inptstat &= ~RSCAN;		/* clear in rept flag */
	if (macstate & EXPAND) {	/* are we expanding */
	  macstate |= MACREP;		/* yes, indicate a repeat within exp */
	  level = 0;			/* show no expansions within rept yet */
	}
endrpr:
	repdone++;			/* count the # of repeats */
	if(--repcnt < 0) {		/* are we done */
endrf:					/* repeat is done */
	  macstate &= ~MACREP;		/* clear the rept flag */
#ifdef DOS
	  _ffree(dumrept);		/* free the repeat header */
	  _ffree(hwrepss);		/* free the repeat space */
#else
	  free(dumrept);		/* free the repeat header */
	  free(hwrepss);		/* free the repeat space */
#endif
	  return;			/* go get next statement */
	}
	macstate |= RPTGEN;		/* indicate a repeat */
	/* reset repeat code base address */
	hwrepsp = (uchrfp)dumrept->desc.value;
#ifdef DEBUG
	{
	    int i;
	    struct symbol FAR *mstp = (struct symbol FAR *)head;
	    uchrfp p = (uchrfp)mstp->desc.value;

	    printf("prtsymt: mstp = %x symbol = %0.8s\n", mstp, mstp->sym);
	    prtval("prtsymt mstp", &mstp->desc);
	    printf("macro %0.8s, addr = %x, count = %x\n",
	      mstp->sym, p, mstp->desc.tmp);
	    for (i=0; i < mstp->desc.tmp; i++) {
	      if (isprint(*p))
	        printf("%c", *p++);
	      else
	        printf("%0.2x", *p++);
	      if (i > 0 && ((i+1)%40 == 0))
		printf("|\n");
	    }
	    printf("|\n");
	}
#endif
	return;				/* go get next statement */
}

static	int32	optmsk = 0x000c63ffL;	/* masks opts 11-13,16-18,21-32 */

/*
 * setpro - process set, sett, setf, opt? commands
 */

void	setpro()
{
	int32	setprov;
	struct	tval	tv;
	struct	tval	setp;
	int32	temp;

	setprov = curops->binop;	/* set default t/f for sett, setf */
	if (curops->binop >= 2) {	/* is op set or opt */
	  tv = val(0);			/* yes, it has a value */
	  setprov = tv.value;		/* get the value */
	}
	/* here, setprov has true, false, or value amount */
	if (!yeanay()) {		/* are we assembling */
	  unst(0x80000000L);		/* no, just unstring elements */
	  return;			/* and leave */
	}
#ifdef SETD
printf("setpro: label = %0.8s, usname = %0.8s\n", label, usname);
#endif
	if (curops->binop >= 3) {	/* is this opts, optr, optt */
	  /* yes, process the option operators */
	  setprov &= 0x3fffffL;		/* just in case */
    	  if (setprov == 55) {		/* option 55? */
    	    temp = OPT55;		/* set the bit */
    	    goto mergeset;		/* merge code */
    	  }
	  if (setprov < 1 || setprov > 32) {	/* option # must be 1-32 */
	    seterr ('X');		/* set range error */
	    return;			/* done */
	  }
	  temp = 1L << (setprov - 1);	/* make bit number into a mask */
					/* which is zero relative */
	  if (temp & optmsk) {		/* make sure a usable option */
	    seterr ('X');		/* no, set range error */
	    return;			/* done */
	  }
mergeset:
	  if (curops->binop == 3) {	/* is this opts */
	    option |= temp;		/* yes, set the option bit */
	    setprov = 1;		/* insure symbol is 1 */
	  }
	  else
	  if (curops->binop == 4) {	/* is this optr */
	    option &= ~temp;		/* yes, reset the option bit */
	    setprov = 0;		/* insure symbol is 0 */
	  }
	  else	{			/* it must be oppt then */
	    if (option & temp)		/* test if bit is on */
	      setprov = 1;		/* yes, insure symbol is 1 */
	    else
	      setprov = 0;		/* no, insure symbol is 0 */
	  }
	  if (hbstac[0] != ' ') {	/* see if terminator was a space */
	    seterr ('X');		/* no, set range error */
	    unst(0x80000000L);		/* unstring rest of line */
	  }
	}
	/* process the set operators and enter opt value in symbol table */
	/* setprov has the value to enter */
	setp.type = TYSETSYM;		/* symbol type is set symbol */
	setp.value = setprov;		/* set the symbol value */
	setp.flags = 0;			/* default to dsect/abs */
	if (inac.flags & (ABSREL | CSDS)) /* was value csect/rel */
	  /* yes, csect and rel, is type extern or program */
	  if (inac.type == TYPP || inac.type == TYPX)
	    inac.flags |= CSDS;		/* yes, indicate csect for set type */
	ss (&setp, label);		/* set cond state in symbol table */
#ifdef SETD
prtval("setpro final val", &setp);
#endif
	if (DPFLG & dpflags)		/* is it datapool */
	  seterr ('V');			/* yes, set datapool error */
	return;				/* done */
}

