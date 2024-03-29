/* pseudo.c */

/* pseudo-op processing */

#include "defs.h"
#include <string.h>

extern struct tval symval;		/* defined in symbol.c */

/* #define DSPACE */
/* #define BUGB */
/* #define BUGT */

#ifdef DOS
void	arel();
void	bouc(int32);
int	tbou(int);
void	bound();
void	ccp1();
void	dpcom();
void	equ();
void	list();
void	lpop();
void	org();
void	pagp();
void	prog();
void	ref();
void	res();
void	rez();
void	rseis();
void	eisset();
void	eisreset();
void	eismerge(int);
void	sdirs();
void	space();
void	titl();
#ifndef CAID
void	stab();
#endif
#endif

#ifndef CAID
int	sudo;		/* processing pseudo-op */
#endif
/*
 * arel - process abs, rel, dsect, and csect pseudops
 * input - normal
 */

void	arel()
{
	int	temp;

	if (!yeanay())return;		/* are we assembling */
	if (pcmode == PCCOM) {		/* are we processing common */
	  /* get common # and see if it is an ssect */
	  temp = (int32)(sectpc[PCCOM].value & 0x00ff0000) >> 24;
	  if ( hwcmsize[temp] & 0x80000000)
	      /* it is ssect, is it bigger than old */
	      if ((sectpc[PCCOM].value & 0xffff) > (hwcmsize[temp] & 0xffff)) 
		/* save new size */
		hwcmsize[temp] = ((hwcmsize[temp] & 0xffff0000) |
		  (sectpc[PCCOM].value & 0xffff));	/* set new size */
	}
	/* get augment and save as section type, see if csect */
	if ((pcmode = curops->aug >> 2) == PCCS)
	  /* it is csect, use expanded loader codes */
	  bits3 |= EXPLFC;		/* csect, use expanded loader codes */
	currpc = sectpc[pcmode];	/* staticize PC */
	tall();				/* allocate current label */
	if (yeanay()) {			/* are we assembling */
	  bits |= CVFL;			/* set flag to print prog cntr */
	}
	return;
}

/*
 * bouc - manipulate PC to multiple of input value
 * set hwcmpb to largest bound 
 * input - pc value
 */

void	bouc(val)
int32	val;
{
	int	tmp = 0;
	int32	retv;

#ifdef BUGB
printf("bounc entry val %x dsect %x csect %x\n", val, hwcmpb[0], hwcmpb[1]);
fflush(stdout);
#endif
	if (!yeanay()) return;			/* return if not assembling */
#ifdef BUGB
printf("bounc entry val %x dsect %x csect %x\n", val, hwcmpb[0], hwcmpb[1]);
fflush(stdout);
#endif
	retv = tbou(val);			/* bound the pc */
	if (retv != 0) {
	  sectpc[pcmode].value += (val - retv);	/* set new pc */
	  currpc = sectpc[pcmode];		/* set new pc */
    	  pcchk();				/* check pc for overflow */
	}
	/* return if not rel to dsect or csect */
	if ((pcmode == PCDS) || (pcmode == PCCS)) {
	  if (currpc.flags & CSDS) tmp = 1;	/* it is csect, use its index */
	  val &= 0xfffff;			/* limit bound to 1mb */
  
#ifdef BUGB
printf("bounding %s old val = %x new val = %x\n", tmp == 1?"csect":"dsect",
    hwcmpb[tmp], val);
fflush(stdout);
#endif
   
	  if (hwcmpb[tmp] <= val)		/* see if new max bound */
	    hwcmpb[tmp] = val;			/* set new bounding max */
    	}
	return;
}

/*
 * tbou - check for correct PC boundry
 * input - boundry value
 * output - zero if boundry is correct
 *          else return correction offest
 */

int	tbou(bound)
int	bound;
{
	int32	tmp;

	tmp = (sectpc[pcmode].value & 0x7fffff);	/* bound PC */
	if (bound == 0)return (0);
	return ((tmp - (bound * (tmp / bound))));
}

/*
 * bound - process bound statement
 * input - normal
 */

void	bound ()
{
	struct	tval	theval;
	int	nb;
	unsigned int32	tmp;

	theval = val (0);		/* skip leading spaces */
	if (!yeanay()) return;		/* if not assembling, return */
	if ((theval.value & 0x7fffff) == 0)	/* see if bound to small */
	  goto boune;			/* error if zero */
	tmp = theval.value = theval.value & 0x7fffff;	/* limit the value */
	for (nb = 0; nb < 32; nb++) {	/* loop for all 32 bits */
	  if (tmp & (unsigned int32)0x80000000)	/* see if sign bit on */
	    break;			/* exit loop done */
	  tmp <<= 1;			/* shift it left one */
	}
	tmp <<= 1;			/* shift it left one */
	tmp &= 0xffffffff;		/* mask for alpha */
	if (tmp != 0)			/* is value zero */
	  goto boune;			/* error if not zero */
	if (nb >= 26)			/* see if within range */
	  goto bour;			/* go of yes */
boune:
	seterr ('Q');			/* set label error */
	return;

bour:
	if (option & ASECT) {		/* are we in auto sect */
	  asctflg |= ASCTBND;		/* indicate deferred bound */
	  asctbvl = theval;		/* save the bound value */
	  asctblc = lict;		/* save the line counter for sect */
	  memcpy (asctblb, label, 8);	/* save the current label */
	  return;			/* exit, deferring bound */
	}
	bouc ((int32)theval.value);	/* bound the pc */
	/* NOTE: If multiple bounds are deferred, only the last one will
	 * be processed.  Any labels on previous ones will be undefined!
	 */
	currpc = sectpc[pcmode];	/* staticize PC */
	tall();				/* allocate current label */
	if (yeanay())			/* are we assembling */
	  bits |= CVFL;			/* set flag to print prog cntr */
	return;
}

/*
 * ccp1 - common pseudo processor (and datapool)
 */

