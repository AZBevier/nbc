/*~!hashsv.c*/
/* Name:  hashsv.c Part No.: _______-____r
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

#ident	"$Id: hashsv.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*
 * $Log $
 */

#include	"hash.h"
#include	"defs.h"
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<errno.h>
#ifndef mpx
#include <unistd.h>
#endif

#define		EXECUTE		01

int chk_access();
void pr_path();
void prf();
static int argpath();
void set_dotpath();
void hash_func();
int findpath();
void what_is_path();
void func_unhash();

extern char **msetenv();
extern void prs_buff();
extern void prc_buff();
extern void prn_buff();
extern int any();
extern int cf();
extern void exitsh();
extern void hscan();
extern int cf();
extern int syslook();

static char cost;
static int dotpath;
static int multrel;
static struct entry *relcmd = 0;

short pathlook(com, flg, arg)
char *com;
int flg;
register struct argnod *arg;
{
    register char *name = com;
    register ENTRY	*h;

    ENTRY		hentry;
    int count = 0;
    int i;
    int pathset = 0;
    int oldpath = 0;
    struct namnod *n;


    hentry.data = 0;

    if (any('/', name))
    	return(COMMAND);

    h = hfind(name);

    if (h) {
    	if (h->data & (BUILTIN | FUNCTION)) {
    	    if (flg)
    	    	h->hits++;
    	    return(h->data);
    	}

    	if (arg && (pathset = argpath(arg)))
    	    return(PATH_COMMAND);

    	if ((h->data & DOT_COMMAND) == DOT_COMMAND) {
    	    if (multrel == 0 && hashdata(h->data) > dotpath)
    	    	oldpath = hashdata(h->data);
    	    else
    	    	oldpath = dotpath;

    	    h->data = 0;
    	    goto pathsrch;
    	}

    	if (h->data & (COMMAND | REL_COMMAND)) {
    	    if (flg)
    	    	h->hits++;
    	    return(h->data);
    	}

    	h->data = 0;
    	h->cost = 0;
    }

    if (i = syslook(name, commands, no_commands)) {
    	hentry.data = (BUILTIN | i);
    	count = 1;
    } else
     {
    	if (arg && (pathset = argpath(arg)))
    	    return(PATH_COMMAND);
pathsrch:
    	count = findpath(name, oldpath);
    }

    if (count > 0) {
    	if (h == 0) {
    	    hentry.cost = 0;
    	    hentry.key = make(name);
    	    h = henter(hentry);
    	}

    	if (h->data == 0) {
    	    if (count < dotpath)
    	    	h->data = COMMAND | count;
    	    else
    	     {
    	    	h->data = REL_COMMAND | count;
    	    	h->next = relcmd;
    	    	relcmd = h;
    	    }
    	}


    	h->hits = flg;
    	h->cost += cost;
    	return(h->data);
    } else	 {
    	return(-count);
    }
}


static void zapentry(h)
ENTRY *h;
{
    h->data &= HASHZAP;
}


void zaphash()
{
    hscan(zapentry);
    relcmd = 0;
}


void zapcd()
{
    while (relcmd) {
    	relcmd->data |= CDMARK;
    	relcmd = relcmd->next;
    }
}


static void hashout(h)
ENTRY *h;
{
    sigchk();

    if (hashtype(h->data) == NOTFOUND)
    	return;

    if (h->data & (BUILTIN | FUNCTION))
    	return;

    prn_buff(h->hits);

    if (h->data & REL_COMMAND)
    	prc_buff('*');


    prc_buff(TAB);
    prn_buff(h->cost);
    prc_buff(TAB);

    pr_path(h->key, hashdata(h->data));
    prc_buff(NL);
}


void hashpr()
{
    prs_buff(hashhdr);
    hscan(hashout);
}


void set_dotpath()
{
    register char *path;
    register int cnt = 1;

    dotpath = 10000;
    path = getpath(nullstr);

    while (path && *path) {
    	if (*path == '/')
    	    cnt++;
    	else
    	 {
    	    if (dotpath == 10000)
    	    	dotpath = cnt;
    	    else
    	     {
    	    	multrel = 1;
    	    	return;
    	    }
    	}

    	path = nextpath(path);
    }

    multrel = 0;
}


