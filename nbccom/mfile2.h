/* mfile2.h */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

/* $Id: mfile2.h,v 1.13 2019/01/31 21:57:26 jbev Exp $ */
/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/

/*
 * $Log: mfile2.h,v $
 * Revision 1.13  2019/01/31 21:57:26  jbev
 * Update for Linux
 *
 * Revision 1.12  1996/10/26 22:18:07  jbev
 * Alpha port fixes
 *
 * Revision 1.11  1996/03/20 21:35:50  jbev
 * Mods for alpha port.
 *
 * Revision 1.10  1995/03/06 21:45:34  jbev
 * needed xdebug.
 *
 * Revision 1.9  1995/03/06  19:44:44  jbev
 * Delete xdebug & edebug.  Multiply defined.
 *
 * Revision 1.8  1995/03/06  19:18:32  jbev
 * Malloc tree node table instead of hard coding size.
 * Allow XTTval  and X2TTval to set node tree table size.
 * Add new option XJ and X2J to inhibit _ being prepended to names.
 * Correct XT[DS]val options for setting table sizes.
 *
 */

#include "macdefs.h"
#include "mac2defs.h"
#include "manifest.h"
#ifdef MYATOF
#include "float.h"
#endif

#ifdef ONEPASS

/*	bunch of stuff for putting the passes together... */
#define	crslab	crs2lab
#define	where	where2
#ifndef BUG1
#define	eprint	e2print
#endif
#define	deflab	def2lab
#define	filename	ftitle
#endif

/*	cookies, used as arguments to codgen */

#define	FOREFF	01	/* compute for effects only */
#define	INAREG	02	/* compute into a register */
#define	INTAREG	04	/* compute into a scratch register */
#define	INBREG	010	/* compute into a lvalue register */
#define	INTBREG	020	/* compute into a scratch lvalue register */
#define	FORCC	040	/* compute for condition codes only */
#define NOREG	0100	/* use this table entry if no reg reg floats */
#define	INTEMP	010000	/* compute into a temporary location */
#define	FORARG	020000	/* compute for an argument of a function */
#define	FORREW	040000	/* search the table, looking for a rewrite rule */
#define	FORZCC	0200000	/* only equality condition codes used */

 /* OP descriptors */
 /* the ASG operator may be used on some of these */

#define	OPSIMP	010000	/* +, -, &, |, ^ */
#define	OPCOMM	010002	/* +, &, |, ^ */
#define	OPMUL	010004	/* *, / */
#define	OPDIV	010006	/* /, % */
#define	OPUNARY	010010	/* unary ops */
#define	OPLEAF	010012	/* leaves */
#define	OPANY	010014	/* any op... */
#define	OPLOG	010016	/* logical ops */
#define	OPFLOAT	010020	/* +, -, *, or / (for floats) */
#define	OPSHFT	010022	/* <<, >> */
#define	OPLTYPE	010024	/* leaf type nodes (e.g, NAME, ICON, etc. ) */
#define	OPBIT	010026	/* & | ^*/

 /* match returns */

#define	MNOPE	010000
#define	MDONE	010001

 /* shapes */

#define	SANY	01	/* same as FOREFF */
#define	SAREG	02	/* same as INAREG */
#define	STAREG	04	/* same as INTAREG */
#define	SBREG	010	/* same as INBREG */
#define	STBREG	020	/* same as INTBREG */
#define	SCC	040	/* same as FORCC */
#define	SNAME	0100
#define	SCON	0200
#define	SFLD	0400
#define	SOREG	01000
/* indirection or wild card shapes */
#ifndef WCARD1
#define	STARNM	02000
#endif
#ifndef WCARD2
#define	STARREG	04000
#endif
#define	SWADD	040000
#define	SPECIAL	0100000
#define	SZCC	0200000

#define MAKESPECIAL(v) SPECIAL|(v<<1)	/* special avoids dumping on SANY */
#define	SZERO	MAKESPECIAL(0)
#define	SONE	MAKESPECIAL(1)
#define	SMONE	MAKESPECIAL(2)
#define	SCCON	MAKESPECIAL(3)	/* -256 <= constant < 256 */
#define	SSCON	MAKESPECIAL(4)	/* -32768 <= constant < 32768 */
#define	SOCON	MAKESPECIAL(5)	/* 0 <= constant <64K */
#define	SPOW2	MAKESPECIAL(6)
#define	SCPOW2	MAKESPECIAL(7)
#define	SICON	MAKESPECIAL(8)	/* non name constant */
#define	SHPOW2	MAKESPECIAL(9)	/* halfword power of 2 */
#define	SHCPOW2	MAKESPECIAL(10)