void	ccp1()
{
	char	dummy[12];			/* dummy loc for usname */
	int32	*tnum;
	int32	temp;
	int	blknum = 0;
	struct	tval	tdef;

	if (!yeanay()) 			/* are we assembling */
	  goto ccp3;			/* no, just go unstring stuff */
	memcpy(dummy, label, 8);	/* get the label, if any */
	dummy[8] = '\0';		/* null terminate it */
#ifndef TEST_LC_datapool
	str2upr(dummy);			/* make upper case */
#endif
/*
printf("entering ccp1 usname = %0.8s, dummy = %0.8s\n", usname, dummy); 
*/
	if (!(strncmp(dummy, "DATAPOOL", 8))) {	/* see if "datapool" */
	  /* yes it is, do datapool item processing */
	  hwdpnum = 100;		/* reserved value for datapool */
	  dpcom();			/* common dp processing routine */
	  return;			/* all done, exit */
	}
	if (!(strncmp(dummy, "DPOOL", 5))) {	/* see if "dpoolxx" */
	  /* yes it is, do multiple datapool item processing */
	  memset(usname, ' ', 8);	/* clear the unstrung name loc */
	  memcpy(usname, &dummy[5], 2);	/* copy in just the number 0-99 */
	  tnum = cnum(10);		/* get the number */
	  hwdpnum = tnum[0];		/* just use the l/o part */
	  if (hwdpnum > 99)		/* only 0-99 are valid */
	    if (yeanay())		/* are we assembling */
	      seterr ('D');		/* set datapool error */
	  dpcom();			/* common dp processing routine */
	  return;			/* all done, exit */
	}
	ss (&ud, label);		/* search/set block name in sym tab */
	if (spmac & INTSS) {		/* was symbol internally generated */
	  seterr ('I');			/* set section definition error */
	  do {				/* unstring the symbol names */
	    unst(0x80c8000);		/* unstring 1 symbol */
	  } while (hbstac[0] != ' ');	/* loop till blank terminator */
	  return;			/* exit */
	}
	if (symval.type == TYPD) {	/* is type a common block def */
	  tdef = symval;		/* get the definition */
	  if (!(PASS & 1))		/* is this pass 1 */
	    /* no, clean block and address */
	    tdef.value = 0;		/* clear block # and disp */
#ifdef MAY_BY_JUNK
/* I think this code is backwards, but I will leave as is */
CCP8     TBM       7,PASS        FIRST PASS?                  84-587
         BS        CCP9            IF NOT THEN GO               84-587
         SRL       3,24                                         84-587
         SLL       3,24                                         84-587
         BU        CCP9            PROCESS BLOCK ENTRIES        84-587
#endif 
	  goto ccp9;			/* yes, go chain the block */
	}
	if (symval.type != TYPU) {	/* was type undefined */
	  /* no, it is a common definition error */
	  seterr ('J');			/* set common definition error */
	  if (EXPAND & macstate) {	/* expanding a macro */
	    /* yes, then we must unstring rest of line */
	    do {			/* unstring the symbol names */
	      unst(0x80c8000);		/* unstring 1 symbol */
	    } while (hbstac[0] != ' ');	/* loop till blank terminator */
	  }
	  return;			/* exit */
	}
	/* symbol was undefined, new block definition */
	if ((blknum = hbccct) > 255) {	/* are there too many */
	  seterr ('R');			/* yes, set relocation error */
	  return;			/* return */
	}
	hbccct++;			/* increment common block # */
	tdef.value = (int32)blknum << 16;	/* set new block # */
ccp9:
#ifndef FIX_012894
    	blknum = tdef.value >> 16;	/* set blknum for later */
#endif
/*
printf("ccp9 blknum = %x, val = %d\n", blknum, (tdef.value >> 16)); 
*/
	tdef.type = TYPC;		/* common type symbol */
	tdef.flags = 0;			/* absrel/csds are zero for common */
ccp3:
	unst(0x80c80000);		/* unstring, term on sp , ( ) */
	if (yeanay()) {			/* are we assembling */
	  /* yes, allow a common definition */
	  if (PASS & 1)			/* if pass 2, don't alloc symbol */
	    ss (&tdef, usname);		/* pass 1, alloc sym to common area */
	}
	temp = 1;			/* default to 1 word for size */
	if (hbstac[0] == '(') {		/* was terminator a ( */
	  /* yes, get the dimension size of this element */
	  unst(0x80c80000);		/* unstring, term on sp , ( ) */
	  tnum = cnum(10);		/* convert the size (in words) */
	  temp = tnum[0];		/* just get l/o part */
	}
	temp <<= 2;			/* make number of words into bytes */
	/* see if size is too big ( > 0xffff) */
	if (((temp + (tdef.value & 0xffff)) & 0xffff0000)) {
	  temp = 0;			/* yes, reset to zero */
	  seterr ('R');			/* set relocation error */
	}
	tdef.value += temp;		/* add in new increment */
ccp5:
	if (hbstac[0] == ',')		/* was terminator a , */
	  goto ccp3;			/* yes, more symbols to do */
	if (hbstac[0] != ' ') {		/* was terminator a sp */
	  runst(0x80c80000);		/* no, unstring, term on sp , ( ) */
	  goto ccp5;			/* without skipping sp, see if done */
	}
	/* we are done, finish up */
	tdef.type = TYPD;		/* set block definition type code */
/*
printf("ccp5 blknum = %x, hbccct = %d label [%0.8s]\n", blknum, hbccct, label);
prtval("ccp ccp5", &tdef);
*/
	hwcmsize[blknum] = (hwcmsize[blknum] & 0xffff0000) | 
	  (tdef.value & 0xffff);	/* save size information */
	if (PASS & 1)			/* pass 1 */
	  if (yeanay())			/* are we assembling */
	    ss (&tdef, label);		/* define common blk # and size */
	return;				/* done */
}

/*
 * dpcom - common processing for sext and datapool directive
 * hwdpnum has the datapool number
 */

void	dpcom()
{
	struct	tval	dpd;
/*
printf("entering dpcom usname = %0.8s\n", usname);
*/
	dpd.flags = 0;			/* zero flags */
	dpd.type = TYPDP;		/* datapool definition */
ccp7:
	unst(0x80c80000);		/* unstring one symbol */
/*
printf("dpcom unst1 usname = %0.8s\n", usname);
*/
	if (hbstac[0] != '(')		/* was term a ( */
	  if (hbstac[0] == ')')		/* no, was it a ) */
	    goto ccp8;			/* yes, ignore ( , ) or sp */
	/* term must be comma or space */
	dpd.value = (int32)hwdpnum << 16;	/* set dp number */
/*
prtval("dpcom dpd", &dpd);
*/
	ss (&dpd, usname);		/* define the symbol */
	if (hbstac[0] == ' ')		/* was term a space */
	  return;			/* yes, all done */
	if (hbstac[0] != '(')		/* was it a '(' */
	  goto ccp7;			/* no, don't ignore data to comma */
ccp8:
	unst(0x80c80000);		/* unstring one symbol */
/*
printf("dpcom unst2 usname = %0.8s\n", usname);
*/
	if (hbstac[0] == ',')		/* was term a , */
	  goto ccp7;			/* yes, get next item */
	if (hbstac[0] == ' ')		/* was term a space */
	  return;			/* yes, all done */
	goto ccp8;			/* no, ignore data to comma */
}

/*
 * equ statements
 * input - normal
 */

void	equ()
{
#ifdef BUGB
 prtval("equ 1", &currpc); 
#endif
	if (ASECT & option) {		/* are auto sectioning? */
	  usname[4] = '\0';		/* null terminate */
	  str2upr(usname);		/* set opcode to uppercase */
	  if (!strncmp(usname, "EQU ", 4))	/* is it just EQU? */
	    asctflg |= ASCTNOD;		/* set no $ evaluation */
	}
					/* evaluate expression */
					/* set new pc value */
	currpc = val (0);		/* tell val to skip leading spaces */
#ifdef BUGB
 prtval("equ 2", &currpc);
#endif
	/* see if type is common */
	if (currpc.type == TYPC) {	/* see if type common */
					/* set block number if it is */
	  currpc.value = ((currpc.value & 0xffff) | ((int32)inacbn << 16));
					/* block # and offset are in pc now */
	} else {
	/* not common, is it datapool? if so ,error */
	if (DPFLG & dpflags) 		/* datapool ? */
	  seterr ('V');			/* if datapool, set VFD error */
	}

#ifdef BUGB
printf("calling tall from equ with label %.8s, pcmode = %x\n",label, pcmode);
fflush(stdout);
#endif

	tall();				/* allocate current label */
#ifdef BUGB
printf("return from calling tall from equ with label %.8s, pcmode = %x\n",label, pcmode);
fflush(stdout);
#endif
	if (yeanay()) {			/* are we assembling */
	  bits |= CVFL;			/* set flag to print prog cntr */
	}
	return;
}

/*
 * list - list directive processing to control printing
 */

