/*
 * xref processing
 */

#include "defs.h"
#include <stdio.h>
#include <string.h>
#ifdef DOS
#include <io.h>
#include <malloc.h>
#endif

/* #define DEBUG */

#define XRBUFSIZE 200*768
static int32	xrefmode;	/* xref mode */
static int32	reccnt;		/* number of records */
static int32 	xrbufp;		/* next buffer entry */
static int32 	segments;	/* number of buffer segments written */

int mycmp();		/* qsort function */
void qsort();

/*
 * xnegate - routine to negate 8 char name for for macro lookup
 * input - 8 char name pointer
 * output - point to 8 char negated name
 */

static char negname[8];		/* the negated name returned */

char * xsnegate (name)
register char * name;
{
	register int	i;
	register char * rname = negname;

	for (i=0; i<8; i++)
	  rname[i] = (char)(-(int)(name[i]));
	return (negname);	/* return negated name pointer */
}

/*
 * function to report symbol references or definitions
 */

void reptr(name, info, val)
unsigned char *name;		/* symbol name */
struct tval *info;	/* symbol description */
int32 val;		/* sort value */
{
	int sval = val & 0x007fffff;	/* clear garbage */
	if(xrefmode & NOXREF)	/* xref required */
	    return;		/* no xref */
	if(xrefmode & PASS2)	/* in pass 2 */
	    return;		/* no reporting in pass 2 */
	if(info->type >= TYMACREQ)
	    return;		/* just macro check, return */
#ifdef YTRY
	if(info->flags & CSDS) {
	    goto report;	/* must be final value */
	}
#endif
	if(sval > 0x0001869f)
	    goto report;	/* must be final data value */
	if(info->type < TYPL)
	    sval |= SREF;	/* symbol reference */
	sval |= SUORD;		/* symbol reference or definition */
report:
	sval |= ((int)info->type << 24);	/* set type */
	if (!(val & SSORT)) {	/* not ss call for reference */
	    sval &= ~SUORD;	/* turn off flag */
	    if (info->flags & ABSREL)
		sval |= (0x800000);	/* set ABS/REL flag */
	}
#ifdef DEBUG
if(info->type == TYPL)
printf("REPTR name [%0.2x%0.2x%0.2x%0.2x] flags %x type %x sval %x\n",
#ifdef mpx
name[4], name[5], name[6], name[7],
#else
name[7], name[6], name[5], name[4],
#endif
info->flags, info->type, sval);
else if(info->type == TYMACDEF)
printf("REPTR name [%0.8s] flags %x type %x sval %x\n",
    xsnegate(name), info->flags, info->type, sval);
else
printf("REPTR name [%0.8s] flags %x type %x value %x sval %x\n",
    name, info->flags, info->type, info->value, sval);
#endif /* DEBUG */

	memcpy(xrbuf+xrbufp, name, 8);	/* copy in the name */
#ifndef mpx
	xrbuf[xrbufp+8] = (sval) & 0xff;
	xrbuf[xrbufp+9] = (sval >> 8) & 0xff;
	xrbuf[xrbufp+10] = (sval >> 16) & 0xff;
	xrbuf[xrbufp+11] = (sval >> 24) & 0xff;
#else
	memcpy(xrbuf+xrbufp+8, (char *)&sval, 4);
#endif
	xrbuf[xrbufp+12] = (char)info->type;
	xrbuf[xrbufp+13] = (char)info->flags;
	xrbuf[xrbufp+14] = '\0';
	xrbuf[xrbufp+15] = '\0';
/*	memcpy(xrbuf+xrbufp+12, (char *)&info->value, 4); */
	xrbufp += 16;		/* bump pointer */
	if(xrbufp >= XRBUFSIZE) {
	    /* sort the buffer before we write it out */
	    qsort(xrbuf, XRBUFSIZE/16, 16, mycmp);
	    segments++;
#ifdef NO_XREF_WRITES
	    if (fwrite(xrbuf, 1, xrbufp, ut2fd) < 0)
		xrer();		/* no return */
#endif
	    xrbufp = 0;		/* reset pointer */
	}
	reccnt++;
	return;			/* we done */
}

/*
 * compare function for qsort
 */