void hash_func(name)
char *name;
{
    ENTRY	 * h;
    ENTRY	hentry;

    h = hfind(name);

    if (h) {

    	if (h->data & (BUILTIN | FUNCTION))
    	    return;
    	else
    	    h->data = FUNCTION;
    } else
     {
    	int i;

    	if (i = syslook(name, commands, no_commands))
    	    hentry.data = (BUILTIN | i);
    	else
    	    hentry.data = FUNCTION;

    	hentry.key = make(name);
    	hentry.cost = 0;
    	hentry.hits = 0;

    	henter(hentry);
    }
}


void func_unhash(name)
char *name;
{
    ENTRY 	 * h;

    h = hfind(name);

    if (h && (h->data & FUNCTION))
    	h->data = NOTFOUND;
}


short hash_cmd(name)
char *name;
{
    ENTRY	 * h;

    if (any('/', name))
    	return(COMMAND);

    h = hfind(name);

    if (h) {
    	if (h->data & (BUILTIN | FUNCTION))
    	    return(h->data);
    	else
    	    zapentry(h);
    }

    return(pathlook(name, 0, 0));
}


void what_is_path(name)
register char *name;
{
    register ENTRY	*h;
    int cnt;
    short hashval;

    h = hfind(name);

    prs_buff(name);
    if (h) {
    	hashval = hashdata(h->data);

    	switch (hashtype(h->data)) {
    	case BUILTIN:
    	    prs_buff(isbuiltin);
    	    return;

    	case FUNCTION:
    	     {
    	    	struct namnod *n = lookup(name);

    	    	prs_buff(isfunct);
    	    	prs_buff(name);
    	    	prs_buff(sfuncstr);
    	    	prf(n->namenv);
    	    	prs_buff(efnlstr);
    	    	return;
    	    }

    	case REL_COMMAND:
    	     {
    	    	short hash;

    	    	if ((h->data & DOT_COMMAND) == DOT_COMMAND) {
    	    	    hash = pathlook(name, 0, 0);
    	    	    if (hashtype(hash) == NOTFOUND) {
    	    	    	prs_buff(nfstr);
    	    	    	return;
    	    	    } else
    	    	    	hashval = hashdata(hash);
    	    	}
    	    }

    	case COMMAND:
    	    prs_buff(ishashed);
    	    pr_path(name, hashval);
    	    prs_buff(rpnlstr);
    	    return;
    	}
    }

    if (syslook(name, commands, no_commands)) {
    	prs_buff(isbuiltin);
    	return;
    }

    if ((cnt = findpath(name, 0)) > 0) {
    	prs_buff(isstr);
    	pr_path(name, cnt);
    	prc_buff(NL);
    } else
    	prs_buff(nfstr);
}


int findpath(name, oldpath)
register char *name;
int oldpath;
{
    register char *path;
    register int count = 1;

    char *p;
    int ok = 1;
    int e_code = 1;

    cost = 0;
    path = getpath(name);

    if (oldpath) {
    	count = dotpath;
    	while (--count)
    	    path = nextpath(path);

    	if (oldpath > dotpath) {
    	    catpath(path, name);
    	    p = curstak();
    	    cost = 1;

    	    if ((ok = chk_access(p)) == 0)
    	    	return(dotpath);
    	    else
    	    	return(oldpath);
    	} else
    	    count = dotpath;
    }

    while (path) {
    	path = catpath(path, name);
    	cost++;
    	p = curstak();

    	if ((ok = chk_access(p)) == 0)
    	    break;
    	else
    	    e_code = max(e_code, ok);

    	count++;
    }

    return(ok ? -e_code : count);
}


int chk_access(name)
register char *name;
{

    if (access(name, EXECUTE) == 0)
    	return(0);

    return(errno == EACCES ? 3 : 1);
}


void pr_path(name, count)
register char *name;
int count;
{
    register char *path;

    path = getpath(name);

    while (--count && path)
    	path = nextpath(path, name);

    catpath(path, name);
    prs_buff(curstak());
}


static int argpath(arg)
register struct argnod *arg;
{
    register char *s;
    register char *start;

    while (arg) {
    	s = arg->argval;
    	start = s;

    	if (letter(*s)) {
    	    while (alphanum(*s))
    	    	s++;

    	    if (*s == '=') {
    	    	*s = 0;

    	    	if (eq(start, pathname)) {
    	    	    *s = '=';
    	    	    return(1);
    	    	} else
    	    	    *s = '=';
    	    }
    	}
    	arg = arg->argnxt;
    }

    return(0);
}