void	list()
{
	int	bb = bits;
	int	bb2 = bits2;

	if (bits & APON)		/* listing allowed */
	  bits &= ~IMIN;		/* no, suppress p/o of list directive */
	/* if expanding a macro, is expansion list allowed */
	if ((macstate & EXPAND) && (bits2 & MACPRINT))
	  bits &= ~IMIN;		/* no, suppress p/o of list directive */
	/* if generating rept code, is expansion list allowed */
	if ((macstate & RPTGEN) && (bits2 & REPPRINT))
	  bits &= ~IMIN;		/* no, suppress p/o of list directive */
list0:
	unst(0x80080000);		/* unstring one item */
	usname[4] = 0;			/* null terminate 4 char directive */
	str2upr(usname);		/* force to uppercase */
	if (!strncmp(usname, "REP ", 4))  /* list rept expansions */
	  bits2 &= ~REPPRINT;		/* list repeat expansions */
	else
	if (!strncmp(usname, "NORE", 4))  /* don't list rept expansions */
	  bits2 |= REPPRINT;		/* don't list repeat expansions */
	else
	if (!strncmp(usname, "MAC ", 4))  /* list maco expansions */
	  bits2 &= ~MACPRINT;		/* list macro expansions */
	else
	if (!strncmp(usname, "NOMA", 4))  /* don't list macro expans */
	  bits2 |= MACPRINT;		/* don't list macro expansions */
	else
	if (!strncmp(usname, "NGLI", 4))  /* list all source lines */
	  bits &= ~NGPRINT;		/* list all source lines */
	else
	if (!strncmp(usname, "NONG", 4))  /* don't list unassembled source */
	  bits |= NGPRINT;		/* don't list unassembled source */
	else
	if (!strncmp(usname, "ON  ", 4))  /* list on */
	  bits &= ~APON;		/* allow listing */
	else
	if (!strncmp(usname, "OFF ", 4))  /* list off */
	  bits |= APON;			/* don't allow listing */
	else
	if (!strncmp(usname, "DATA", 4))  /* list extensions */
	  bits &= ~APEX;		/* allow extensions */
	else
	if (!strncmp(usname, "NODA", 4))  /* don't list extensions */
	  bits |= APEX;			/* don't allow extensions */
	else {				/* not valid directive */
	  if (yeanay()) {		/* are we assembling */
	    seterr ('K');		/* set invalid list directive error */
	    goto list2;			/* go test terminator */
	  }
	}				/* valid entry found */
	if (!yeanay()) {		/* are we assembling */
	  /* not assembling, restore bits and bits2 to original state */
	  bits = bb;			/* restore bits */
	  bits2 = bb2;			/* restore bits2 */
	}
list2:
	if (hbstac[0] == ',')		/* if comma term, more directives */
	  goto list0;			/* get next directive */
	return;				/* get out */
}

/*
 * lpop - lpool processor
 */

void	lpop()
{

	if (macstate & EXPAND) {	/* are we expanding */
	  hwmspbuf = 0;			/* clear store ptr for macro print */
	  spmac |= LPOOLM;		/* indicate we are processing an */						/* lpool in a macro expansion */
	}
	if (yeanay()) {			/* are we assembling */
	  if (bits & LPOOL31)		/* too many lpools? */
	    seterr ('Z');		/* set lpool error */
	  else
	    prlit();			/* process any pending literals */
	  bits |= IMIN;			/* set buffer image ready */
	}
	spmac &= ~LPOOLM;		/* set finished with lpool */
	return;
}

/*
 * org - process org statement
 */

void	org()
{
	int	temp;
	
	if (ASECT & option) {		/* are auto sectioning? */
	  usname[4] = '\0';		/* null terminate */
	  str2upr(usname);		/* set opcode to uppercase */
	  if (!strncmp(usname, "ORG ", 4))	/* is it just ORG? */
	    asctflg |= ASCTNOD;		/* set no $ evaluation */
	}
	val(0);				/* skip spaces & get value */
	if (!yeanay())			/* are we assembling */
	  return;			/* no, just return */
	if (inac.type == TYPC)		/* is type common */
	  goto org3;			/* yes, go process */
	/* see if org out of common attempted */
	if (pcmode == PCCOM) {		/* error, can't chg from com in org */
org2:
	  seterr ('Q');			/* set label error */
org0:
	  currpc = sectpc[pcmode];	/* staticize PC */
	  tall();			/* allocate current label */
	  if (yeanay())			/* are we assembling */
	    bits |= CVFL;		/* set flag to print prog cntr */
	  return;			/* exit this thing */
	}
#ifndef MAY_BE_JUNK
	if (pcmode == PCDS)		/* are we in dsect */
	  if (sectpc[pcmode].value > max.value)	/* are we at new max */
	    max = sectpc[pcmode];	/* yes, set new max */
#ifdef OLDJUNK
	r6 = sectpc[pcmode];	/* get current prog ctn fro section */
         CAR       R6,R3           BACKWARDS ORG ?              S8700512
         BGE       ORG.1           NO IF NON-NEGATIVE           S8700512
         CAMW      R6,MAX          IS P.C. GREATER THAN MAX ?   S8700512
         BLE       ORG.1           CONTINUE IF NOT              S8700512
         STW       R6,MAX          SAVE NEW MAX VALUE           S8700512
ORG.1    CEQU      $                                            ESCT-32
#endif
#endif
	/* do input type and pc type agree */
	if (sectpc[pcmode].type == inac.type && 
	  sectpc[pcmode].flags == inac.flags)
	  goto org4;			/* yes, o.k. */
	if (pcmode == PCABS)		/* abs now trying to go rel */
	  goto org2;			/* yes, error */
	if (!(inac.flags & ABSREL)) {	/* try to go to abs mode */
	  /* yes, force user to stay in rel mode at offset in inac */
	  inac.flags |= ABSREL;		/* force on rel flag */
	  goto org4;			/* and continue */
	}
	/* switch from one rel section to another */
	if (inac.flags & CSDS)		/* into csect */
	  pcmode = PCCS;		/* set csect mode */
	else				/* must be dsect */
	  pcmode = PCDS;		/* set dsect mode */
	goto org4;			/* and continue */

org3:					/* process common org */
	temp = (int32)(sectpc[PCCOM].value >> 16) & 0xff;  /* common blk # */
	if (hwcmsize[temp] & 0x80000000) {	/* is this ssect */
	  /* it is, see if we need to save size */
	  if ((sectpc[PCCOM].value & 0xffff) > (hwcmsize[temp] & 0xffff))
	    hwcmsize[temp] = ((hwcmsize[temp] & 0xffff0000) | 
	      (sectpc[PCCOM].value & 0xffff));	/* or in new size */
	}
	if (!(PASS & 1)) {		/* is this pass 2 */
	  /* pass 2 - check new common size */
	  if (hwcmsize[inacbn] < inac.value)	/* input is greater, error */
	    goto org2;			/* go report error */
	}
	if (hwcmsize[inacbn] & 0x80000000)	/* is this an ssect */
	  goto org2;			/* yes, org invalid, error */
	sectpc[PCCOM] = inac;		/* save new definition */
	sectpc[PCCOM].value = ((sectpc[PCCOM].value & 0xffff0000) |
	  ((int32)inacbn << 16));	/* or in block number */
	pcmode = PCCOM;			/* set the PC pointer to common */
	goto org0;			/* finish up and exit */

org4:
	sectpc[pcmode] = inac;		/* save new definition */
	sectpc[PCCOM].value = ((sectpc[PCCOM].value & 0xff00ffff) |
	  ((int32)inacbn << 16));	/* or in block number */
	goto org0;			/* finish up and exit */
}

/* 
 * pagp - pseudo op page command
 */

void	pagp()
{
	if (bits & APON)		/* check whether listing */
	  return;			/* no listing, return */
	if ((macstate & EXPAND) && (bits2 & MACPRINT))
	  return;			/* no expansion list, return */
	if ((macstate & RPTGEN) && (bits2 & REPPRINT))
	  return;			/* no repeat list return */
	if (!(PASS & 1)) {		/* if pass 1 return */
	  if (yeanay()) {		/* are we assembling */
	    ejct (tcwd);		/* set header for tof on lo */
	    bits &= ~IMIN;		/* indicate no buffer image ready */
	  }
	}
	return;				/* return */
}

