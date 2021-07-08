/*~!func.c*/
/* Name:  func.c Part No.: _______-____r
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

#ident	"$Id: func.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

#include	"defs.h"

extern void free();
void freeio();
void free_arg();
void freereg();
void freetree();
void prarg();
void prn_buff();
void prc_buff();
void prs_buff();
void prio();
extern void exitsh();
extern void unlink();

void freefunc(n)
struct namnod *n;
{
    freetree((struct trenod *)(n->namenv));
}


void freetree(t)
register struct trenod *t;
{
    if (t) {
    	register int type;

    	if (t->tretyp & CNTMSK) {
    	    t->tretyp--;
    	    return;
    	}

    	type = t->tretyp & COMMSK;

    	switch (type) {
    	case TFND:
    	    free(fndptr(t)->fndnam);
    	    freetree(fndptr(t)->fndval);
    	    break;

    	case TCOM:
    	    freeio(comptr(t)->comio);
    	    free_arg(comptr(t)->comarg);
    	    free_arg(comptr(t)->comset);
    	    break;

    	case TFORK:
    	    freeio(forkptr(t)->forkio);
    	    freetree(forkptr(t)->forktre);
    	    break;

    	case TPAR:
    	    freetree(parptr(t)->partre);
    	    break;

    	case TFIL:
    	case TLST:
    	case TAND:
    	case TORF:
    	    freetree(lstptr(t)->lstlef);
    	    freetree(lstptr(t)->lstrit);
    	    break;

    	case TFOR:
    	     {
    	    	struct fornod *f = (struct fornod *)t;

    	    	free(f->fornam);
    	    	freetree(f->fortre);
    	    	if (f->forlst) {
    	    	    freeio(f->forlst->comio);
    	    	    free_arg(f->forlst->comarg);
    	    	    free_arg(f->forlst->comset);
    	    	    free(f->forlst);
    	    	}
    	    }
    	    break;

    	case TWH:
    	case TUN:
    	    freetree(whptr(t)->whtre);
    	    freetree(whptr(t)->dotre);
    	    break;

    	case TIF:
    	    freetree(ifptr(t)->iftre);
    	    freetree(ifptr(t)->thtre);
    	    freetree(ifptr(t)->eltre);
    	    break;

    	case TSW:
    	    free(swptr(t)->swarg);
    	    freereg(swptr(t)->swlst);
    	    break;
    	}
    	free(t);
    }
}


void free_arg(argp)
register struct argnod *argp;
{
    register struct argnod *sav;

    while (argp) {
    	sav = argp->argnxt;
    	free(argp);
    	argp = sav;
    }
}


void freeio(iop)
register struct ionod *iop;
{
    register struct ionod *sav;

    while (iop) {
    	if (iop->iofile & IODOC) {

#ifdef DEBUG
    	    prs("unlinking ");
    	    prs(iop->ioname);
    	    newline();
#endif

    	    unlink(iop->ioname);

    	    if (fiotemp == iop)
    	    	fiotemp = iop->iolst;
    	    else
    	     {
    	    	struct ionod *fiop = fiotemp;

    	    	while (fiop->iolst != iop)
    	    	    fiop = fiop->iolst;

    	    	fiop->iolst = iop->iolst;
    	    }
    	}
    	free(iop->ioname);
    	free(iop->iolink);
    	sav = iop->ionxt;
    	free(iop);
    	iop = sav;
    }
}


void freereg(regp)
register struct regnod *regp;
{
    register struct regnod *sav;

    while (regp) {
    	free_arg(regp->regptr);
    	freetree(regp->regcom);
    	sav = regp->regnxt;
    	free(regp);
    	regp = sav;
    }
}


void prf(t)
register struct trenod *t;
{
    sigchk();

    if (t) {
    	register int type;

    	type = t->tretyp & COMMSK;

    	switch (type) {
    	case TFND:
    	     {
    	    	register struct fndnod *f = (struct fndnod *)t;

    	    	prs_buff(f->fndnam);
    	    	prs_buff(sfuncstr);
    	    	prf(f->fndval);
    	    	prs_buff(efuncstr);
    	    	break;
    	    }

    	case TCOM:
    	     {
    	    	prarg(comptr(t)->comset);
    	    	prarg(comptr(t)->comarg);
    	    	prio(comptr(t)->comio);
    	    	break;
    	    }

    	case TFORK:
    	    prf(forkptr(t)->forktre);
    	    prio(forkptr(t)->forkio);
    	    if (forkptr(t)->forktyp & FAMP)
    	    	prs_buff(amperstr);
    	    break;

    	case TPAR:
    	    prs_buff(lparstr);
    	    prf(parptr(t)->partre);
    	    prs_buff(rparstr);
    	    break;

    	case TFIL:
    	    prf(lstptr(t)->lstlef);
    	    prs_buff(pipestr);
    	    prf(lstptr(t)->lstrit);
    	    break;

    	case TLST:
    	    prf(lstptr(t)->lstlef);
    	    prc_buff(NL);
    	    prf(lstptr(t)->lstrit);
    	    break;

    	case TAND:
    	    prf(lstptr(t)->lstlef);
    	    prs_buff(andstr);
    	    prf(lstptr(t)->lstrit);
    	    break;

    	case TORF:
    	    prf(lstptr(t)->lstlef);
    	    prs_buff(orstr);
    	    prf(lstptr(t)->lstrit);
    	    break;

    	case TFOR:
    	     {
    	    	register struct argnod *arg;
    	    	register struct fornod *f = (struct fornod *)t;

    	    	prs_buff(forstr);
    	    	prs_buff(f->fornam);

    	    	if (f->forlst) {
    	    	    arg = f->forlst->comarg;
    	    	    prs_buff(instr);

    	    	    while (arg != ENDARGS) {
    	    	    	prc_buff(SP);
    	    	    	prs_buff(arg->argval);
    	    	    	arg = arg->argnxt;
    	    	    }
    	    	}

    	    	prs_buff(dostr);
    	    	prf(f->fortre);
    	    	prs_buff(donestr);
    	    }
    	    break;

    	case TWH:
    	case TUN:
    	    if (type == TWH)
    	    	prs_buff(whilestr);
    	    else
    	    	prs_buff(untilstr);
    	    prf(whptr(t)->whtre);
    	    prs_buff(dostr);
    	    prf(whptr(t)->dotre);
    	    prs_buff(donestr);
    	    break;

    	case TIF:
    	     {
    	    	struct ifnod *f = (struct ifnod *)t;

    	    	prs_buff(ifstr);
    	    	prf(f->iftre);
    	    	prs_buff(thenstr);
    	    	prf(f->thtre);

    	    	if (f->eltre) {
    	    	    prs_buff(elsestr);
    	    	    prf(f->eltre);
    	    	}

    	    	prs_buff(fistr);
    	    	break;
    	    }

    	case TSW:
    	     {
    	    	register struct regnod *swl;

    	    	prs_buff(casestr);
    	    	prs_buff(swptr(t)->swarg);
    	    	prs_buff(instr);

    	    	swl = swptr(t)->swlst;
    	    	while (swl) {
    	    	    struct argnod *arg = swl->regptr;

    	    	    prc_buff(NL);
    	    	    if (arg) {
    	    	    	prs_buff(arg->argval);
    	    	    	arg = arg->argnxt;
    	    	    }

    	    	    while (arg) {
    	    	    	prs_buff(pipestr);
    	    	    	prs_buff(arg->argval);
    	    	    	arg = arg->argnxt;
    	    	    }

    	    	    prc_buff(')');
    	    	    prf(swl->regcom);
    	    	    prs_buff(dsemistr);
    	    	    swl = swl->regnxt;
    	    	}
    	    	prs_buff(esacstr);
    	    }
    	    break;
    	}
    }

    sigchk();
}


void prarg(argp)
register struct argnod *argp;
{
    while (argp) {
    	prs_buff(argp->argval);
    	prc_buff(SP);
    	argp = argp->argnxt;
    }
}


void prio(iop)
register struct ionod *iop;
{
    register int iof;
    register char *ion;

    while (iop) {
    	iof = iop->iofile;
    	ion = iop->ioname;

    	if (ion && *ion) {
    	    prn_buff(iof & IOUFD);

    	    if (iof & IODOC)
    	    	prs_buff(fromstr);
    	    else if (iof & IOMOV) {
    	    	if (iof & IOPUT)
    	    	    prs_buff(toastr);
    	    	else
    	    	    prs_buff(fromastr);

    	    } else if (iof & IORDW)
    	    	prs_buff(rdwstr);
    	    else if ((iof & IOPUT) == 0)
    	    	prc_buff('<');
    	    else if (iof & IOAPP)
    	    	prs_buff(ontostr);
    	    else
    	    	prc_buff('>');

    	    prs_buff(ion);
    	    prc_buff(SP);
    	}
    	iop = iop->ionxt;
    }
}

