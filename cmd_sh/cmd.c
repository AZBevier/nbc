/*~!cmd.c*/
/* Name:  cmd.c Part No.: _______-____r
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

#ident	"$Id: cmd.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

#include	"defs.h"
#include	"sym.h"

extern void exitsh();
extern void chkpr();
extern void prp();
extern void prn();
extern void prc();
extern void prs();
extern void prs_cntl();

extern int word();
extern int length();

extern char skipc();
extern char nextc();

extern short pathlook();

static struct trenod *makelist();
static struct regnod *syncase();
static struct trenod *item();
static struct trenod *term();
static struct trenod *list();
static struct ionod *inout();

static int skipnl();
static int synbad();
static int prsym();
static int chksym();
static int chkword();


/* ======== storage allocation for functions ======== */

char *getstor(asize)
int asize;
{
#ifdef NOTNOW
printf("cmd:getstor entry asize=%x, fndef=%x\n", asize, fndef);
#endif
    if (fndef)
    	return(alloc(asize));
    else
    	return(getstak(asize));
}


/* ========	command line decoding	========*/

struct trenod *makefork(flgs, i)
int flgs;
struct trenod *i;
{
    register struct forknod *t;

#ifdef NOTNOW
printf("cmd:makefork entry flgs=%x\n", flgs);
#endif
    t = (struct forknod *)getstor(sizeof(struct forknod ));
    t->forktyp = flgs | TFORK;
    t->forktre = i;
    t->forkio = 0;
    return((struct trenod *)t);
}

static struct trenod *makelist(type, i, r)
int type;
struct trenod *i, *r;
{
    register struct lstnod *t;

#ifdef NOTNOW
printf("cmd:makelist entry type=%x\n", type);
#endif
    if (i == 0 || r == 0)
    	synbad();
    else
     {
    	t = (struct lstnod *)getstor(sizeof(struct lstnod ));
    	t->lsttyp = type;
    	t->lstlef = i;
    	t->lstrit = r;
    }
#ifdef NOTNOW
printf("cmd:makelist exit t=%x\n", t);
#endif
    return((struct trenod *)t);
}

/*
 * cmd
 *	empty
 *	list
 *	list & [ cmd ]
 *	list [ ; cmd ]
 */
struct trenod *cmd(sym, flg)
register int sym;
int flg;
{
    register struct trenod *i, *e;

#ifdef NOTNOW
printf("cmd: entry, before list, sym=%x, flg=%x\n", sym, flg);
#endif
    i = list(flg);
#ifdef NOTNOW
printf("cmd: after list, wdval = %x\n", wdval);
#endif
    if (wdval == NL) {
    	if (flg & NLFLG) {
    	    wdval = ';';
#ifdef NOTNOW
printf("cmd: before chkpr\n");
#endif
    	    chkpr();
#ifdef NOTNOW
printf("cmd: after chkpr\n");
#endif
    	}
    } else if (i == 0 && (flg & MTFLG) == 0)
    	synbad();

#ifdef NOTNOW
printf("cmd: before switch wdval = %x\n", wdval);
#endif
    switch (wdval) {
    case '&':
    	if (i)
    	    i = makefork(FINT | FPRS | FAMP, i);
    	else
    	    synbad();

    case ';':
#ifdef NOTNOW
printf("cmd: switch val ';', before cmd call\n");
#endif
    	if (e = cmd(sym, flg | MTFLG))
    	    i = makelist(TLST, i, e);
    	else if (i == 0)
    	    synbad();
#ifdef NOTNOW
printf("cmd: switch val ';', after cmd call\n");
#endif
    	break;

    case EOFSYM:
    	if (sym == NL)
    	    break;

    default:
#ifdef NOTNOW
printf("cmd: switch val default, after cmd call\n");
#endif
    	if (sym)
    	    chksym(sym);
    }
#ifdef NOTNOW
printf("cmd: returning\n");
#endif
    return(i);
}


/*
 * list
 *	term
 *	list && term
 *	list || term
 */
static struct trenod *list(flg)
int flg;
{
    register struct trenod *r;
    register int b;

#ifdef NOTNOW
printf("cmd:list flg=%x\n", flg);
#endif
    r = term(flg);
#ifdef NOTNOW
printf("cmd:list term return r=%x\n", r);
#endif
    while (r && ((b = (wdval == ANDFSYM)) || wdval == ORFSYM))
    	r = makelist((b ? TAND : TORF), r, term(NLFLG));
#ifdef NOTNOW
printf("cmd:list return r=%x\n", r);
#endif
    return(r);
}


/*
 * term
 *	item
 *	item |^ term
 */