char	prodidl = 0;		/* length of product id */
char	prodid[24];		/* product id 0-20 bytes */

/*
 * prog - process program directive
 * input - normal
 */

void	prog()
{
    char	dummy[12];			/* dummy loc for usname */

    if (yeanay()) {		/* are we assembling */
    	if (PROGF & bits) {	/* is this the first program statement */
    	    seterr ('P');	/* set invalid program statement error */
    	    return;		/* return */
    	}
    	bits |= PROGF;		/* set program statement found */
    }
    unst (0x80080000);		/* terminate on space or comma */
    memcpy(dummy, usname, 8);	/* get the program name */
    dummy[8] = '\0';		/* null terminate it */
/*    str2upr(dummy);*/		/* make upper case */
    memcpy (TCWPROG, dummy, 8); /* set program name */
/*
printf("program usname = %0.16s, TCWPROG = %0.16s\n", usname, TCWPROG);
*/
    prodidl = 0;		/* clear id length */
    if (option & ID) {
    	unst (0x80000000);	/* unstring product id */
    	if (yeanay()) {		/* are we assembling */
    	    /* round up to words */
    	    unstnp = ((unstnp+3) >> 2) << 2;
    	    prodidl = (unstnp > 20 ? 20 : unstnp);	/* max of 20 bytes */
    	    if (prodidl > 0)
    		memcpy (prodid, usname, prodidl);	/* move product id */
    	}
    }
    return;
}

static	struct	tval	refd = {	/* def/ext definition entry */
		TYPX,		/* type is def/ext definition */
		0,		/* dsect/abs */
		0,		/* not used */
		0		/* no value yet */
};

/*
 * ref - process def and ext operations
 */

void	ref()
{
/*  struct	symbol	FAR *stp; */
	int32	temp;
	
	if (curops->aug & 1)		/* is this an extern */
	  refd.type = TYPX;		/* yes, set type code */
	else				/* else it is a def (or sdef) */
	  refd.type = TYPU;		/* default to undefined for def */
	do {				/* process ext/def while term is , */
	  unst(0x80080000);		/* term on sp or comma */
	  if (!yeanay())		/* are we assembling */
	    continue;			/* process next element */

	  if (*usname == ' ') {		/* was a name entered */
	    seterr ('F');		/* no, set blank name error */
	    continue;			/* process next element */
	  }
/* stp = ss (&refd, usname);*/	/* search and insert in sym tab */
	  ss (&refd, usname);	/* search and insert in sym tab */
	  if (INTSS & spmac) {		/* was symbol internally generated */
	    seterr ('I');		/* set internal ref error */
	    continue;			/* process next element */
	  }
	  if (refd.type == TYPX)	/* it this an ext directive */
	    continue;			/* yes, no more processing */
	  /* process external definition (def directive) */
	  if (PASS & 1)			/* is this pass 1 */
	    continue;			/* pass 1, nothing else to do */
	  if (symval.type == TYPP) {	/* is this normal prog type aloc */
	    /* yes, publish definition */
	    *hbbs = 0;			/* reset bo stack */
	    if (bits3 & EXPLFC) {	/* using expanded loader funct codes */
	      goto expout;		/* yes, generate exp loader func */
	    }
	    /* using standard loader functions */
	    bfn ();			/* put name from usname onto bo */
/* prtval("def", &symval); */
	    temp = symval.value;	/* get the address */
#ifdef OLD_BAD_WAY
	    if (symval.flags & CSDS)	/* test cs/ds flag */
	      temp |= 0x800000;	/* set csect flag */
#else
	    if (symval.flags & ABSREL)	/* test abs/rel flag */
	      temp |= 0x800000;	/* set rel flag */
#endif
	    bfa (temp);			/* put address on bo stream */
	    pb (hbbs, PTED, 0);		/* output entry point def */
	    continue;			/* do next entry */
	  }
	  if (symval.type != TYPC) {	/* is this common type */
	    seterr ('F');		/* no, set symbol definition error */
	    continue;			/* do next entry */
	  }
	  /* common, publish definition */
	  temp = ((symval.value >> 16) & 0xff);	/* get comm blk # */
	  /* if common block not ssect or sext, error */
	  if (!((hwcmsize[temp] & 0x80000000) || (curops->aug & 2))) {
	    seterr ('F');		/* set symbol definition error */
	    continue;			/* do next entry */
	  }
	  *hbbs = 0;			/* reset bo stack pointer */
expout:					/* generate expanded loader codes */
	  bfb(LFEXTDF);			/* put ldr func sub code into bo */
	  bfb(0);			/* output dummy byte count */
	  bfb(0);			/* output unused byte */
	  if (curops->aug & 2) {	/* is this sext */
	    /* yes, output the definition */
	    temp = (symval.value >> 16) & 0xff;	/* common block # */
	    bfb(temp + 2);		/* output common blk number plus 2 */
	    temp = (symval.value & 0xffff);	/* get offset in common */
	  } else {			/* not sext */
	    /* output section number (dsec/csect) */
	    bfb ((symval.flags & CSDS) ? 1 : 0);
	    temp = symval.value;	/* get the offset address */
	    temp |= ((symval.flags & ABSREL) ? 0x800000 : 0); /* set abs/rel */
	  }
	  bfa (temp);			/* output 3 bytes to bo stack */
	  bfn0 ();			/* output name to bo from usname */
	  pb (hbbs, EXPFUNC, 0);	/* publish definition */
	  continue;			/* do next entry */
	}				/* end do */
	while (hbstac[0] == ',');	/* more defs/exts if comma */
	return;				/* all done, exit */
}

/*
 * res statement
 * normat input 
 */

void	res()
{
	int32	pc;		/* temp pc value */

    	bacflag |= 64;		/* show res statement read */
	grps();			/* evaluate expression */
	if (!yeanay()) return;	/* if not assembling, return */
/*
prtval("res 1 currpc", &currpc);
prtval("res 1 expr[0]", &expr[0]);
printf("res 1 expr[0].value = %x\n", expr[0].value);
*/
	if (expr[0].tmp) 	/* see if non-numeric terminator */
/* CHANGED 03/31/93 ????? */
/*	  bouc (expr[0].value);	*/ /* get PC to correct boundry */
	bouc ((int32)expr[0].tmp);	/* get PC to correct boundry */
	pc = sectpc[pcmode].value;	/* get the program counter */
/* printf("res 1 pc = %x\n", pc); */
	/* retain type code and add res value to pc */
/* printf("res 1 before sectpc[pcmode].value = %x\n", sectpc[pcmode].value); */
	sectpc[pcmode].value = (((expr[0].value & 0x3fffff) +
	  (pc & 0x3fffff)) & 0x3fffff);
/*
printf("res 1 after sectpc[pcmode].value = %x\n", sectpc[pcmode].value);
prtval("res 2 sectpc", &sectpc[pcmode]);
*/
    	pcchk();		/* check pc for overflow */
	tall();			/* allocate current label */
	if (yeanay()) {		/* are we assembling */
	  bits |= CVFL;		/* set flag to print prog cntr */
	}
	return;
}

/*
 * rez statement
 * normat input 
 */

