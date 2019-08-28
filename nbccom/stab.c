/* stab.c */

/*
 * 	(c) Copyright 1990 J B Systems
 *	This file contains non-based support modifications
 *	for operation under MPX.  Derived from Encores' base
 *	mode C compiler.
 */

#ifndef lint
static char *rcsid = "$Header: /bulk2/simhv/nbc-master/nbccom/RCS/stab.c,v 1.8 2019/01/31 22:02:16 jbev Exp $";
#endif

/*
 * $Log: stab.c,v $
 * Revision 1.8  2019/01/31 22:02:16  jbev
 * Update for Linux
 *
 * Revision 1.7  1997/01/22 18:28:07  jbev
 * Correct pointer/integer problem with error messages.
 * Only on Alpha because of 64 bit pointers and 32 bit ints.
 *
 * Revision 1.6  1996/10/26 22:29:03  jbev
 * Fix for Alpha Port
 * l.
 *
 * Revision 1.5  1996/03/22 00:15:04  jbev
 * Cleanup for Alpha port.
 *
 * Revision 1.4  1996/03/20 23:43:30  jbev
 * Use O/S malloc function for alpha, not internal function.
 * More mods for alpha port.
 *
 * Revision 1.3  1996/03/20 21:42:39  jbev
 * Mods for alpha port.
 *
 * Revision 1.2  1996/03/18 23:55:06  jbev
 * Mods for Alpha port.
 *
 */

/*
    Ported from the 4.1c Berkeley Standard
	Distribution source for a VAX portable C compiler.
*/

/*
 * Symbolic debugging info interface.
 *
 * Here we generate pseudo-ops that cause the assembler to put
 * symbolic debugging information into the object file.
 */

#include "mfile1.h"

#if defined(mpx)
#include <types.h>
#define N_LCSYM 0
#else
#include <sys/types.h>
#endif

# if defined(linux) || defined(__alpha)
#include "a.out.h"
#include <string.h>
#include <stdlib.h>
# else
#include <a.out.h>
# endif

#define private static
private int testtype();

#ifdef MPX
static int entertype();
static void inittypes();
static void gentype();
static void genstruct();
static void geninfo();
#endif

#define and &&
#define or ||
#define not !
#define div /
#define mod %
#define nil 0

#define bytes(bits) ((bits) / SZCHAR)
#define bsize(p) bytes(dimtab[p->sizoff])	/* size in bytes of a symbol */

#define NILINDEX -1
#define FORWARD -2

typedef int     Boolean;

#define false 0
#define true 1

#ifndef BUG1
extern int  ddebug;
#endif
extern int  gdebug;
extern char    *domalloc();

int	stabLCSYM;

/*
 * Since type names are lost in the travels and because C has
 * structural type equivalence we keep a table of type words that
 * we've already seen.  The first time we see a type, it is assigned
 * (inline) a number and future references just list that number.
 * Structures, unions, enums, and arrays must be handled carefully
 * since not all the necessary information is in the type word.
 */

typedef struct Typeid  *Typeid;

struct      Typeid
{
    TWORD       tword;
    int         tarray;
    int         tstruct;
    int         tstrtag;
    int         tnum;
    char	*tname;		/* type in ascii */
    Typeid      chain;
};

#define TABLESIZE 2003

private int tcount = 1;
private int t_int, t_char;
private Typeid  typetable[TABLESIZE];
private Typeid typelookup();

/*
 * Generate debugging info for a parameter.
 * The offset isn't known when it is first entered into the symbol table
 * since the types are read later.
 */

void fixarg(p)
struct symtab  *p;
{
#ifndef BUG1
    if(ddebug && gdebug) {
	printf("fixarg(%x)\n", p);
    }
#endif
	if (gdebug) {
    	    /* emit calling parameter definition */
	    printf(" .sym _%.7s", p->sname);
	    gentype(p);
	    printf(" PARM %d LA%d+%d\n",
		    bsize(p), ftnno+1, bytes(argoff));
	}
}

/*
 * Generate debugging info for a given symbol.
 */