#define SBPOW2	MAKESPECIAL(11)	/* byte power of 2 */
#define SBCPOW2 MAKESPECIAL(12)
#define	SACON	MAKESPECIAL(13)	/* constant OK for ANDI */
#define STCON	MAKESPECIAL(14)	/* top half constant, bottom ignored */
#define SHCON	MAKESPECIAL(15)	/* half constant (upper part ignored) */
				/* i.e. - reverse of TCON */
#ifdef MPX
#define	SMCON	MAKESPECIAL(16)	/* constant OK for LA (0 -> 7ffff) */
#endif

 /* FORARG and INTEMP are carefully not conflicting with shapes */

 /* types */

#define	TCHAR	01
#define	TSHORT	02
#define	TINT	04
#define	TLONG	010
#define	TFLOAT	020
#define	TDOUBLE	040
#define	TPOINT	0100
#define	TUCHAR	0200
#define	TUSHORT	0400
#define	TUNSIGNED	01000
#define	TULONG	02000
#define	TPTRTO	04000	/* pointer to one of the above */
#define	TANY	010000	/* matches anything within reason */
#define	TSTRUCT	020000	/* structure or union */

 /* reclamation cookies */

#define	RNULL	0	/* clobber result */
#define	RLEFT	01
#define	RRIGHT	02
#define	RESC1	04
#define	RESC2	010
#define	RESC3	020
#define	RESCC	04000
#define	RNOP	010000	/* DANGER: can cause loops.. */
#define	RESUPPER	020000	/* upper part of two regs */
#define	RESINT		040000	/* lower part */

 /* needs */

#define	NAMASK	0xf
#define	NAREG	1
#define	NACOUNT	3
#define	NASL	4	/* share left register */
#define	NASR	8	/* share right register */
#define	NBMASK	0xf0
#define	NBREG	0x10
#define	NBCOUNT	0x30
#define	NBSL	0x40
#define	NBSR	0x80
#define	NTEMP	0x100
#define	NTMASK	0xf00
#define	REWRITE	0x1000
#define	NDREG	0x2000
#define	NDMASK  0x6000
#define	EITHER	040000	/* "either" modifier for needs */

/* MUSTDO and NOPREF are now defined in macdefs.h */
/* MUSTDO	=> force register requirements */
/* NOPREF	=> no preference for register assignment */

 /* register allocation */

extern int  rstatus[];
extern int  busy[];

extern struct   respref
{
    int         cform;
    int         mform;
}           respref[];

#define	isbreg(r)	(rstatus[r]&SBREG)
#define	istreg(r)	(rstatus[r]&(STBREG|STAREG))
#define	istnode(p)	(p->in.op==REG && istreg(p->tn.rval))
#define	isfakereg(r)	(r > R7)

#define	TBUSY	01000
#define	REGLOOP(i)	for(i=0;i<REGSZ;++i)

#define	SETSTO(x,y)	(stotree=(x),stocook=(y))
extern int  stocook;
#define	DELAYS	20
extern NODE    *deltrees[DELAYS];
extern int  deli;		/* mmmmm */

extern NODE    *stotree;
extern int  callflag;
extern int  get2lab();
extern void genswitch();
extern void makeheap();
extern void walkheap();
extern void def2lab();
extern void cbgen();
extern int sselect();
extern void prbusy();
extern void cerror();
extern void rfree();
extern void tfree();
extern void walkf();
extern void fwalk();
extern void allchk();
extern void callchk();
extern void rmove();
extern void where2();
extern void expand();
extern void adrcon();
extern void initcon();
extern void ahcon();
extern void acon();
extern void adrput();
extern void zerof();
extern void order();
extern void rmove();
extern void ahcon();
extern void cbgen();
extern void optim2();
extern void acon();
extern void LAddrFix();
extern void LNameFix();
extern void harops();
extern void canon();
extern void myreader();
extern void prditch();
extern void regfix();
extern void eobl2();
extern void oreg2();
extern void deflab();
extern void reclaim();
extern void werror();
extern void mkdope();
extern void setrew();
extern void lineid();
extern void wderror();
extern void treeinit();
extern void allo0();
extern void delay();
extern void setregs();
extern void rbusy();
extern void prbusy();
extern void delay();
extern void delay2();
extern void codgen();
extern void store();
extern void rcount();
extern void cbranch();
extern void uerror();
extern void offstar();
extern void rallo();
extern void store();
extern void stoasg();
extern void markcall();
extern void constore();
extern void treeinit();
extern void moveaddr();
extern void eprint();
extern void tprint();
extern void stoarg();
extern void oreg2();
extern void mkadrs();
extern void zzzcode();
extern void hopcode();
extern void conput();
extern void insput();
extern void upput();
extern void prtype();
extern void cderror();
extern int print();
extern int special();
extern int delincr();
extern int notoff();
extern int setincr();
extern int setstr();
extern int setasg();
extern int setbin();
extern int nextcook();
extern int busytregs();
extern int lastchance();
extern int lastditch();
extern int freereg();
extern int freetemp();
extern int shareit();
extern int usable();
extern int tshape();
extern int shumul();
extern int settmpstr();
extern int genscall();
extern int gencall();
extern int argsize();
extern int busytregs();
extern int match();
extern int ispow2();
extern int canaddr();
extern int setdouble();
extern int ttype();
extern int setasop();
extern int delay1();
extern int autoincr();
extern int deltest();
extern int unsispow2();
extern int shtemp();
extern int flshape();
extern int shltype();
extern int allo();