void	rez()
{
    	bacflag |= 64;			/* show rez statement read */
	grps();				/* evaluate expression */
	if (!yeanay()) return;		/* if not assembling, return */
/*
prtval("rez 1 currpc", &currpc);
prtval("rez 1 expr[0]", &expr[0]);
prtval("rez 1 expr[1]", &expr[1]);
*/
/*	if (!expr[0].tmp)*/		/* see if non-numeric terminator */
	if (expr[0].tmp)		/* see if non-numeric terminator */
/*	  bouc (expr[0].value);	*/ 	/* get PC to correct boundry */
	bouc ((int32)expr[0].tmp);	/* get PC to correct boundry */
/*
prtval("rez 2 currpc", &currpc);
*/
	tall();				/* allocate current label */
	if ((expr[0].value & 0x7fffff) == 0)  /* largest num of bytes to rez */
	  return;			/* zero bytes to rez, return */
	if (expr[0].value < 0) {  	/* if neg bytes, error */
	  if (yeanay())			/* are we assembling */
	    seterr ('B');		/* set bounding error */
	  return;			/* return for more */
	}
	/* rez number of bytes */
	hbtttf = 0;			/* indicate data to be generated */
	expr[0].value = -expr[0].value;	/* make neg for tdg */
	do {
	  tdg((int32)0, 0, (int)expr[0].value);	/* generate 1 byte of zero's */
	}
	while (++expr[0].value);	/* generate all bytes of zero */
	return;				/* next statement */
}

/*
 * opcodes for unmapped instructions
 */

/* in reset enhanced instruction set (reis) mode */
char	eisrld = 0xae;		/* opcode for lb, lh, lw, ld */
char	eisrst = 0xd6;		/* opcode for stb, sth, stw, std */
char	eisrlr = 0x82;		/* opcode for lear */

/* in set enhanced instruction set (seis) mode */
char	eissld = 0x5e;		/* opcode for lcb,lch,lcw,lcd */
char	eissst = 0x56;		/* opcode for stcb,stch,stcw,stcd */
char	eisslr = 0x5a;		/* opcode for lcra */

/*
 * rseis ()
 * reset/set enhanced instruction set mode
 */

void	rseis()
{
	if (yeanay()) {			/* are we assembling */
	  if (PASS & 1)return;		/* ignore if pass 1 */
	  if (!strncmp(usname, "SEIS", 4))	/* is it SEIS */
	    eisset();			/* force opcodes to SEIS mode */
	  else
	  if (!strncmp(usname, "REIS", 4))	/* is it REIS */
	    eisreset();			/* force opcodes to REIS mode */
	}
	return;				/* return for NEXT */
}

/*
 * set opcodes to SEIS mode
 */

void	eisset()
{
	eismerge (EISON);		/* set opcodes */
	return;
}

/*
 * reset opcodes to REIS mode
 */

void	eisreset()
{
	eismerge (EISOFF);		/* reset opcodes */
	return;
}

/*
 * merge point for set/reset opcodes to/from SEIS mode
 */

void	eismerge(onoff)
int	onoff;		/* on/off flag */
{
	int	i;

	for (i=0; i<4; i++) {
	  if (onoff)opstab[i].binop = eissld;	/* set reis mode */
	  else opstab[i].binop = eisrld;	/* set seis mode */
	  if (onoff)opstab[i+4].binop = eissst; /* set reis mode */
	  else opstab[i+4].binop = eisrst;	/* set seis mode */
	}
	if (onoff)opstab[8].binop = eisslr;	/* set reis mode */
	else opstab[8].binop = eisrlr;		/* set seis mode */
	return;
}

/*
 * sdirs - process section directives
 */

void	sdirs()
{
/*	int	cnts; */
	int	temp;
	char	dummy[8];
	struct	tval	sdef;

	switch (curops->aug) {		/* go to proper type routine */

	  case 2:			/* sorg directive */

/*	cnts = inscnt;	*/		/* save input buffer pointer */
	val(0);				/* skip blanks and get value */
	if (!yeanay())			/* are we assembling */
	  return;			/* return if not assembling */
	if (inac.type == TYPC) {	/* is val type common */
	  /* type is common, see if same block # */
	  if (((int32)(sectpc[PCCOM].value & 0xff0000) >> 16) != inacbn)
	    /* not same block, error */
	    goto sorg2;			/* it is an error */
	}
	if (pcmode == PCCOM) {		/* is curr sect common */
	  /* yes, is it an ssect */
	  if (hwcmsize[(int32)(sectpc[PCCOM].value & 0xff0000) >> 16]
	    & 0x80000000)
	    /* yes, process it */
	    goto sorg3;			/* process sorg */
	}
sorg2:					/* we have an error */
 	seterr ('Q');			/* set section error */
sorg0:
	currpc = sectpc[pcmode];	/* staticize PC */
	tall();				/* allocate current label */
	if (yeanay())			/* are we assembling */
	  bits |= CVFL;			/* set flag to print prog cntr */
	return;

sorg3:					/* process common type */
	if (inac.type != TYPC) {	/* is type already common */
	  /* type not common, we need to check it further */
	  /* set up to fake out val */
	  hbstac[0] = '+';		/* set terminator to + */
	  hbstac[1] = ' ';		/* prev was blank */
/*	  cnts = inscnt;    */	/* reset count */
	  inag = sectpc[PCCOM];		/* get common sect info */
	  inag.value &= 0xffff0000;	/* with offset zero */
	  bits2 |= ALVAL;		/* indicate 1st operand evaluation */
	  val(0);			/* tell val unstrung */
	}
	temp = (sectpc[PCCOM].value >> 16) & 0xff;	/* common blk # */
	/* see if we need to save size */
	if ((sectpc[PCCOM].value & 0xffff) > (hwcmsize[temp] & 0xffff))
	  hwcmsize[temp] = ((hwcmsize[temp] & 0xffff0000) | 
	    (sectpc[PCCOM].value & 0xffff));	/* or in new size */

	/* force inac to have type common and abs/dsect flags */
	inac.flags = 0;			/* abs/dsect */
	inac.type = TYPC;		/* type of common */
	/* set section # to that in pc */
	inacbn = ((int32)(sectpc[PCCOM].value & 0x00ff0000) >> 24);
	sectpc[PCCOM] = inac;		/* save new definition */
	sectpc[PCCOM].value = ((sectpc[PCCOM].value & 0xffff0000) |
	  ((int32)inacbn << 16));	/* or in block number */
	goto sorg0;			/* finish up and exit */
	
	  case 1:			/* ssect directive */

	if (yeanay()) {			/* are we assembling */
	  unst(0x80c80000);		/* yes, unstring on sp , ( ) */
	  if ((hbstac[0] = ' '))	/* space terminator */
	    goto ssect1;		/* only 1 symbol, o.k. */
/* printf("ssect: X error\n"); */
	  seterr ('X');			/* set section error */
	}
	unst(0x80000000);		/* unstring, term on space */
	return;				/* done */

ssect1:
	memcpy(dummy, usname, 7);	/* copy 7 chars of name */
	dummy[7] = ' ';			/* truncate to 7 chars */
	ss (&ud, dummy);		/* search symbol table */
	if (symval.type == TYPC) {	/* is type common */
	  /* symbol is common, see if ssect */
	  if (hwcmsize[(int32)(symval.value & 0xff0000l) >> 16] & 0x80000000) {
	    /* yes, process it */
	    if (usname[7] != ' ')	/* is name <= 7 chars */
/* printf("ssect1: X error\n"); */
	      seterr ('X');		/* no, set section definition error */
	    goto ssect21;		/* merge code */
	  } else {			/* not ssect, error */
	    seterr ('M');		/* set multiple definition error */
	    return;
	  }
	}				/* not common type */
	if (symval.type != TYPU) {	/* type undefined */
	  if (symval.type == TYPM)	/* multiple defined */
	    clrerr('M');		/* yes, change error from M to J */
	  seterr ('J');			/* set J error */
	  return;
	}				/* type is undefined */
	/* define new ssect */
	if (hbccct > 254) {		/* see if too many sections */
	  seterr ('Z');			/* set section definition error */
	  return;
	}
	hwcmsize[hbccct] &= 0x80000000;	/* make it into ssect */
	sdef.type = TYPC;		/* set type for common */
	sdef.flags = 0;			/* no flags for common */
	sdef.value = (int32)hbccct << 16;	/* set blk # with 0 offset */
	if (usname[7] != ' ')		/* is name <= 7 chars */
	  seterr ('X');			/* no, set section definition error */
	ss (&sdef, dummy);		/* alloc symbol to common block */
	sdef.type = TYPD;		/* set type for common blk def */
	memcpy(&dummy[1], usname, 7);	/* copy 7 chars of name */
	dummy[0] = ')';			/* prepend name with a ) */
	ss (&sdef, dummy);		/* define the section name */
	hbccct++;			/* increment common block # */
ssect21:
	usname[7] = ' ';		/* force last char to a blank */
	val(1);				/* evaluate unstrung element */
	/* see if curr common blk # is same as new blk # */
	temp = (sectpc[PCCOM].value >> 16) & 0xff;	/* common blk # */
	if (temp == inacbn)		/* are they the same */
	  /* they are the same, make sure curr sect is common */
	  if (pcmode == PCCOM)		/* make sure common */
	    goto sorg0;			/* yes, go finish up */

	/* not the same, fixup some stuff */
	if (hwcmsize[temp] & 0x80000000) {	/* is section an ssect */
	  /* see if we need to save size */
	  if ((sectpc[PCCOM].value & 0xffff) > (hwcmsize[temp] & 0xffff))
	    hwcmsize[temp] = ((hwcmsize[temp] & 0xffff0000) | 
	      (sectpc[PCCOM].value & 0xffff));	/* or in new size */
	}
	sectpc[PCCOM].type = inac.type;	/* set new type */
	sectpc[PCCOM].value = ((((hwcmsize[inacbn] & 0xffff) + inac.value)
	  & 0xffff) | ((int32)inacbn << 16));	/* or in block number */
	pcmode = PCCOM;			/* set the PC pointer to common */
	goto sorg0;			/* go finish up */

	  case 3:			/* sext directive */

	if (yeanay()) {			/* are we assembling */
	  hwdpnum = 255;		/* value for sect in datapool defs */
	  dpcom();			/* go process as datapool */
	  return;			/* exit */
	}	/* not assembling */
	unst(0x80000000);		/* unstring, term on space */
	return;				/* next statement */
	}	/* end of switch */
	return;
}