void outstab(sym)
struct symtab  *sym;
{
    register struct symtab *p;
    char       *classname;
    int         offset;
    Boolean     ignore;
    static Boolean  firsttime = true;
    char	*nn;

#ifndef BUG1
    if(ddebug && gdebug) {
	printf("outstab(%x)\n", sym);
    }
#endif
	if (gdebug) {
	    if (firsttime) {
		firsttime = false;
		inittypes();
	    }
	    ignore = false;
	    p = sym;
	    offset = bytes(p->offset);
	    switch (p->sclass) {
		case REGISTER: 
		    classname = "REG";
/*		    classname = ""; */
		    offset = p->offset;
		    break;

	    /* 
	     * Locals are the default class.
	     */
		case AUTO: 
		    classname = "AUTO";
/*		    classname = ""; */
		    break;

		case USTATIC: 
		case STATIC: 
		    if (ISFTN(p->stype)) {
			ignore = true;
		    }
		    else
			if (p->slevel <= 1) {
			    classname = "STATIC"; 
/*			    classname = ""; */
    		if (BTYPE(p->stype) == STRTY)goto DOstruct;
    		if (BTYPE(p->stype) == UNIONTY)goto DOunion;
			}
			else {
			    classname = "VSTATIC"; 
/*			    classname = ""; */
			}
		    break;

		case EXTDEF: 
		    if (ISFTN(p->stype)) {
			ignore = true;
		    }
		    else {
			classname = "DEF";
/*			classname = ""; */
    		if (BTYPE(p->stype) == STRTY)goto DOstruct;
    		if (BTYPE(p->stype) == UNIONTY)goto DOunion;
		    }
		    break;

		case EXTERN: 
		    if (ISFTN(p->stype)) {
			ignore = true;
		    }
		    else {
			classname = "EXT";
/*			classname = ""; */
		    }
		    break;

		case TYPEDEF: 
		    classname = "TYPEDEF";
/*		    classname = "TYPEDEF"; */
    		if (BTYPE(p->stype) == STRTY)goto DOstruct;
    		if (BTYPE(p->stype) == UNIONTY)goto DOunion;
		    ignore = true;	/* new for caid */
		    break;

		case PARAM: 
		case MOS: 
		case MOU: 
		case MOE: 
		    ignore = true;
		    break;

		case ENAME: 
    	nn = (char *) domalloc(strlen(p->sname) + 7);
    	strcpy(nn, "enum ");
    	strcat(nn, "_");
    	strcat(nn, p->sname);
    	nn[13] = '\0';		/* truncate at 7 chars */
/* printf(" outstab ENAME entertype %s\n", nn); */
    entertype(p->stype, NILINDEX, FORWARD, dimtab[p->sizoff + 3], nn);
		    ignore = true;
		    break;
		case UNAME: 
		    ignore = true;
DOunion:
    	nn = (char *) domalloc(strlen(p->sname) + 8);
    	strcpy(nn, "union ");
    	strcat(nn, "_");
    	strcat(nn, p->sname);
    	nn[14] = '\0';		/* truncate at 7 chars */
/* printf(" outstab UNAME entertype %s\n", nn); */
    entertype(p->stype, NILINDEX, FORWARD, dimtab[p->sizoff + 3], nn);
		    break;
		case STNAME: 
		    ignore = true;
DOstruct:
    	nn = (char *) domalloc(strlen(p->sname) + 9);
    	strcpy(nn, "struct ");
    	strcat(nn, "_");
    	strcat(nn, p->sname);
    	nn[15] = '\0';		/* truncate at 7 chars */
/* printf(" outstab STNAME entertype %s\n", nn); */
    entertype(p->stype, NILINDEX, FORWARD, dimtab[p->sizoff + 3], nn);
		    break;

		default: 
		    if ((p->sclass & FIELD) == 0) {
		 printf("*- no info for %.7s (%d) \n", p->sname, p->sclass);
		    }
		    ignore = true;
		    break;
	    }
	    if (not ignore) {
    		if (BTYPE(p->stype) == STRTY || BTYPE(p->stype) == UNIONTY) {
    		    if (p->sname != nil) {
    			int	i;
    			register Typeid	typeid;
/*    			private Typeid typelookup(); */

    			i = dimtab[p->sizoff + 3];
    			typeid = typelookup(p->stype, NILINDEX, FORWARD, i);
/*    printf("name _%s class %x type %x flags %x tname %s\n",
      p->sname, p->sclass, p->stype, p->sflags, typeid->tname); */
    			if (typeid && testtype(p, typeid->tname)) {
    			    gentype(p);
    			    geninfo(p);
    			} else {
#ifndef FTII_FIX
    			  if(p->sclass != TYPEDEF) {
#endif
    			    printf(" .sym _%.7s", p->sname);
    			    gentype(p);
    			    geninfo(p);
#ifndef FTII_FIX
    			  }
#endif
    			}
    		    }
    		} else {
		    printf(" .sym _%.7s", p->sname);
		    gentype(p);
		    geninfo(p);
    		}
	    }
	}
}

