/* symbol.c */

#include "defs.h"
#include <ctype.h>
#include <string.h>
/*#include <stdlib.h> */
/*#define DBUGS*/
/*#define SYM*/

#ifdef DOS
#include <malloc.h>
#include <io.h>

struct symbol FAR * ss(struct tval *, char *);
struct symbol FAR * macss(struct tval *, char *, int);
void	prtsymt();
char	FAR * Memcpy(char FAR *, char *, int);
char	* memCpy(char *, char FAR *, int);
int	MemCmp(char FAR *, char FAR *, int);
int	memCmp(char *, char FAR *, int);
#else
struct symbol FAR * ss(/* struct tval *, char * */);
struct symbol FAR * macss(/* struct tval *, char *, int */);
void	prtsymt();
char	FAR * Memcpy(/* char FAR *, char *, int */);
char	* memCpy(/* char *, char FAR *, int */);
int	MemCmp(/* char FAR *, char FAR *, int */);
int	memCmp(/* char *, char FAR *, int */);
#endif

extern void	lnegate();

/* 
**********************************************************************
*        WORD 1 OF EACH SYMBOL TABLE ITEM CONTAINS THE FIRST 4 BYTES *
*                  OF THE SYMBOL NAME (MACRO AND FORM NAMES STORED   *
*                  NEGATED)     FOR LITERALS (BITS0-14=0,            *
* BIT 15 SET INDICATES LITERAL ADDRESS IN WORD 2 IS IN CSECT         *
*                               IF BIT 23 IS SET IN WORD 1           *
* BIT 15 RESET INDICATES LITERAL ADDRESS IN WORD 2 IS IN DSECT       *
*                               IF BIT 23 IS SET IN WORD 1           *
*                  BIT15-22=LITERAL TYPE,BIT23=ABS/REL FLAG OF VALUE,*
*                  BITS24-31=COMMON BLOCK NUMBER IF COMMON TYPE      *
*                  LITERAL OTHERWISE BITS24-31=0)                    *
*        WORD 2 OF EACH SYMBOL TABLE ITEM CONTAINS THE SECOND 4 BYTES*
*                  OF THE SYMBOL NAME (MACRO AND FORM NAMES STORED   *
*                  NEGATED)    FOR LITERALS, WORD 2 = LITERAL VALUE  *
*        WORD 3 OF EACH SYMBOL TABLE ITEM CONTAINS DEFINITION        *
*                  INFORMATION AS DESCRIBED BELOW:                   *
**********************************************************************
*               ( ABS/REL FLAG = 0 IF ABSOLUTE , 1 IF RELOCATABLE)   *
**********************************************************************
**********************************************************************
*  BYTE 0 - SYMBOL TYPE         *  BYTES 1 TO 3 - VALUE              *
**********************************************************************
**********************************************************************
*  UNDEFINED (1)                *  BIT8=ABS/REL FLAG , BITS 9-31=LAST*
*                               *  ADDRESS  IN UNDEFINED STRINGBACK  *
*                               *  CHAIN.                            *
* BIT 0 = DSECT/CSECT FLAG      *                                    *
*   SET - SYMBOL IN CSECT       *                                    *
*   NOT SET - SYMBOL IN DSECT   *                                    *
**********************************************************************
*  LITERAL (2)                  * BITS 8-15 CONTAIN LITERAL          *
*                               * POOL NUMBER (A NUMBER              *
*                               * IN THE RANGE 0 - 124 REPRESENTING  *
*                               * LPOOLS 0 - 31),                    *
*                               * BITS 16-31 CONTAIN THE NUMBER      *
*                               * OF THE LITERAL (0 - 65535)         *
*                               * WITHIN THE LPOOL                   *
* BIT 0 = DSECT/CSECT FLAG      *                                    *
*   SET - SYMBOL IN CSECT       *                                    *
*   NOT SET - SYMBOL IN DSECT   *                                    *
**********************************************************************
*  COMMON SYMBOL NAME (3)       *  BYTE1=BLOCK NUMBER,BYTES2-3=      *
*                               *  DISPLACEMENT FROM BASE OF COMMON  *
*                               *  BLOCK.                            *
**********************************************************************
*  PROGRAM (4)                  *  BIT8=ABS/REL FLAG,BITS9-31=PROGRAM*
*                               *  ADDRESS.                          *
* BIT 0 = DSECT/CSECT FLAG      *                                    *
*   SET - SYMBOL IN CSECT       *                                    *
*   NOT SET - SYMBOL IN DSECT   *                                    *
**********************************************************************
*  MULTIPLY DEFINED (5)         *  BIT8=ABS/REL FLAG,BITS9-31=LAST   *
*                               *  VALUE ASSIGNED TO SYMBOL.         *
* BIT 0 = DSECT/CSECT FLAG      *                                    *
*   SET - SYMBOL IN CSECT       *                                    *
*   NOT SET - SYMBOL IN DSECT   *                                    *
**********************************************************************
*  EXTERNAL (6)                 *  BIT8=ABS/REL FLAG,BITS9-31=ADDR   *
*                               *  OF 2 WORD ENTRY CONTAINING LAST   *
*                               *  EXTERNAL STRINGBACK ADDRESSES     *
* BIT 0 = DSECT/CSECT FLAG      *  FOR DSECT AND CSECT REFERENCES    *
*   SET - SYMBOL IN CSECT       *  DSECT - 1ST WORD  CSECT - 2ND WRD *
*   NOT SET - SYMBOL IN DSECT   *                                    *
**********************************************************************
*  COMMON BLOCK DEFINITION (7)  *  BYTE1=BLOCK NUMBER,BYTES2-3=SIZE  *
*                               *  (IN BYTES) OF COMMON BLOCK.       *
**********************************************************************
*  SET (8)                      *  BIT8=ABS/REL FLAG,BITS9-31=VALUE  *
*                               *  TO WHICH SYMBOL WAS LAST SET.     *
* BIT 0 = DSECT/CSECT FLAG      *                                    *
*   SET - SYMBOL IN CSECT       *                                    *
*   NOT SET - SYMBOL IN DSECT   *                                    *
**********************************************************************
*  MACRO DEFINITION (9)         *  BYTES1-3=DISPLACEMENT FROM BASE OF*
*                               *  MACRO STORAGE TABLE.              *
**********************************************************************
*  FORM DEFINITION (A)          *  BYTES1-3=DISPLACEMENT FROM BASE OF*
*                               *  MACRO STORAGE TABLE.              *
**********************************************************************
*  DATAPOOL (C)                 *  BYTES1-3=ZERO.                    *
**********************************************************************
*/