/*
 * space - process space pseudo-op
 */

void	space(cpass)
char cpass;
{
	int	lines;

#ifdef DSPACE
	unsigned short *Sptr;		/* stack pointer */
	Sptr = (unsigned short *)&cpass;	/* address */
	DumpStk(Sptr,64);
#endif

#ifdef DSPACE
printf("space: enter\n");
#endif
	val(0);				/* get number of lines to space */
	lines = inac.value & 0x7fffff;	/* the value */
#ifdef DSPACE
printf("space: lines = %d\n", lines);
#endif
	if (lines < 1)			/* 1 is the minimum */
	  lines = 1;			/* at least 1 line */
	if (lines >= 60) {		/* max allowed */
	  if (yeanay())			/* are we assembling */
	    seterr ('G');		/* set invalid space error */
	  return;			/* go release image and don't space */
	}
	if (PASS & 1)			/* is this pass 1 */
	  return;			/* yes, wait till pass 2 */
	if (bits & APON)		/* listing allowed */
	  return;			/* no, just leave */
	/* if expanding a macro, is expansion list allowed */
	if ((macstate & EXPAND) && (bits2 & MACPRINT))
	  return;			/* no, just return */
	/* if generating rept code, is expansion list allowed */
	if ((macstate & RPTGEN) && (bits2 & REPPRINT))
	  return;			/* no, just return */
	if (!yeanay()) return;		/* return if not assembling */
#ifdef DSPACE
printf("space: calling ppp for %d lines\n", lines);
#endif
	do {				/* loop to print request lines */
	  char tspace[8];
	  memset(tspace, ' ', 8);
	  /* print 4 spaces, and tell ppp no errors on this line */
	  if (ppp (4, tspace, 0))	/* print the line, see if TOF reached */
#ifdef OLDWAY
	  /* print 4 spaces, and tell ppp no errors on this line */
	  if (ppp (4, "    ", 0))	/* print the line, see if TOF reached */
#endif
	    break;			/* new page reached, exit loop */
	} while (--lines);		/* decr cnt and check if done */
	bits &= ~IMIN;			/* indicate no buffer image ready */
#ifdef DSPACE
	DumpStk(Sptr,64);
#endif
#ifdef DSPACE
printf("space: exit\n");
#endif
	return;				/* return */
}

/*
 * titl - get title
 */
void	titl()
{
	char	chr;
	char	*til = TCWTITL;
    uint8	hbtitm = 0;	/* count for title */

	memset(TCWTITL, ' ',TCWTTLE-TCWTITL);	/* clear title buffer */
	do {
	  chr = gbyt(0x80800000);	/* get a byte */
	}
	 while ((inscnt < 72) && (chr == ' '));
	/* non blank char found */
	if (!(PASS & 1)) {		/* if pass 2 store char */
	  if (inscnt < 72)
	    til[hbtitm++] = chr;	/* store the char */    
	}
	
	while ((inscnt < 72) && (hbtitm < (TCWTTLE-TCWTITL))) {
	  chr = gbyt(0x80800000);	/* get a byte */
	  if (!(PASS & 1)) {		/* if pass 2 store char */
	    if (yeanay()) {		/* are we assembling */
	      til[hbtitm++] = chr;	/* store the char */    
	    }
	  }
	}
	pagp();				/* do page eject */
	return;
}

/*
 * stab - process debugger commands
 *	.SRC	source statement
 *	.COM	comment line
 *	.ARG	argument
 *	.XEQ	executable line
 *	.SYM	a symbol definition
 *	.END	end of executable code
 *	.STAB	symbol definition
 *	.STABC	symbol definition continuation (structs, unions, etc.)
 */

unsigned char lastsdot[9];	/* last s. or c. input */