/*
 * Look for the given type word in the type table.
 */

private Typeid typelookup(type, arrindex, strindex, strtag)
TWORD       type;
int         arrindex;
int         strindex;
int         strtag;
{
    register TWORD  tword;
    register int    i1, i2;
    Typeid      t;

#ifndef BUG1
    if(ddebug && gdebug) {
	printf("typelookup(0x%x, %d, %d, %d)\n", type, arrindex, strindex,
		strtag);
    }
#endif
    t = typetable[type mod TABLESIZE];
    while (t != nil) {
	if (t->tword == type and
		strindex == t->tstruct and strtag == t->tstrtag) {
	    if (arrindex == NILINDEX) {
		break;
	    }
	    else {
		tword = (unsigned)type >> TSHIFT;
		i1 = arrindex;
		i2 = t -> tarray;
		while (ISARY(tword) and dimtab[i1] == dimtab[i2]) {
		    ++i1;
		    ++i2;
		    tword = (unsigned)tword >> TSHIFT;
		}
		if (!ISARY(tword)) {
		    break;
		}
	    }
	}
	t = t->chain;
    }
    return t;
}

/*
 * Enter a type word and associated symtab indices into the type table.
 */

private int entertype(type, arrindex, strindex, strtag, tnp)
TWORD       type;
int         arrindex;
int         strindex;
int         strtag;
char	*tnp;
{
    register Typeid     t;
    register int    i;

#ifndef BUG1
    if(ddebug && gdebug) {
	printf("entertype(0x%x, %d, %d, %d, %s)\n", type, arrindex, strindex,
		strtag, tnp);
    }
#endif
    t = (Typeid) domalloc(sizeof(struct Typeid));
    t->tword = type;
    t->tarray = arrindex;
    t->tstruct = strindex;
    t->tstrtag = strtag;
    t->tnum = tcount;
    t->tname = tnp;
/* printf("\nNew type [%s][%d]\n", tnp, tcount);*/
    ++tcount;
    i = type mod TABLESIZE;
    t->chain = typetable[i];
    typetable[i] = t;
    return t->tnum;
}

/*
 * Change the information associated with a type table entry.
 * Since I'm lazy this just creates a new entry with the number
 * as the old one.
 */

private void reentertype(typeid, type, arrindex, strindex, strtag)
Typeid      typeid;
TWORD       type;
int         arrindex;
int         strindex;
int         strtag;
{
    register Typeid     t;
    register int    i;

#ifndef BUG1
    if(ddebug && gdebug) {
	printf("reentertype(%d, 0x%x, %d, %d, %d)\n", typeid, type,
		arrindex, strindex, strtag);
    }
#endif
    t = (Typeid) domalloc(sizeof(struct Typeid));
    t->tword = type;
    t->tarray = arrindex;
    t->tstruct = strindex;
    t->tstrtag = strtag;
    t->tnum = typeid->tnum;
    t->tname = typeid->tname;
    i = type mod TABLESIZE;
    t->chain = typetable[i];
    typetable[i] = t;
}

/*
 * Initialize type table with predefined types.
 */

#define builtintype(type, name) entertype(type, NILINDEX, NILINDEX, NILINDEX, name)