char	dpitem[8];			/* last datapool item */
struct	symbol FAR *symdex;		/* curr symhead address */
struct	symbol FAR *symhead[32];	/* head pointers for symbol table */
struct	symbol FAR *symprevp;		/* last symbol pointer */
struct	tval	symval;			/* last info from table */
struct	symbol FAR *symtab;		/* pointer to 1st symbol table entry */
struct	symbol dumsym;			/* dummy symbol */
#define	KINTL3	33			/* must equal define in goasm.c */

 char *prtyp[] = {
"TYPCON",
"TYPU",
"TYPL",
"TYPC",
"TYPP",
"TYPM",
"TYPX",
"TYPD",
"TYSETSYM",
"TYMACDEF",
"TYFRM",
"TYP0B",
"TYPDP",
"TYP0D",
"TYMACREQ"
};

/*
 * memCpy.c
 * Copy s2 to s1, always copy n bytes.
 * Return s1
 */
char *
memCpy(s1, s2, n)
register char *s1;
register char FAR *s2;
register int n;
{
	register char *os1 = s1;

	while (--n >= 0)
		*s1++ = *s2++;
	return (os1);
}

/*
 * Memcpy.c
 * Copy s2 to s1, always copy n bytes.
 * Return s1
 */
char FAR *
Memcpy(s1, s2, n)
register char FAR *s1;
register char *s2;
register int n;
{
	register char FAR *os1 = s1;

	while (--n >= 0)
		*s1++ = *s2++;
	return (os1);
}

/*
 * memCmp.c
 * Compare n bytes:  s1>s2: >0  s1==s2: 0  s1<s2: <0
 */
int
memCmp(s1, s2, n)
register char *s1;
register char FAR *s2;
register int n;
{
	int diff;

	if (s1 != s2)
		while (--n >= 0)
			if ((diff = *s1++ - *s2++))
				return (diff);
	return (0);
}

