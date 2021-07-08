/*~!getenv.c*/
/* Name:  getenv.c Part No.: _______-____r
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

#ident	"@(#)nbclib:getenv.c	1.1"

/*
 *	getenv(name)
 *	returns ptr to value associated with name, if any, else NULL
 */
#define NULL	0

#ifdef mpx
#include <timeb.h>	/* were TZ is defined */
#endif
extern char **environ;
static char *nvmatch();

char *
getenv(name)
register char *name;
{
    register char *v, **p=environ;

    if(p == NULL)
    	return(NULL);
    while(*p != NULL)
    	if((v = nvmatch(name, *p++)) != NULL)
    	    return(v);
#ifdef mpx
    if (!strcmp(name,"TZ")) {
    	/* not there, use default */
    	return(TZ);
    }
#endif
    return(NULL);
}

/*
 *	s1 is either name, or name=value
 *	s2 is name=value
 *	if names match, return value of s2, else NULL
 *	used for environment searching: see getenv
 */

static char *
nvmatch(s1, s2)
register char *s1, *s2;
{
    while(*s1 == *s2++)
    	if(*s1++ == '=')
    	    return(s2);
    if(*s1 == '\0' && *(s2-1) == '=')
    	return(s2);
    return(NULL);
}