static struct trenod *term(flg)
int flg;
{
    register struct trenod *t;

#ifdef NOTNOW
printf("cmd:term entry flg=%x\n", flg);
#endif
    reserv++;
    if (flg & NLFLG)
    	skipnl();
    else
    	word();
#ifdef NOTNOW
printf("cmd:term before item call flg=%x\n", flg);
#endif
    if ((t = item(TRUE)) && (wdval == '^' || wdval == '|')) {
    	struct trenod *left;
    	struct trenod *right;

#ifdef NOTNOW
printf("cmd:term after item call t=%x\n", t);
#endif
    	left = makefork(FPOU, t);
#ifdef NOTNOW
printf("cmd:term after makefork call left=%x\n", left);
#endif
    	right = makefork(FPIN | FPCL, term(NLFLG));
#ifdef NOTNOW
printf("cmd:term after makefork call right=%x\n", right);
printf("cmd:term returns makefork\n");
#endif
    	return(makefork(0, makelist(TFIL, left, right)));
    } else {
#ifdef NOTNOW
printf("cmd:term return t=%x\n", t);
#endif
    	return(t);
    }
}


static struct regnod *syncase(esym)
register int esym;
{
    skipnl();
    if (wdval == esym)
    	return(0);
    else
     {
    	register struct regnod *r = (struct regnod *)getstor(sizeof(struct regnod ));
    	register struct argnod *argp;

    	r->regptr = 0;
    	for (; ; ) {
    	    if (fndef) {
    	    	argp = wdarg;
    	    	wdarg = (struct argnod *)alloc(length(argp->argval) + BYTESPERWORD);
    	    	movstr(argp->argval, wdarg->argval);
    	    }

    	    wdarg->argnxt = r->regptr;
    	    r->regptr = wdarg;
    	    if (wdval || (word() != ')' && wdval != '|'))
    	    	synbad();
    	    if (wdval == '|')
    	    	word();
    	    else
    	    	break;
    	}
    	r->regcom = cmd(0, NLFLG | MTFLG);
    	if (wdval == ECSYM)
    	    r->regnxt = syncase(esym);
    	else
    	 {
    	    chksym(esym);
    	    r->regnxt = 0;
    	}
    	return(r);
    }
}


/*
 * item
 *
 *	( cmd ) [ < in  ] [ > out ]
 *	word word* [ < in ] [ > out ]
 *	if ... then ... else ... fi
 *	for ... while ... do ... done
 *	case ... in ... esac
 *	begin ... end
 */