/*
 * MemCmp.c
 * Compare n bytes:  s1>s2: >0  s1==s2: 0  s1<s2: <0
 */
int
MemCmp(s1, s2, n)
register char FAR *s1;
register char FAR *s2;
register int n;
{
	int diff;

	if (s1 != s2)
		while (--n >= 0)
			if ((diff = *s1++ - *s2++))
				return (diff);
	return (0);
}

/*
 * ss - symbol table worker
 * input - type = type code 01 - 0C
 *         name = pointer to 8 char ascii name, macs negated
 *	   value = value to put in symbol table
 *	   flags = ABSREL and/or CSDS flags
 * output - returns pointer to symbol table entry, 0 if not found
 *	    symval.type has last type from table
 *	    symval.flags has last flags
 *	    symval.value has last value
 */

struct symbol FAR * ss(dval, name)
struct	tval	*dval;
uint8	*name;
{
	int	headoff;
	struct	symbol FAR *stp;
	int32	val;
	int32	lval;
	int16   ttype;
	struct	strback	FAR *sbp = {0};
	int16 ntype;
#ifdef OLDOLD
	int	*symp;
#endif
	uint8 nname[9];

	lnegate(name, nname);	/* negate name */
	nname[8] = '\0';
#ifdef DBUGS
if(dval->type == TYPL)
printf("ss entry 1 name [%.2x%.2x%.2x%.2x] flags %x type %s value %x\n",
name[4], name[5], name[6], name[7],
dval->flags, prtyp[dval->type], dval->value);
else
if(dval->type == TYFRM || dval->type == TYMACDEF || dval->type == TYMACREQ)
printf("ss entry 2 name [%.8s] flags %x type %s value %x\n",
    nname, dval->flags, prtyp[dval->type], dval->value);
else
printf("ss entry 3 name [%.8s] flags %x type %s value %x\n",
    name, dval->flags, prtyp[dval->type], dval->value);
prtval("ss entry 4", dval);
#ifdef OLDOLD
symp = (int *)name;
printf("ss entry name [%.8s]\n", name);
/* printf("ss entry %x, sym = %x,%x\n", dval, symp[0], symp[1]); */
prtval("entry", dval);
#endif
#endif
	if (*name == '!') {		/* is it an internal symbol */
	  spmac |= INTSS;		/* show internal symbol */
	  headoff = name[4];		/* character for headcell generation */
/* JUNK
         LW        R3,HWLICT        CURRENT LINE COUNT
         TBM       XREFINT,OPTION  ARE WE XREFING INTERNALS
         BNS       SSUNI        NO
         ZMW       REPTYPE         INDICATE SYMBOL REPORT TO XREF
         BL        REPTR          REPORT INT SYM TO XREF.
 */
	} else {
	  struct  tval tmpval;
	  spmac &= ~INTSS;		/* show not internal symbol */
	  /* report to xrefer */
	  tmpval = *dval;
/*	  tmpval.value = lict; */
	  reptr (name, &tmpval, (int32)lict | SSORT);
	  headoff = name[0];		/* character for headcell generation */
	}
	headoff &= 0x1f;		/* 1 of 32 only */
	if ((stp = symhead[headoff])) {	/* any entries in the head yet */

#ifdef DBUGS
printf("ss head # %d has entry %x name %.2x%.2x%.2x%.2x\n", headoff, (uint32)stp,
name[4], name[5], name[6], name[7]);
printf("ss literal entry name [%.2x%.2x%.2x%.2x] flags %x type %s value %x\n",
name[4], name[5], name[6], name[7],
dval->flags, prtyp[dval->type], dval->value);
#endif

	  for(;;) {			/* do forever */
		unsigned char ntmp[9];
		lnegate(stp->sym, ntmp);	/* negate name */
		ntmp[8] = '\0';
	    val = memCmp(name, stp->sym, 8);	/* test symbol */
#ifdef DBUGS
if(dval->type == TYFRM || dval->type == TYMACDEF || dval->type == TYMACREQ)
	printf("ss cmp1 neg stp %x, val %x, comparing name = %.8s sym = %.8s\n", (uint32)stp, val, nname, stp->sym);
else
	printf("ss cmp2 reg stp %x, val %x, comparing name = %.8s sym = %.8s\n", (uint32)stp, val, name, stp->sym);
#endif
	    if (val == 0)goto gotsym;	/* if found, process it */
	    if (val < 0)
	      stp = stp->llink;		/* if less, follow decending link */
	    else
	      stp = stp->rlink;		/* else, follow asending link */
	    if(stp)continue;		/* if valid link, continue */
	    break;			/* not here, return */
	  }
	}
#ifdef DBUGS
printf("ss sym not found head # %d has entry %x\n", headoff, (uint32)symhead[headoff]);
#endif
	/* name not found in symbol table */
	symdex = symhead[headoff];	/* save head cell */
	/* entry not found */
	if (dval->type == TYMACREQ) {	/* was this macro request */
	  /* if macro request, then o.k. if name not found */
	  return ((struct symbol FAR *)0);	/* o.k., return not found */
	}
	if (!(PASS & 1)) {		/* is this pass 2, if so error */
	  seterr ('T');			/* set symbol table error */
	}
	/* insert new entry into symbol table */
	/* get mem for symbol entry */
#ifdef DOS
	stp = (struct symbol FAR *)_fmalloc(sizeof(struct symbol));
#else
	stp = (struct symbol *)calloc(sizeof(struct symbol), sizeof(char));
#endif
	if (!stp)			/* if no memory terminate assemble */
 	  abortm("** UNABLE TO ALLOCATE MEMORY FOR SYMBOL TABLE ENTRY **");

	if (symprevp) symprevp->flink = stp;  /* set forward link */
	else symtab = stp;			/* set start of symbol table */
	symprevp = stp;				/* set prev ptr to current */
	if (dval->type == TYPX) {	/* if type extern, alloc stringbacks */
	  /* get memory for stringback entry */
#ifdef DOS
	  sbp = (struct strback FAR *)_fmalloc(sizeof(struct strback));
#else
	  sbp = (struct strback *)calloc(sizeof(struct strback), sizeof(char));
#endif
	  if (!sbp)			/* if no memory terminate assemble */
 	    abortm("** UNABLE TO ALLOCATE MEMORY FOR STRING BACK POINTERS **");
	  stp->desc.type = dval->type;	/* mark as external */
	  stp->desc.flags = dval->flags;  /* set sect & relocation flags */
	  stp->desc.value = (int32)sbp;	/* set stringback pointer */
#ifdef DBUGS
printf("ss EXT entry stp = %x, sbp = %x, sym = %.8s\n", (uint32)stp, (uint32)sbp, name);
prtval("TYPX 1st sb", &stp->desc);
#endif
	}
	if (!symhead[headoff])		/* if head cell empty, initialize it */
	  symhead[headoff] = stp;	/* set entry address */
	symdex = symhead[headoff];	/* start at saved head cell */
	Memcpy(stp->sym, name, 8);	/* copy in symbol name */
	stp->flink = (struct symbol FAR *)0;	/* insure null forward link */
	for (;;) {			/* scan until opening found */
	  val = MemCmp(stp->sym, symdex->sym, 8);	/* do compare */
#ifdef DBUGS
printf("ss srh reg stp %x, symdex %x, comparing name %.8s sym %.8s\n",
    (uint32)stp, (uint32)symdex, stp->sym, symdex->sym);
#endif
	  if ( val < 0) {		/* new less than last, decend */
	    if (symdex->llink) {	/* is there a link here? */
	      symdex = symdex->llink;	/* get next decending link address */
	      continue;			/* follow link */
	    }
	    symdex->llink = stp;	/* set decending link to new entry */
	  } else
	  if ( val > 0) {		/* new greater than last, ascend */
	    if (symdex->rlink) {	/* is there a link here? */
	      symdex = symdex->rlink;	/* get next decending link address */
	      continue;			/* follow link */
	    }
	    symdex->rlink = stp;	/* set ascending link to new entry */
	  }
	  stp->llink = (struct symbol FAR *)0;	/* clear new entry */
	  stp->rlink = (struct symbol FAR *)0;	/* clear new entry */
#ifdef DBUGS
if(dval->type == TYFRM || dval->type == TYMACDEF || dval->type == TYMACREQ)
	printf("ss added new entry %x, sym = %.8s, val = %x, typ = %s, flags = %s,%s\n",
 	(uint32)stp, nname, stp->desc.value, prtyp[stp->desc.type],
	 (stp->desc.flags & CSDS ? "CSECT" : "DSECT"),
	 (stp->desc.flags & ABSREL ? "REL" : "ABS"));
else
printf("ss added new entry %x, sym = %.8s, val = %x, typ = %s, flags = %s,%s\n",
	 (uint32)stp, name, stp->desc.value, prtyp[stp->desc.type],
	 (stp->desc.flags & CSDS ? "CSECT" : "DSECT"),
	 (stp->desc.flags & ABSREL ? "REL" : "ABS"));
#endif
	  break;			/* go do next entry */
	}				/* end of forloop for insertion */
	if (dval->type == TYPX) {	/* init stringback values if extern */
	  sbp->dsdesc = *dval;		/* do csect */
	  sbp->csdesc = *dval;		/* do dsect */
#ifdef DBUGS
printf("EXT init stp = %x, sbp = %x, sym = %.8s\n", (uint32)stp, (uint32)sbp, name);
prtval("TYPX 2nd sb", &stp->desc);
prtval("TYPX 2nd ds", &sbp->dsdesc);
prtval("TYPX 2nd cs", &sbp->csdesc);
#endif
	} else {			/* init normal entry */
	  stp->desc = *dval;		/* set symbol info */
	}
symret:
	symval = stp->desc;		/* get old values */

#ifdef DBUGS
if(dval->type == TYFRM || dval->type == TYMACDEF || dval->type == TYMACREQ)
printf("return1 from ss entry %x, sym = %.8s, val = %x, typ = %s, flags = %s,%s\n",
	 (uint32)stp, nname, stp->desc.value, prtyp[stp->desc.type],
	 (stp->desc.flags & CSDS ? "CSECT" : "DSECT"),
	 (stp->desc.flags & ABSREL ? "REL" : "ABS"));
else
printf("return2 from ss entry %x, sym = %.8s, val = %x, typ = %s, flags = %s,%s\n",
	 (uint32)stp, name, stp->desc.value, prtyp[stp->desc.type],
	 (stp->desc.flags & CSDS ? "CSECT" : "DSECT"),
	 (stp->desc.flags & ABSREL ? "REL" : "ABS"));
#endif
	return (stp);			/* return symbol pointer */

gotsym:
#ifdef DBUGS
printf("gotsym found head # %d has entry %x\n", headoff, (uint32)symhead[headoff]);
#endif
	/* entry found, stp points to it */
	ttype = stp->desc.type;		/* just get the type */
	ntype = dval->type;		/* just get the type */
	if (ttype == TYPM) {		/* is the symbol multiple defined */
	  return(stp);			/* return pointer */
	}
	/* is type literal, undefined, or macro request */
	if (ntype <= TYPL || ntype >= TYMACREQ) {

	  /* see if table code was datapool */
	  if (ttype == TYPDP) {		/* is table code datapool */
	    symval = stp->desc;		/* get old values */
	    dpnum = (symval.value >> 16) & 0xff;	/* dp num */
	    symval.value &= 0xffff;	/* just value */
	    symval.flags = ABSREL;	/* rel data */
	    symval.type = TYPP;		/* just program type */
	    if (DPFLG & dpflags) {	/* is it multiply defined? */
	      seterr ('V');		/* set undefined error */
	      dpnum = 0;		/* clear dp number */
	      symval = *dval;		/* get input values */
	      return(stp);		/* return symbol pointer */
	    }
	    dpflags |= DPFLG;		/* set dp item flag */
	    Memcpy(dpitem, name, 8);	/* copy in symbol name */
#ifdef DBUGS
printf("symbol: datapool2 stp %x, name [%.8s]\n", (uint32)stp, name);
prtval("TYPDP2 dval", dval);
prtval("TYPDP3 dval", &symval);
#endif
	    return(stp);		/* return symbol pointer */
	  }

	  if (ttype == TYPU) {		/* was old type undefined */
	    seterr ('U');		/* set undefined error */
	    symval = stp->desc;		/* get old values */
	    stp->desc = *dval;		/* update with new value */
	    return(stp);		/* return symbol pointer */
	  }
	  if (ttype != TYPX) 		/* is type external */
	    goto symret;		/* no, set old info and exit */
	  if (curops->opproc >= KINTL3) { /* is external allowed for opcode */
	    seterr ('A');		/* no, set addressing error */
	    goto symret;		/* no, set old info and exit */
	  }
	  /* process an external stringback */
	  sbp = (struct strback FAR *)stp->desc.value; /* get stringback ptr */
	  if (pcmode != PCCS) { 	/* is current section not csect */
#ifdef COMPILER_BUG_FIXED
	    int *tf = (int*)&sbp->dsdesc;
	    int *tt = (int*)&symval;
	    tt[0] = tf[0];
	    tt[1] = tf[1];
#else
	    /* we have dsect */
	    symval = sbp->dsdesc;	/* get old values */
#endif
	    sbp->dsdesc = *dval;	/* update with new value */
	    sbp->dsdesc.type = TYPX;	/* set external type */
	  } else {
	    /* we have csect */
    	    if (option & ASECT &&	/* auto sectioning */
    	      option & OPT11 &&		/* option 11 */
    	      extflg & 2) {		/* non branch instr ref */
    	      extflg &= ~2;		/* clear flag */
    	      extflg |= 1;		/* show ext ref record needed */
    	      extwrd = sbp->csdesc;	/* save old value */
    	      memcpy(extnam, name, 8);	/* copy symbol name */
	      symval = sbp->csdesc;	/* get old values */
    	      symval.type = TYPX;	/* type is external */
    	      symval.flags = 0;		/* no flags */
    	      symval.value = 0;		/* stringback to address 0 */
    	    } else {
	      symval = sbp->csdesc;	/* get old values */
	      sbp->csdesc = *dval;	/* update with new value */
    	    }
	    sbp->csdesc.type = TYPX;	/* set external type */
	  }
#ifdef SYM
printf("EXT proc stp = %x, sbp = %x, sym = %.8s\n", (uint32)stp, (uint32)sbp, name);
prtval("TYPX 3nd sb", &stp->desc);
prtval("TYPX 3nd ds", &sbp->dsdesc);
prtval("TYPX 3nd cs", &sbp->csdesc);
#endif
	  return(stp);			/* old info set, just exit */
	}

	/* is type common symbol, program symbol, common block or set symbol */
	if (ntype == TYPC || ntype == TYPP || ntype == TYPD
	 || (ntype == TYSETSYM)) {
	  /* if table type the same or undefined, update and leave */
	  /* normal pass1 occurance */
	  if (ntype == ttype || ttype == TYPU) {
	    stp->desc = *dval;		/* set new desc in table */
	    goto symret;		/* no, set old info and exit */
	  }
	  /* name is multiple defined, set error */
/*
symp = (int *)name;
printf("ss entry %x, sym = %x,%x\n", dval, symp[0], symp[1]);
prtval("TYPM being set", &stp->desc);
*/
	  seterr ('M');			/* set multiply defined error */
	  stp->desc.type = TYPM;	/* set multiple defined type */
	  goto symret;			/* no, set old info and exit */
	}

	if (ntype == TYPDP) {		/* is it datapool item */
	  stp->desc = *dval;		/* set new desc in table */

/*
printf("symbol: datapool stp = %x, sym = %.8s\n", stp, name);
prtval("TYPDP dval", dval);
*/

	  goto symret;			/* no, set old info and exit */
	}

	/* is type a macro definition or form definition */
	if (ntype == TYMACDEF || ntype == TYFRM) {
	  seterr ('M');			/* set multiply defined error */
	  goto symret;			/* no, set old info and exit */
	}

	if (ttype != TYPU) {		/* is table code undefined */
	  if (ttype == TYPX)		/* no, is table type external */
	    return(stp);		/* yes, just return */
	  seterr ('M');			/* no, set multiply defined error */
	  stp->desc.type = TYPM;	/* set multiple defined type */
	  goto symret;			/* no, set old info and exit */
	}

	/* here we need to turn an undefined into an external definition */
	/* get memory for stringback entry */
#ifdef DOS
	sbp = (struct strback FAR *)_fmalloc(sizeof(struct strback));
#else
	sbp = (struct strback *)calloc(sizeof(struct strback), sizeof(char));
#endif
	if (!sbp)			/* if no memory terminate assemble */
 	  abortm("** UNABLE TO ALLOCATE MEMORY FOR STRING BACK POINTERS **");
	stp->desc.type = TYPX;		/* mark as external */

	lval = stp->desc.value;		/* save old stringback address */
	stp->desc.value = (int32)sbp;	/* set new stringback pointer */

	sbp->dsdesc = *dval;		/* set dsect info */
	sbp->dsdesc.value = lval;	/* set dsect info */
	sbp->csdesc = *dval;		/* set csect info */

	goto symret;			/* no, set old info and exit */
}