extern char *domalloc();
extern int  fregs;
#define ncopy(q,p) *(q) = *(p)	/* node copy */

#ifndef ONEPASS
union       ndu
{

    struct {
	int         op;
	int         rall;
	TWORD       type;
	int         su;
	char       *name;
	long        stalign;	/* alignment of structure objects */
	NODE       *left;
	NODE       *right;
    }           in;		/* interior node */

    struct {
	int         op;
	int         rall;
	TWORD       type;
	int         su;
	char       *name;
	long        stalign;	/* alignment of structure objects */
	long        lval;
	long        rval;
    } tn;			/* terminal node */

    struct {
	int	op;
	int	rall;
	TWORD	type;
	int	su;
	char	*name;
#ifdef MYATOF
/*	int         stalign;	/* alignment of structure objects */
	FPN	fpnum;
#else
	int         stalign;	/* alignment of structure objects */
	FP_DOUBLE dval;
#endif
    } fpn;	/* floating point node */

    struct {
	int         op;
	int         rall;
	TWORD       type;
	int         su;
	long        label;	/* for use with branching */
	long        stalign;	/* alignment of structure objects */
    } bn;			/* branch node */

    struct {
	int         op;
	int         rall;
	TWORD       type;
	int         su;
	long        stsize;	/* sizes of structure objects */
	long        stalign;	/* alignment of structure objects */
    } stn;			/* structure node */

};

#ifdef MPX
struct tstrngs /* structure for stuffing away strings for dsect output */
{
	int slabel;
	short length;
	char *strng;
	struct tstrngs *next;
};

extern struct tstrngs *begstrng;
extern struct tstrngs *currstng;

#endif
#endif

extern NODE     *nodep;

extern struct   optab
{
    int         op;
    int         visit;
    int         lshape;
    int         ltype;
    int         rshape;
    int         rtype;
    int         needs;
    int         rewrite;
    char       *cstring;
} table[];

extern NODE     resc[];

extern OFFSZ    tmpoff;
extern OFFSZ    maxoff;
extern OFFSZ    baseoff;
extern OFFSZ    maxtemp;
extern int  maxtreg;
extern int  ftnno;
extern int  rtyflg;

extern int  nrecur;	/* flag to keep track of recursions */

#define	NRECUR	1000

extern      NODE
*talloc(),
*eread(),
*tcopy(),
*getlr();

extern CONSZ rdin();

extern NODE *getfartmp();

extern char    *rnames[];
extern int	szrnames;	/* size of rnames[], see local2.c */

extern int  lineno;
extern char     filename[];
extern int  fldshf, fldsz;
extern int  lflag;
#ifndef BUG1
extern int  xdebug, udebug, odebug, rdebug, radebug, tdebug, sdebug;
#endif

#ifndef callchk
#define	callchk(x)	allchk()
#endif

#ifndef PUTCHAR
#define	PUTCHAR(x)	putchar(x)
#endif

 /* macros for doing double indexing */
#define	R2PACK(x,y,z)	(0200*((x)+1)+y+040000*z)
#define	R2UPK1(x)	((((x)>>7)-1)&0177)
#define	R2UPK2(x)	((x)&0177)
#define	R2UPK3(x)	(x>>14)
#define	R2TEST(x)	((x)>=0200)

#ifdef MULTILEVEL

union       mltemplate
{
    struct      ml_head {
	int         tag;		/* identifies class of tree */
	int         subtag;		/* subclass of tree */
	union mltemplate   *nexthead;	/* linked by mlinit() */
    }           mlhead;
    struct      ml_node {
	int         op;		/* either an operator or op description */
	int         nshape;		/* shape of node */
 /* both op and nshape must match the node.
  * where the work is to be done entirely by 
  * op, nshape can be SANY, visa versa, op can 
  * be OPANY. */
	int         ntype;		/* type descriptor from mfile2 */
    }           mlnode;
};

#endif

#define rewfld(x)	1
#define callreg(x)	R0

#define szty(t)  (((t) == LONG || (t) == DOUBLE) ? 2 : 1)
#define GETL(p) (optype((p)->in.op)==LTYPE?(p):(p)->in.left)
#define GETR(p) (optype((p)->in.op)==BITYPE?(p)->in.right:(p))