static struct trenod *item(flag)
BOOL	flag;
{
    register struct trenod *r;
    register struct ionod *io;

#ifdef NOTNOW
printf("cmd:item entry flag=%x\n", flag);
#endif
    if (flag)
    	io = inout((struct ionod *)0);
    else
    	io = 0;
#ifdef NOTNOW
printf("cmd:item before switch io=%x, wdval = %x\n", io, wdval);
#endif
    switch (wdval) {
    case CASYM:
    	 {
    	    register struct swnod *t;

    	    t = (struct swnod *)getstor(sizeof(struct swnod ));
#ifdef NOTNOW
printf("cmd:item sw CASYM getstor ret t=%x\n", t);
#endif
    	    r = (struct trenod *)t;

    	    chkword();
    	    if (fndef)
    	    	t->swarg = make(wdarg->argval);
    	    else
    	    	t->swarg = wdarg->argval;
    	    skipnl();
    	    chksym(INSYM | BRSYM);
    	    t->swlst = syncase(wdval == INSYM ? ESSYM : KTSYM);
    	    t->swtyp = TSW;
    	    break;
    	}

    case IFSYM:
    	 {
    	    register int w;
    	    register struct ifnod *t;

    	    t = (struct ifnod *)getstor(sizeof(struct ifnod ));
#ifdef NOTNOW
printf("cmd:item sw IFSYM getstor ret t=%x\n", t);
#endif
    	    r = (struct trenod *)t;

    	    t->iftyp = TIF;
    	    t->iftre = cmd(THSYM, NLFLG);
    	    t->thtre = cmd(ELSYM | FISYM | EFSYM, NLFLG);
    	    t->eltre = ((w = wdval) == ELSYM ? cmd(FISYM, NLFLG) : (w == EFSYM ?
    	      (wdval = IFSYM, item(0)) : 0));
    	    if (w == EFSYM)
    	    	return(r);
    	    break;
    	}

    case FORSYM:
    	 {
    	    register struct fornod *t;

    	    t = (struct fornod *)getstor(sizeof(struct fornod ));
#ifdef NOTNOW
printf("cmd:item sw FORSYM getstor ret t=%x\n", t);
#endif
    	    r = (struct trenod *)t;

    	    t->fortyp = TFOR;
    	    t->forlst = 0;
#ifdef NOTNOW
printf("cmd:item sw1 FORSYM getstor ret t=%x\n", t);
#endif
    	    chkword();
#ifdef NOTNOW
printf("cmd:item sw2 FORSYM chkword ret t=%x\n", t);
#endif
    	    if (fndef)
    	    	t->fornam = make(wdarg->argval);
    	    else
    	    	t->fornam = wdarg->argval;
#ifdef NOTNOW
printf("cmd:item sw3 FORSYM make ret t->fornam=%x\n", t->fornam);
#endif
    	    if (skipnl() == INSYM) {
    	    	chkword();

    	    	nohash++;
    	    	t->forlst = (struct comnod *)item(0);
#ifdef NOTNOW
printf("cmd:item sw3a FORSYM item ret t->forlst=%x, wdval = %x\n", t->forlst, wdval);
#endif
    	    	nohash--;

    	    	if (wdval != NL && wdval != ';')
    	    	    synbad();
    	    	if (wdval == NL)
    	    	    chkpr();
    	    	skipnl();
    	    }
#ifdef NOTNOW
printf("cmd:item sw4 FORSYM before chksym call t=%x\n", t);
#endif
    	    chksym(DOSYM | BRSYM);
    	    t->fortre = cmd(wdval == DOSYM ? ODSYM : KTSYM, NLFLG);
    	    break;
    	}

    case WHSYM:
    case UNSYM:
    	 {
    	    register struct whnod *t;

    	    t = (struct whnod *)getstor(sizeof(struct whnod ));
#ifdef NOTNOW
printf("cmd:item sw WHSYM/UNSYM getstor ret t=%x\n", t);
#endif
    	    r = (struct trenod *)t;

    	    t->whtyp = (wdval == WHSYM ? TWH : TUN);
    	    t->whtre = cmd(DOSYM, NLFLG);
    	    t->dotre = cmd(ODSYM, NLFLG);
    	    break;
    	}

    case BRSYM:
    	r = cmd(KTSYM, NLFLG);
#ifdef NOTNOW
printf("cmd:item sw BRSYM cmd ret r=%x\n", r);
#endif
    	break;

    case '(':
    	 {
    	    register struct parnod *p;

    	    p = (struct parnod *)getstor(sizeof(struct parnod ));
#ifdef NOTNOW
printf("cmd:item sw '(' getstor ret p=%x\n", p);
#endif
    	    p->partre = cmd(')', NLFLG);
    	    p->partyp = TPAR;
    	    r = makefork(0, p);
    	    break;
    	}

    default:
    	if (io == 0)
    	    return(0);

    case 0:
    	 {
    	    register struct comnod *t;
    	    register struct argnod *argp;
    	    register struct argnod **argtail;
    	    register struct argnod **argset = 0;
    	    int keywd = 1;
    	    char *com;

    	    if ((wdval != NL) && ((peekn = skipc()) == '(')) {
    	    	struct fndnod *f;
    	    	struct ionod *saveio;

    	    	saveio = iotemp;
    	    	peekn = 0;
    	    	if (skipc() != ')')
    	    	    synbad();

    	    	f = (struct fndnod *)getstor(sizeof(struct fndnod ));
#ifdef NOTNOW
printf("cmd:item sw1 '0' getstor ret f=%x\n", f);
#endif
    	    	r = (struct trenod *)f;

    	    	f->fndtyp = TFND;
    	    	if (fndef)
    	    	    f->fndnam = make(wdarg->argval);
    	    	else
    	    	    f->fndnam = wdarg->argval;
    	    	reserv++;
    	    	fndef++;
    	    	skipnl();
    	    	f->fndval = (struct trenod *)item(0);
    	    	fndef--;

    	    	if (iotemp != saveio) {
    	    	    struct ionod *ioptr = iotemp;

    	    	    while (ioptr->iolst != saveio)
    	    	    	ioptr = ioptr->iolst;

    	    	    ioptr->iolst = fiotemp;
    	    	    fiotemp = iotemp;
    	    	    iotemp = saveio;
    	    	}
    	    	return(r);
    	    } else
    	     {
    	    	t = (struct comnod *)getstor(sizeof(struct comnod ));
#ifdef NOTNOW
printf("cmd:item sw2 '0' getstor ret t=%x\n", t);
#endif
    	    	r = (struct trenod *)t;

    	    	t->comio = io; /*initial io chain*/
    	    	argtail = &(t->comarg);

    	    	while (wdval == 0) {
    	    	    if (fndef) {
    	    	    	argp = wdarg;
    	    	    	wdarg = (struct argnod *)alloc(length(argp->argval) + BYTESPERWORD);
    	    	    	movstr(argp->argval, wdarg->argval);
    	    	    }

    	    	    argp = wdarg;
    	    	    if (wdset && keywd) {
    	    	    	argp->argnxt = (struct argnod *)argset;
    	    	    	argset = (struct argnod **)argp;
    	    	    } else
    	    	     {
    	    	    	*argtail = argp;
    	    	    	argtail = &(argp->argnxt);
    	    	    	keywd = flags & keyflg;
    	    	    }
    	    	    word();
    	    	    if (flag)
    	    	    	t->comio = inout(t->comio);
    	    	}

    	    	t->comtyp = TCOM;
    	    	t->comset = (struct argnod *)argset;
    	    	*argtail = 0;

    	    	if (nohash == 0 && (fndef == 0 || (flags & hashflg))) {
    	    	    if (t->comarg) {
    	    	    	com = t->comarg->argval;
    	    	    	if (*com && *com != DOLLAR)
    	    	    	    pathlook(com, 0, t->comset);
    	    	    }
    	    	}

#ifdef NOTNOW
printf("cmd:item sw2 '0' returns r=%x\n", r);
#endif
    	    	return(r);
    	    }
    	}

    }
    reserv++;
    word();
    if (io = inout(io)) {
    	r = makefork(0, r);
    	r->treio = io;
    }
#ifdef NOTNOW
printf("cmd:item return r=%x\n", r);
#endif
    return(r);
}