struct	symbol	FAR *macprevp;		/* last symbol pointer */
struct	tval	macval;			/* last info from table */
/* pointer to 1st symbol table entry */
struct	symbol FAR *mactab = (struct symbol FAR *)0;

/*
 * macss - macro symbol table worker
 * input - dval = address of a tval structure
 *	   dval.type = type code 01 - 0C
 *	   dval.value = address of macro storage
 *	   dval.flags = parameter count
 *	   dval.tmp = length of macro in bytes
 *
 *         name = pointer to 8 char ascii macro name
 *
 *	   request = action required (MACADD, MACDEL, MACLOOK)
 * output - returns pointer to symbol table entry, 0 if not found
 *	    macval.type has last type from table
 *	    macval.flags has last flags
 *	    macval.value has last value
 */

struct symbol FAR * macss(dval, name, request)
struct	tval	*dval;
char	*name;
int	request;
{
	struct	symbol FAR *stp;
	struct	symbol FAR *nstp;
	int	val;
#ifdef DBUGM
printf("macss entry %x, sym = %.8s request = %x\n", dval, name, request);
prtval("macss entry dval", dval);
#endif
	if (request == MACLOOK || request == MACADD) {
	  if ((stp = mactab)) {		/* any entries in the table yet */
	    for(;;) {			/* do forever */
	      val = memCmp(name, stp->sym, 8);	/* test symbol */
	      if (val == 0)goto gotsym;	/* if found, process it */
	      if (val < 0)
	        stp = stp->llink;	/* if less, follow decending link */
	      else
	        stp = stp->rlink;	/* else, follow ascending link */
	      if(stp)continue;		/* if valid link, continue */
	      break;			/* not here, return */
	    }
	  }
	}

	/* name not found in symbol table */
	if (request == MACLOOK) {	/* was this macro request */
	  return ((struct symbol FAR *)0);	/* yes, return not found */
	}

	/* insert new entry into symbol table */
	/* get mem for symbol entry */
#ifdef DOS
	stp = (struct symbol FAR *)_fmalloc(sizeof(struct symbol));
#else
	stp = (struct symbol *)malloc(sizeof(struct symbol));
#endif
	if (!stp)			/* if no memory terminate assemble */
 	  abortm("** UNABLE TO ALLOCATE MEMORY FOR MACRO TABLE ENTRY **");

	/* copy user information in */
	stp->desc = *dval;		/* user stuff */
#ifdef DBUGM
	printf("macss add: name %s\n", name);
	prtval("macss dval", &stp->desc);
#endif
	/* if the value is zero, get some storage */
	if (dval->value == 0) {		/* get 256 bytes of memory */
	  /* get memory for macro storage, default to 256 bytes */
#ifdef DOS
	  stp->desc.value = (int32)_fmalloc(256);
#else
	  stp->desc.value = (int32)malloc((uint32)256);
#endif
	  if (!stp->desc.value)		/* if no memory terminate assemble */
 	    abortm("** UNABLE TO ALLOCATE MEMORY FOR MACRO STORAGE **");
	  stp->desc.tmp = 256;		/* initial storage size */
	}

	if (macprevp) macprevp->flink = stp;  /* set forward link */
	else mactab = stp;		/* set start of symbol table */
	macprevp = stp;			/* set prev ptr to current */
	nstp = stp;			/* set start of symbol table */

	Memcpy(stp->sym, name, 8);	/* copy in symbol name */
	stp->flink = (struct symbol FAR *)0;	/* insure null forward link */
	for (;;) {			/* scan until opening found */
	  val = MemCmp(stp->sym, nstp->sym, 8);	/* do compare */
	  if ( val < 0) {		/* new less than last, decend */
	    if (nstp->llink) {		/* is there a link here? */
	      nstp = nstp->llink;	/* get next decending link address */
	      continue;			/* follow link */
	    }
	    nstp->llink = stp;		/* set decending link to new entry */
	  } else
	  if ( val > 0) {		/* new greater than last, ascend */
	    if (nstp->rlink) {		/* is there a link here? */
	      nstp = nstp->rlink;	/* get next decending link address */
	      continue;			/* follow link */
	    }
	    nstp->rlink = stp;		/* set ascending link to new entry */
	  }
	  stp->llink = (struct symbol FAR *)0;	/* clear new entry */
	  stp->rlink = (struct symbol FAR *)0;	/* clear new entry */
#ifdef DBUGM
printf("added mac %x, sym = %.8s, val = %x, typ = %s, flags = %x, tmp = %x\n",
 stp, name, stp->desc.value, prtyp[stp->desc.type], stp->desc.flags, stp->desc.tmp);
prtval("macss desc", &stp->desc);
#endif
	  break;			/* go do next entry */
	}				/* end of forloop for insertion */

	macval = stp->desc;		/* get old values */
#ifdef DBUGM
prtval("macss exit", &macval);
#endif
	return (stp);			/* return macro symbol pointer */

gotsym:
	/* entry found, stp points to it */
	macval = stp->desc;		/* current parameters */

	if (request == MACADD) {	/* was this macro add request */
	  /* name is multiple defined, set error */
	  seterr ('M');			/* set multiply defined error */
	  stp->desc.type = TYPM;	/* set multiple defined type */
	  macval.type = TYPM;		/* set multiple defined type */
	
	  return ((struct symbol FAR *)0);	/* yes, error, return found */
	}

	if (request == MACLOOK) {	/* was this macro lookup request */
	  return (stp);			/* yes, return found */
	}

	/* must be MACMOD, modify the entry */
	stp->desc = *dval;		/* update with new value */
	return(stp);			/* return symbol pointer */
					/* macval has previous contents */
}