private void inittypes()
{
    int         t;

#ifndef BUG1
    if(ddebug && gdebug) {
	printf("inittypes()\n");
    }
#endif
    t_int = builtintype(INT, "int");
    t_char = builtintype(CHAR, "char");
    builtintype(LONG, "long");
    builtintype(SHORT, "short");
    builtintype(UCHAR, "uchar");
    builtintype(USHORT, "ushort");
    builtintype(ULONG, "ulong");
    builtintype(UNSIGNED, "uint");
    builtintype(FLOAT, "float");
    builtintype(DOUBLE, "double");
#ifdef NEW15JUNE93
    t = builtintype(UNDEF, "undef");
#else
/*    t = builtintype(UNDEF, "void"); */
    t = builtintype(UNDEF, "int");
#endif
    t = builtintype(FARG, "FARG");
}

/*
 * Generate debugging information for the given type of the given symbol.
 */

private void gentype(sym)
struct symtab  *sym;
{
    register struct symtab *p;
    register TWORD  t;
    register TWORD  basictype;
    register Typeid     typeid;
    int         i, arrindex, strindex, strtag;
    TWORD t2;
    Typeid typ2;
    
#ifndef BUG1
    if(ddebug && gdebug) {
	printf("gentype(%x)\n", sym);
    }
#endif
    p = sym;
    t = p->stype;
    if (ISFTN(t)) {
	t = DECREF(t);
    }
    basictype = BTYPE(t);
    if (ISARY(t)) {
	arrindex = p->dimoff;
    }
    else {
	arrindex = NILINDEX;
    }
    if (basictype == STRTY or basictype == UNIONTY or basictype == ENUMTY) {
	strindex = dimtab[p->sizoff + 1];
	if (strindex == -1) {
	    strindex = FORWARD;
	    strtag = dimtab[p->sizoff + 3];
	}
	else {
	    strtag = NILINDEX;
	}
    }
    else {
	strindex = NILINDEX;
	strtag = NILINDEX;
    }
    i = arrindex;
    typeid = typelookup(t, arrindex, strindex, strtag);
    while (t != basictype ) {
	t2 = DECREF(t);
    	while(t2 != basictype)
    	    t2 = DECREF(t2);
    	typ2 = typelookup(t2, NILINDEX, strindex, strtag);
    	/* enter new type */
    	if (typ2 == nil) {
    	entertype(t, i, strindex, strtag, "undef");
    	}
	switch (t & TMASK) {
	    case PTR: 
		printf(" PTR");
		break;

	    case FTN: 
#ifdef CAID_NOT_USED
		printf(" FTN");
#endif
		break;

	    case ARY: 
		printf(" ARY 0 %d", dimtab[i++] - 1);
		break;
	}
	t = DECREF(t);
	if (t == basictype) {
	    typeid = typelookup(t, NILINDEX, strindex, strtag);
	}
	else {
	    typeid = typelookup(t, i, strindex, strtag);
	}
    }
    if (typeid == nil) {
	if (strindex == FORWARD) {
	    typeid = typelookup(t, NILINDEX, FORWARD, dimtab[p->sizoff + 3]);
	    if (typeid == nil) {
		cerror("unbelievable forward reference");
	    }
	    printf("%d(%s)", typeid->tnum, typeid->tname);
	}
	else {
/* printf("\ngentype call to genstruct for %s\n", p->sname); */
	    genstruct(t, NILINDEX, strindex, p->sname, bsize(p), p);
	}
    }
    else {
	printf(" %s", typeid->tname);
    }
}