static int skipnl()
{
    while ((reserv++, word() == NL))
    	chkpr();
    return(wdval);
}


static struct ionod * inout(lastio)
struct ionod *lastio;
{
    register int iof;
    register struct ionod *iop;
#ifdef mpx
    char c;
#else
    register char c;
#endif

#ifdef NOTNOW
printf("cmd:inout entry lastio=%x\n", lastio);
#endif
    iof = wdnum;
    switch (wdval) {
    case DOCSYM:	/*	<<	*/
    	iof |= IODOC;
    	break;

    case APPSYM:	/*	>>	*/
    case '>':
    	if (wdnum == 0)
    	    iof |= 1;
    	iof |= IOPUT;
    	if (wdval == APPSYM) {
    	    iof |= IOAPP;
    	    break;
    	}

    case '<':
    	if ((c = nextc(0)) == '&')
    	    iof |= IOMOV;
    	else if (c == '>')
    	    iof |= IORDW;
    	else
    	    peekc = c | MARK;
    	break;

    default:
    	return(lastio);
    }

    chkword();
#ifdef NOTNOW
printf("cmd:inout getstor call\n");
#endif
    iop = (struct ionod *)getstor(sizeof(struct ionod ));
#ifdef NOTNOW
printf("cmd:inout getstor returned iop=%x\n", iop);
#endif

    if (fndef)
    	iop->ioname = make(wdarg->argval);
    else
    	iop->ioname = wdarg->argval;

    iop->iolink = 0;
    iop->iofile = iof;
    if (iof & IODOC) {
    	iop->iolst = iopend;
    	iopend = iop;
    }
    word();
    iop->ionxt = inout(lastio);
#ifdef NOTNOW
printf("cmd:inout returned iop=%x\n", iop);
#endif
    return(iop);
}


static int chkword()
{
#ifdef NOTNOW
printf("chkword: entry, calling word\n");
#endif
    if (word())
    	synbad();
#ifdef NOTNOW
printf("chkword: return from word\n");
#endif
}


static int chksym(sym)
int sym;
{
    register int x = sym &wdval;

    if (((x & SYMFLG) ? x : sym) != wdval)
    	synbad();
}


static int prsym(sym)
int sym;
{
    if (sym & SYMFLG) {
    	register struct sysnod *sp = reserved;

    	while (sp->sysval && sp->sysval != sym)
    	    sp++;
    	prs(sp->sysnam);
    } else if (sym == EOFSYM)
    	prs(endoffile);
    else
     {
    	if (sym & SYMREP)
    	    prc(sym);
    	if (sym == NL)
    	    prs(neworsemi);	/* DAG -- made string sharable */
    	else
    	    prc(sym);
    }
}


static int synbad()
{
    prp();
    prs(synmsg);
    if ((flags & ttyflg) == 0) {
    	prs(atline);
    	prn(standin->flin);
    }
    prs(colon);
    prc(LQ);
    if (wdval)
    	prsym(wdval);
    else
    	prs_cntl(wdarg->argval);
    prc(RQ);
    prs(unexpected);
    newline();
    exitsh(SYNBAD);
}