/*
 * print symtab
 */

void	prtsymt()
{
	struct symbol FAR *stp = symtab;	/* address of 1st symbol */

	printf("##### SYMBOL TABLE #####\n");
	while (stp) {
	  if (stp->desc.type == TYMACDEF || stp->desc.type == TYFRM) {
	  printf("prtsymt: stp = %x symbol = %.8s\n", (uint32)stp, csnegate(stp->sym));
	  } else
	  {
	  printf("prtsymt: stp = %x symbol = %.8s\n", (uint32)stp, stp->sym);
	  }
	  prtval("prtsymt", &stp->desc);
	  if (stp->desc.type == TYMACDEF) {
	    int i;
	    struct symbol FAR *mstp = (struct symbol FAR *)stp->desc.value;
	    uchrfp p = (uchrfp)mstp->desc.value;

	    printf("prtsymt: mstp = %x symbol = %.8s\n", (uint32)mstp, mstp->sym);
	    prtval("prtsymt mstp", &mstp->desc);
	    printf("macro %.8s, addr = %x, count = %x\n",
	      mstp->sym, (uint32)p, mstp->desc.tmp);
	    for (i=0; i < mstp->desc.tmp; i++) {
	      if (isprint(*p))
	        printf("%c", *p++);
	      else
	        printf("%.2x", *p++);
	      if (i > 0 && ((i+1)%40 == 0))
		printf("|\n");
	    }
	    printf("|\n");
	  }
	  printf("next stp = %x llink = %x rlink = %x flink = %x\n\n",
	    (uint32)stp, (uint32)stp->llink, (uint32)stp->rlink, (uint32)stp->flink);
	  stp = stp->flink;
	}

	stp = mactab;			/* address of 1st symbol */
	printf("##### MACRO SYMBOL TABLE #####\n");
	while (stp) {
	  printf("prtsymt: stp = %x symbol = %.8s\n", (uint32)stp, stp->sym);
	  prtval("prtsymt", &stp->desc);
	  printf("next stp = %x llink = %x rlink = %x flink = %x\n\n",
	    (uint32)stp, (uint32)stp->llink, (uint32)stp->rlink, (uint32)stp->flink);
	  stp = stp->flink;
	}
	return;
}