private int testtype(sym, ns)
struct symtab  *sym;
char *ns;
{
    register struct symtab *p;
    register TWORD  t;
    register TWORD  basictype;
    register Typeid     typeid;
    int         i, arrindex, strindex, strtag;
    TWORD t2;
    Typeid typ2;
    
    p = sym;
    t = p->stype;
    if (ISFTN(t)) {
	t = DECREF(t);
    }
    basictype = BTYPE(t);
    if (ISARY(t)) {
	arrindex = p->dimoff;
    }
    else {
	arrindex = NILINDEX;
    }
    if (basictype == STRTY or basictype == UNIONTY or basictype == ENUMTY) {
	strindex = dimtab[p->sizoff + 1];
	if (strindex == -1) {
	    strindex = FORWARD;
	    strtag = dimtab[p->sizoff + 3];
	}
	else {
	    strtag = NILINDEX;
	}
    }
    else {
	strindex = NILINDEX;
	strtag = NILINDEX;
    }
    i = arrindex;
    typeid = typelookup(t, arrindex, strindex, strtag);
    while (t != basictype ) {
	t2 = DECREF(t);
    	while(t2 != basictype)
    	    t2 = DECREF(t2);
    	typ2 = typelookup(t2, NILINDEX, strindex, strtag);

	t = DECREF(t);
	if (t == basictype) {
	    typeid = typelookup(t, NILINDEX, strindex, strtag);
	}
	else {
	    typeid = typelookup(t, i, strindex, strtag);
	}
    }
    if (typeid == nil) {
	if (strindex == FORWARD) {
	    typeid = typelookup(t, NILINDEX, FORWARD, dimtab[p->sizoff + 3]);
	    if (typeid == nil) {
		cerror("unbelievable forward reference");
	    }
	    printf("%d(%s)", typeid->tnum, typeid->tname);
	}
	else {
    	    printf("*.stabs _%.7s %s", p->sname, ns);
	    genstruct(t, NILINDEX, strindex, p->sname, bsize(p), p);
    	    return (1);
	}
    }
    else {
	return (0);
    }
    return (0);	/* NOTREACHED */
}

/*
 * Generate type information for structures, unions, and enumerations.
 */

