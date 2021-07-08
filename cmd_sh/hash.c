/*~!hash.c*/
/* Name:  hash.c Part No.: _______-____r
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

#ident	"$Id: hash.c,v 1.2 2021/07/07 23:09:52 jbev Exp $"

/*	$Log $
 */

#include	"hash.h"
#include	"defs.h"

extern int cf();

#define STRCMP(A, B)	(cf(A, B) != 0)
#define FACTOR 		035761254233	/* Magic multiplication factor */
#define TABLENGTH	64		/* must be multiple of 2 */
#define LOG2LEN		6		/* log2 of TABLENGTH */

/*
    NOTE: The following algorithm only works on machines where
    the results of multiplying two integers is the least
    significant part of the double word integer required to hold
    the result.  It is adapted from Knuth, Volume 3, section 6.4.
*/

#define hash(str) (((unsigned)(crunch(str) * FACTOR)) >> shift)

struct node {
    ENTRY item;
    struct node *next;
};

static struct node **last;
static struct node *next;
static struct node **table;

static unsigned int bitsper;		/* Bits per byte */
static unsigned int shift;

static unsigned int crunch();

void hcreate()
{
    unsigned char c = ~0;			/* A byte full of 1's */
    int j;

    table = (struct node **)alloc(TABLENGTH * sizeof(struct node *));

    for (j = 0; j < TABLENGTH; ++j) {
    	table[j] = 0;
    }

    bitsper = 0;

    while (c) {
    	c >>= 1;
    	bitsper++;
    }

    shift = (bitsper * sizeof(int)) - LOG2LEN;
}


void hscan(uscan)
void	(*uscan)();
{
    struct node *p, *nxt;
    int j;

    for (j = 0; j < TABLENGTH; ++j) {
    	p = table[j];
    	while (p) {
    	    nxt = p->next;
    	    (*uscan)(&p->item);
    	    p = nxt;
    	}
    }
}



ENTRY *hfind(str)
char *str;
{
    struct node *p;
    struct node **q;
    unsigned int i;
    int res;

#ifdef smpx
    /* this is my fix, comp wants to do sra instead of srl?? */
    i = crunch(str) * FACTOR;
    i >>= shift;
#else
    i = hash(str);
#endif
#if gould_comp_bug
    i &= ~(0x80000000 >> (shift - 1));	/* work around compiler bug */
#endif

    if (table[i] == 0) {
    	last = &table[i];
    	next = 0;
    	return(0);
    } else	 {
    	q = &table[i];
    	p = table[i];
    	while (p != 0 && (res = STRCMP(str, p->item.key))) {
    	    q = &(p->next);
    	    p = p->next;
    	}

    	if (p != 0 && res == 0)
    	    return(&(p->item));
    	else
    	 {
    	    last = q;
    	    next = p;
    	    return(0);
    	}
    }
}


ENTRY *henter(item)
ENTRY item;
{
    struct node *p = (struct node *)alloc(sizeof(struct node ));

    p->item = item;
    *last = p;
    p->next = next;
    return(&(p->item));
}


static unsigned int crunch(key)
char *key;
{
    unsigned int sum = 0;
    int s;

    for (s = 0; *key; s++)	/* Simply add up the bytes */
    	sum += *key++;

    return(sum + s);
}