int mycmp(p1, p2)
#ifdef mpx
char *p1;
char *p2;
#else
void *p1;
void *p2;
#endif
{
	int i;
#ifdef JUNK
	unsigned char *e1 = (unsigned char *)p1;
	unsigned char *e2 = (unsigned char *)p2;
	for (i=0; i<12; i++) {
	    if (e1[i] < e2[i])return(-1);
	    if (e1[i] > e2[i])return(1);
	}
#else
	int *e1 = (int *)p1;
	int *e2 = (int *)p2;
	unsigned char *f1 = (unsigned char *)p1;
	unsigned char *f2 = (unsigned char *)p2;
	for (i=0; i<8; i++) {
	    if (f1[i] < f2[i])return(-1);
	    if (f1[i] > f2[i])return(1);
	}
	for (i=2; i<3; i++) {
	    if (e1[i] < e2[i])return(-1);
	    if (e1[i] > e2[i])return(1);
	}
#endif
	return(0);
}

/*
 * send command to xref
 *
 *	0x1	PASS1		Starting pass 1
 *	0x2	PASS2		Starting pass 2
 *	0x4	DOXREF		User wants xref
 *	0x8	NOXREF		User doesn't want xref
 */

void xref_cmd(cmd)
int cmd;			/* type of command */
{
	switch (cmd) {
	    case DOXREF:
		xrefmode = cmd;	/* save current mode */
		return;		/* xref cnd done */
	    case NOXREF:
		xrefmode = cmd;	/* save current mode */
		return;		/* xref cnd done */
	    case PASS1:
		xrefmode &= ~PASS2;	/* not pass 2 */
		xrefmode |= PASS1;	/* now pass 1 */
		if(xrefmode & NOXREF)	/* xref required */
		    return;		/* no xref */
		/* it is start of pass1 and doing xref */
		reccnt = 0;		/* no entries */
		xrbufp = 0;		/* nothing in buffer */
		segments = 0;		/* nothing written */
#ifdef NO_XREF_WRITES
		fseek (ut2fd, (int32)0, 0);	/* rewind ut2 file */
#endif
		return;		/* xref cmd done */
	    case PASS2:
		xrefmode &= ~PASS1;	/* not pass 1 */
		xrefmode |= PASS2;	/* now pass 2 */
		if(xrefmode & NOXREF)	/* xref required */
		    return;		/* no xref */
		if (xrbufp) {		/* any records in buffer */
		    int32 modcnt = xrbufp % 768;
		    int32 remcnt = 768 - modcnt;
		    memset(xrbuf+xrbufp, '\0', remcnt);
		    /* sort the buffer before we write it out */
		    qsort(xrbuf, xrbufp/16, 16, mycmp);
#ifdef NO_XREF_WRITES
		    if (fwrite(xrbuf, 1, xrbufp+remcnt, ut2fd) < 0)
			xrer();		/* no return */
		    fseek (ut2fd, (int32)0, 0);	/* rewind ut2 file */
#endif
		}
		return;			/* xref cnd done */
	}
}

static char prmt[132];

/*
 * function to output cross reference information
 */