private void genstruct(t, structid, index, name, size, p)
TWORD	t;
int	structid;
int	index;
char	*name;
int	size;
struct	symtab *p;
{
    register int    i;
    register struct symtab *field;
    int         id;
    char	*nn = "NULL";
    Typeid typeid;
    Typeid type2id;
    char mymsg[64];

#ifndef BUG1
    if(ddebug && gdebug) {
	printf("genstruct(0x%x, %d, %d, %x: %s, %d)\n", t, structid, index,
		name, name, size);
    }
#endif
    if (structid == NILINDEX) {
    	nn = (char *) domalloc(strlen(name) + 9);
    	if (t == STRTY) {
    	    strcpy(nn, "struct ");
    	    strcat(nn, "_");
    	    strcat(nn, name);
    	    nn[15] = '\0';		/* truncate at 7 chars */
    	} else if (t == UNIONTY) {
    	    strcpy(nn, "union ");
    	    strcat(nn, "_");
    	    strcat(nn, name);
    	    nn[14] = '\0';		/* truncate at 7 chars */
    	} else {
    	    strcpy(nn, "enum ");
    	    strcat(nn, "_");
    	    strcat(nn, name);
	    nn[13] = '\0';		/* truncate at 7 chars */
    	}
/* printf(" genstruct entertype %s\n", nn); */
	id = entertype(t, NILINDEX, index, NILINDEX, nn);
    }
    else {
	id = structid;
    }
    typeid = typelookup(t, NILINDEX, index, NILINDEX);
/*  printf(" genstruct typeid %x name [%s]\n",
 typeid, typeid == nil ? "NULL" : typeid->tname); */
    switch (t) {
	case STRTY: 
	case UNIONTY: 
    	    field = &stab[dimtab[index]];
#ifdef OLD_WAY
    	    if (field->sclass == EXTDEF)	/* just print def's */
    		printf(" %s GSYM %d\n", typeid->tname, size);
    	    else
    		printf(" %s ESYM(%d) %d\n", typeid->tname, field->sclass, size);
#else
    	    geninfo(p);
#endif
	    i = index;
	    while (dimtab[i] != -1) {
		field = &stab[dimtab[i]];
    		/* see if another struct/union being defined */
#ifdef XXX
    		if ((field->stype == STRTY || field->stype == UNIONTY)
    		  && (structid != NILINDEX)) {
#else
    		if (field->stype == STRTY || field->stype == UNIONTY) {
#endif
    		    type2id = typelookup(t, NILINDEX,
    		      dimtab[field->sizoff+1], NILINDEX);
    		    if (type2id == nil)
    		    /* we are defining a new struct/union at a new level */
    			if (field->stype == STRTY)
    			    printf("*.stabs _%.7s struct _%.7s",
    			      field->sname, field->sname);
    			else
#ifndef FTTI_FIX
    			if (testtype(field, typeid->tname)) {
/*    			    printf(" union _%.7s", field->sname); */
/*    			    printf("*.stabs _%.7s union _%.7s",
    			      field->sname, field->sname); */
    			} else {
    			    printf("*.stabc _%.7s", field->sname);
/*    			    gentype(field); */
/*    			    geninfo(field); */
    			}
#else
    			    printf("*.stabs _%.7s union _%.7s",
    			      field->sname, field->sname);
#endif
    		    else
    			printf("*.stabc _%.7s", field->sname);
    		} else {
    		    printf("*.stabc _%.7s", field->sname);
    		}
		gentype(field);
		if (field->sclass > FIELD) {
		    printf(" off:%d cls:%d;\n",
    		      field->offset, field->sclass - FIELD);
		}
		else {
		    printf(" off:%d siz:%d;\n", field->offset,
		      tsize(field->stype, field->dimoff, field->sizoff));
		}
		++i;
	    }
    	    if (p->sclass <= 0 ||
    	      (p->sclass == STNAME || p->sclass == UNAME)) {
		printf("*.stabe _%.7s %s", name, typeid->tname);
    		break;
    	    }
#ifdef NASA_FIX_82393
	    printf("*.stabe _%.7s %s", name, typeid->tname);
    	    geninfo(p);
    	    if (p->sclass == EXTDEF || p->sclass == STATIC) {
    		printf(" .sym _%.7s %s", name, typeid->tname);
#else
    	    if (p->sclass == EXTDEF || p->sclass == STATIC || p->sclass == AUTO) {
    		printf("*.stabe _%.7s %s", name, typeid->tname);
    		geninfo(p);
    		printf(" .sym _%.7s", name);
#endif
    	    } else {
#ifdef NASA_FIX_82393
    		printf("*.stabe _%.7s %s", name, typeid->tname);
    		printf("*CLASS %x .stabc _%.7s %s",
    		  p->sclass, name, typeid->tname);
#else
    		if (p->sclass != TYPEDEF) {
    		    printf("*.stabe _%.7s %s", name, typeid->tname);
    		    geninfo(p);
#ifndef FTII_FIX
    		    if(p->sclass == MOS && nn[0] == 'u')
    		    printf("*.stabc(%d%s) _%.7s", p->sclass, nn, name);
    		    else
#endif
    		    printf("*.stabc(%d%s) _%.7s %s", p->sclass, nn, name, typeid->tname);
    		}
    		else
    		    printf("*.stabe _%.7s", name);
#endif
    	    }
	    break;

	case ENUMTY: 
#ifdef OLD_WAY
    	    field = &stab[dimtab[index]];
    	    if (field->sclass == EXTDEF)	/* just print def's */
    		printf(" %s GSYM %d\n", typeid->tname, size);
    	    else
    		printf(" %s ESYM(%d) %d\n", typeid->tname, field->sclass, size);
#else
    	    geninfo(p);
#endif
	    i = index;
	    while (dimtab[i] != -1) {
		field = &stab[dimtab[i]];
		printf("*.stabc _%.7s", field->sname);
    		printf(" PARM");
		printf(" value:%d\n", field->offset);
		i++;
	    }
	    printf("*.stabe _%.7s %s", name, typeid->tname);
	    break;

	default: 
#ifdef alpha_fix
	    cerror("*couldn't find basic type %d for %s", t, name);
#else
	    sprintf(mymsg, "*couldn't find basic type %d for %s", t, name);
	    cerror(mymsg);
#endif
	    break;
    }
}

/*
 * Generate offset and size info.
 */

private void geninfo(p)
register struct symtab *p;
{
#ifndef BUG1
    if(ddebug && gdebug) {
	printf("geninfo(%x):\n", p);
    }
#endif
    if (p == nil) {
    }
    else {
	switch (p->sclass) {
	    case EXTERN: 
	    case EXTDEF: 
		if (ISFTN(p->stype)) {
		    printf(" GFTN %d\n", bsize(p));
		}
		else {
    		    if (p->sclass == EXTDEF)	/* just print def's */
		        printf(" GSYM %d\n", bsize(p));
    		    else
		        printf(" ESYM %d\n", bsize(p));
		}
		break;

	    case STATIC: 
		if (ISFTN(p->stype)) {
		    printf(" SFTN %d\n", bsize(p));
		}
		else
		    if (p->slevel > 1) {
			printf(" HSYM %d L%d\n", bsize(p), p->offset);
		    }
		    else {
			printf(" LSYM %d\n", bsize(p));
		    }
		break;

	    case REGISTER: 
		printf(" RSYM %d %d\n", bsize(p), p->offset);
		break;

	    case PARAM: 
		printf(" PARM %d LA%d+%d\n",
			bsize(p), ftnno+1, bytes(argoff));
		break;

	    case TYPEDEF: 
#ifdef XXXX_NOT_USED
		printf(" TDSYM %d\n", bsize(p));
#else
    		if (BTYPE(p->stype) == STRTY)
    		    printf(" SNAM %d\n", bsize(p));
    		else if (BTYPE(p->stype) == UNIONTY)
    		    printf(" UNAM %d\n", bsize(p));
#endif
		break;

	    case AUTO:
		printf(" AUTO %d LOC%d+%d\n",
			bsize(p), ftnno, bytes(p->offset)+32);
		break;

	    case STNAME:	/* structure name */
		printf(" SNAM %d\n", bsize(p));
/*		printf(" %d\n", bsize(p)); */
		break;
	    case UNAME:		/* union name */
		printf(" UNAM %d\n", bsize(p));
/*		printf(" %d\n", bsize(p)); */
		break;
	    case ENAME:		/* enumeration name */
		printf(" ENUM %d\n", bsize(p));
/*		printf(" %d\n", bsize(p)); */
		break;

	    case MOS:		/* member of structure */
    		if (p->stype == PARAM)
		    printf(" USYM %d\n", bsize(p));
    		else
		    printf(" SSYM %d\n", bsize(p));
/*		printf(" SSYM %d\n", bsize(p)); */
		break;

	    case MOU:		/* member of union */
		printf(" USYM %d\n", bsize(p));
/*		printf(" USYM %d\n", bsize(p)); */
		break;

	    /*
	     * For now complain if we ever try to geninfo for any of these
	     * storage classes.  We'll fix them as we find it necessary.
	     */
	    case SNULL:
	    case LABEL:
	    case ULABEL:
	    case FORTRAN:
	    case MOE:		/* member of enumeration */
	    case UFORTRAN:
	    case USTATIC:
	    default: 
		fprintf(stderr,
			"warning: geninfo for unexpected storage class %d.\n",
			(p->sclass));
		printf(" UNSYM %d (%d)\n", bsize(p), p->sclass);
/*		printf(" USYM %d LOC%d+%d\n",
			bsize(p), ftnno, bytes(p->offset)); */
		break;
	}
    }
}

/*
 * Generate information for a newly-defined structure.
 */

void outstruct(szindex, paramindex)
int         szindex, paramindex;
{
    register Typeid     typeid;
    register struct symtab *p;
    register int    i, t, strindex;

#ifndef BUG1
    if(ddebug && gdebug) {
	printf("outstruct(%d, %d)\n", szindex, paramindex);
    }
#endif
    if (!gdebug) {
	return;
    }
    i = dimtab[szindex + 3];
    p = &stab[i];
    if (p->sname != nil) {
    	strindex = dimtab[p->sizoff + 1];
    	typeid = typelookup(p->stype, NILINDEX, FORWARD, i);
    	if (typeid == nil) {
    	    t = 0;
    	}
    	else {
    	    t = typeid->tnum;
    	    reentertype(typeid, p->stype, NILINDEX, strindex, NILINDEX);
    	}
    	/* we are at the first level of definition */
/*    	printf("*.stabs _%.7s", p->sname); */
    	printf("*.stabs _%.7s %s", p->sname, typeid->tname);
    	genstruct(p->stype, t, strindex, p->sname, bsize(p), p);
    	geninfo(p);
    }
}

void pstab(name, type)
char       *name;
int         type;
{
    register int    i;
    register char   c;

#ifndef BUG1
    if(gdebug && ddebug) {
	printf("pstab(%x, 0x%x):\n", name, type);
    }
#endif
    if (!gdebug) {
	return;
    }
 /* locctr(PROG);  /* .stabs must appear in .text for c2 */
#ifdef ASSTRINGS
    if (name[0] == '\0')
	printf("*.stabn ");
    else
	printf("*.stabs _%s ", name);
#else
    printf("*.stab _");
    for (i = 0; i < 8; i++)
	if (c = name[i])
	    printf("'%c,", c);
	else
	    printf("0,");
#endif
    printf("0x%x,", type);
}

#ifdef STABDOT
void pstabdot(type, value)
int         type;
int         value;
{
#ifndef BUG1
    if(ddebug && gdebug) {
	printf("pstabdot(0x%x, %x)\n", type, value);
    }
#endif
    if (!gdebug) {
	return;
    }
}
#endif

extern char     NULLNAME[8];
extern int  labelno;
extern int  fdefflag;

void psline()
{
    static int  lastlineno;
    register char  *cp, *cq;
    register int    i;

#ifndef BUG1
    if(ddebug && gdebug) {
	printf("psline()\n");
    }
#endif
    if (!gdebug) {
	return;
    }

    cq = ititle;
    cp = ftitle;

    while (*cq)
	if (*cp++ != *cq++)
	    goto neq;
    if (*cp == '\0')
	goto eq;

neq: for (i = 0; i < 100; i++)
	ititle[i] = '\0';
    cp = ftitle;
    cq = ititle;
    while (*cp)
	*cq++ = *cp++;
    *cq = '\0';
    *--cq = '\0';
    *cq = '"';
    labelno++;

eq: if (lineno == lastlineno)
	return;
    lastlineno = lineno;

    if (fdefflag) {
#ifdef STABDOT
	pstabdot(N_SLINE, lineno);
#else
	pstab(NULLNAME, N_SLINE);
	printf("0,%d,LL%d\n", lineno, labelno);
	printf("LL%d:\n", labelno++);
#endif
    }
}

void plcstab(level)
int         level;
{
#ifndef BUG1
    if(ddebug && gdebug) {
	printf("plcstab(%d)\n", level);
    }
#endif
    if (!gdebug) {
	return;
    }
#ifdef STABDOT
	/*..... UTX assembler is defective. You might be in data space
		when the { stabd is emitted. Stabd is a misnomer, the
		value of "dot" is supposed to come from the symboltype.

		DJK: CSD-Urbana 25 april 95

	*/
    locctr(PROG);
    pstabdot(N_LBRAC, level);
#else
    pstab(NULLNAME, N_LBRAC);
    printf("0,%d,LL%d\n", level, labelno);
    printf("LL%d:\n", labelno++);
#endif
}

void prcstab(level)
int         level;
{
#ifndef BUG1
    if(ddebug && gdebug) {
	printf("prcstab(%d)\n", level);
    }
#endif
    if (!gdebug) {
	return;
    }
#ifdef STABDOT
    pstabdot(N_RBRAC, level);
#else
    pstab(NULLNAME, N_RBRAC);
    printf("0,%d,LL%d\n", level, labelno);
    printf("LL%d:\n", labelno++);
#endif
}

void pfstab(sname)
char       *sname;
{
    register struct symtab *p;

#ifndef BUG1
    if(ddebug && gdebug) {
	printf("pfstab(%x: %s)\n",  sname, sname);
    }
#endif
    if (gdebug) {
	    p = &stab[lookup(sname, 0)];
    	    printf(" .sym _%.7s", p->sname);
/*	    printf("%s", (p->sclass == STATIC) ? "SFTN" : "FTN"); */
	    gentype(p);
	    geninfo(p);
    }
}