void stab()
{
    int	temp;
    int32 temp2;
    int charcnt = 0; /* chars in src line */
    int	blnkcnt = 0; /* blanks at start of line */
    unsigned char sline[80];	/* the source line */
    unsigned char chr;	/* the character read in */
    char dummy[12];	/* dummy loc for usname */
    char suname[12]; 	/* struct/union name */
    int lower[16];	/* lower bound, always zero */
    int upper[16];	/* upper bound, size - 1 */
    int	ptrcnt = 0;	/* count of ptr cmd found */
    int	arycnt = 0;	/* count of ary cmd found */
    int type = 2;	/* default to int */
    int size = 0;	/* variable size */
    int regval = 0;	/* register number */
    int	offset;		/* stack offset */
    int nosym = 0;	/* auto, reg, or hsym if set */
    int flags = 0;	/* flags byte to output */

    memset(suname, ' ',12);	/* clear name buffer */
    switch (curops->aug) {
    	case 0x4:	/* .sym */
    	    /* unstring one element skipping leading blanks. */
    	    /* Name in usname. Get _symbol we are defining */
    	    unst(0x80000000);		/* unstring, term on space */
    	    /* was a name entered */
    	    if (*usname == ' '){
    		seterr ('F');		/* no, set blank name error */
    		return;			/* process next element */
    	    }
    	    memcpy(dummy, usname, 8);	/* get the symbol, if any */
    	    dummy[8] = '\0';		/* null terminate it */
loopy:
    	    unst(0x80000000);		/* unstring item, term on space */
    	    if (*usname == ' ')		/* see if done */
    		goto wedone;		/* no more info, build symbol */
    	    usname[8] = 0;		/* null terminate 5 char directive */
    	    str2upr(usname);		/* force to uppercase */
/* fprintf(stderr, "scan val [%.8s]\n", usname); */
    	    if (!strncmp(usname, "PTR ", 4)) {  /* pointer type */
    		ptrcnt++;		/* incr for each one */
    		flags |= 0x20;		/* set bit 26 for pointer */
    	    } else
    	    if (!strncmp(usname, "ARY ", 4)) {  /* see if array def */
    		/* get lower array information */
    		val(0);			/* skip spaces & get value */
    		lower[arycnt] = inac.value;	/* get the value */
    		/* get upper array information */
    		val(0);			/* skip spaces & get value */
    		upper[arycnt] = inac.value;	/* get the value */
    		arycnt++;		/* incr for each one */
    		flags |= 0x40;		/* set bit 25 for array */
    	    } else
    	    if (!strncmp(usname, "CHAR", 4))  /* char variable */
    		type = 0;
    	    else
    	    if (!strncmp(usname, "SHORT", 5))  /* short variable */
    		type = 1;
    	    else
    	    if (!strncmp(usname, "INT ", 4))  /* int variable */
    		type = 2;
    	    else
    	    if (!strncmp(usname, "LONG", 4))  /* long variable */
    		type = 3;
    	    else
    	    if (!strncmp(usname, "FLOAT", 5))  /* float variable */
    		type = 4;
    	    else
    	    if (!strncmp(usname, "DOUBLE", 6))  /* double variable */
    		type = 5;
    	    else
    	    if (!strncmp(usname, "STRUCT", 6)) {  /* struct variable */
    		type = 6;
    		unst(0x80000000);	/* unstring structure name */
    					/* term on space */
    		usname[8] = 0;		/* null terminate 8 char name */
    		memcpy(suname, usname, 8);	/* save the name */
    		suname[8] = '\0';	/* null terminate it */
    		flags |= 0x08;		/* set bit 28 for s/u ref */
    	    } else
    	    if (!strncmp(usname, "UNION", 5)) {  /* union variable */
    		type = 7;
    		unst(0x80000000);	/* unstring union name */
    					/* term on space */
    		usname[8] = 0;		/* null terminate 8 char name */
    		memcpy(suname, usname, 8);	/* save the name */
    		suname[8] = '\0';	/* null terminate it */
    		flags |= 0x08;		/* set bit 28 for s/u ref */
    	    } else
    	    if (!strncmp((char *)usname, "UCHAR", 5))  /* uchar variable */
    		type = 8;
    	    else
    	    if (!strncmp((char *)usname, "USHORT", 6))  /* ushort variable */
    		type = 9;
    	    else
    	    if (!strncmp((char *)usname, "UINT", 4))  /* uint variable */
    		type = 10;
    	    else
    	    if (!strncmp((char *)usname, "ULONG", 5))  /* ulong variable */
    		type = 11;
    	    else
    	    if (!strncmp((char *)usname, "ENUM", 4)) {  /* enum variable */
    		type = 12;
    		unst(0x80000000);	/* unstring enum name */
    					/* term on space */
    		usname[8] = 0;		/* null terminate 8 char name */
    		memcpy(suname, usname, 8);	/* save the name */
    		suname[8] = '\0';	/* null terminate it */
    		flags |= 0x08;		/* set bit 28 for s/u ref */
	    } else
    	    if (!strncmp((char *)usname, "GSYM", 4)) {  /* global (def) variable */
    		/* get variable size */
    		val(0);			/* skip spaces & get value */
    		size = inac.value;	/* get the value */
    	    } else
    	    if (!strncmp((char *)usname, "ESYM", 4)) {  /* global (ext) variable */
    		type = -1;		/* do not output extern's */
    		/* get variable size */
    		val(0);			/* skip spaces & get value */
    		size = inac.value;	/* get the value */
    	    } else
    	    if (!strncmp((char *)usname, "LSYM", 4)) {  /* local variable */
    		/* get variable size */
    		val(0);			/* skip spaces & get value */
    		size = inac.value;	/* get the value */
    	    } else
    	    if (!strncmp((char *)usname, "GFTN", 4)) {  /* global (ext) function */
    		/* get variable size */
    		val(0);			/* skip spaces & get value */
    		size = inac.value;	/* get the value */
    	    } else
    	    if (!strncmp((char *)usname, "SFTN", 4)) {  /* static function */
    		/* get variable size */
    		val(0);			/* skip spaces & get value */
    		size = inac.value;	/* get the value */
    	    } else
    	    if (!strncmp((char *)usname, "PARM", 4)) {  /* local parameter */
    		/* get variable size */
    		val(0);			/* skip spaces & get value */
    		size = inac.value;	/* get the value */
    		/* get offset in stack */
    		val(0);			/* skip spaces & get value */
    		offset = inac.value;	/* get the value */
    		nosym = 1;		/* not in symbol table */
    		flags |= 0x10;		/* set bit 27 for stack variable */
    		flags |= 0x02;		/* set bit 30 for abs address */
    	    } else
    	    if (!strncmp((char *)usname, "USYM", 4)) {  /* unknown variable */
    		/* get variable size */
    		val(0);			/* skip spaces & get value */
    		size = inac.value;	/* get the value */
    	    } else
    	    if (!strncmp((char *)usname, "RSYM", 4)) {  /* register variable */
    		/* get variable size */
    		val(0);			/* skip spaces & get value */
    		size = inac.value;	/* get the value */
    		/* get register number */
    		val(0);			/* skip spaces & get value */
    		regval = inac.value;	/* get the value */
    		offset = inac.value;	/* get the value */
    		nosym = 1;		/* not in symbol table */
    		flags |= 0x04;		/* set bit 29 for register */
    		flags |= 0x02;		/* set bit 30 for abs address */
    	    } else
    	    if (!strncmp((char *)usname, "AUTO", 4)) {  /* stack variable */
    		/* get variable size */
    		val(0);			/* skip spaces & get value */
    		size = inac.value;	/* get the value */
    		/* get offset in stack */
    		val(0);			/* skip spaces & get value */
    		offset = inac.value;	/* get the value */
    		nosym = 1;		/* not in symbol table */
    		flags |= 0x10;		/* set bit 27 for stack variable */
    		flags |= 0x02;		/* set bit 30 for abs address */
    	    } else
    	    if (!strncmp((char *)usname, "HSYM", 4)) {  /* hidden static variable */
    		/* get variable size */
    		val(0);			/* skip spaces & get value */
    		size = inac.value;	/* get the value */
    		/* get assigned label address */
    		val(0);			/* skip spaces & get value */
    		offset = inac.value;	/* get the value */
    		nosym = 1;		/* not in symbol table */
    	    } else {			/* not valid directive */
    		if (yeanay()) {		/* are we assembling */
    		    seterr ('K');	/* set invalid .sym directive error */
    		return;			/* just get out */
    		}
    	    }				/* valid entry found */
    	    goto loopy;			/* get next one */
 wedone:
    	    charcnt = 0;		/* char count for title */
    	    blnkcnt = 0;		/* count of blanks */
    	    memset(sline, ' ',80);	/* clear source buffer */
    	    /* process debugger record */
    	    if (PASS & 1)		/* is this pass 1 */
    		return;			/* pass 1, nothing else to do */
    	    if (!(option & DBG))	/* see if debug info to go out */
    		return;			/* no, just get out */
    	    if (type == -1)		/* see if extern */
    		return;			/* yes, do nothing */
    	    if (nosym) {		/* not in symbol table */
    		symval = ud;		/* we are undefined */
    		symval.flags = 0;	/* in stack, reg, or dsect */
    		symval.value = offset;	/* set offset */
    	    } else {
    		/* lookup the symbol in symbol table */
    		ss (&ud, dummy);	/* search symbol table */
    	    }
    	    /* symval will have symbol information */
    	    *hbbs = 0;			/* reset bo stack */
    					/* generate expanded loader codes */
    	    bfb(LFCDBUG);		/* put ldr func sub code into bo */
    	    bfb(0);			/* output dummy byte count */
    	    /* output section number (dsect/csect) to flags byte */
    	    temp = (symval.flags & CSDS) ? 1 : 0;
/*    	    temp = (currpc.flags & CSDS) ? 1 : 0; */
    	    flags |= temp;		/* set value for bit 31 */
    	    /* see if an array defined */
#ifdef OLDWAY
    	    if (arycnt)
    		temp |= 0x40;		/* set array def flag */
#endif
    	    bfb(flags);			/* output flags byte */
    	    bits |= CVFL;		/* set flag to print prog cntr */
    	    /* ptrcnt determines type modification */
#ifdef OLDWAY
    	    if (ptrcnt == 0)
    		bfb(type);		/* output base type */
    	    else
    	    if (ptrcnt == 1)
    		bfb(type + 64);		/* output pointer type */
    	    else
    	    if (ptrcnt == 2)
    		bfb(type + 96);		/* output ptr ptr type */
    	    else			/* more than ptr ptr, do base */
    		bfb(type);		/* output base type */
#endif
    	    bfb(type);			/* output base type */
    	    bfb(ptrcnt);		/* output pointer level byte */
    	    bfh(size);			/* output halfword of size */
    	    if (regval)			/* see if reg variable */
    		bfw(regval << 3);	/* output 4 bytes to bo stack */
    	    else {
    		temp2 = symval.value << 3;	/* get current address */
/*    		temp2 = currpc.value << 3;	*/ /* get current address */
/*    		temp2 = sectpc[pcmode].value << 3; */ /* get current address */
/* fprintf(stderr, "addr: %x\n", temp2); */
/*    	temp2 = sectpc[PCCS].value << 3;	*/ /* get current address */
    		bfw(temp2);		/* output 4 bytes to bo stack */
    	    }
    	    memcpy(usname, dummy, 8);	/* get the symbol, if any */
    	    bfn0a();			/* output 8 chars from usname to bo */
    	    if (flags & 0x08) {		/* see if structure/union reference */
    		memcpy(usname, suname, 8);	/* get the name */
    		bfn0a();		/* output 8 chars from usname to bo */
    	    }
    	    if (arycnt) {		/* look to see if array */
    		bfb(arycnt);		/* output number of indexes */
    		bfb(arycnt * 2);	/* always upper/lower bounds */
    		for (temp = 0, temp2 = 0; temp < arycnt; temp++) {
    		    temp2 |= (1 << (temp * 2));	/* set the bit */
    		} 
    		bfh(temp2);		/* output the flags */
    		bfb(8 + arycnt * 8);	/* total bytes */
    		bfb(0);			/* not used byte */
    		bfh(0);			/* no sym values */
    		for (temp = 0; temp < arycnt; temp++) {
    		    bfw(lower[temp]);	/* output lower bound (0) */
    		    bfw(upper[temp]);	/* output upper bound */
    		}
    	    }
    	    pb(hbbs, EXPFUNC, 0);	/* publish debugger record */
    	    return;			/* all done, exit */

    	case 0x0:	/* .src */
    	case 0x1:	/* .com */
    	case 0x6:	/* .xeq */
    	    /* unstring one element skipping leading blanks. */
    	    /* Name in usname. Get S.nn or C.nn or E.nn */
    	    unst(0x80000000);		/* unstring, term on space */
    	    /* was a name entered */
    	    if (*usname != 's') {
    		seterr ('F');		/* no, set blank name error */
    		return;			/* process next element */
    	    }
    	    charcnt = 0;		/* char count for source */
    	    blnkcnt = 0;		/* count of blanks */
    	    memset(sline, ' ',80);	/* clear source buffer */
#ifdef XXXX
    	    if(curops->aug == 6)	/* .xeq */
    	      break;
#endif
    	bits |= INSTAB;			/* ignore ';' and '"' chars */
    	sudo = 1;			/* do tabs mod 8 */
	do {
	  chr = gbyt(0x80800000);	/* get a byte */
	}
	 while ((inscnt < 72) && (chr == ' ') && ++blnkcnt);
    	/* blnkcnt has count of leading blanks */
	/* non blank char found */
	if (!(PASS & 1)) {		/* if pass 2 store char */
	  if (inscnt < 72)
	    sline[charcnt++] = chr;	/* store the char */    
	}
	
    	/* now get the rest of the line */
	while ((inscnt < 72) && (charcnt < 80)) {
	  chr = gbyt(0x80800000);	/* get a byte */
	  if (!(PASS & 1)) {		/* if pass 2 store char */
	    if (yeanay()) {		/* are we assembling */
	      sline[charcnt++] = chr;	/* store the char */    
	    }
	  }
	}
    	bits &= ~INSTAB;		/* allow ';' and '"'chars */
    	sudo = 0;			/* do default tabs */
	while (charcnt > 1) {
    	  if(sline[charcnt - 1] == ' ' || sline[charcnt - 1] == '\t') {
    	    charcnt--;		/* strip trailing blank or tabs */
    	  } else
    	    break;		/* non blank, exit loop */
	}
    	    break;
    	case 0x2:	/* .stab */
    	case 0x3:	/* .stabc */
    	case 0x5:	/* .end */
    	case 0x7:	/* .arg */
    	    return;	/* do nothing yet */
    	    break;
    }

    /* process debugger record */
#ifdef JUNK_NOW
    if (yeanay()) {		/* are we assembling */
      bits |= CVFL;		/* set flag to print prog cntr */
    }
#endif
    if (PASS & 1)		/* is this pass 1 */
    	return;			/* pass 1, nothing else to do */
    if (!(option & DBG))	/* see if debug info to go out */
    	return;			/* no, just get out */
    *hbbs = 0;			/* reset bo stack */
				/* generate expanded loader codes */
    bfb(LFCDBUG);		/* put ldr func sub code into bo */
    bfb(0);			/* output dummy byte count */
    /* output section number (dsect/csect) to flags byte */
    if(curops->aug == 6) {	/* .xeq */
#ifndef TEMP_FIX
#ifdef NASA_FIX_052794
    	bfb((currpc.flags & CSDS) ? 1 : 0);
#else /* NASA_FIX_052794 */
    	bfb(1);			/* show as CSECT always */
#endif /* NASA_FIX_052794 */
#else
    	bfb(1);			/* show as CSECT always */
#endif
    	bits |= CVFL;		/* set flag to print prog cntr */
    } else
    	bfb(1);			/* show as CSECT always */
    bfb(14);			/* output type, 14 - statement label */
    bfb(0);			/* output rsvd unused byte */
    bfh(0);			/* output halfword of size zero */
    temp = sectpc[PCCS].value << 3;	/* get current address */
    bfw(temp);			/* output 4 bytes to bo stack */
    bfn0a();			/* output all 8 chars from usname to bo */
    /* set ISC type, src is not compressed */
    if (curops->aug == 0)	/* .src */
      bfb(0x81);		/* declaration */
    else
    if(curops->aug == 1)	/* .com */
      bfb(0x84);		/* comment */
    else
    if(curops->aug == 6)	/* .xeq */
      bfb(0x82);		/* executable statement */
    else
      bfb(0x81);		/* default to declaration */
    bfb(0);			/* caret value is zero */
    bfb(charcnt);		/* bytes of source */
    bfb(blnkcnt);		/* blanks before 1st byte of source */
    for(temp = 0; temp < charcnt; temp++)
      bfb(sline[temp]);		/* output source chars */
    pb(hbbs, EXPFUNC, 0);	/* publish debugger record */
    return;			/* all done, exit */
}
