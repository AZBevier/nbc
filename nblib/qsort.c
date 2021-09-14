/*~!qsort.c*/
/* Name:  qsort.c Part No.: _______-____r
 *
 * Copyright 1992 - J B Systems, Morrison, CO
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

#ident	"@(#)nbclib:qsort.c	1.1"

#ifdef gould       /* number is determined experimentally on gould */
#define MINCPY	24 /* minimum number of characters worth using memcpy for */
#else              /* number is determined experimentally on 3b20s */
#define MINCPY	8  /* minimum number of characters worth using memcpy for */
#endif

#define NULL	0
#define CPY(i, j) ((void) memcpy(i, j, n))
extern char *malloc(), *realloc(), *memcpy();
static char *qsbuf = NULL;

static 	qses, (*qscmp)();

void
qsort(a, n, es, fc)
char	*a;
unsigned n, es;
int	(*fc)();
{
	void qs1();

	{
		static unsigned qsbufsize;

		if (es >= MINCPY)
			if (qsbuf == NULL)
				qsbuf = malloc(qsbufsize = es);
			else if (qsbufsize < es)
				qsbuf = realloc(qsbuf, qsbufsize = es);
	}
	qscmp = fc;
	qses = es;
	qs1(a, a+n*es);
}

static void
qs1(a, l)
char	*a, *l;
{
	register char *i, *j;
	register int es;
	char	*lp, *hp;
	int	c;
	void	qsexc(), qstexc();
	unsigned n;

	es = qses;
start:
	if((n=l-a) <= es)
		return;
	n = es * (n / (2*es));
	hp = lp = a+n;
	i = a;
	j = l-es;
	while(1) {
		if(i < lp) {
			if((c = (*qscmp)(i, lp)) == 0) {
				qsexc(i, lp -= es);
				continue;
			}
			if(c < 0) {
				i += es;
				continue;
			}
		}

loop:
		if(j > hp) {
			if((c = (*qscmp)(hp, j)) == 0) {
				qsexc(hp += es, j);
				goto loop;
			}
			if(c > 0) {
				if(i == lp) {
					qstexc(i, hp += es, j);
					i = lp += es;
					goto loop;
				}
				qsexc(i, j);
				j -= es;
				i += es;
				continue;
			}
			j -= es;
			goto loop;
		}

		if(i == lp) {
			if(lp-a >= l-hp) {
				qs1(hp+es, l);
				l = lp;
			} else {
				qs1(a, lp);
				a = hp+es;
			}
			goto start;
		}

		qstexc(j, lp -= es, i);
		j = hp -= es;
	}
}

static void
qsexc(ri, rj)
register char *ri, *rj;
{
	register int n = qses;

	if (n >= MINCPY && qsbuf != NULL) {
		CPY(qsbuf, ri);
		CPY(ri, rj);
		CPY(rj, qsbuf);
		return;
	}
	do {
		register char c = *ri;
		*ri++ = *rj;
		*rj++ = c;
	} while(--n);
}

static void
qstexc(ri, rj, rk)
register char *ri, *rj, *rk;
{
	register int n = qses;

	if (n >= MINCPY && qsbuf != NULL) {
		CPY(qsbuf, ri);
		CPY(ri, rk);
		CPY(rk, rj);
		CPY(rj, qsbuf);
		return;
	}
	do {
		register char c = *ri;
		*ri++ = *rk;
		*rk++ = *rj;
		*rj++ = c;
	} while(--n);
}