void writerep(length)
int length;
{
	int pp;
	unsigned char oldname[8];
	char xx[12];
	char *til = TCWTITL;
	char *ep;
	int i;
	unsigned char name[8];
	int value, literal;
	char flags, type;

/*
printf("*****PASS2***** %d segments %d entries, %d sectors\n",
 segments, reccnt, reccnt/768+1);
*/
	/* only handle 1 segment for now */
	if (segments > 1)	/* can't handle more than one */
	    return;
	/* data for one segment is in xrbuf */
	if (!reccnt)
	    return;		/* no data */
	/* do the heading */
	memset(TCWTITL, ' ',TCWTTLE-TCWTITL);	/* clear title buffer */
	memcpy(TCWTITL, "CROSS REFERENCE", 15);	/* set title buffer */
	pagp();			/* do page eject */
	memset(prmt, ' ', length);	/* clear print line */
	memset(oldname, '\0', 8);	/* clear old name */
	pp = 0;				/* clear print pointer */
	/* process the buffer */
	for (i = 0; i < reccnt; i++) {
	    struct tval tt;
	    int sval = 0;

	    ep = &xrbuf[i*16];
	    memcpy(name, ep, 8);	/* copy in the name */
#ifndef mpx
	    sval |= (*(ep+8) & 0xff);
	    sval |= (*(ep+9) & 0xff) << 8;
	    sval |= (*(ep+10) & 0xff) << 16;
	    sval |= (*(ep+11) & 0xff) << 24;
#else
	    memcpy((char *)&sval, ep+8, 4);
#endif
	    type = *(ep+12);
	    flags = *(ep+13);
/*	    memcpy((char *)&value, ep+12, 4); */

#ifdef DEBUG
if(type == TYPL)
printf("WRITR name [%2.2x%2.2x%2.2x%2.2x] flags %x type %x sval %x\n",
name[4], name[5], name[6], name[7],
flags, type, sval);
else if(type == TYMACDEF)
printf("WRITR name [%0.8s] flags %x type %x sval %x\n",
    xsnegate(name), flags, type, sval);
else
printf("WRITR name [%0.8s] flags %x type %x sval %x\n",
    name, flags, type, sval);
#endif /* DEBUG */

	    /* see if same name */
	    if (memCmp(name, oldname, 8) != 0) {
		memcpy(oldname, name, 8);	/* copy the name */
		if((prmt[12] & 0xff) == 0xff)	/* see if internal symbol */
		    prmt[12] = '!';	/* yes, replace 1st char */
		if(prmt[12] == ')')	/* is it common */
		    if(prmt[2] == 'D')	/* typed common? */
			prmt[2] = 'S';	/* its SSECT, change type */
		/* see if a ref to the symbol, if not delete */
		if(prmt[2] != 'L') {
		    if(pp > 8)			/* used, print */
			goto doline;
		    if(prmt[12] == ' ' && prmt[13] == ' ')
			goto doline;		/* must be 2nd line */
		    /* else ignore line */
/* printf("ignore type %d name %0.8s\n", type, name);  */
		} else 
		{
	doline:
		    /* print the line */
		    ppp(length, prmt, 0);	/* print the line */
		}
		/* clear print buffer */
		memset(prmt, ' ', length);	/* clear print line */
		pp = 0;
		/* format the location counter */
/*		tt.value = value; */
/*		tt.value = sval & 0x7fffff; */
		tt.value = sval & 0xffffff;
	        if (tt.flags & ABSREL)
		    sval &= ~0x800000;		/* reset ABS/REL flag */
		tt.flags = flags;
/*		tt.type = type; */
		tt.type = (sval & 0x0f000000) >> 24;
/*
printf("type %d ttype %d\n", type, tt.type);
*/
		type = tt.type;
		loch(&tt, 0, prmt);		/* set 5 chars */
		if(type == TYPL) { 		/* literal */
#ifndef alpha_fix
		    literal = (int)(name[4] & 0xff) << 24;
		    literal |= (int)(name[5] & 0xff) << 16;
		    literal |= (int)(name[6] & 0xff) << 8;
		    literal |= (int)(name[7] & 0xff);
#else
	    	    memcpy((char *)&literal, &name[4], 4);
#endif
		    /* store 8 hex chars */
		    sprintf(xx, "%0.8X", literal);
		    memcpy(&prmt[12], xx, 8);
		    continue;
		} else if (type < TYMACDEF) {
		    /* most everything else */
		    memcpy(&prmt[12], name, 8);	/* copy the name */
		    continue;
		} else if (type == TYPDP) {
		    /* datapool item */
/*		    if((value >> 16) & 0xff == 0xff) { */
		    if(((sval >> 16) & 0xff) == 0xff) {
			prmt[3] = '0';
			prmt[2] = 'S';	/* ssect */
		    } else {
			prmt[2] = 'A';	/* datapool */
		    }
		    memcpy(&prmt[12], name, 8);	/* copy the name */
		    continue;
		} else if(type < 20) {
		    /* copy the negated macro/form name */
		    memcpy(&prmt[12], xsnegate(name), 8);
		    continue;
		} else {
		    sprintf(xx, "%0.8X", literal);
/*
printf("fixup type %d name %0.8s\n", type, name);
*/
		    /* unknown, fix it up */
		    memcpy(&prmt[12], name, 8);	/* copy the name */
		    memset(prmt, ' ', 8);	/* blank prog cntr */
		}
	    } /* end new name */
	    /* process another reference to the same name */
	    if((pp+36) > length) {
		if((prmt[12] & 0xff) == 0xff)	/* see if internal symbol */
		    prmt[12] = '!';	/* yes, replace 1st char */
		ppp(length, prmt, 0);	/* print filled line */
		/* clear print buffer */
		memset(prmt, ' ', length);	/* clear print line */
		pp = 0;
	    }
	    sval &= ~SUORD;		/* clear flag */
	    if (!(sval & SREF)) {	/* symbol reference */
		prmt[pp + 22] = '*';	/* a definition, set * */
		sval &= ~SREF;		/* clear flag */
	    }
	    sval &= 0x7fffff;
	    /* store 5 dec chars */
/*	    sprintf(xx, "%0.5d", value); */
	    sprintf(xx, "%0.5d", sval);
	    memcpy(&prmt[pp + 23], xx, 5);
	    pp += 8;			/* next print position */
	    continue;
	}
	/* we is done */
	ppp(length, prmt, 0);	/* print last line */
	return;
}
